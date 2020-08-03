//
//  PasswordGenerator.swift
//  genpass
//
//  Created by Sylvan Martin on 7/9/20.
//  Copyright © 2020 Sylvan Martin. All rights reserved.
//

import Foundation

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
        
        rdrand_bytes(byteBuffer, wordCount)
        
        var bytes = Array( UnsafeMutableBufferPointer<UInt8>(start: byteBuffer, count: byteCount) )
        
        
        var characters: [Character] {
            bytes.map {
                Character(UnicodeScalar( ($0 % 90) + 32 ))
            }
        }

        // make sure that, if we made any illegal characters, we fix that.
        if forbiddenCharacters.count != 0 {
            for i in 0..<passwordLength {
                while forbiddenCharacters.contains(characters[i]) {
                    rdrand_byte(&bytes[i])
                }
            }
        }
        
        password = String(characters[0..<passwordLength])
        
        return 1 // probably should do something better with this
        
    }
    
    /**
     * Generates a random number in a given range
     */
    @discardableResult
    func generateNumber(_ bounds: ClosedRange<UInt>?, number: inout UInt) -> Int32 {
        
        let error = rdrand(&number)
        
        if let range = bounds {
            number %= (range.upperBound - range.lowerBound) + 1
            number += range.lowerBound
        }
        
        return error
        
    }
    
}
