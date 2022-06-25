//
//  PasswordGenerator.swift
//  genpass
//
//  Created by Sylvan Martin on 7/9/20.
//  Copyright © 2020 Sylvan Martin. All rights reserved.
//

import Foundation
import CommonCrypto

class Generator {
    
    // MARK: Properties
    
    /**
     * A list of characters that cannot appear in the random password
     */
    var forbiddenCharacters: [Character]
    
    /**
     * The length of the password, in characters. Default is 16
     */
    var passwordLength: Int
    
    /**
     * Wether or not the generated password should only be alphanumeric
     */
    var alphaNumeric: Bool = false
    
    // MARK: Initializers
    
    init(excluding: [Character], ofLength length: Int = 16) {
        forbiddenCharacters = excluding
        passwordLength = length
    }
    
    // MARK: Methods
    
    /**
     * Generates a random password
     *
     * - Parameters:
     *      - password: `inout String` to hold the resulting password
     *
     * - Returns: Any error that occured
     */
    @discardableResult
    func generatePassword(_ password: inout String) -> Int32 {
        
        let operation  = passwordLength.quotientAndRemainder(dividingBy: MemoryLayout<UInt>.size)
        let wordCount  = operation.quotient + (operation.remainder != 0 ? 1 : 0)
        
        let byteCount  = wordCount * MemoryLayout<UInt>.size
        let byteBuffer = UnsafeMutablePointer<UInt8>.allocate(capacity: byteCount)
        
        let err = SecRandomCopyBytes(kSecRandomDefault, byteCount, byteBuffer)
        
        if err != errSecSuccess {
            return err
        }
        
        var bytes = Array( UnsafeMutableBufferPointer<UInt8>(start: byteBuffer, count: byteCount) )
        
        // I'm worreid that my conversion from a byte to a character is not secure.
        // By using the modulo operator some characters would be more likely than others.
        //
        // I can't think of a good way to convert the random data to a valid character
        var characters: [Character] {
            bytes.map {
                
                if alphaNumeric {
                    
                    // we are only choosing between 62 total characters, which is close to 64 characters, so we only care about the last 6 bits of the byte.
                    let bits = $0 % 62
                    
                    // map the 0-61 value to a valid ascii character
                    return Character(UnicodeScalar(
                        bits < 10 ? bits + 48 : ( bits < 36 ? bits + 55 : bits + 61 )
                    ))
                    
                }
                
                return Character(UnicodeScalar( ($0 % 90) + 33 ))
            }
        }

        if !alphaNumeric {
            // make sure that, if we made any illegal characters, we fix that.
            if forbiddenCharacters.count != 0 {
                for i in 0..<passwordLength {
                    while forbiddenCharacters.contains(characters[i]) {
                        generateRandomByte(&bytes[i])
                    }
                }
            }
        }
        
        password = String(characters[0..<passwordLength])
        
        return err 
        
    }
    
    /**
     * Generates a random number in a given range
     */
    @discardableResult
    func generateNumber(_ bounds: ClosedRange<UInt>?, number: inout UInt) -> Int32 {
        
        let error = SecRandomCopyBytes(kSecRandomDefault, MemoryLayout<UInt>.size, &number)
        
        if let range = bounds {
            number %= (range.upperBound - range.lowerBound) + 1
            number += range.lowerBound
        }
        
        return error
        
    }
    
    /**
     * Generates a single random byte
     */
    @discardableResult
    func generateRandomByte(_ result: UnsafeMutablePointer<UInt8>) -> Int32 {
        SecRandomCopyBytes(kSecRandomDefault, 1, result)
    }
    
}
