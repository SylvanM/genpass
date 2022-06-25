//
//  drng.h
//  genpass
//
//  Created by Sylvan Martin on 8/2/20.
//  Copyright © 2020 Sylvan Martin. All rights reserved.
//

/*
 * If the computer's processor has the RDRAND instruction, then we will use that instead of Apple's CSRNG
 */

#ifndef drng_h
#define drng_h

#include <stdio.h>
#include <immintrin.h>

/**
 * Generates random bits that will be treated as a byte array, but the length will be treated as 64 bit words
 */
void rdrand_bytes(unsigned char *bytes, size_t len);

/**
 * Generates a random word
 */
int rdrand(unsigned long *rand);

/**
 * Generates a random byte
 */
int rdrand_byte(unsigned char *rand);

#endif /* drng_h */
