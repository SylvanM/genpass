//
//  Convenience.swift
//  genpass
//
//  Created by Sylvan Martin on 7/30/20.
//  Copyright © 2020 Sylvan Martin. All rights reserved.
//

import Foundation

extension Array {
    
    /**
     * Safely returns a value of an array. If the value does not exist, it just returns nil. Just for convenience.
     *
     * I know this probably uses more code than it saves, but oh well.
     */
    subscript(safe index: Int) -> Element? {
        get { self.indices.contains(index) ? self[index] : nil }
    }
    
}
