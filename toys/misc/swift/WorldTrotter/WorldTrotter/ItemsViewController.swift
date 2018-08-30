//
//  ItemsViewController.swift
//  WorldTrotter
//
//  Created by Bart Bartel on 10/30/16.
//  Copyright © 2016 Bart Bartel. All rights reserved.
//

import UIKit

class ItemsViewController: UITableViewController {
    
    var itemStore: ItemStore!
    
    var imageStore: ImageStore!

    //override func loadView() {
    //    itemStore = ItemStore()
    //}
    
    required init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
        
        navigationItem.leftBarButtonItem = editButtonItem
        
    }
    
    @IBAction func addNewItem(sender: AnyObject) {
        print("Items: add")
        
        let newItem = itemStore.createItem()
        
        // figure out where that item is in the array
        if let index = itemStore.allItems.index(of: newItem) {
            let indexPath = NSIndexPath(row: index, section: 0)
            
            // insert this new row into the table
            tableView.insertRows(at: [indexPath as IndexPath], with: .automatic)
        }
    }

    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        print("Items: count")
        return itemStore.allItems.count
    }

    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        print("Items: cell row")
        let cell = tableView.dequeueReusableCell(withIdentifier: "ItemCell",
                            for: indexPath) as! ItemCell
        
        // update the labels for the new preferred text size
        cell.updateLabels()
        
        // set the text onthe cell with the description of the item
        // tht is at the nth index of items, where n = row this cell
        // will appear in on the tableView
        let item = itemStore.allItems[indexPath.row]
        
        // configure the cell with the Item
        cell.nameLabel.text = item.name
        cell.serialNumberLabel.text = item.serialNumber
        cell.valueLabel.text = "\(item.valueInPoints)"
        
        return cell
    }

    override func tableView(_ tableView: UITableView, commit editingStyle: UITableViewCellEditingStyle, forRowAt indexPath: IndexPath) {
        print("Items: edit style")
        
        // if the table view is asking to commit a delete command
        if editingStyle == .delete {
            let item = itemStore.allItems[indexPath.row]
            
            //if item.name == "No more items!" {
            //    return
            //}
            
            // alert user
            let title = "Delete \(item.name)?"
            let message = "Are you sure you want to delete this item?"
            
            let ac = UIAlertController(title: title,
                                       message: message,
                                       preferredStyle: .actionSheet)
            
            // add cancel action into alert
            let cancelAction = UIAlertAction(title: "Cancel",
                                             style: .cancel,
                                             handler: nil)
            ac.addAction(cancelAction)
            
            // add delete action into the alert
            let deleteAction = UIAlertAction(title: "Delete",
                                             style: .destructive,
                                             handler: {(action) -> Void in
                self.itemStore.removeItem(item: item)
                                                
                // Remove the item's image from the image store
                self.imageStore.deleteImageForKey(key: item.itemKey)
                                                
                // Also remove that row from the table view with an animation
                self.tableView.deleteRows(at: [indexPath as IndexPath], with: .automatic)

            
            })
            ac.addAction(deleteAction)
            
            // present the alert
            present(ac, animated: true, completion: nil)
            
            // remove item from the store
            //itemStore.removeItem(item: item)
            
            // also remove that row from the table view with an animation
            //tableView.deleteRows(at: [indexPath as IndexPath], with: .automatic)
        }
    }
    
    override func tableView(_ tableView: UITableView, moveRowAt sourceIndexPath: IndexPath, to destinationIndexPath: IndexPath) {
        print("Items: move")
        
        // update the model
        itemStore.moveItemAtIndex(fromIndex: sourceIndexPath.row, toIndex: destinationIndexPath.row)
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        itemStore = ItemStore()

        print("Items: Did load")
        
        tableView.rowHeight = UITableViewAutomaticDimension
        tableView.estimatedRowHeight = 65
        
        title = "Code Tracker"
        view.backgroundColor = UIColor.yellow // bad bad, don't access views here
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        if segue.identifier == "ShowItem" {
            
            // figure out which row was just tapped
            if let row = tableView.indexPathForSelectedRow?.row {
                // get the item associated with this row and pass it along
                let item = itemStore.allItems[row]
                let detailViewController = segue.destination as! DetailViewController
                detailViewController.item = item
                detailViewController.imageStore = imageStore
            }
        }
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        
        tableView.reloadData()
    }
    
    
}
