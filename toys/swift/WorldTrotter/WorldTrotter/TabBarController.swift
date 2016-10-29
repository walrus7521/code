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
        let tabOneBarItem = UITabBarItem(title: "Map View", image: UIImage(named: "MapIcon.png"), selectedImage: UIImage(named: "MapIcon.png"))
        tabOne.tabBarItem = tabOneBarItem
        
        // Create Tab two
        let tabTwo = storyboard.instantiateViewController(withIdentifier: "ConversionViewControllerId")
        let tabTwoBarItem2 = UITabBarItem(title: "Convert View", image: UIImage(named: "ConvertIcon.png"), selectedImage: UIImage(named: "ConvertIcon.png"))
        tabTwo.tabBarItem = tabTwoBarItem2

        // Create Tab three
        let tabThree = WebViewController()
        let tabThreeBarItem3 = UITabBarItem(title: "Web View", image: UIImage(named: "WebIcon.png"), selectedImage: UIImage(named: "WebIcon.png"))
        tabThree.tabBarItem = tabThreeBarItem3
        
        // Create Tab four -- this one is in the storyboard
        let tabFour = storyboard.instantiateViewController(withIdentifier: "QuizViewControllerId")
        let tabFourBarItem4 = UITabBarItem(title: "Quiz View", image: UIImage(named: "QuizIcon.png"), selectedImage: UIImage(named: "QuizIcon.png"))
        tabFour.tabBarItem = tabFourBarItem4
        
        // order of tabs in bar, first one is default
        self.viewControllers = [tabOne, tabTwo, tabThree, tabFour]
    }
    
    func tabBarController(_ tabBarController: UITabBarController, didSelect viewController: UIViewController) {
        print("Selected \(viewController.title!)")
    }
    

}
