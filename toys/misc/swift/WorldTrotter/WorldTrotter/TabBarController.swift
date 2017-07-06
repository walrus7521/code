//
//  TabBarController.swift
//  WorldTrotter
//
//  Created by Bart Bartel on 10/29/16.
//  Copyright © 2016 Bart Bartel. All rights reserved.
//

import UIKit

//class ViewController: UITabBarController, UITabBarControllerDelegate {
class TabBarController: UITabBarController, UITabBarControllerDelegate {
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        //Assign self for delegate for that ViewController can respond to UITabBarControllerDelegate methods
        self.delegate = self
        
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)

        let storyboard = UIStoryboard(name: "Main", bundle: nil)
        
        // Create Tab one -- this one is in the storyboard
        let tabOne = MapViewController()
        let tabOneBarItem = UITabBarItem(title: "Map", image: UIImage(named: "MapIcon.png"), selectedImage: UIImage(named: "MapIcon.png"))
        tabOne.tabBarItem = tabOneBarItem
        
        // Create Tab two
        let tabTwo = storyboard.instantiateViewController(withIdentifier: "ConversionViewControllerId")
        let tabTwoBarItem2 = UITabBarItem(title: "Convert", image: UIImage(named: "ConvertIcon.png"), selectedImage: UIImage(named: "ConvertIcon.png"))
        tabTwo.tabBarItem = tabTwoBarItem2

        // Create Tab three
        let tabThree = WebViewController()
        let tabThreeBarItem3 = UITabBarItem(title: "Web", image: UIImage(named: "WebIcon.png"), selectedImage: UIImage(named: "WebIcon.png"))
        tabThree.tabBarItem = tabThreeBarItem3
        
        // Create Tab four -- this one is in the storyboard
        let tabFour = storyboard.instantiateViewController(withIdentifier: "QuizViewControllerId")
        let tabFourBarItem4 = UITabBarItem(title: "Quiz", image: UIImage(named: "QuizIcon.png"), selectedImage: UIImage(named: "QuizIcon.png"))
        tabFour.tabBarItem = tabFourBarItem4

        // Create Tab five (version 1) -- this one is in the storyboard
        let tabFive = storyboard.instantiateViewController(withIdentifier: "ItemsViewControllerId")
        let tabFiveBarItem5 = UITabBarItem(title: "Items", image: UIImage(named: "QuizIcon.png"), selectedImage: UIImage(named: "QuizIcon.png"))
        tabFive.tabBarItem = tabFiveBarItem5
        //let itemsController = tabFive as! ItemsViewController
        //let itemStore = ItemStore() // instantiate the itemStore
        //itemsController.itemStore = itemStore

        // Create Tab five (version 2) -- this one is in the storyboard
        //let tabFive = storyboard.instantiateViewController(withIdentifier: "ItemsViewControllerId")
        //let tabFiveBarItem5 = UITabBarItem(title: "Items", image: UIImage(named: "QuizIcon.png"), selectedImage: UIImage(named: "QuizIcon.png"))
        //tabFive.tabBarItem = tabFiveBarItem5
        // this is for ItemsStore
        // access the ItemsViewController and set its item store
        //let itemsController = tabFive as! ItemsViewController
        //let tabFiveN = storyboard.instantiateViewController(withIdentifier: "NavigationControllerId")
        //let navControllerRoot = tabFive as! UINavigationController
        //var window: UIWindow
        //window = UIWindow(frame: UIScreen.main.bounds)
        //window.makeKeyAndVisible
        //if let window = self.window {
        //window.rootViewController = navControllerRoot
        //let navControllerRoot = window.rootViewController as! UINavigationController
        //}
        //navControllerRoot.setNavigationBarHidden(false, animated: true)
        //navControllerRoot.pushViewController(tabFive, animated: true)
        //let itemsController = navControllerRoot.topViewController as! ItemsViewController
        //let itemStore = ItemStore() // instantiate the itemStore
        //itemsController.itemStore = itemStore
        
        // order of tabs in bar, first one is default
        self.viewControllers = [tabOne, tabTwo, tabThree, tabFour, tabFive]
    }
    
    func tabBarController(_ tabBarController: UITabBarController, didSelect viewController: UIViewController) {
        print("Selected \(viewController.title!)")
    }
    

}
