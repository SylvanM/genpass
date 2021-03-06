//
//  genpass.c
//  genpass
//
//  Created by Sylvan Martin on 8/3/20.
//  Copyright © 2020 Sylvan Martin. All rights reserved.
//

#include "genpass.h"

int genpass(unsigned char *pass, int passlen, unsigned char *forbidden_chars, int alphanum) {
    // find how many words we need to generate
    int i, wordcount = (passlen / sizeof(size_t)) + (passlen % sizeof(size_t) ? 1 : 0);
    rdrand_bytes(pass, wordcount);

    if (alphanum) {

        for ( i = 0; i < passlen; ++i ) {
            pass[i] %= 62;

            if (pass[i] < 10) {
                pass[i] += 48;
            } else if (pass[i] < 36) {
                pass[i] += 55;
            } else {
                pass[i] += 61;
            }
        }

    } else {

        for ( i = 0; i < passlen; ++i ) {
            while (isIllegal(BYTE_TO_ASCII_CHAR(pass[i]), forbidden_chars))
                rdrand_byte(pass + i); // should I just use &pass[i] instead?

            pass[i] %= 90;
            pass[i] += 33;
        }

    }

    // null terminate string
    pass[passlen] = 0;

    return 1;

}

int randnum(unsigned long *num, unsigned long lower, unsigned long upper) {

    int err = rdrand(num);

    *num %= upper - lower + 1;
    *num += lower;

    return err;

}

int isIllegal(unsigned char c, unsigned char *forbidden_chars) {
    for ( ; *forbidden_chars != 0; ++forbidden_chars )
        if (c == *forbidden_chars)
            return 1;
    return 0;
}
