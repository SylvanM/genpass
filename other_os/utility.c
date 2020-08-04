//
//  utility.c
//  genpass
//
//  Created by Sylvan Martin on 8/3/20.
//  Copyright © 2020 Sylvan Martin. All rights reserved.
//

#include "utility.h"

void error(char *description, int ecode) {
    printf("Error: %s\n", description);
    advertise_usage();
    exit(ecode);
}

void advertise_usage() {
    printf("Use genpass -h or genpass --help to see usage\n");
}

void print_usage() {

    printf("genpass is used to generate random passwords or random numbers using Apple's secure random number generator (or so they say)");
    printf("\n");
    printf(" -- Password Generation -- ");
    printf("\n");
    printf("Running genpass with no arguments passed in will give you a random password, 16 characters in length. Possible characters include any non-control character in 7-bit ASCII. For example:");
    printf("\n");
    printf("\t$ genpass");
    printf("\tEfwL:&q\"wx\\QPcN7");
    printf("\n");
    printf("To specify a desired password length, pass in the lengh you want after the call to genpass. For example:");
    printf("\n");
    printf("\tgenpass 12");
    printf("\n");
    printf("Will generate a random password 12 characters in length.");
    printf("\n");
    printf("If you want to only generate a password with alphanumeric characters, pass the -a or --alphanumeric argument.");
    printf("\n");
    printf("\tgenpass -a 12");
    printf("\n");
    printf("Some sites and services prohibit the use of certain characters in your password. In order to tell genpass to not include specific characters, list all the illegal characters in a single argument following the '-x' or '--except' option. For example:");
    printf("\n");
    printf("\tgenpass -x ~_/?!");
    printf("\n");
    printf("Will give you a password that does not contain a '~', '_', '/', '?', or '!'. If you want to specify the length of the password AND illegal characters, you must put the length before the illegal characters. This is done so that we don't mistake the length for one of the characters you don't want to see. For example:");
    printf("\n");
    printf("\tgenpass 12 -x ~_/?!");
    printf("\n");
    printf("Will give you a 12 digit character without any of those characters.");
    printf("\n");
    printf("\n");
    printf(" -- Random Number Generation -- ");
    printf("\n");
    printf("To generate a random number instead of a password, pass the '-n' or '--number' flag:");
    printf("\n");
    printf("\t$ genpass -n");
    printf("\t48534859");
    printf("\n");
    printf("The number will be an integer that can be represented by your machine's word length. On most modern machines, that's 64 bits, so you'll get a number between 0 and 2^64 - 1.");
    printf("\n");
    printf("You can also specify a range the random number should be in. Like before, the bounds [a, b] (where a < b) of this range must both be numbers that fit into one machine word (typically 64 bits). For example:");
    printf("\n");
    printf("\t$ genpass -n 1 10 # generates a random number between 1 and 10, inclusive");
    printf("\t6");

}