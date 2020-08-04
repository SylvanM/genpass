//
//  genpass.h
//  genpass
//
//  Created by Sylvan Martin on 8/3/20.
//  Copyright © 2020 Sylvan Martin. All rights reserved.
//

#ifndef genpass_h
#define genpass_h

#include "../drng/drng.h"

#define BYTE_TO_ASCII_CHAR(b) ( (b % 90) + 33 )

/**
 * Generates a random password of a specified length
 */
int genpass(unsigned char *pass, int passlen, unsigned char *forbidden_chars, int alphanum);

/**
 * Generates a random number in a given range
 */
int randnum(unsigned long *num, unsigned long lower, unsigned long upper);

/**
 * Checks whether a character is forbidden
 */
int isIllegal(unsigned char c, unsigned char *forbidden_chars);

#endif