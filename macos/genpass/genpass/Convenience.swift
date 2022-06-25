//
//  Convenience.swift
//  genpass
//
//  Created by Sylvan Martin on 7/30/20.
//  Copyright © 2020 Sylvan Martin. All rights reserved.
//

import Foundation

func warning(_ description: String) {
    // might do something different with this later, like use some unicode tricks to print it in yellow or something
    print(description)
}

func error(_ description: String? = nil, returnValue: Int32 = -1) -> Never {
    if description != nil { print(description!) }
    advertiseUsage()
    exit(returnValue)
}

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
