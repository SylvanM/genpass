//
//  main.c
//  genpass
//
//  Created by Sylvan Martin on 8/3/20.
//  Copyright © 2020 Sylvan Martin. All rights reserved.
//

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "utility.h"
#include "genpass.h"

int main(int argc, char const *argv[])
{
    int passlen = 16;
    int alphnum = 0;

    // the argument index we expect to see the first option flag, be it -a or -x
    int expectedFlagIndex = 1;

    unsigned long num, lower, upper;

    unsigned char *pass;
    unsigned char *forbidden_chars = { 0 };

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

                if (upper < lower)
                    error("The upper bound must be greater than or equal to the lower bound.", -1);

            }

            randnum(&num, lower, upper);
            printf("%lu\n", num);
            exit(0);

        }

        if ( (passlen = atoi(argv[1])) )
            expectedFlagIndex++;
        else
            passlen = 16;
        
        
        if (expectedFlagIndex < argc) {
            if ( strcmp(argv[expectedFlagIndex], "-a") * strcmp(argv[expectedFlagIndex], "--alphanumeric") == 0 ) {
                alphnum = 1;
            } else if ( strcmp(argv[expectedFlagIndex], "-x") * strcmp(argv[expectedFlagIndex], "--except") == 0 ) {

                if (argc < expectedFlagIndex + 2)
                    error("Please enter some evil characters to exclude.", -1);

                forbidden_chars = (unsigned char *) argv[expectedFlagIndex + 1];
            } else {
                error( "Unrecognized argument.", -1 );
            }
        }
    
    }

    pass = (unsigned char *) malloc(passlen + 1);
    genpass(pass, passlen, forbidden_chars, alphnum);

    printf("%s\n", pass);

    return 0;
}
