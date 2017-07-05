//
//  ItemCell.swift
//  WorldTrotter
//
//  Created by Bart Bartel on 10/31/16.
//  Copyright © 2016 Bart Bartel. All rights reserved.
//

import UIKit

class ItemCell: UITableViewCell {
    
    @IBOutlet var nameLabel: UILabel!
    @IBOutlet var serialNumberLabel: UILabel!
    @IBOutlet var valueLabel: UILabel!
    
    func updateLabels() {
        let bodyFont = UIFont.preferredFont(forTextStyle: UIFontTextStyle.body)
        nameLabel.font = bodyFont
        nameLabel.textColor = UIColor.magenta
        valueLabel.font = bodyFont
        valueLabel.textColor = UIColor.green
        
        let caption1Font = UIFont.preferredFont(forTextStyle: UIFontTextStyle.caption1)
        serialNumberLabel.font = caption1Font
        serialNumberLabel.textColor = UIColor.orange
    }
    
    
}
