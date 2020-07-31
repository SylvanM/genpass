//
//  main.swift
//  genpass
//
//  Created by Sylvan Martin on 7/9/20.
//  Copyright © 2020 Sylvan Martin. All rights reserved.
//

import Foundation

/*
 * Interpret User's desire
 */

// These are just for my convenience
@inlinable var argc: Int      { Int(CommandLine.argc) }
@inlinable var args: [String] { CommandLine.arguments }

let generator = Generator(excluding: [], ofLength: 16)

if let firstParam = args[safe: 1] {
    
    if firstParam == "-h" || firstParam == "--help" {
        printUsage()
        exit(0)
    }
    
    if firstParam == "-n" || firstParam == "--number" {
        
        // the user has given an option indicating that they want to generate a random number
        
        var range: ClosedRange<UInt>? = nil
        var number: UInt = 0
        
        // the reason I'm doing nested if-let statements is so that I can give the user more information about what went wrong,
        // so I know exactly what condition failed. I know it looks ugly and unclean but I think it's worth the ease of use until I find a better way
        if let lowerBoundString = args[safe: 2] {
            
            if let upperBoundString = args[safe: 3] {
                
                if let lowerBound = UInt(lowerBoundString) {
                    
                    if let upperBound = UInt(upperBoundString) {
                        
                        guard lowerBound < upperBound else {
                            error("Sorry, the lower bound must be less than the upper bound.\n\(lowerBound) is not less than \(upperBound)")
                        }
                        
                        range = lowerBound...upperBound
                        
                    } else {
                        error("Sorry, \(upperBoundString) could not be converted to a \(UInt.bitWidth)-bit unsigned integer.")
                    }
                    
                } else {
                    error("Sorry, \(lowerBoundString) could not be converted to a \(UInt.bitWidth)-bit unsigned integer.")
                }
                
            } else {
                print("No upper bound specified. Ignoring lower bound.")
            }
            
        }

        generator.generateNumber(range, number: &number)
        print(number)
        exit(0)
        
    }
    
    // where we will look for the user specifying illegal characters. This is usually the first parameter, UNLESS the user has entered a password length before it.
    var illegalFlagExpectedIndex = 1
    
    // If the user is specifying a specific password length, then the first parameter should be that length
    if let passwordLength = Int(firstParam) {
        illegalFlagExpectedIndex += 1 // we check the NEXT argument for illegal characters, since this argument is specifying password length
        generator.passwordLength = passwordLength
    }
    
    if let nextParam = args[safe: illegalFlagExpectedIndex] {
        if nextParam == "-x" || nextParam == "--except" {
            
            guard argc >= 2 + illegalFlagExpectedIndex else {
                error("Sorry, you must specify some characters to forbid from being in the password. No characters were specified after \(nextParam) flag.")
            }
            
            generator.forbiddenCharacters = Array(args[1 + illegalFlagExpectedIndex])
            
        } else {
            error("Unrecognized option \(nextParam)")
        }
    }
    
}

var password: String = ""

generator.generatePassword(&password)

print(password)

