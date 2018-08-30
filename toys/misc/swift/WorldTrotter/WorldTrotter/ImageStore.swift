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
        
        // create full URL for image
        let imageURL = imageURLForKey(key: key)
        // turn image into JPEG data
        if let data = UIImageJPEGRepresentation(image, 0.5) {
            // write it to full URL
            //data.write(to: imageURL, options: true)
            do {
                try data.write(to: imageURL, options: .atomic)
            } catch let writeError {
                print("Error saving image to disk: \(writeError)")
            }
        }
        
    }
    
    func imageURLForKey(key: String) -> URL {
        let documentsDirecories =
            FileManager.default.urls(for: .documentDirectory,
                                            in: .userDomainMask)
        let documentDirectory = documentsDirecories.first!
        return documentDirectory.appendingPathComponent(key) as URL
    }
    
    func imageForKey(key: String) -> UIImage? {
        //return cache.object(forKey: key as AnyObject) as? UIImage
        
        if let existingImage = cache.object(forKey: key as AnyObject) as? UIImage {
            return existingImage
        }
        
        let imageURL = imageURLForKey(key: key)
        guard let imageFromDisk = UIImage(contentsOfFile: imageURL.path) else {
            return nil
        }
        
        cache.setObject(imageFromDisk, forKey: key as AnyObject)
        
        return imageFromDisk
        
    }
    
    func deleteImageForKey(key: String) {
        cache.removeObject(forKey: key as AnyObject)
        
        let imageURL = imageURLForKey(key: key)
        do {
             try FileManager.default.removeItem(at: imageURL)
        } catch let deleteError {
            print("Error removing image from disk: \(deleteError)")
        }
    
    }
    
}
