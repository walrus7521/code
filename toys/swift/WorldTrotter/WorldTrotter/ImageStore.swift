//
//  ImageStore.swift
//  WorldTrotter
//
//  Created by Bart Bartel on 11/5/16.
//  Copyright © 2016 Bart Bartel. All rights reserved.
//

import UIKit

class ImageStore: NSObject {
    let cache = NSCache<AnyObject, AnyObject>()
    
    func setImage(image: UIImage, forKey key: String) {
        cache.setObject(image, forKey: key as AnyObject)
    }
    
    func imageForKey(key: String) -> UIImage? {
        return cache.object(forKey: key as AnyObject) as? UIImage
    }
    
    func deleteImageForKey(key: String) {
        cache.removeObject(forKey: key as AnyObject)
    }
    
}
