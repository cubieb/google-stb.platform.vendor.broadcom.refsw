/*
 * Note: this file originally auto-generated by mib2c using
 *        mib2c.brcm.iterate.conf 2003/6/16 turcotte
 */
#ifndef DOCSIFDOWNSTREAMCHANNELTABLE_H
#define DOCSIFDOWNSTREAMCHANNELTABLE_H

/*
 * function declarations 
 */
void            init_docsIfDownstreamChannelTable(void);
void            initialize_table_docsIfDownstreamChannelTable(void);
Netsnmp_Node_Handler docsIfDownstreamChannelTable_handler;


/*
 * column number definitions for table docsIfDownstreamChannelTable 
 */
#define COLUMN_DOCSIFDOWNCHANNELID		1
#define COLUMN_DOCSIFDOWNCHANNELFREQUENCY		2
#define COLUMN_DOCSIFDOWNCHANNELWIDTH		3
#define COLUMN_DOCSIFDOWNCHANNELMODULATION		4
#define COLUMN_DOCSIFDOWNCHANNELINTERLEAVE		5
#define COLUMN_DOCSIFDOWNCHANNELPOWER		6
#endif                          /* DOCSIFDOWNSTREAMCHANNELTABLE_H */
