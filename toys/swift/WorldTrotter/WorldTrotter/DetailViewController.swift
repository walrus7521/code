//
//  DetailViewController.swift
//  WorldTrotter
//
//  Created by Bart Bartel on 11/2/16.
//  Copyright © 2016 Bart Bartel. All rights reserved.
//

import UIKit

class DetailViewController: UIViewController, UITextFieldDelegate {
    
    @IBOutlet var nameField: UITextField!
    @IBOutlet var serialField: UITextField!
    @IBOutlet var valueField: UITextField!
    @IBOutlet var dateLabel: UILabel!
    @IBOutlet var imageView: UIImageView!

    @IBAction func backgroundTapped(_ sender: UITapGestureRecognizer) {
        view.endEditing(true)
    }
    
    @IBAction func takePicture(_ sender: UIBarButtonItem) {
    }
    
    // property observer for item
    var item: Item! {
        didSet {
            navigationItem.title = "Dude!! " + item.name
        }
    }
    
    
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
        
        print("Detail: viewWillAppear")
        
        nameField.text = item.name
        serialField.text = item.serialNumber
        let val = item.valueInPoints as NSNumber
        valueField.text = numberFormatter.string(from: val)
        dateLabel.text = DateFormatter.localizedString(from: item.dateCreated as Date, dateStyle: .medium,
        timeStyle: .none)
        
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        super.viewWillDisappear(animated)
        
        print("Detail: viewWillDisappear")
        
        // Clear first responder
        view.endEditing(true)
        
        // Save changes to item
        item.name = nameField.text ?? ""
        item.serialNumber = serialField.text
        
        if let valueText = valueField.text,
            let value = numberFormatter.number(from: valueText) {
            item.valueInPoints = value.intValue
        } else{
            item.valueInPoints = 0
        }
    }
    
    func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        textField.resignFirstResponder()
        return true
        
    }
}


