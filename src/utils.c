/**
 ******************************************************************************
 * @file utils.c
 * @version 1.0.1
 * @date 2020-09-01
 * @copyright Copyright © 2020 by University of Luxembourg.
 * @author Developed at SnT APSIA by: H. Cheng, J. Groszschaedl, and J. Tian.
 *
 * @brief C source file of utility functions.
 *
 * @details
 * This file contains utility functions such as radix-conversion functions and
 * a print function.
 ******************************************************************************
 */

#include "gfparith.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>  // srandom, rand
#include <string.h>


/**
 * @brief Generation of a pseudo-randon 32-bit integer.
 *
 * @details
 * Generates a pseudo-randon 32-bit integer using the rand() function of the
 * standard C library (only used for the generation of test vectors).
 */
uint32_t mpi29_rand32(void)
{
  uint32_t r;

  r = (rand() & 0x7FFF);
  r <<= 15;
  r |= (rand() & 0x7FFF);
  r <<= 15;
  r |= (rand() & 0x7FFF);

  return r;
}


/**
 * @brief Conversion from mpi32 to mpi29.
 *
 * @details
 * Convert a multi-precision integer that is given as an array of 32-bit words
 * to an array of 29-bit words.
 *
 * @param r Mpi29 integer
 * @param rlen Length of r
 * @param a Mpi32 integer
 * @param alen Length of a
 */
void mpi29_conv_32to29(uint32_t *r, int rlen, const uint32_t *a, int alen)
{
  uint32_t w0, w1;
  int lbits = 29, rbits = 0, i, j = 0;

  for (i = 0; i < rlen; i++) {
    w0 = (j < alen) ? a[j] : 0;
    w1 = (j + 1 < alen) ? a[j+1] : 0;

    r[i] = w0 >> rbits;
    if (rbits > 3) {
      r[i] |= (w1 << lbits);
    }
    r[i] &= MASK29;
    // printf("i = %02i, j = %02i, ", i, j);
    // printf("lbits = %02i, rbits = %02i\n", lbits, rbits);

    rbits += 29;
    if (rbits >= 32) {
      rbits -= 32;
      j++;
    }
    lbits = 32 - rbits;
  }
}


/**
 * @brief Conversion from mpi29 to mpi32.
 *
 * @details
 * Convert a multi-precision integer that is given as an array of 29-bit words
 * to an array of 32-bit words. Note that 'rlen' can be smaller than 'alen'.
 *
 * @param r Mpi29 integer
 * @param rlen Length of r
 * @param a Mpi32 integer
 * @param alen Length of a
 */
void mpi29_conv_29to32(uint32_t *r, int rlen, const uint32_t *a, int alen)
{
  uint32_t w0, w1, w2;
  int lbits = 29, rbits = 0, i, j = 0;

  for (i = 0; i < rlen; i++) {
    w0 = (j < alen) ? a[j] : 0;
    w1 = (j + 1 < alen) ? a[j+1] : 0;
    w2 = (j + 2 < alen) ? a[j+2] : 0;

    r[i] = (w1 << lbits) | (w0 >> rbits);
    if (lbits < 3) {
      r[i] |= (w2 << (29 + lbits));
    }
    // printf("i = %02i, j = %02i, ", i, j);
    // printf("lbits = %02i, rbits = %02i\n", lbits, rbits);

    rbits += 32;
    while (rbits >= 29) {
      rbits -= 29;
      j++;
    }
    lbits = 29 - rbits;
  }
}


/**
 * @brief Print a multiprecision integer.
 *
 * @details
 * Print a multiprecision integer in an ordinary order with an string ahead.
 *
 * @param c Arbitry string
 * @param a Multiprecision integer
 * @param len Length of a
 */
void mpi29_print(const char *c, const uint32_t *a, int len)
{
  int i;

  if ((c != NULL) && (strlen(c) > 0)) {
    printf("%s", c);
  }
  for (i = len - 1; i > 0; i--) {
    printf("%08X", a[i]);
  }
  printf("%08X\n", a[0]);
}
