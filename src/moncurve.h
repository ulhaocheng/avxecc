/**
 ******************************************************************************
 * @file moncurve.h
 * @version 1.0.1
 * @date 2020-09-01
 * @copyright Copyright © 2020 by University of Luxembourg.
 * @author Developed at SnT APSIA by: H. Cheng, J. Groszschaedl, and J. Tian.
 *
 * @brief Header file of point arithmetic on Montgomery curve.
 *
 * @details 
 * This file defines a struct for points in projective coordinates and contains
 * function prototypes for (4*1)-way parallel point operations on a Montgomery 
 * curve.
 ******************************************************************************
 */

#ifndef _MONCURVE_H
#define _MONCURVE_H

#include "gfparith.h"

// projective points with coordinates [x, y, z] 
typedef struct projective_point {
  __m256i x[NWORDS];  // projective x coordinate
  __m256i y[NWORDS];  // projective y coordinate
  __m256i z[NWORDS];  // projective z coordinate
} ProPoint;

// function prototypes
void mon_ladder_step_avx2(ProPoint *p, ProPoint *q, const __m256i *xd);
void mon_mul_varbase_avx2(__m256i *r, const __m256i *k, const __m256i *x);
void mon_mul_fixbase_avx2(__m256i *r, const __m256i *k);

#endif
