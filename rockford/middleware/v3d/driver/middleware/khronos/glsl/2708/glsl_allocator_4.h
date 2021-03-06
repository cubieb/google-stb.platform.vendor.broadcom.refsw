/*=============================================================================
Copyright (c) 2009 Broadcom Europe Limited.
All rights reserved.

Project  :  khronos
Module   :  Header file
File     :  $RCSfile: $
Revision :  $Revision: $

FILE DESCRIPTION
Responsible for fitting nodes into the ADD and MUL units and allocating registers
for their destinations.
=============================================================================*/
#ifndef GLSL_ALLOCATOR_4_H
#define GLSL_ALLOCATOR_4_H

#include "middleware/khronos/common/khrn_mem.h"

extern void glsl_allocator_add_node(Dataflow *dataflow);
extern bool glsl_allocator_add_input_dependency(Dataflow *dataflow);
extern bool glsl_allocator_init(uint32_t type, bool is_threaded, uint32_t num_attribute_rows);
extern void glsl_allocator_dump(void);
extern bool glsl_allocator_finish(void);
extern void glsl_allocator_mem_term(void);
extern uint32_t *glsl_allocator_get_shader_pointer(void);
extern uint32_t glsl_allocator_get_shader_size(void);
extern uint32_t *glsl_allocator_get_unif_pointer(void);
extern uint32_t glsl_allocator_get_unif_count(void);
extern uint32_t *glsl_allocator_get_varying_pointer(void);
extern uint32_t glsl_allocator_get_varying_count(void);
extern bool glsl_allocator_failed(void);
extern void glsl_allocator_mark_failed_nodes_on_stack(void);
extern Dataflow *glsl_allocator_get_next_scheduler_node(void);
extern void glsl_allocator_finish_scheduler_node(Dataflow *suggestion);
extern bool glsl_dataflow_is_unpack(const Dataflow *dataflow);

#ifdef BACKEND_VERIFY_SHADERS
extern void glsl_backend_verify_vertex_shader(uint32_t seed, Dataflow *dataflow, const void *shader, uint32_t num_instr, const uint32_t *unif_map, uint32_t num_unif, uint32_t num_outputs);
#endif

#define BACKEND_UNIFORM 0
#define BACKEND_UNIFORM_LITERAL 1
#define BACKEND_UNIFORM_TEX_PARAM0 2
#define BACKEND_UNIFORM_TEX_PARAM1 3
#define BACKEND_UNIFORM_TEX_CUBE_STRIDE 4
#define BACKEND_UNIFORM_TEX_NOT_USED 5
#define BACKEND_UNIFORM_TEX_UNIF 0x10
#define BACKEND_UNIFORM_SCALE_X 0x80000008//now handled as a state offset
#define BACKEND_UNIFORM_SCALE_Y 0x80000010//now handled as a state offset
#define BACKEND_UNIFORM_SCALE_Z 0x80000014//now handled as a state offset
#define BACKEND_UNIFORM_OFFSET_Z 0x80000018//now handled as a state offset
#define BACKEND_UNIFORM_VPM_READ_SETUP 0x8000001c
#define BACKEND_UNIFORM_VPM_WRITE_SETUP 0x80000020
#define BACKEND_UNIFORM_NEXT_USER_SHADER 0x80000024
#define BACKEND_UNIFORM_NEXT_USER_UNIF 0x80000028
#define BACKEND_UNIFORM_VDR_SETUP0 0x8000002c
#define BACKEND_UNIFORM_VDR_SETUP1 0x80000030
#define BACKEND_UNIFORM_VDR_ADDR_START 0x80000034
#define BACKEND_UNIFORM_VDR_ADDR_INCR 0x80000038
#define BACKEND_UNIFORM_VDR_ADDR_END 0x8000003c
#define BACKEND_UNIFORM_VDW_SETUP0 0x80000040
#define BACKEND_UNIFORM_VDW_SETUP1 0x80000044
#define BACKEND_UNIFORM_VDW_ADDR_START 0x80000048
#define BACKEND_UNIFORM_VDW_ADDR_INCR 0x8000004c
#define BACKEND_UNIFORM_DEPTHRANGE_NEAR 0x80000050
#define BACKEND_UNIFORM_DEPTHRANGE_FAR 0x80000054
#define BACKEND_UNIFORM_DEPTHRANGE_DIFF 0x80000058
#define BACKEND_UNIFORM_STENCIL_FRONT 0x8000005c
#define BACKEND_UNIFORM_STENCIL_BACK 0x80000060
#define BACKEND_UNIFORM_STENCIL_MASK 0x80000068
#define BACKEND_UNIFORM_BLEND_COLOR 0x8000006c
#define BACKEND_UNIFORM_ADDRESS 0x80000070
#define BACKEND_UNIFORM_FBHEIGHT 0x80000074
#define BACKEND_UNIFORM_EGL_OUTPUT_FORMAT 0x80000078

