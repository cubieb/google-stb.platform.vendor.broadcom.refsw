/***************************************************************************
 *     Copyright (c) 2007-2011, Broadcom Corporation
 *     All Rights Reserved
 *     Confidential Property of Broadcom Corporation
 *
 *  THIS SOFTWARE MAY ONLY BE USED SUBJECT TO AN EXECUTED SOFTWARE LICENSE
 *  AGREEMENT  BETWEEN THE USER AND BROADCOM.  YOU HAVE NO RIGHT TO USE OR
 *  EXPLOIT THIS MATERIAL EXCEPT SUBJECT TO THE TERMS OF SUCH AN AGREEMENT.
 *
 * $brcm_Workfile: $
 * $brcm_Revision: $
 * $brcm_Date: $
 *
 * Module Description:
 *
 * Media player for MPEG-2 Transport 
 * 
 * Revision History:
 *
 * $brcm_Log: $
 * 
 *******************************************************************************/
#include "bstd.h"
#include "bkni.h"
#include "bmpeg2ts_parser.h"
#include "bmpeg2ts_player.h"
#include "btime_indexer.h"
#include "botf_marker.h"
#include "biobits.h"

BDBG_MODULE(bmpeg2ts_player);
#define BDBG_MSG_TRACE(x) /* BDBG_MSG(x) */

BDBG_OBJECT_ID(bmpeg2ts_player_t);

typedef enum b_mpeg2ts_player_file_mode {
    b_mpeg2ts_player_file_mode_sequential, 
    b_mpeg2ts_player_file_mode_forward,
    b_mpeg2ts_player_file_mode_backward
} b_mpeg2ts_player_file_mode;

typedef enum b_mpeg2ts_player_decoder_mode {
    b_mpeg2ts_player_decoder_mode_normal,
    b_mpeg2ts_player_decoder_mode_otf,
    b_mpeg2ts_player_decoder_mode_fragmented
} b_mpeg2ts_player_decoder_mode;

typedef enum b_file_feed_mode {
    b_file_feed_mode_sequential, 
    b_file_feed_mode_forward,
    b_file_feed_mode_backward
} b_file_feed_mode;

typedef enum b_file_feed_state {
    b_file_feed_state_header,
    /* b_file_feed_state_tail, */
    b_file_feed_state_eof_tail, /* after reading last byte of data we need to prepend trailer */
    b_file_feed_state_data
} b_file_feed_state;

struct b_mpeg2ts_feed_config {
    b_file_feed_mode mode; /* mode of operation */
    size_t chunk; /* size of contignous data chunk */
    size_t stride; /* distance between chunks */
};

struct bmpeg2ts_player {
       bmpeg2ts_parser_pid pcr_pid; /* must be first */
       BDBG_OBJECT(bmpeg2ts_player_t)
       struct b_mpeg2ts_feed_config feed_config;
       bmedia_player_status status;
       off_t read_offset;
       off_t feed_stop_offset; /* current location of end of the feed block, reset when advanced to new feed */
       off_t feed_start_offset; /* current location of end of the feed block, reset when advanced to new feed */ 
       size_t async_read_size; /* size of the last async read */
       unsigned feed_count;
       b_mpeg2ts_player_decoder_mode decoder_mode;
       b_file_feed_state feed_state;
       bmpeg2ts_parser_t parser;
       batom_pipe_t ts_pipe;
       btime_indexer_t index;
       bmedia_time_scale time_scale;
       bmedia_player_pos  pcr_position;
       bfile_io_read_t fd;
       unsigned nindexentries;
       uint32_t last_pts;
       bool last_pts_valid;
       bool index_error;
       bmedia_player_config config;
       bmedia_player_stream stream;
       uint8_t packet_buf[(BMPEG2TS_PKT_LEN+4)*5];
       bool pcr_pid_found;
       unsigned pcr_pid_index;
       unsigned timestamp_offset;
};


static bmpeg2ts_parser_action 
b_mpeg2ts_player_pcr_payload(bmpeg2ts_parser_pid *pid, unsigned flags, batom_accum_t src, batom_cursor *cursor, size_t len);

#define B_MPEG2TS_PLAYER_MIN_BLOCK ((BMPEG2TS_PKT_LEN/4)*BIO_BLOCK_SIZE)
#define B_MPEG2TS_PLAYER_READ_SIZE (BIO_BLOCK_SIZE*15)

#define B_MPEG2TS_PLAYER_ADVANCE_BRACKETS  (2*BMEDIA_PLAYER_POS_SCALE)

