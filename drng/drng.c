//
//  drng.c
//  genpass
//
//  Created by Sylvan Martin on 8/2/20.
//  Copyright © 2020 Sylvan Martin. All rights reserved.
//

#include "drng.h"

void rdrand_bytes(unsigned char *bytes, size_t len) {

    size_t i;
    unsigned long *words = (unsigned long *) bytes;

    for ( i = 0; i < len; ++i )
        rdrand(words++);

}

int rdrand(unsigned long *rand) {
    unsigned char ok;

    _rdrand64_step(<#unsigned long long *__p#>)

    return (int) ok;

}

int rdrand_byte(unsigned char *rand) {
    return rdrand( (unsigned long *) rand );
}
