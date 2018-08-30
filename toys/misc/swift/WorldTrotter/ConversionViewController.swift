//
//  ConversionViewController.swift
//  WorldTrotter
//
//  Created by Bart Bartel on 10/24/16.
//  Copyright © 2016 Bart Bartel. All rights reserved.
//

import UIKit

class ConversionViewController: UIViewController, UITextFieldDelegate {
    

    //var button: UIButton!
    
    //@IBAction func convButton(sender: AnyObject) {
    //    print("convButton pressed")
    //}
    
    
//    func createButton() {
//        let button = UIButton(type: .system)
//        button.frame = CGRect(x: 100.0, y: 100.0, width: 100.0, height: 100.0)
//        //button.setTitle("Button", comment: "Button"), for: .normal)
//        button.backgroundColor = .green
//        button.addTarget(self, action: #selector(buttonAction(sender:)), for: .touchUpInside)
//        view.addSubview(button)
//    }
//    
//    @objc func buttonAction(sender: UIButton) {
//        print("Button pushed")
//    }
    
    
    
//    override func loadView() {
//    }
//    
//    var label: UILabel = UILabel()
//    label.frame = CGRectMake(50, 50, 200, 21)
//    label.backgroundColor = UIColor.blackColor()
//    label.textColor = UIColor.whiteColor()
//    label.textAlignment = NSTextAlignment.Center
//    label.text = "test label"
//    self.view.addSubview(label)
//    
//    var txtField: UITextField = UITextField()
//    txtField.frame = CGRectMake(50, 70, 200, 30)
//    txtField.backgroundColor = UIColor.grayColor()
//    self.view.addSubview(txtField)
//    
    
//    @IBOutlet var celsiusLabel: UILabel!
//    @IBOutlet var textField: UITextField!
//    //var storyboard: UIStoryboard?
//    
//    override func loadView() {
//        
//        let storyboard = UIStoryboard(name: "Main", bundle: nil)
//        let vc = storyboard.instantiateViewController(withIdentifier: "ConversionViewControllerId")
//        
//        //let myVC = UIStoryboard(name: "Main", bundle: nil).instantiateViewController(withIdentifier: "ConversionViewId") as! ConversionViewController
//        
//        
//        self.navigationController!.pushViewController(vc, animated: true)
//        
//        
//        //storyboard = UIStoryboard(name: "Main", bundle: nil)
//        //let initialViewController = storyboard.instantiateViewController(withIdentifier: "ConversionViewController")
//    }
//    
//    
//    
    var celsiusValue: Double? {
        if let value = fahrenheitValue {
            return (value - 32) * (5/9)
        } else {
            return nil
        }
    }
    
    func updateCelsiusLabel() {
        if let value = celsiusValue {
            let locale = NSLocale.current
            let val = value as NSNumber
            let nf = NumberFormatter()
            nf.numberStyle = .decimal
            nf.locale = locale //NSLocale(localeIdentifier: "en_US") as Locale!
            nf.numberStyle = NumberFormatter.Style.currency
            nf.minimumFractionDigits = 0
            nf.maximumFractionDigits = 1
            //celsiusLabel.text = nf.string(from: val)
            let text = nf.string(from: val)
            print("temp: \(text)")
        } else {
            //celsiusLabel.text = "???"

        }
    }
    
    var fahrenheitValue: Double? = 32
    //var fahrenheitValue: Double? {
    //    didSet {
    //        updateCelsiusLabel()
    //    }
    //}
//    
//    @IBAction func fahrenheitFieldEditingChanged(textField: UITextField) {
//        
//        if let text = textField.text, let value = Double(text) {
//            fahrenheitValue = value
//        } else {
//            fahrenheitValue = nil
//        }
//    }
//    
//    @IBAction func dismissKeyboard(sender: AnyObject) {
//        textField.resignFirstResponder()
//    }
//    
//    func textField(_ textField: UITextField,
//                   shouldChangeCharactersIn range: NSRange,
//                   replacementString string: String) -> Bool {
//        //print("Current text: \(textField.text)")
//        //print("Replacement text: \(string)")
//        let existingTextHasDecimalSeparator = textField.text?.range(of: ".")
//        let replacementTextHasDecimalSeparator = string.range(of: ".")
//        
//        if existingTextHasDecimalSeparator != nil &&
//            replacementTextHasDecimalSeparator != nil {
//            return false
//        } else {
//            return true
//        }
//    }

    
    override func viewDidLoad() {
        super.viewDidLoad()
        //button = UIButton(frame: CGRect(x: 10, y: 10, width: 100, height: 100))
        //button.backgroundColor = UIColor.green
        //button.addTarget(self, action: #selector(ConversionViewController.pressButton(button:)), for: .touchUpInside)
        //button.tag = 1
        //self.view.addSubview(button)
        
        fahrenheitValue = fahrenheitValue! + 2.0
        updateCelsiusLabel()
        title = "Convert"
        view.backgroundColor = UIColor.red // bad bad, don't access views here

    }
    
    func pressButton(button: UIButton) {
        print("pressed!")
    }
    
   
    
//    override func didReceiveMemoryWarning() {
//        super.didReceiveMemoryWarning()
//        // Dispose of any resources that can be recreated.
//    }
//    
//    override func viewWillAppear(_ animated: Bool) {
//        super.viewWillAppear(animated)
//        let hour = Calendar.current.component(.hour, from: Date())
//        print("hour: \(hour)")
//        switch hour {
//        case 0...12:
//            self.view.backgroundColor = UIColor.yellow
//        case 13...24:
//            self.view.backgroundColor = UIColor.blue
//        default:
//            self.view.backgroundColor = UIColor.white
//        }
//        print("ConversionViewController will appear")
//    }

    
}