static int
b_mpeg2ts_player_advance(bmpeg2ts_player_t player, bmedia_player_pos destination)
{
	batom_pipe_t ts_pipe;
	int rc=0;
	bmedia_player_pos destination_min, destination_max;
	bmedia_player_pos step;
    bmedia_player_pos step_size = BINDEX_SEEK_STEP;

    if (player->config.force_seek_step != 0) {
        step_size = player->config.force_seek_step;
    }

	ts_pipe = player->ts_pipe;
	for(step=step_size;;) {
		btime_indexer_position position;
		uint64_t offset;
		bmedia_player_pos delta;

        if(destination>=step) {
            destination_min = destination-step;
        } else {
            destination_min = 0;
        }
        destination_max = destination+step;
        if(btime_indexer_position_by_time(player->index, destination, &position)!=true) {
            BDBG_WRN(("b_mpeg2ts_player_advance:%p can't get position for %u", (void *)player, (unsigned)destination));
            rc = -1;
            break;
        }
        BDBG_MSG(("b_mpeg2ts_player_advance:%p range %u:%u %u:%u", (void *)player, (unsigned)position.prev.time, (unsigned)destination_min, (unsigned)position.next.time, (unsigned)destination_max));
        while(position.prev.time >= destination_min && position.next.time <= destination_max ) {
            BDBG_MSG(("b_mpeg2ts_player_advance:%p step %u -> %u", (void *)player, (unsigned)step, (unsigned)step/2));
            step /= 2;
            if(step<B_MPEG2TS_PLAYER_ADVANCE_BRACKETS) {
                goto done;
            }
        }
        if(position.next.time < destination ) {
            if(destination >= position.next.time + step) {
                delta = step;
            } else  if (destination > position.next.time) {
                delta = destination - position.next.time;
            } else {
                delta = 0;
        }
        btime_indexer_seek(player->index, position.next.time+delta);
        offset = position.next.offset + ((uint64_t)position.byterate * delta)/BMEDIA_PLAYER_POS_SCALE;
        BDBG_MSG(("b_mpeg2ts_player_advance:%p forward time:%u(%u) offset:" B_OFFT_FMT "(" B_OFFT_FMT ")", (void *)player, (unsigned)(position.next.time+delta), (unsigned)position.next.time, B_OFFT_ARG(offset), B_OFFT_ARG(position.next.offset)));
    } else {
        if(destination >= position.prev.time && destination <= position.next.time) {
            if(position.next.time - destination >= destination - position.prev.time) {
                delta = destination - position.prev.time;
                btime_indexer_seek(player->index, position.prev.time+delta);
                offset = position.prev.offset + ((uint64_t)position.byterate * delta)/BMEDIA_PLAYER_POS_SCALE;
                BDBG_MSG(("b_mpeg2ts_player_advance:%p search forward time:%u(%u) offset:" B_OFFT_FMT "(" B_OFFT_FMT ")", (void *)player, (unsigned)(position.prev.time+delta), (unsigned)position.prev.time, B_OFFT_ARG(offset), B_OFFT_ARG(position.prev.offset)));
            } else {
                delta = position.next.time - destination;
                if(delta<B_MPEG2TS_PLAYER_ADVANCE_BRACKETS) {
                    delta = B_MPEG2TS_PLAYER_ADVANCE_BRACKETS;
                    if(delta > position.next.time) {
                        delta = position.next.time;
                    }
                }
                btime_indexer_seek(player->index, position.next.time-delta);
                offset = position.next.offset - ((uint64_t)position.byterate * delta)/BMEDIA_PLAYER_POS_SCALE;
                BDBG_MSG(("b_mpeg2ts_player_advance:%p search reverse time:%u(%u) offset:" B_OFFT_FMT "(" B_OFFT_FMT ")", (void *)player, (unsigned)(position.next.time-delta), (unsigned)position.next.time, B_OFFT_ARG(offset), B_OFFT_ARG(position.next.offset)));
                }
            } else {
                continue;
            }
        }
        batom_pipe_flush(ts_pipe);
        bmpeg2ts_parser_seek(player->parser, offset);

        for(;;) {
            bfile_buffer_result result;
            size_t atom_len;
            unsigned nindexentries = player->nindexentries;
            size_t feed_len;
            batom_t atom = bfile_buffer_read(player->config.buffer, offset, B_MPEG2TS_PLAYER_READ_SIZE, &result);
            if(atom==NULL) {
                BDBG_MSG(("b_mpeg2ts_player_advance:%p read completed %u at %u", (void *)player, result, (unsigned)offset));
                goto done;
            }
            atom_len = batom_len(atom);
            BDBG_MSG_TRACE(("b_mpeg2ts_player_advance:%p read %u:%u -> %p", (void *)player, (unsigned)offset, atom_len, (void *)atom));
            offset += atom_len;
            batom_pipe_push(ts_pipe, atom);
            feed_len = bmpeg2ts_parser_feed(player->parser, ts_pipe);
            BDBG_MSG_TRACE(("b_mpeg2ts_player_advance:%p %u:%u time:%u", (void *)player, (unsigned)offset, atom_len, player->pcr_position));
            if(nindexentries!=player->nindexentries) {
                break;
            }
            if(feed_len!=atom_len ) {
                BDBG_WRN(("b_mpeg2ts_player_advance:%p parser didn't consume all data %u:%u", (void *)player, (unsigned)feed_len, (unsigned)atom_len));
                rc = -1;
                goto done;
            }
        }
    }
done:
    bmpeg2ts_parser_flush(player->parser);
    batom_pipe_flush(ts_pipe);
    return rc;
}

static int
b_mpeg2ts_add_other_pid(bmpeg2ts_player_t player)
{
	if(!player->pcr_pid_found){
		if(player->stream.other[player->pcr_pid_index]) {
			bmpeg2ts_parser_remove_pid(player->parser, player->pcr_pid.pid);
			bmpeg2ts_parser_pid_init(&player->pcr_pid, player->stream.other[player->pcr_pid_index]);
			bmpeg2ts_parser_add_pid(player->parser, &player->pcr_pid);
			player->pcr_pid.payload = b_mpeg2ts_player_pcr_payload;
			player->pcr_pid_index++;
			return 0;
		} else {
			return -1;
		}		
	}

	return -1;
}

static int
b_mpeg2ts_player_open_file(bmpeg2ts_player_t player)
{
    off_t off=0;
    bfile_buffer_t buf;
    bmpeg2ts_parser_t parser;
    batom_pipe_t pipe;
    size_t read_len = B_MPEG2TS_PLAYER_READ_SIZE;
    off_t first, last;
    int rc;

    BDBG_OBJECT_ASSERT(player, bmpeg2ts_player_t);
    rc = player->fd->bounds(player->fd, &first, &last);
    if(rc==0 && last>0 && last < ((off_t)read_len * 8)) {
        read_len = BIO_BLOCK_SIZE;
    }

try_again:
	parser = player->parser;
	buf = player->config.buffer;
	pipe = player->ts_pipe;
	bmpeg2ts_parser_seek(parser, off);
	batom_pipe_flush(pipe);
	
	for(;off<8*1024*1024;) { /* don't read more than  8MBytes worth of data */
		batom_t atom;
		bfile_buffer_result result;
		size_t feed_len;
		size_t atom_len;
		unsigned nindexentries = player->nindexentries;

        BDBG_MSG_TRACE(("b_mpeg2ts_player_open_file:%p reading %u:%u", (void *)player, (unsigned)off, read_len));
		atom = bfile_buffer_read(buf, off, read_len, &result);
		if(atom==NULL) {
            BDBG_MSG(("b_mpeg2ts_player_open_file:%p read completed %u at %u", (void *)player, result, (unsigned)off));
			break;
		}
		BDBG_ASSERT(atom);
		atom_len = batom_len(atom);
        BDBG_MSG_TRACE(("b_mpeg2ts_player_open_file:%p read %u:%u -> %#lx", (void *)player, (unsigned)off, atom_len, (unsigned long)atom));
		off += atom_len;
		batom_pipe_push(pipe, atom);
		feed_len = bmpeg2ts_parser_feed(parser, pipe);
		if(feed_len!=atom_len) {
			break;
		}
		if(player->index_error) {
			break;
		}
		if(nindexentries!=player->nindexentries) {
			btime_indexer_status status;
			btime_indexer_get_status(player->index, &status);
			if(status.byterate_valid) {
				break;
			}
		}
	}
	bmpeg2ts_parser_flush(player->parser);
	batom_pipe_flush(pipe);


    if(player->index_error || player->nindexentries<2) {
		if(b_mpeg2ts_add_other_pid(player)) {
			return BERR_TRACE(-1);
		}
		else {
			off=0;
			goto try_again;
		}
	} else {
		return 0;
	}
}

