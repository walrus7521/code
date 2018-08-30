//
//  ItemsNavigationController.swift
//  WorldTrotter
//
//  Created by Bart Bartel on 11/3/16.
//  Copyright © 2016 Bart Bartel. All rights reserved.
//

import UIKit

class ItemsNavigationController: UINavigationController
{
  
    override func viewDidLoad() {
        super.viewDidLoad()
        
        print("ItemsNav: Did load")
        
        title = "ItemsNav"
        view.backgroundColor = UIColor.purple // bad bad, don't access views here
    }
    
    
}
