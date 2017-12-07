/******************************************************************************
 *  Copyright (C) 2017 Broadcom. The term "Broadcom" refers to Broadcom Limited and/or its subsidiaries.
 ******************************************************************************/
#pragma once

#include "bitmap.h"
#include "../helpers/semaphore.h"

namespace nxpl
{

class DispItem
{
public:
   DispItem(std::unique_ptr<nxpl::Bitmap> &&bitmap, std::unique_ptr<helper::Semaphore> &&fence, int swap_interval = 1) :
      m_bitmap(std::move(bitmap)),
      m_fence(std::move(fence)),
      m_swapInterval(swap_interval)
   {};
   ~DispItem() = default;

   std::unique_ptr<nxpl::Bitmap>       m_bitmap;
   std::unique_ptr<helper::Semaphore>  m_fence;
   int                                 m_swapInterval;
};

}