static bmpeg2ts_parser_action 
b_mpeg2ts_player_pcr_payload(bmpeg2ts_parser_pid *pid, unsigned flags, batom_accum_t src, batom_cursor *cursor, size_t len)
{
	bmpeg2ts_parser_action  action = bmpeg2ts_parser_action_skip;
	bmpeg2ts_player_t player = (bmpeg2ts_player_t)pid;
	BDBG_OBJECT_ASSERT(player, bmpeg2ts_player_t);

	BSTD_UNUSED(src);
	BSTD_UNUSED(cursor);
	BSTD_UNUSED(len);
	if(flags&BMPEG2TS_PCR_FLAG) {
		int rc;
		bmpeg2ts_parser_status status;

        bmpeg2ts_parser_get_status(player->parser, &status);
        BDBG_MSG_TRACE(("b_mpeg2ts_player_pcr_payload:%p PCR:%#u offset:" BDBG_UINT64_FMT "", (void *)player, (unsigned)player->pcr_pid.pcr_base, BDBG_UINT64_ARG(status.offset)));
		rc = btime_indexer_add(player->index, player->pcr_pid.pcr_base, status.offset, &player->pcr_position);
		if(rc>=0) {
			if((unsigned)rc!=player->nindexentries) {
				action = bmpeg2ts_parser_action_hold;
			}
			player->nindexentries = (unsigned)rc;
		} else {
            BDBG_WRN(("b_mpeg2ts_player_pcr_payload:%p index error:%d", (void *)player, rc));
            player->index_error = true;
		}
		player->pcr_pid_found = true;
	}
	return action;
}

static void
b_mpeg2ts_player_update_feed(bmpeg2ts_player_t player, off_t start_offset)
{
    BDBG_MSG(("b_mpeg2ts_player_update_feed:%p " B_OFFT_FMT "", (void *)player, B_OFFT_ARG(start_offset)));
    start_offset -= start_offset%(BMPEG2TS_PKT_LEN+player->timestamp_offset);
    switch(player->feed_config.mode) {
    case b_mpeg2ts_player_file_mode_sequential:
        /* fall through */
    case b_mpeg2ts_player_file_mode_forward:
        player->feed_start_offset = start_offset;
        player->feed_stop_offset = player->feed_start_offset + player->feed_config.chunk;
        break;
    case b_mpeg2ts_player_file_mode_backward:
        if(start_offset >= 0) {
            player->feed_start_offset = start_offset;
            player->feed_stop_offset = player->feed_start_offset + player->feed_config.chunk;
        } else {
            size_t chunk;
            start_offset += player->feed_config.stride;
            if(start_offset >= (off_t)player->feed_config.chunk) {
                chunk = player->feed_config.chunk;
            } else {
                chunk = start_offset;
            }
            player->feed_start_offset = 0;
            player->feed_stop_offset = chunk;
        }
        break;
    }
    player->read_offset = player->feed_start_offset;
    player->feed_state = b_file_feed_state_header;
    batom_pipe_flush(player->ts_pipe);
    bmpeg2ts_parser_seek(player->parser, player->feed_start_offset);
    return;
}

bmpeg2ts_player_t
bmpeg2ts_player_create(bfile_io_read_t fd, const bmedia_player_config *config, const bmedia_player_stream *stream)
{
	bmpeg2ts_player_t player;
	bmpeg2ts_parser_cfg parser_cfg;
    BERR_Code rc;

	BDBG_ASSERT(fd);
	BDBG_ASSERT(config);
	BDBG_ASSERT(stream && stream->format == bstream_mpeg_type_ts);
	BSTD_UNUSED(fd);

	if(!config->buffer) {
		BDBG_ERR(("bmpeg2ts_player_create: buffer has to be provided"));
		rc = BERR_TRACE(BERR_NOT_SUPPORTED);
		goto err_config;
	}
	if(!config->factory) {
		BDBG_ERR(("bmpeg2ts_player_create: atom_factory has to be provided"));
		rc = BERR_TRACE(BERR_NOT_SUPPORTED);
		goto err_config;
	}
	if(stream->stream.mpeg2ts.packet_size != 188 && stream->stream.mpeg2ts.packet_size != 192) {
		rc = BERR_TRACE(BERR_NOT_SUPPORTED);
		goto err_config;
	}
	player = BKNI_Malloc(sizeof(*player));
	if (!player) {
		BDBG_ERR(("bmpeg2ts_player_create: can't allocate %u bytes", (unsigned)sizeof(*player)));
		rc = BERR_TRACE(BERR_OUT_OF_SYSTEM_MEMORY);
		goto err_alloc;
	}
	BDBG_OBJECT_INIT(player, bmpeg2ts_player_t);

	player->config = *config;
	player->stream = *stream;
	
	bmedia_player_init_status(&player->status);
	player->status.format = bstream_mpeg_type_ts;
	player->timestamp_offset = (stream->stream.mpeg2ts.packet_size==192)?4:0;
	player->time_scale = BMEDIA_TIME_SCALE_BASE;
	player->pcr_position = 0;
	player->nindexentries = 0;
	player->index_error = false;
	player->feed_state = b_file_feed_state_header;
	player->decoder_mode = b_mpeg2ts_player_decoder_mode_normal;
	player->read_offset = 0;
	player->feed_config.mode = b_mpeg2ts_player_file_mode_sequential;
	player->feed_config.chunk = B_MPEG2TS_PLAYER_MIN_BLOCK + (player->timestamp_offset?BIO_BLOCK_SIZE:0);
	player->feed_config.stride = B_MPEG2TS_PLAYER_MIN_BLOCK + (player->timestamp_offset?BIO_BLOCK_SIZE:0);
	player->fd = fd;
	player->last_pts = 0;
	player->last_pts_valid = false;
	player->feed_count = 0;
	player->async_read_size = 0;
	player->pcr_pid_found = false;
	player->pcr_pid_index = 0;
        
	bmpeg2ts_parser_default_cfg(&parser_cfg);
	parser_cfg.header_size = player->timestamp_offset;
	player->parser = bmpeg2ts_parser_create(player->config.factory, &parser_cfg);
	if(!player->parser) {
		goto err_parser;
	}

	bmpeg2ts_parser_pid_init(&player->pcr_pid, stream->master);
	bmpeg2ts_parser_add_pid(player->parser, &player->pcr_pid);
	player->pcr_pid.payload = b_mpeg2ts_player_pcr_payload;

	player->ts_pipe = batom_pipe_create(player->config.factory);
	if(!player->ts_pipe) {
		goto err_pipe;
	}
	player->index = btime_indexer_create();
	if(!player->index) {
		goto err_index;
	}
	b_mpeg2ts_player_update_feed(player, 0);

    /*
	if(b_mpeg2ts_player_open_file(player)<0) {
		goto err_open;
	}
    */

	return player;
/* err_open: */
	/* btime_indexer_destroy(player->index); */
err_index:
	batom_pipe_destroy(player->ts_pipe);
err_pipe:
	bmpeg2ts_parser_remove_pid(player->parser, player->pcr_pid.pid);
	bmpeg2ts_parser_destroy(player->parser);
err_parser:
	BKNI_Free(player);
err_alloc:
err_config:
	return NULL;
}

