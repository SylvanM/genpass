//
//  main.c
//  genpass
//
//  Created by Sylvan Martin on 8/3/20.
//  Copyright © 2020 Sylvan Martin. All rights reserved.
//

#include <string.h>

#include "utility.h"
#include "genpass.h"

int main(int argc, char const *argv[])
{
    int passlen = 16;
    int alphnum = 0;

    unsigned long num, lower, upper;

    unsigned char *pass;
    unsigned char *forbidden_chars;

    lower = 0;
    upper = ~lower;

    // I. hate. handling. user. input.
    
    if (argc > 1) {

        // if one of them is zero, then we just multiplly them and the output should be 0
        if (strcmp("-h", argv[1]) * strcmp("--help", argv[1]) == 0) {
            print_usage();
            exit(0);
        }

        if (strcmp("-h", argv[1]) * strcmp("--number", argv[1]) == 0) {
            
            if (argc == 4) {

                // I'll add error checking later. Unconveniently, strtoul returns 0 if there is an error, but 0 is a valid value for the range, so I'll have to be creative.
                lower = strtoul(argv[2], NULL, strlen(argv[2]));
                upper = strtoul(argv[2], NULL, strlen(argv[2]));

            }

            randnum(&num, lower, upper);
            exit(0);

        }

    }

    pass = (unsigned char *) malloc(passlen + 1);
    genpass(pass, passlen, forbidden_chars, alphnum);

    printf("%s\n", pass);

    return 0;
}
