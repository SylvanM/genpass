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

    if let passwordLengh = Int(firstParam) {
        
        // if the first argument passed is a number, then treat it as the length of the password that the user wants
        generator.passwordLength = passwordLengh
        
        // now check if the user specified some illegal characters
        
        if let secondParam = args[safe: 2] {
            if secondParam == "-x" || secondParam == "--except" {
                
                // I know this is code repetition, I'll come up with a better fix later
                
                if argc >= 4 {
                    generator.forbiddenCharacters = args[3..<argc].map {
                        guard $0.count == 1 else {
                            print("Must give a list of single characters.")
                            print("\($0) contains more than one character.")
                            print("Sorry, I know you're trying your best. Here's the usage of genpass:")
                            printUsage()
                            exit(-1)
                        }
                        
                        return Character($0)
                    }
                } else {
                    print("It looks like you tried giving the \(firstParam) option, but didn't specify any characters to exclude!")
                    print("That's okay. For future reference, you should list several characters following the \(firstParam) flag that you do not want to see appear in the password.")
                    printUsage()
                    exit(-1)
                }
            }
        }
        
    } else if firstParam == "-n" || firstParam == "--number" {
        
        // the user has given an option indicating that they want to generate a random number
        
        var range: ClosedRange<UInt>? = nil
        var number: UInt = 0
        
        if let lowerBoundString = args[safe: 2], let upperBoundString = args[safe: 3] {
            if let lowerBound = UInt(lowerBoundString), let upperBound = UInt(upperBoundString) {
                range = lowerBound...upperBound
            }
        }

        generator.generateNumber(range, number: &number)
        print(number)
        exit(0)
        
    } else if firstParam == "-x" || firstParam == "--excluding" {
        
        // the user wants us to know that the following characters are FORBIDEN from appearing in the password they are going to generate
        if argc >= 3 {
            generator.forbiddenCharacters = args[2..<argc].map {
                guard $0.count == 1 else {
                    print("Must give a list of single characters.")
                    print("\($0) contains more than one character.")
                    print("Sorry, I know you're trying your best. Here's the usage of genpass:")
                    printUsage()
                    exit(-1)
                }
                
                return Character($0)
            }
        } else {
            print("It looks like you tried giving the \(firstParam) option, but didn't specify any characters to exclude!")
            print("That's okay. For future reference, you should list several characters following the \(firstParam) flag that you do not want to see appear in the password.")
            printUsage()
            exit(-1)
        }
    } else {
        print("Sorry, not sure what \(firstParam) means. Here's the usage:")
        printUsage()
        exit(-1)
    }
    
}


var password: String = ""

generator.generatePassword(&password)

print(password)