void 
bmpeg2ts_player_destroy(bmpeg2ts_player_t player)
{
	BDBG_OBJECT_ASSERT(player, bmpeg2ts_player_t);
	btime_indexer_destroy(player->index);
	batom_pipe_destroy(player->ts_pipe);
	bmpeg2ts_parser_remove_pid(player->parser, player->pcr_pid.pid); 
	bmpeg2ts_parser_destroy(player->parser);
	BDBG_OBJECT_DESTROY(player, bmpeg2ts_player_t);
	BKNI_Free(player);
	return;
}

static void 
b_mpeg2ts_player_data_error(bmpeg2ts_player_t player)
{
    BSTD_UNUSED(player);
    return;
}


static int
b_mpeg2ts_player_process_data(bmpeg2ts_player_t player, batom_t atom, bmedia_player_entry *entry)
{
	batom_pipe_t pipe;
    size_t atom_len;
    size_t feed_len;

    BDBG_ASSERT(atom);

	entry->type = bmedia_player_entry_type_atom;

    pipe = player->ts_pipe;
    atom_len = batom_len(atom);
    BDBG_MSG_TRACE(("b_mpeg2ts_player_process_data:%#lx read from %lu:%u", (unsigned long)player, (unsigned long)player->read_offset, atom_len));
    entry->length = atom_len;
    entry->atom = atom;
    player->read_offset += atom_len;
    batom_pipe_push(pipe, atom);
    batom_lock(atom);
    feed_len = bmpeg2ts_parser_feed(player->parser, pipe);
    if(feed_len!=atom_len) {
        goto err_parser;
    }
    player->status.position = player->pcr_position;
	entry->timestamp = player->pcr_position;
    if(player->status.bounds.last<player->status.position) {
        player->status.bounds.last = player->status.position;
    }
    return 0;

err_parser:
    entry->type = bmedia_player_entry_type_error;
    b_mpeg2ts_player_data_error(player);
    batom_release(atom);
    batom_pipe_flush(pipe);
	BDBG_MSG(("b_mpeg2ts_player_process_data: %#lx EOF reached", (unsigned long)player));
	return -1;
}

static int
b_mpeg2ts_player_send_header_otf(bmpeg2ts_player_t player, bmedia_player_entry *entry, bool eof)
{
    BOTF_MarkerParams marker;
    BERR_Code rc;
    BKNI_Memset(&marker, 0, sizeof(marker));
    marker.Pid = player->stream.master;
    marker.ChunkCntr = eof? B_MARKER_CHUNK_EOF : player->feed_count ;
    marker.OffsetHi = (player->read_offset >> 32);
    marker.OffsetLow = player->read_offset;
    marker.TimestampOffset = player->timestamp_offset;
    rc = BOTF_BuildMarkerTS(&marker, player->packet_buf, sizeof(player->packet_buf), &entry->length);
    if(rc!=BERR_SUCCESS) {
        rc = BERR_TRACE(rc);entry->length = 2*(BMPEG2TS_PKT_LEN+player->timestamp_offset);
    }
    entry->type = bmedia_player_entry_type_embedded;
    entry->embedded = player->packet_buf;
    return 0;
}

/**
Summary:
BTP mode values
Description:
These are the supported values in word[0] of a BTP or BUD
**/
#define TT_MODE_PLAY                0x00
#define TT_MODE_DISPLAY             0x01
#define TT_MODE_BUILD_REFERENCE     0x02
#define TT_MODE_PROCESS             0x03
#define TT_MODE_DISCARD_TILL_BTP    0x04
#define TT_MODE_DISPLAY_FORWARD     0x05
#define TT_MODE_DISPLAY_REWIND      0x06
#define TT_MODE_DISPLAY_PAST_BUFFER 0x07
#define TT_MODE_PIC_OUTPUT_COUNT         0x09    /* picture output count */
#define TT_MODE_INLINE_FLUSH              0x0A        /* also known as Trick Play Discontinuity (TPD) */
#define TT_MODE_TIMING_MARKER       0x0C
#define TT_MODE_PICTURE_TAG         0x0D

typedef struct b_mpeg2ts_btp_pkt{
    uint32_t data[10]; 
} b_mpeg2ts_btp_pkt;

static void 
b_mpeg2ts_ts_make_filler(uint16_t pid, uint8_t *pkt, unsigned timestamp_offset)
{
    unsigned i;

    BKNI_Memset(pkt, 0, BMPEG2TS_PKT_LEN+timestamp_offset);
    pkt += timestamp_offset;
    pkt[0] = 0x47;
    pkt[1] = B_GET_BITS(pid, 12, 8);
    pkt[2] = B_GET_BITS(pid, 7, 0);
    pkt[3] = 0x10;
    /* create dummy startcodes */
    for(i=4;i<BMPEG2TS_PKT_LEN;i+=8) {
        pkt[i] =   0x00;
        pkt[i+1] = 0x00;
        pkt[i+2] = 0x00;
        pkt[i+3] = 0x00;
        pkt[i+4] = 0x00;
        pkt[i+5] = 0x00;
        pkt[i+6] = 0x01;
        pkt[i+7] = 0xFF;
    }
    return;
}

