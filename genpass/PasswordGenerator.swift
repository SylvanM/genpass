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
     *      - password `inout String` to hold the resulting password
     *
     * - Returns: Any error that occured
     */
    @discardableResult
    func generatePassword(_ password: inout String) -> Int32 {
        
        var bytes = [UInt8](repeating: 0, count: passwordLength)
        
        let error = SecRandomCopyBytes(kSecRandomDefault, passwordLength, &bytes)
        
        password = ""
        
        for i in 0..<bytes.count {
            var character: Character { Character(UnicodeScalar( (bytes[i] % 90) + 32 )) }
            
            while forbiddenCharacters.contains(character) {
                // get a new character!
                _ = SecRandomCopyBytes(kSecRandomDefault, 1, &bytes[i])
            }
            
            password.append(character)
        }
        
        return error
        
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
    
}
