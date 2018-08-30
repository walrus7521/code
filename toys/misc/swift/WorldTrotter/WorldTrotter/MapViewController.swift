//
//  MapViewController.swift
//  WorldTrotter
//
//  Created by Bart Bartel on 10/24/16.
//  Copyright © 2016 Bart Bartel. All rights reserved.
//

import UIKit
import MapKit

class MapViewController: UIViewController {
    
    
    var mapView: MKMapView!
 
    override func loadView() {
        // create a map view
        mapView = MKMapView()
        
        // set it as *the* view of this view controller
        view = mapView
        
        let segmentedControl = UISegmentedControl(items: ["Standard", "Hybrid", "Satellite"])
        segmentedControl.backgroundColor = UIColor.init(white: 1.0, alpha: 0.5)
        segmentedControl.selectedSegmentIndex = 0
        
        segmentedControl.addTarget(self, action: #selector(MapViewController.mapTypeChanged), for: .valueChanged)
        
        segmentedControl.translatesAutoresizingMaskIntoConstraints = false
        view.addSubview(segmentedControl)
        
        let topConstraint
            = segmentedControl.topAnchor.constraint(equalTo: topLayoutGuide.bottomAnchor,
                                                    constant: 8)
        let margins = view.layoutMarginsGuide
        let leadingConstraint
            = segmentedControl.leadingAnchor.constraint(equalTo: margins.leadingAnchor)
        let trailingConstraint
            = segmentedControl.trailingAnchor.constraint(equalTo: margins.trailingAnchor)

        topConstraint.isActive = true
        leadingConstraint.isActive = true
        trailingConstraint.isActive = true
        print("MapView: loaded")
    }

    func mapTypeChanged(segControl: UISegmentedControl) {
        switch segControl.selectedSegmentIndex {
        case 0:
            mapView.mapType = .standard
        case 1:
            mapView.mapType = .hybrid
        case 2:
            mapView.mapType = .satellite
        default:
            break
        }
    }

    override func viewDidLoad() {
        super.viewDidLoad()
    
        let latitude:CLLocationDegrees = 31.7683 //insert latitutde
        let longitude:CLLocationDegrees = 35.2137 //insert longitude
        let latDelta:CLLocationDegrees = 0.15
        let lonDelta:CLLocationDegrees = 0.15
        let span = MKCoordinateSpanMake(latDelta, lonDelta)
        let location = CLLocationCoordinate2DMake(latitude, longitude)
        let region = MKCoordinateRegionMake(location, span)
        self.mapView.setRegion(region, animated: false)
        
        // Do any additional setup after loading the view.
        //view.backgroundColor = UIColor.red // bad bad, don't access views here
        title = "Map"
        print("MapView: DidLoad")
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        print("MapView: warning")
        // Dispose of any resources that can be recreated.
    }
    
    override func viewWillAppear(_ animated: Bool) {
         super.viewWillAppear(animated)
         print("MapView will appear")
    }
    
}