static void 
b_mpeg2ts_btp_make(uint16_t pid, uint8_t *pkt, const b_mpeg2ts_btp_pkt *btp, unsigned timestamp_offset)
{
    unsigned i;
    BKNI_Memset(pkt, 0, BMPEG2TS_PKT_LEN+timestamp_offset);
    pkt += timestamp_offset;
    pkt[0] = 0x47;
    pkt[1] = B_GET_BITS(pid, 12, 8);
    pkt[2] = B_GET_BITS(pid, 7, 0);
    pkt[3] = 0x20;
    pkt[4] = 183;
    pkt[5] = 0x02;
    pkt[6] = 45;
    pkt[7] = 0;
    pkt[8 ] = 'B';
    pkt[9 ] = 'R';
    pkt[10] = 'C';
    pkt[11] = 'M';
    for(i=0;i<sizeof(btp->data)/sizeof(btp->data[0]);i++) {
        pkt[12+4*i+0] = B_GET_BITS(btp->data[i], 31, 24);
        pkt[12+4*i+1] = B_GET_BITS(btp->data[i], 23, 16);
        pkt[12+4*i+2] = B_GET_BITS(btp->data[i], 15, 8);
        pkt[12+4*i+3] = B_GET_BITS(btp->data[i], 7, 0);
    }
    BDBG_CASSERT(BMPEG2TS_PKT_LEN>12+sizeof(btp->data));
    return;
}

static int
b_mpeg2ts_player_send_header_fragmented(bmpeg2ts_player_t player, bmedia_player_entry *entry)
{
    b_mpeg2ts_btp_pkt btp;
    BKNI_Memset(&btp, 0, sizeof(btp));
    btp.data[0] = TT_MODE_PROCESS;
    btp.data[7] = 0;
    btp.data[8] = 0;
    b_mpeg2ts_btp_make(player->stream.master, player->packet_buf, &btp, player->timestamp_offset);
    entry->type = bmedia_player_entry_type_embedded;
    entry->length = BMPEG2TS_PKT_LEN+player->timestamp_offset;
    entry->embedded = player->packet_buf;
#if 1
    BKNI_Memset(&btp, 0, sizeof(btp));
    btp.data[0] = TT_MODE_PIC_OUTPUT_COUNT;
    btp.data[9] = 1;
    b_mpeg2ts_btp_make(player->stream.master,player->packet_buf+entry->length, &btp, player->timestamp_offset);
    entry->length += BMPEG2TS_PKT_LEN+player->timestamp_offset;
#endif
    return 0;
}

static int
b_mpeg2ts_player_send_tail_fragmented(bmpeg2ts_player_t player, bmedia_player_entry *entry)
{
    b_mpeg2ts_btp_pkt btp;
    BKNI_Memset(&btp, 0, sizeof(btp));
    btp.data[0] = TT_MODE_INLINE_FLUSH;
    b_mpeg2ts_btp_make(player->stream.master,player->packet_buf, &btp, player->timestamp_offset);
    entry->type = bmedia_player_entry_type_embedded;
    entry->length = BMPEG2TS_PKT_LEN+player->timestamp_offset;
    entry->embedded = player->packet_buf;
    return 0;
}

static int
b_mpeg2ts_player_send_header(bmpeg2ts_player_t player, bmedia_player_entry *entry, bool eof)
{
    switch(player->decoder_mode) {
    default:
    case b_mpeg2ts_player_decoder_mode_normal:
        BDBG_ASSERT(0);
        entry->type = bmedia_player_entry_type_no_data;
        return 0;
    case b_mpeg2ts_player_decoder_mode_otf:
        return b_mpeg2ts_player_send_header_otf(player, entry, eof);
    case b_mpeg2ts_player_decoder_mode_fragmented:
        return b_mpeg2ts_player_send_header_fragmented(player, entry);
    }
}


static int
b_mpeg2ts_player_start_eof(bmpeg2ts_player_t player, bmedia_player_entry *entry)
{
    BDBG_MSG(("b_mpeg2ts_player_start_eof: %#lx", (unsigned long) player));
    if(player->decoder_mode == b_mpeg2ts_player_decoder_mode_otf ||
       !(player->feed_config.mode==b_file_feed_mode_sequential || player->decoder_mode==b_mpeg2ts_player_decoder_mode_normal)) {
        int rc = b_mpeg2ts_player_send_header(player, entry, true);
        player->feed_state = b_file_feed_state_eof_tail;
        if(rc==0) {
            BDBG_ASSERT(player->packet_buf == entry->embedded);
            BDBG_ASSERT(sizeof(player->packet_buf)>= entry->length + 2*BMPEG2TS_PKT_LEN);
            b_mpeg2ts_ts_make_filler(player->stream.master, player->packet_buf + entry->length, player->timestamp_offset);
            entry->length += BMPEG2TS_PKT_LEN + player->timestamp_offset;
            b_mpeg2ts_ts_make_filler(player->stream.master, player->packet_buf + entry->length, player->timestamp_offset);
            entry->length += BMPEG2TS_PKT_LEN + player->timestamp_offset;
        }
        return rc;
    }
    entry->type = bmedia_player_entry_type_end_of_stream; /* just EOF */
    return 0; 
}

static int
b_mpeg2ts_player_handle_read_error(bmpeg2ts_player_t player, bfile_buffer_result read_result, bmedia_player_entry *entry)
{
    int rc=0;
    switch(read_result) {
    case bfile_buffer_result_async:
        BDBG_ASSERT(0);
        break;
    case bfile_buffer_result_no_data:
        entry->type = bmedia_player_entry_type_no_data;
        break;
    case bfile_buffer_result_eof:
        if(player->feed_config.mode==(b_file_feed_mode)b_mpeg2ts_player_file_mode_backward) {
            entry->type = bmedia_player_entry_type_no_data;
            player->read_offset = player->feed_stop_offset;
        } else {
            rc = b_mpeg2ts_player_start_eof(player, entry);
        } 
        break;
    default:
        b_mpeg2ts_player_data_error(player);
        rc =b_mpeg2ts_player_start_eof(player, entry);
        break;
    }
    return rc;
}

static void 
b_mpeg2ts_player_read_cont(void *cntx, batom_t atom, bfile_buffer_result result)
{
    bmpeg2ts_player_t player = cntx;
	bmedia_player_entry entry;
    int rc=0;

	BDBG_OBJECT_ASSERT(player, bmpeg2ts_player_t);

    bmedia_player_init_entry(&entry);
    if(atom) {
        b_mpeg2ts_player_process_data(player, atom, &entry);
    } else {
        entry.atom = NULL;
        if(!(result==bfile_buffer_result_no_data || result==bfile_buffer_result_eof)) {
            BDBG_WRN(("b_mpeg2ts_player_read_cont: read failed %p (" B_OFFT_FMT ":%u)", (void *)player, B_OFFT_ARG(player->read_offset), (unsigned)player->async_read_size));
        }
        rc = b_mpeg2ts_player_handle_read_error(player, result, &entry);
    }
    if(rc<0) {
        entry.type = bmedia_player_entry_type_error;
    }
	BDBG_ASSERT(player->config.atom_ready);
    player->async_read_size = 0;
	player->config.atom_ready(player->config.cntx, &entry);
	return;
}



