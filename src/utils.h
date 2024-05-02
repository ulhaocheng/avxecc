/**
 ******************************************************************************
 * @file utils.h
 * @version 1.0.1
 * @date 2020-09-01
 * @copyright Copyright © 2020 by University of Luxembourg.
 * @author Developed at SnT APSIA by: H. Cheng, J. Groszschaedl, and J. Tian.
 *
 * @brief Header file of utility functions.
 *
 * @details 
 * This file contains function prototypes of utility functions such as
 * radix-conversion functions and a print function.
 ******************************************************************************
 */

#ifndef _UTILS_H
#define _UTILS_H

#include <stdint.h>

// function prototypes

uint32_t mpi29_rand32(void);
void mpi29_conv_32to29(uint32_t *r, int rlen, const uint32_t *a, int alen);
void mpi29_conv_29to32(uint32_t *r, int rlen, const uint32_t *a, int alen);
void mpi29_print(const char *c, const uint32_t *a, int len);

#endif
