/******************************************************************************
 *    (c)2008-2010 Broadcom Corporation
 *
 * This program is the proprietary software of Broadcom Corporation and/or its licensors,
 * and may only be used, duplicated, modified or distributed pursuant to the terms and
 * conditions of a separate, written license agreement executed between you and Broadcom
 * (an "Authorized License").  Except as set forth in an Authorized License, Broadcom grants
 * no license (express or implied), right to use, or waiver of any kind with respect to the
 * Software, and Broadcom expressly reserves all rights in and to the Software and all
 * intellectual property rights therein.  IF YOU HAVE NO AUTHORIZED LICENSE, THEN YOU
 * HAVE NO RIGHT TO USE THIS SOFTWARE IN ANY WAY, AND SHOULD IMMEDIATELY
 * NOTIFY BROADCOM AND DISCONTINUE ALL USE OF THE SOFTWARE.
 *
 * Except as expressly set forth in the Authorized License,
 *
 * 1.     This program, including its structure, sequence and organization, constitutes the valuable trade
 * secrets of Broadcom, and you shall use all reasonable efforts to protect the confidentiality thereof,
 * and to use this information only in connection with your use of Broadcom integrated circuit products.
 *
 * 2.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
 * AND WITH ALL FAULTS AND BROADCOM MAKES NO PROMISES, REPRESENTATIONS OR
 * WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT TO
 * THE SOFTWARE.  BROADCOM SPECIFICALLY DISCLAIMS ANY AND ALL IMPLIED WARRANTIES
 * OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR PURPOSE,
 * LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION
 * OR CORRESPONDENCE TO DESCRIPTION. YOU ASSUME THE ENTIRE RISK ARISING OUT OF
 * USE OR PERFORMANCE OF THE SOFTWARE.
 *
 * 3.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL BROADCOM OR ITS
 * LICENSORS BE LIABLE FOR (i) CONSEQUENTIAL, INCIDENTAL, SPECIAL, INDIRECT, OR
 * EXEMPLARY DAMAGES WHATSOEVER ARISING OUT OF OR IN ANY WAY RELATING TO YOUR
 * USE OF OR INABILITY TO USE THE SOFTWARE EVEN IF BROADCOM HAS BEEN ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGES; OR (ii) ANY AMOUNT IN EXCESS OF THE AMOUNT
 * ACTUALLY PAID FOR THE SOFTWARE ITSELF OR U.S. $1, WHICHEVER IS GREATER. THESE
 * LIMITATIONS SHALL APPLY NOTWITHSTANDING ANY FAILURE OF ESSENTIAL PURPOSE OF
 * ANY LIMITED REMEDY.
 *
 * $brcm_Workfile: $
 * $brcm_Revision: $
 * $brcm_Date: $
 *
 * Module Description:
 *
 * Revision History:
 *
 * $brcm_Log: $
 *
 *****************************************************************************/

#include <string.h>
#include <math.h>

#include "esutil.h"

void esTranslate(ESMatrix *result, float tx, float ty, float tz)
{
	result->m[3][0] += (result->m[0][0] * tx + result->m[1][0] * ty + result->m[2][0] * tz);
	result->m[3][1] += (result->m[0][1] * tx + result->m[1][1] * ty + result->m[2][1] * tz);
	result->m[3][2] += (result->m[0][2] * tx + result->m[1][2] * ty + result->m[2][2] * tz);
	result->m[3][3] += (result->m[0][3] * tx + result->m[1][3] * ty + result->m[2][3] * tz);
}

void esScale(ESMatrix *result, float sx, float sy, float sz)
{
	result->m[0][0] *= sx;
	result->m[0][1] *= sx;
	result->m[0][2] *= sx;
	result->m[0][3] *= sx;

	result->m[1][0] *= sy;
	result->m[1][1] *= sy;
	result->m[1][2] *= sy;
	result->m[1][3] *= sy;

	result->m[2][0] *= sz;
	result->m[2][1] *= sz;
	result->m[2][2] *= sz;
	result->m[2][3] *= sz;
}

void esMatrixMultiply(ESMatrix *result, ESMatrix *srcA, ESMatrix *srcB)
{
	ESMatrix tmp;
	int i;

	for (i=0; i<4; i++)
	{
		tmp.m[i][0] =	(srcA->m[i][0] * srcB->m[0][0]) +
						(srcA->m[i][1] * srcB->m[1][0]) +
						(srcA->m[i][2] * srcB->m[2][0]) +
						(srcA->m[i][3] * srcB->m[3][0]) ;

		tmp.m[i][1] =	(srcA->m[i][0] * srcB->m[0][1]) +
						(srcA->m[i][1] * srcB->m[1][1]) +
						(srcA->m[i][2] * srcB->m[2][1]) +
						(srcA->m[i][3] * srcB->m[3][1]) ;

		tmp.m[i][2] =	(srcA->m[i][0] * srcB->m[0][2]) +
						(srcA->m[i][1] * srcB->m[1][2]) +
						(srcA->m[i][2] * srcB->m[2][2]) +
						(srcA->m[i][3] * srcB->m[3][2]) ;

		tmp.m[i][3] =	(srcA->m[i][0] * srcB->m[0][3]) +
						(srcA->m[i][1] * srcB->m[1][3]) +
						(srcA->m[i][2] * srcB->m[2][3]) +
						(srcA->m[i][3] * srcB->m[3][3]) ;
	}
	memcpy(result, &tmp, sizeof(ESMatrix));
}