static int
b_mpeg2ts_player_read_data(bmpeg2ts_player_t player, bmedia_player_entry *entry)
{
	batom_t atom;
    bfile_buffer_result read_result;
    size_t read_size;
    int rc = 0;

    if(player->read_offset + B_MPEG2TS_PLAYER_READ_SIZE <= player->feed_stop_offset) {
        read_size = B_MPEG2TS_PLAYER_READ_SIZE;
    } else {
        BDBG_ASSERT(player->feed_stop_offset - player->read_offset);
        read_size = player->feed_stop_offset - player->read_offset;
    }

    if(player->config.atom_ready) {
       atom = bfile_buffer_async_read(player->config.buffer, player->read_offset, read_size, &read_result, b_mpeg2ts_player_read_cont, player);
       player->async_read_size = 0;
       if(atom==NULL) {
           switch(read_result) {
           case bfile_buffer_result_async:
                player->async_read_size = read_size;
                entry->type = bmedia_player_entry_type_async;
                break;
           default:
                rc = b_mpeg2ts_player_handle_read_error(player, read_result, entry);
                break;
           }
           goto done;
       }
    } else {
        atom = bfile_buffer_read(player->config.buffer, player->read_offset, read_size, &read_result);
        if(atom==NULL) {
            rc = b_mpeg2ts_player_handle_read_error(player, read_result, entry);
            goto done;
        }
    }
    b_mpeg2ts_player_process_data(player, atom, entry);
done:
    return rc;
}


int
bmpeg2ts_player_next(bmpeg2ts_player_t player, bmedia_player_entry *entry)
{
    int rc = 0;

	BDBG_OBJECT_ASSERT(player, bmpeg2ts_player_t);
	BDBG_ASSERT(entry);

    bmedia_player_init_entry(entry);

    BDBG_MSG_TRACE(("bmpeg2ts_player_next:%p reading position %lu(%lu)", (void *)player, (unsigned long)player->read_offset, (unsigned long)player->feed_stop_offset));
    BDBG_ASSERT(player->async_read_size==0); /* we can't allow multiple outstanding calls into the async I/O */

    if(player->feed_state == b_file_feed_state_eof_tail) {
        entry->type = bmedia_player_entry_type_end_of_stream;
        goto done;
    } else if(player->feed_config.mode!=(b_file_feed_mode)b_mpeg2ts_player_file_mode_sequential && player->feed_state==b_file_feed_state_header) {
        player->feed_state = b_file_feed_state_data;
        rc = b_mpeg2ts_player_send_header(player, entry, false);
        goto done;
    } else {
        player->feed_state = b_file_feed_state_data;
        if(player->read_offset >= player->feed_stop_offset) {
            off_t stride;
            BDBG_MSG(("bmpeg2ts_player_next:%p end of block:%u at %lu", (void *)player, player->feed_count, (unsigned long)player->read_offset));
            player->feed_count ++;
            stride = player->feed_config.mode==(b_file_feed_mode)b_mpeg2ts_player_file_mode_backward? -(off_t)player->feed_config.stride : (off_t)player->feed_config.stride;
            b_mpeg2ts_player_update_feed(player, player->feed_start_offset + stride);
            if(player->feed_start_offset == player->feed_stop_offset) {
                /* reached begining of the file */
                rc = b_mpeg2ts_player_start_eof(player, entry);
                goto done;
            }
            BDBG_MSG(("bmpeg2ts_player_next:%#lx new block:%u at %lu..%lu", (unsigned long)player, player->feed_count, (unsigned long)player->feed_start_offset, (unsigned long)player->feed_stop_offset));
            if(player->feed_config.mode==(b_file_feed_mode)b_mpeg2ts_player_file_mode_sequential) {
                rc = b_mpeg2ts_player_read_data(player, entry);
            } else {
                if(player->decoder_mode==b_mpeg2ts_player_decoder_mode_fragmented) {
                    player->feed_state = b_file_feed_state_header;
                    rc = b_mpeg2ts_player_send_tail_fragmented(player, entry);
                } else {
                    player->feed_state = b_file_feed_state_data;
                    rc = b_mpeg2ts_player_send_header(player, entry, false);
                }
            }
        } else {
            rc = b_mpeg2ts_player_read_data(player, entry);
        }
    }

done:
    BDBG_MSG_TRACE(("bmpeg2ts_player_next:%#lx position:%u", (unsigned long)player, (unsigned)player->status.position));
    return rc;
}

void 
bmpeg2ts_player_tell(bmpeg2ts_player_t player, bmedia_player_pos *pos)
{
	BDBG_OBJECT_ASSERT(player, bmpeg2ts_player_t);
	*pos = player->status.position;
    if(player->last_pts_valid) {
        int rc;
        btime_indexer_location location;
        location.timestamp = player->last_pts;
        location.offset = player->read_offset;
        location.direction = player->time_scale<0 ? btime_indexer_direction_backward:btime_indexer_direction_forward;
        /* btime_indexer_dump(player->index); */
        rc = btime_indexer_get_time_by_location(player->index, &location, pos);
    }
    BDBG_MSG(("bmpeg2ts_player_tell:%p %s %u:%u", (void *)player, player->last_pts_valid?"WITH PTS":"", player->last_pts, (unsigned)*pos));
	return;
}

void 
bmpeg2ts_player_get_status(bmpeg2ts_player_t player, bmedia_player_status *status)
{
	btime_indexer_status indexer_status;
	BDBG_OBJECT_ASSERT(player, bmpeg2ts_player_t);
	BDBG_MSG_TRACE(("bmpeg2ts_player_get_status:> %p", (void *)player));
	*status = player->status;
	btime_indexer_get_status(player->index, &indexer_status);
	if(indexer_status.byterate==0 && player->async_read_size == 0) {
		int rc = b_mpeg2ts_player_open_file(player);
		if(rc==0) {
			btime_indexer_get_status(player->index, &indexer_status);
			bmpeg2ts_parser_seek(player->parser, player->read_offset);
			btime_indexer_seek(player->index, player->status.position);
		}
	} 
	if(indexer_status.byterate>0) {
		off_t first, last;
		int rc = player->fd->bounds(player->fd, &first, &last);
		if(rc>=0) {
			status->bounds.last = (last*BMEDIA_PLAYER_POS_SCALE) / indexer_status.byterate;
		} 
	} 
	BDBG_MSG_TRACE(("bmpeg2ts_player_get_status:< %p %ld:%ld", (void *)player, (long)status->bounds.first, (long)status->bounds.last));
	return;
}

