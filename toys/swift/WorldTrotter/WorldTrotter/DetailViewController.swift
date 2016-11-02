//
//  DetailViewController.swift
//  WorldTrotter
//
//  Created by Bart Bartel on 11/2/16.
//  Copyright © 2016 Bart Bartel. All rights reserved.
//

import UIKit

class DetailViewController: UIViewController {
    
    @IBOutlet var nameField: UITextField!
    @IBOutlet var serialField: UITextField!
    @IBOutlet var valueField: UITextField!
    @IBOutlet var dateLabel: UILabel!

    var item: Item!
    
    let numberFormatter: NumberFormatter = {
       let formatter = NumberFormatter()
        formatter.numberStyle = .decimal
        formatter.minimumFractionDigits = 2
        formatter.maximumIntegerDigits = 3
        return formatter
    }()
    
    let dateFormatter: DateFormatter = {
       let formatter = DateFormatter()
        formatter.dateStyle = .medium
        formatter.timeStyle = .none
        return formatter
    }()
    
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        
        nameField.text = item.name
        serialField.text = item.serialNumber
        let val = item.valueInDollars as NSNumber
        valueField.text = numberFormatter.string(from: val)
        dateLabel.text = DateFormatter.localizedString(from: item.dateCreated as Date, dateStyle: .medium,
        timeStyle: .none)
        
    }
}