void esRotate(ESMatrix *result, float angle, float x, float y, float z)
{
	float sinAngle, cosAngle;
	float mag = sqrtf(x * x + y * y + z * z);

	sinAngle = sinf(angle * (float)M_PI / 180.0f);
	cosAngle = cosf(angle * (float)M_PI / 180.0f);
	if (mag > 0.0f)
	{
		float xx, yy, zz, xy, yz, zx, xs, ys, zs;
		float oneMinusCos;
		ESMatrix rotMat;

		x /= mag;
		y /= mag;
		z /= mag;

		xx = x * x;
		yy = y * y;
		zz = z * z;
		xy = x * y;
		yz = y * z;
		zx = z * x;
		xs = x * sinAngle;
		ys = y * sinAngle;
		zs = z * sinAngle;
		oneMinusCos = 1.0f - cosAngle;

		rotMat.m[0][0] = (oneMinusCos * xx) + cosAngle;
		rotMat.m[1][0] = (oneMinusCos * xy) - zs;
		rotMat.m[2][0] = (oneMinusCos * zx) + ys;
		rotMat.m[3][0] = 0.0F;

		rotMat.m[0][1] = (oneMinusCos * xy) + zs;
		rotMat.m[1][1] = (oneMinusCos * yy) + cosAngle;
		rotMat.m[2][1] = (oneMinusCos * yz) - xs;
		rotMat.m[3][1] = 0.0F;

		rotMat.m[0][2] = (oneMinusCos * zx) - ys;
		rotMat.m[1][2] = (oneMinusCos * yz) + xs;
		rotMat.m[2][2] = (oneMinusCos * zz) + cosAngle;
		rotMat.m[3][2] = 0.0F;

		rotMat.m[0][3] = 0.0F;
		rotMat.m[1][3] = 0.0F;
		rotMat.m[2][3] = 0.0F;
		rotMat.m[3][3] = 1.0F;

		esMatrixMultiply(result, &rotMat, result);
	}
}

void esMatrixLoadIdentity(ESMatrix *result)
{
	memset(result, 0x0, sizeof(ESMatrix));
	result->m[0][0] = 1.0f;
	result->m[1][1] = 1.0f;
	result->m[2][2] = 1.0f;
	result->m[3][3] = 1.0f;
}

void esFrustum(ESMatrix *result, float left, float right, float bottom, float top, float nearZ, float farZ)
{
	float deltaX = right - left;
	float deltaY = top - bottom;
	float deltaZ = farZ - nearZ;
	ESMatrix frust;

	if ((nearZ <= 0.0f) || (farZ <= 0.0f) ||
		(deltaX <= 0.0f) || (deltaY <= 0.0f) || (deltaZ <= 0.0f))
		return;

	frust.m[0][0] = 2.0f * nearZ / deltaX;
	frust.m[0][1] = frust.m[0][2] = frust.m[0][3] = 0.0f;

	frust.m[1][1] = 2.0f * nearZ / deltaY;
	frust.m[1][0] = frust.m[1][2] = frust.m[1][3] = 0.0f;

	frust.m[2][0] = (right + left) / deltaX;
	frust.m[2][1] = (top + bottom) / deltaY;
	frust.m[2][2] = -(nearZ + farZ) / deltaZ;
	frust.m[2][3] = -1.0f;

	frust.m[3][2] = -2.0f * nearZ * farZ / deltaZ;
	frust.m[3][0] = frust.m[3][1] = frust.m[3][3] = 0.0f;

	esMatrixMultiply(result, &frust, result);
}

void esPerspective(ESMatrix *result, float fovy, float aspect, float zNear, float zFar)
{
	ESMatrix m;
	float sine, cotangent, deltaZ;
	float radians = fovy / 2.0f * (float)M_PI / 180.0f;

	deltaZ = zFar - zNear;
	sine = sinf(radians);
	if ((deltaZ == 0) || (sine == 0) || (aspect == 0))
	{
		return;
	}
	cotangent = cosf(radians) / sine;

	m.m[0][0] = cotangent / aspect; m.m[0][1] =                          0; m.m[0][2] =                          0; m.m[0][3] =  0;
	m.m[1][0] =                  0; m.m[1][1] =                  cotangent; m.m[1][2] =                          0; m.m[1][3] =  0;
	m.m[2][0] =                  0; m.m[2][1] =                          0; m.m[2][2] =   -(zFar + zNear) / deltaZ; m.m[2][3] = -1;
	m.m[3][0] =                  0; m.m[3][1] =                          0; m.m[3][2] = -2 * zNear * zFar / deltaZ; m.m[3][3] =  0;

	esMatrixMultiply(result, &m, result);
}