static size_t 
b_mpeg2ts_player_get_chunk_size(bmpeg2ts_player_t player)
{
    btime_indexer_position entry;
    size_t stream_based_size;
    size_t cdb_based_size;
    size_t size, min_block;
    unsigned pkt_len = BMPEG2TS_PKT_LEN + player->timestamp_offset;

    min_block = B_MPEG2TS_PLAYER_MIN_BLOCK + (player->timestamp_offset?BIO_BLOCK_SIZE:0);

    size = player->config.key_frame_distance;

    if (size==0) {
        if(btime_indexer_position_by_time(player->index, player->status.position, &entry)==true) {
            stream_based_size = 1*entry.byterate; /* assuming gop is less then 1 second */
        } else {
            stream_based_size = min_block;
        }
        cdb_based_size = (3*player->config.decoder_features.video_buffer_size) / 4; /* video buffer should be able to keep at least 2 chunks */
        if(stream_based_size <= cdb_based_size) {
            size = stream_based_size;
        } else {
            size = cdb_based_size;
            BDBG_WRN(("Limiting size of the trickmode chunk based on the CDB size %u -> %u", (unsigned)stream_based_size, (unsigned)cdb_based_size));
        }
    } 

    if(size>min_block) {
	    size += pkt_len - (size%pkt_len);
    } else {
	    size = min_block;
    }
    return size;
}

static bmedia_time_scale
b_mpeg2ts_time_scale_abs(bmedia_time_scale time_scale)
{
    return time_scale>=0?time_scale:-time_scale;
}

static void
b_mpeg2ts_player_I_only_mode(bmpeg2ts_player_t player, bmedia_time_scale time_scale, bmedia_player_decoder_mode *mode)
{
    mode->display_frames = bmedia_player_decoder_frames_I;
    mode->reordering_mode = bmedia_player_reordering_mode_none;
    time_scale = b_mpeg2ts_time_scale_abs(time_scale);
    player->feed_config.stride = player->feed_config.chunk * ((time_scale / (4*BMEDIA_TIME_SCALE_BASE))+1);
    mode->time_scale = time_scale/16;
    if(mode->time_scale>BMEDIA_TIME_SCALE_BASE) {
        mode->time_scale = BMEDIA_TIME_SCALE_BASE;
    }
    return;
}

void 
bmpeg2ts_player_set_direction(bmpeg2ts_player_t player, bmedia_player_step direction, bmedia_time_scale time_scale, bmedia_player_decoder_mode *mode)
{
	BDBG_OBJECT_ASSERT(player, bmpeg2ts_player_t);
    BSTD_UNUSED(mode);

	BDBG_MSG_TRACE(("bmpeg2ts_player_set_direction:> %#lx %ld", (unsigned long)player, (long)direction));
    BDBG_ASSERT(mode);
    mode->brcm = false;
    mode->dqt = false;
    mode->host_paced = false;
    mode->display_frames = bmedia_player_decoder_frames_all;
    player->feed_count = 0;
    if(time_scale >= 0 && time_scale <= BMEDIA_TIME_SCALE_BASE) {
        /* normal play */
        mode->continuous = true;
        mode->tsm = true;
        mode->reordering_mode = bmedia_player_reordering_mode_none;
        mode->time_scale = time_scale;
        if(player->time_scale!=time_scale) {
            player->feed_config.mode = b_mpeg2ts_player_file_mode_sequential;
            player->feed_config.chunk = B_MPEG2TS_PLAYER_MIN_BLOCK + (player->timestamp_offset?BIO_BLOCK_SIZE:0);
            player->feed_config.stride = B_MPEG2TS_PLAYER_MIN_BLOCK + (player->timestamp_offset?BIO_BLOCK_SIZE:0);
            b_mpeg2ts_player_update_feed(player, player->read_offset);
        }
    } else {
        /* trick mode */
        mode->continuous = false;
        mode->tsm = false;
        if(player->config.decoder_features.otf && player->stream.stream.es.video_codec == bvideo_codec_mpeg2) {
            /* MPEG-2 OTF PVR */
            player->feed_state = b_file_feed_state_header;
            player->decoder_mode = b_mpeg2ts_player_decoder_mode_otf;
            if(time_scale >= 0 && time_scale <= 8 * BMEDIA_TIME_SCALE_BASE) {
                mode->reordering_mode = bmedia_player_reordering_mode_sequential;
                mode->time_scale = time_scale;
                player->feed_config.mode = b_mpeg2ts_player_file_mode_sequential;
                player->feed_config.chunk = B_MPEG2TS_PLAYER_MIN_BLOCK + (player->timestamp_offset?BIO_BLOCK_SIZE:0);
                player->feed_config.stride = B_MPEG2TS_PLAYER_MIN_BLOCK + (player->timestamp_offset?BIO_BLOCK_SIZE:0) ;
            } else {
                size_t overlap_chunk;
                player->feed_config.chunk = b_mpeg2ts_player_get_chunk_size(player);
                player->feed_config.mode = time_scale >= 0 ? b_mpeg2ts_player_file_mode_forward : b_mpeg2ts_player_file_mode_backward;
                overlap_chunk = (player->feed_config.chunk * 5)/2; /* overlap chunk should be 2x GOP size */
                if(time_scale < 0 && time_scale >= -4 * BMEDIA_TIME_SCALE_BASE && 
                        overlap_chunk <= player->config.decoder_features.video_buffer_size/2 /* and decoder buffer is large enough */ ) {
                    mode->reordering_mode = bmedia_player_reordering_mode_interleaved;
                    player->feed_config.stride = player->feed_config.chunk;
                    player->feed_config.chunk = overlap_chunk;
                    mode->time_scale = b_mpeg2ts_time_scale_abs(time_scale);
                } else {
                    if(time_scale < 0 && time_scale >= -4 * BMEDIA_TIME_SCALE_BASE) {
                        BDBG_WRN(("not enough CBD size for real 1x reverse %u %u", (unsigned)(2*overlap_chunk), (unsigned)player->config.decoder_features.video_buffer_size));
                    }
                    mode->reordering_mode = time_scale >= 0 ? bmedia_player_reordering_mode_forward : bmedia_player_reordering_mode_backward;
                    mode->time_scale = b_mpeg2ts_time_scale_abs(time_scale);
                    if(mode->time_scale>10*BMEDIA_TIME_SCALE_BASE) {
                        mode->time_scale = 10*BMEDIA_TIME_SCALE_BASE;
                    }
                    player->feed_config.stride = ((uint64_t)player->feed_config.chunk * b_mpeg2ts_time_scale_abs(time_scale))/mode->time_scale;
                }
            }
            b_mpeg2ts_player_update_feed(player, player->read_offset);
            BDBG_MSG(("bmpeg2ts_player_set_direction:%p OTF feeding data %u:%u rate:%u", (void *)player, (unsigned)player->feed_config.chunk, (unsigned)player->feed_config.stride, (unsigned)mode->time_scale));
        } else if(player->config.decoder_features.fragmented) {
            /* fragmented decode */
            player->feed_config.mode = time_scale>=0?b_mpeg2ts_player_file_mode_forward:b_mpeg2ts_player_file_mode_backward;
            player->feed_state = b_file_feed_state_header;
            player->decoder_mode = b_mpeg2ts_player_decoder_mode_fragmented;
            mode->display_frames = bmedia_player_decoder_frames_I;
            mode->fragmented = true;
            player->feed_config.chunk = b_mpeg2ts_player_get_chunk_size(player);
            b_mpeg2ts_player_I_only_mode(player, time_scale, mode);
            b_mpeg2ts_player_update_feed(player, player->read_offset);
            BDBG_MSG(("bmpeg2ts_player_set_direction:%p FRAGMENTED feeding data %u:%u rate:%u", (void *)player, (unsigned)player->feed_config.chunk, (unsigned)player->feed_config.stride, (unsigned)mode->time_scale));
        } else {
            BDBG_ERR(("bmpeg2ts_player_set_direction:%p trickmodes aren't supported", (void *)player));
            goto done;
        }
    }
	player->status.direction = direction;
	player->time_scale = time_scale;
done:
	BDBG_MSG_TRACE(("bmpeg2ts_player_set_direction:<%p %ld", (void *)player, (long)0));
	return;
}


