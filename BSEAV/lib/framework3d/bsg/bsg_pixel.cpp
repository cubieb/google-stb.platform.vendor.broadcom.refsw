/******************************************************************************
 *  Copyright (C) 2016 Broadcom. The term "Broadcom" refers to Broadcom Limited and/or its subsidiaries.
 ******************************************************************************/
#include "bsg_pixel.h"
#include <assert.h>
#include <cstdio>

Pixel Pixel::ReadPixel(int x, int y)
{
   GLubyte r[4];

   glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, r);

   TYPE_CONVERT_T cr, cg, cb, ca;

   cr.ui = r[0];
   cg.ui = r[1];
   cb.ui = r[2];
   ca.ui = r[3];

   cr.ui = qpu_float_unpack_uint_n(r[0], 8);
   cg.ui = qpu_float_unpack_uint_n(r[1], 8);
   cb.ui = qpu_float_unpack_uint_n(r[2], 8);
   ca.ui = qpu_float_unpack_uint_n(r[3], 8);

   Pixel p(cr.f, cg.f, cb.f, ca.f);

   return (p);
}

bool Pixel::operator!=(const Pixel &p) const
{
   return !operator==(p);
}

bool Pixel::operator==(const Pixel &p) const
{
   TYPE_CONVERT_T this_cr, this_cg, this_cb, this_ca;

   this_cr.f = m_r;
   this_cg.f = m_g;
   this_cb.f = m_b;
   this_ca.f = m_a;

   TYPE_CONVERT_T arg_cr, arg_cg, arg_cb, arg_ca;

   arg_cr.f = p.m_r;
   arg_cg.f = p.m_g;
   arg_cb.f = p.m_b;
   arg_ca.f = p.m_a;

   if ((qpu_float_pack_uint8(this_cr.ui) == qpu_float_pack_uint8(arg_cr.ui)) &&
       (qpu_float_pack_uint8(this_cg.ui) == qpu_float_pack_uint8(arg_cg.ui)) &&
       (qpu_float_pack_uint8(this_cb.ui) == qpu_float_pack_uint8(arg_cb.ui)) &&
       (qpu_float_pack_uint8(this_ca.ui) == qpu_float_pack_uint8(arg_ca.ui)))
   {
      return true;
   }
   else
   {
      printf("Left colour: %d, %d, %d, %d\n",   qpu_float_pack_uint8(this_cr.ui),
                                                qpu_float_pack_uint8(this_cg.ui),
                                                qpu_float_pack_uint8(this_cb.ui),
                                                qpu_float_pack_uint8(this_ca.ui));

      printf("Right colour: %d, %d, %d, %d\n",   qpu_float_pack_uint8(arg_cr.ui),
                                                 qpu_float_pack_uint8(arg_cg.ui),
                                                 qpu_float_pack_uint8(arg_cb.ui),
                                                 qpu_float_pack_uint8(arg_ca.ui));
      return false;
   }
}


//    Helper functions

/* This is the conversion factor which the HW uses to go from IEEE to int, we need to use this rather than the
 * host CPU.  File originated in qpu_float.c */
unsigned int Pixel::qpu_float_pack_uint8(unsigned int fl)
{
   int exp, mmt, rsh, ans, ans256;

   exp = (fl >> 23) & 0xff;
   mmt = (fl & 0x7fffff) | 0x800000; // bit 24 = hidden bit

   if ((fl >> 31) || (exp <= 117))
      return 0;

   if (exp >= 127)
      return 255;

   // between 1/512 and 1

   rsh = (127 - exp) + 12;
   ans256 = mmt >> rsh;
   if ((mmt << (32 - rsh)) != 0)
      ans256 |= 1;

   ans = ans256 >> 8;
   if ((ans256 << 24) != 0)
      ans |= 1;

   // subtract 1/256th of ans from itself (so multiplying by 255 not 256)
   ans = ans256 - ans;

   // work out rounding
   return (ans + 4) >> 3;
}

/*!
 * \brief Converts an 8-bit unsigned integer to a float.
 *
 * This is used to convert colour components from integer representations to floating point
 * values. Given input in the range 0 <= data <= 255, it divides by 255 and returns a
 * floating point value between 0 and 1. The bits of the floating point value are returned
 * as an integer for convenience - but it's a float really!
 *
 * \param data is an integer in the range 0 to 255.
 * \return A bit pattern representing a single-precision float.
 */
unsigned int Pixel::qpu_float_unpack_uint_n(unsigned int data, unsigned int n)
{
   unsigned int m,exp;
   unsigned int max;

   if (n==32)
      max = 0xffffffff;
   else
      max = (1<<n) - 1;

   assert(n >= 1 && n <= 32);
   assert(data <= max);

   if (data == max)
      return 0x3f800000;

   if (data == 0)
      return 0;

   /* If data=abc then we want m=abcabcab */
   data <<= 32 - n;
   m = 0;

   while (data != 0)
   {
      m |= data;
      if (n == 32)
         data = 0; /* shifting by 32 does nothing :-( */
      else
         data >>= n;
   }

   exp = 0x3a800000;
   while (m >= 0x1000000)
   {
      exp += 0x800000;
      m >>= 1;
   }

   return exp + m;
}
