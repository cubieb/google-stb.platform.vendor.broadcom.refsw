/*=============================================================================
Copyright (c) 2008 Broadcom Europe Limited.
All rights reserved.

Project  :  khronos
Module   :  Header file

FILE DESCRIPTION
OpenGL ES 1.1 matrix and matrix stack implementation.
=============================================================================*/
/*
   gl11_matrix_load(GLfloat *d, const GLfloat *a)

   Copies a matrix from one place to another. (source and destination
   should not be identical or overlap).

   Khronos documentation:

   LoadMatrix takes a pointer to a 4 � 4 matrix stored in column-major order as 16
   consecutive fixed- or floating-point values, i.e. as

   a0  a4  a8  a12
   a1  a5  a9  a13
   a2  a6  a10 a14
   a3  a7  a11 a15

   (This differs from the standard row-major C ordering for matrix elements. If the
   standard ordering is used, all of the subsequent transformation equations are transposed,
   and the columns representing vectors become rows.)

   so we have a_ij is at a[i + j * 4]

   when multiplying we have d_01 = a_00 * b_01 + a_01 * b_11 + a_02 * b_21 + a_03 * b_31

   Implementation notes:

   We use the same internal representation of a matrix as GL does, therefore
   we can use this to move matrices from client land into our internal stuff
   directly. (Hence why we quoted the above thing about LoadMatrix).

   Preconditions:

   a, d are valid pointers to 16 floats
   a, d do not overlap

   Postconditions:

   -
*/

void gl11_matrix_load(float *d, const float *a)
{
   khrn_memcpy(d, a, 16 * sizeof(float));
}

/*
   Returns the offset into a column-major matrix, in units of sizeof(float)
   where i is the row number and j is the column number.
   Preconditions:
      0 <= i < 4
      0 <= j < 4
   Postconditions:
      0 <= result < 16
*/
#define OFFSET(i, j) ((i) + (j) * 4)


/*
   gl11_matrix_mult(float *d, const float *a, const float *b)

   Calculates the matrix product ab

   Implementation notes:

   It's OK for any of the pointers to overlap.

   Preconditions:

   d, a and b are valid pointers to 16 floats

   Postconditions:

   -
*/
/*
void gl11_matrix_mult(float *d, const float *a, const float *b)
{
   int i;
   float t[16];

   for (i = 0; i < 4; i++)
   {
      int j;
      for (j = 0; j < 4; j++) {
         float v = 0.0f;
         int k;
         for (k = 0; k < 4; k++)
            v += a[OFFSET(i, k)] * b[OFFSET(k, j)];

         t[OFFSET(i, j)] = v;
      }
   }

   gl11_matrix_load(d, t);
}
*/
void gl11_matrix_mult(float *d, const float *a, const float *b)
{
   int i;
   float t[16];

   for (i = 0; i < 4; i++)
   {
      int j4 = 0;
      int oa = i;
      int ob = j4;
      float v = 0.0f;
      v += a[oa] * b[ob]; oa+=4;ob++;
      v += a[oa] * b[ob]; oa+=4;ob++;
      v += a[oa] * b[ob]; oa+=4;ob++;
      v += a[oa] * b[ob];

      t[i+j4] = v;

      j4 = 4;
      oa = i;
      ob = j4;
      v = 0.0f;
      v += a[oa] * b[ob]; oa+=4;ob++;
      v += a[oa] * b[ob]; oa+=4;ob++;
      v += a[oa] * b[ob]; oa+=4;ob++;
      v += a[oa] * b[ob];

      t[i+j4] = v;

      j4 = 8;
      oa = i;
      ob = j4;
      v = 0.0f;
      v += a[oa] * b[ob]; oa+=4;ob++;
      v += a[oa] * b[ob]; oa+=4;ob++;
      v += a[oa] * b[ob]; oa+=4;ob++;
      v += a[oa] * b[ob];

      t[i+j4] = v;

      j4 = 12;
      oa = i;
      ob = j4;
      v = 0.0f;
      v += a[oa] * b[ob]; oa+=4;ob++;
      v += a[oa] * b[ob]; oa+=4;ob++;
      v += a[oa] * b[ob]; oa+=4;ob++;
      v += a[oa] * b[ob];

      t[i+j4] = v;

   }

   gl11_matrix_load(d, t);
}
