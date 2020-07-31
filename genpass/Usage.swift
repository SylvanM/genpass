//
//  Usage.swift
//  genpass
//
//  Created by Sylvan Martin on 7/30/20.
//  Copyright © 2020 Sylvan Martin. All rights reserved.
//

import Foundation


func printUsage() {
    
    print("genpass is used to generate random passwords or random numbers using Apple's secure random number generator (or so they say)")
    print()
    print(" -- Password Generation -- ")
    print()
    print("Running genpass with no arguments passed in will give you a random password, 16 characters in length. Possible characters include any non-control character in 7-bit ASCII. For example:")
    print()
    print("\t$ genpass")
    print("\tEfwL:&q\"wx\\QPcN7")
    print()
    print("To specify a desired password length, pass in the lengh you want after the call to genpass. For example:")
    print()
    print("\tgenpass 12")
    print()
    print("Will generate a random password 12 characters in length.")
    print()
    print("Some sites and services prohibit the use of certain characters in your password. In order to tell genpass to not include specific characters, list all the illegal characters following the '-x' or '--except' option. For example:")
    print()
    print("\tgenpass -x ~ _ / ? !")
    print()
    print("Will give you a password that does not contain a '~', '_', '/', '?', or '!'. If you want to specify the length of the password AND illegal characters, you must put the length before the illegal characters. This is done so that we don't mistake the length for one of the characters you don't want to see. For example:")
    print()
    print("\tgenpass 12 -x ~ _ / ? !")
    print()
    print("Will give you a 12 digit character without any of those characters.")
    print()
    print()
    print(" -- Random Number Generation -- ")
    print()
    print("To generate a random number instead of a password, pass the '-n' or '--number' flag:")
    print()
    print("\t$ genpass -n")
    print("\t48534859")
    print()
    print("The number will be an integer that can be represented by your machine's word length. On most modern machines, that's 64 bits, so you'll get a number between 0 and 2^64 - 1.")
    print()
    print("You can also specify a range the random number should be in. Like before, the bounds [a, b] (where a < b) of this range must both be numbers that fit into one machine word (typically 64 bits). For example:")
    print()
    print("\t$ genpass -n 1 10 # generates a random number between 1 and 10, inclusive")
    print("\t6")
    
}