void esOrtho(ESMatrix *result, float left, float right, float bottom, float top, float nearZ, float farZ)
{
	float deltaX = right - left;
	float deltaY = top - bottom;
	float deltaZ = farZ - nearZ;
	ESMatrix ortho;

	if ((deltaX == 0.0f) || (deltaY == 0.0f) || (deltaZ == 0.0f))
		return;

	esMatrixLoadIdentity(&ortho);
	ortho.m[0][0] = 2.0f / deltaX;
	ortho.m[3][0] = -(right + left) / deltaX;
	ortho.m[1][1] = 2.0f / deltaY;
	ortho.m[3][1] = -(top + bottom) / deltaY;
	ortho.m[2][2] = -2.0f / deltaZ;
	ortho.m[3][2] = -(nearZ + farZ) / deltaZ;

	esMatrixMultiply(result, &ortho, result);
}

int esInverse(ESMatrix * in, ESMatrix * out)
{
	float det_1;
	float abssum, temp;

#  define PRECISION_LIMIT (1.0e-15)

	/*
	Calculate the determinant of submatrix A and determine if the
	the matrix is singular.
	*/
	temp =  in->m[0][0] * in->m[1][1] * in->m[2][2];
	det_1 = temp; abssum = fabsf(temp);
	temp =  in->m[1][0] * in->m[2][1] * in->m[0][2];
	det_1 += temp; abssum += fabsf(temp);
	temp =  in->m[2][0] * in->m[0][1] * in->m[1][2];
	det_1 += temp; abssum += fabsf(temp);
	temp = -in->m[2][0] * in->m[1][1] * in->m[0][2];
	det_1 += temp; abssum += fabsf(temp);
	temp = -in->m[1][0] * in->m[0][1] * in->m[2][2];
	det_1 += temp; abssum += fabsf(temp);
	temp = -in->m[0][0] * in->m[2][1] * in->m[1][2];
	det_1 += temp; abssum += fabsf(temp);

	/* Is the submatrix A singular? */
	if ((det_1 == 0.0f) || (fabsf(det_1 / abssum) < PRECISION_LIMIT))
	{
		/* Matrix M has no inverse */
		return 0;
	}
	else
	{
		/* Calculate inverse(A) = adj(A) / det(A) */
		det_1 = 1.0f / det_1;
		out->m[0][0] =   (in->m[1][1] * in->m[2][2] - in->m[2][1] * in->m[1][2]) * det_1;
		out->m[1][0] = - (in->m[0][1] * in->m[2][2] - in->m[2][1] * in->m[0][2]) * det_1;
		out->m[2][0] =   (in->m[0][1] * in->m[1][2] - in->m[1][1] * in->m[0][2]) * det_1;
		out->m[0][1] = - (in->m[1][0] * in->m[2][2] - in->m[2][0] * in->m[1][2]) * det_1;
		out->m[1][1] =   (in->m[0][0] * in->m[2][2] - in->m[2][0] * in->m[0][2]) * det_1;
		out->m[2][1] = - (in->m[0][0] * in->m[1][2] - in->m[1][0] * in->m[0][2]) * det_1;
		out->m[0][2] =   (in->m[1][0] * in->m[2][1] - in->m[2][0] * in->m[1][1]) * det_1;
		out->m[1][2] = - (in->m[0][0] * in->m[2][1] - in->m[2][0] * in->m[0][1]) * det_1;
		out->m[2][2] =   (in->m[0][0] * in->m[1][1] - in->m[1][0] * in->m[0][1]) * det_1;

		/* Calculate -C * inverse(A) */
		out->m[3][0] = - (in->m[0][3] * out->m[0][0] +
						  in->m[1][3] * out->m[1][0] +
						  in->m[2][3] * out->m[2][0]);
		out->m[3][1] = - (in->m[0][3] * out->m[0][1] +
						  in->m[1][3] * out->m[1][1] +
						  in->m[2][3] * out->m[2][1]);
		out->m[3][2] = - (in->m[0][3] * out->m[0][2] +
						  in->m[1][3] * out->m[1][2] +
						  in->m[2][3] * out->m[2][2]);

		/* Fill in last column */
		out->m[0][3] = out->m[1][3] = out->m[2][3] = 0.0;
		out->m[3][3] = 1.0;

		return 1;
	}
}