#define BACKEND_UNIFORM_ATTRIB0 0x80000100
#define BACKEND_UNIFORM_ATTRIB1 0x80000104
#define BACKEND_UNIFORM_ATTRIB2 0x80000108
#define BACKEND_UNIFORM_ATTRIB3 0x8000010c
#define BACKEND_UNIFORM_ATTRIB4 0x80000110
#define BACKEND_UNIFORM_ATTRIB5 0x80000114
#define BACKEND_UNIFORM_ATTRIB6 0x80000118
#define BACKEND_UNIFORM_ATTRIB7 0x80000120
#define BACKEND_UNIFORM_ATTRIB8 0x80000124
#define BACKEND_UNIFORM_ATTRIB9 0x80000128
#define BACKEND_UNIFORM_ATTRIB10 0x8000012c
#define BACKEND_UNIFORM_ATTRIB11 0x80000130
#define BACKEND_UNIFORM_ATTRIB12 0x80000134
#define BACKEND_UNIFORM_ATTRIB13 0x80000138
#define BACKEND_UNIFORM_ATTRIB14 0x8000013c
#define BACKEND_UNIFORM_ATTRIB15 0x80000140
#define BACKEND_UNIFORM_ATTRIB16 0x80000144
#define BACKEND_UNIFORM_ATTRIB17 0x80000148
#define BACKEND_UNIFORM_ATTRIB18 0x8000014c
#define BACKEND_UNIFORM_ATTRIB19 0x80000150
#define BACKEND_UNIFORM_ATTRIB20 0x80000154
#define BACKEND_UNIFORM_ATTRIB21 0x80000158
#define BACKEND_UNIFORM_ATTRIB22 0x8000015c
#define BACKEND_UNIFORM_ATTRIB23 0x80000160
#define BACKEND_UNIFORM_ATTRIB24 0x80000164
#define BACKEND_UNIFORM_ATTRIB25 0x80000168
#define BACKEND_UNIFORM_ATTRIB26 0x8000016c
#define BACKEND_UNIFORM_ATTRIB27 0x80000170
#define BACKEND_UNIFORM_ATTRIB28 0x80000174
#define BACKEND_UNIFORM_ATTRIB29 0x80000178
#define BACKEND_UNIFORM_ATTRIB30 0x8000017c
#define BACKEND_UNIFORM_ATTRIB31 0x80000180

#define BACKEND_PASS_AWAITING_SCHEDULE 123000
#define BACKEND_PASS_SCHEDULED  123001
#define BACKEND_PASS_FIND_ATRIBS 123002
#define BACKEND_PASS_SEEN_INPUT  123003
#define BACKEND_PASS_VISITING  123004
#define BACKEND_PASS_DIVING 123005
#define BACKEND_PASS_FAILED_ON_STACK 123006

#define BACKEND_ACTUAL_PASS_BUSHINESS 123009
#define BACKEND_ACTUAL_PASS_SCHEDULE 123010
#define BACKEND_ACTUAL_PASS_PRINT 123011

#define GLSL_BACKEND_TYPE_FRAGMENT (1<<1)
#define GLSL_BACKEND_TYPE_VERTEX (1<<2)
#define GLSL_BACKEND_TYPE_COORD (1<<3)
#define GLSL_BACKEND_TYPE_OFFLINE_VERTEX (1<<4)

#ifdef WIN32
__declspec(dllimport) void __stdcall OutputDebugStringA(const char * lpOutputString);
#define debug_print(s) OutputDebugStringA(s)
#else
#define debug_print(s) printf("%s",s)
#endif

#endif //GLSL_2760SIM_ALLOCATOR_H
