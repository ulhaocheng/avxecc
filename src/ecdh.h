/**
 ******************************************************************************
 * @file ecdh.h
 * @version 1.0.1
 * @date 2020-09-01
 * @copyright Copyright © 2020 by University of Luxembourg.
 * @author Developed at SnT APSIA by: H. Cheng, J. Groszschaedl, and J. Tian.
 *
 * @brief Header file of ECDH key exchange functions.
 *
 * @details 
 * This file contains function prototypes of the ECDH key-pair generation and
 * the computation of the shared secret.
 ******************************************************************************
 */

#ifndef _KEM_H
#define _KEM_H

#include "gfparith.h"

// function prototypes

void keygen(__m256i *pk, const __m256i *sk);
void sharedsecret(__m256i *ss, const __m256i *ska, const __m256i *pkb);

#endif
