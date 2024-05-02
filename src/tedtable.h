/**
 ******************************************************************************
 * @file tedtable.h
 * @version 1.0.1
 * @date 2020-09-01
 * @copyright Copyright © 2020 by University of Luxembourg.
 * @author Developed at SnT APSIA by: H. Cheng, J. Groszschaedl, and J. Tian.
 *
 * @brief Header file of load function for pre-computed table.
 * 
 * @details
 * This file defines a struct for points in extended affine coordinates (in 
 * Duif representation) and contains function prototypes for (4*1)-way 
 * parallel loading of points from a pre-computed table containing multiples
 * of the base point.
******************************************************************************
 */

#ifndef _TEDTABLE_H
#define _TEDTABLE_H

#include <stdint.h>
#include "moncurve.h"

// Point of look-up table in Duif representation, i.e. in extended affine 
// representation of the form [(y+x)/2, (y-x)/2, d*x*y] 
typedef struct table_point {
  uint64_t x[4];  // Duif (y+x)/2 coordinate
  uint64_t y[4];  // Duif (y-x)/2 coordinate
  uint64_t z[4];  // Duif d*x*y coordinate
} LutPoint;

// function prototypes

void lut_conv_coor2mpi29_avx2(__m256i *r, const __m256i *a);
void ted_point_query_table_avx2(ProPoint *r, const int pos, const __m256i b);

#endif
