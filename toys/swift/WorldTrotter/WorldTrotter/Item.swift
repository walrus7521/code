//
//  Item.swift
//  WorldTrotter
//
//  Created by Bart Bartel on 10/30/16.
//  Copyright © 2016 Bart Bartel. All rights reserved.
//

import UIKit

class Item: NSObject {
    var name: String
    var valueInPoints: Int
    var serialNumber: String?
    let dateCreated: NSDate
    let itemKey: String
    
    init(name: String, serialNumber: String?, valueInDollars: Int) {
        self.name = name
        self.valueInPoints = valueInDollars
        self.serialNumber = serialNumber
        self.dateCreated = NSDate()
        self.itemKey = NSUUID().uuidString
        
        super.init()
    }
 
    //convenience init(name: String) {
    //    self.init(name: name, serialNumber: nil, valueInDollars: nil)
    //}
    
    convenience init(random: Bool = false) {
        if random {
            let adjectives = ["Easy", "Medium", "Difficult"]
            let nouns = ["List", "Hash", "Graph", "Tree"]
        
            var idx = arc4random_uniform(UInt32(adjectives.count))
            let randomAdjective = adjectives[Int(idx)]
        
            idx = arc4random_uniform(UInt32(nouns.count))
            let randomNoun = nouns[Int(idx)]
        
            let randomName = "\(randomAdjective) \(randomNoun)"
            let randomValue = Int(arc4random_uniform(100))
            let randomSerialNumber = NSUUID().uuidString.components(separatedBy: "-").first!
        
            self.init(name: randomName,
                      serialNumber: randomSerialNumber,
                      valueInDollars: randomValue)
        } else {
            self.init(name: "", serialNumber: nil, valueInDollars: 0)
        }
    }
    
}