int
bmpeg2ts_player_seek(bmpeg2ts_player_t player, bmedia_player_pos pos)
{
    int rc;
    off_t read_offset;

    BDBG_OBJECT_ASSERT(player, bmpeg2ts_player_t);
    BDBG_MSG(("bmpeg2ts_player_seek:>%p %u(%u)", (void *)player, (unsigned)pos, (unsigned)player->status.position));
    player->feed_count = 0;
    if(pos!=0) {
        off_t first, last;
        btime_indexer_position position;
        if(pos > player->status.bounds.last) {
            rc = b_mpeg2ts_player_advance(player, pos);
            if(rc<0) { 
                rc = b_mpeg2ts_player_open_file(player);
                if(rc<0) { rc=BERR_TRACE(rc);goto error;}
                rc = b_mpeg2ts_player_advance(player, pos);
                if(rc<0) { rc=BERR_TRACE(rc);goto error;}
            }
        }
        if(btime_indexer_position_by_time(player->index, pos, &position)!=true) {
            rc = b_mpeg2ts_player_open_file(player);
            if(rc<0) { rc=BERR_TRACE(rc);goto error;}
            if(!btime_indexer_position_by_time(player->index, pos, &position)) {
                rc=BERR_TRACE(rc);goto error;
            }
        }
        rc = player->fd->bounds(player->fd, &first, &last);
        if(rc>=0 && (off_t)position.offset > last) {
            position.offset = last;
        }
	    player->status.position = position.time;
	    read_offset = position.offset;
    } else {
	    player->status.position = 0;
        read_offset = 0;
    }
	player->last_pts_valid = false;
	player->pcr_position = pos;
	if(player->feed_config.mode==(b_file_feed_mode)b_mpeg2ts_player_file_mode_backward) {
		read_offset -= player->feed_config.stride;
	}
	b_mpeg2ts_player_update_feed(player, read_offset);
	btime_indexer_seek(player->index, player->status.position);

	BDBG_MSG(("bmpeg2ts_player_seek:< %#lx %u:%u(%lu)", (unsigned long)player, (unsigned)pos, (unsigned)player->status.position, (unsigned long)read_offset));
	return 0;
error:
	BDBG_WRN(("bmpeg2ts_player_seek:%#lx seek error", (unsigned long)player));
	return -1;
}

void 
bmpeg2ts_player_update_position(bmpeg2ts_player_t player, uint32_t pts)
{
	BDBG_OBJECT_ASSERT(player, bmpeg2ts_player_t);

    player->last_pts = pts;
    player->last_pts_valid = true;
    return;
}


static void *
b_mpeg2ts_player_create(bfile_io_read_t fd, const bmedia_player_config *config, const bmedia_player_stream *stream)
{
	return bmpeg2ts_player_create(fd, config, stream);
}

static void
b_mpeg2ts_player_destroy(void *player)
{
	bmpeg2ts_player_destroy(player);
}

static int
b_mpeg2ts_player_next(void *player, bmedia_player_entry *entry)
{
	return bmpeg2ts_player_next(player, entry);
}

static void 
b_mpeg2ts_player_tell(void *player, bmedia_player_pos *pos)
{
	bmpeg2ts_player_tell(player, pos);
	return;
}

static void 
b_mpeg2ts_player_get_status(void *player, bmedia_player_status *status)
{
	bmpeg2ts_player_get_status(player, status);
	return;
}

static int
b_mpeg2ts_player_set_direction(void *player, bmedia_player_step direction, bmedia_time_scale time_scale, bmedia_player_decoder_mode *mode)
{
	bmpeg2ts_player_set_direction(player, direction, time_scale, mode);
	return 0;
}

static int  
b_mpeg2ts_player_seek(void *player, bmedia_player_pos pos)
{
	return bmpeg2ts_player_seek(player, pos);
}

const bmedia_player_methods bmpeg2ts_player_methods = {
	b_mpeg2ts_player_create,
	b_mpeg2ts_player_destroy,
	b_mpeg2ts_player_next,
	b_mpeg2ts_player_tell,
	b_mpeg2ts_player_get_status,
	b_mpeg2ts_player_set_direction,
	b_mpeg2ts_player_seek
};

