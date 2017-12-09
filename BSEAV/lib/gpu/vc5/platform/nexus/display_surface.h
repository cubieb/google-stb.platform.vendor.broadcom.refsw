/******************************************************************************
 *  Copyright (C) 2016 Broadcom. The term "Broadcom" refers to Broadcom Limited and/or its subsidiaries.
 ******************************************************************************/
#ifndef __DISPLAY_SURFACE_H__
#define __DISPLAY_SURFACE_H__

#include "private_nexus.h"
#include <EGL/begl_displayplatform.h>

bool CreateSurface(NXPL_Surface *s,
   BEGL_BufferFormat format,
   uint32_t    width,
   uint32_t    height,
   uint32_t    miplevels,
   bool        secure,
   const char *desc);

void DestroySurface(NXPL_Surface *s);
bool isNXPL_Surface(NXPL_Surface *s);

#endif /* __DISPLAY_SURFACE_H__ */
