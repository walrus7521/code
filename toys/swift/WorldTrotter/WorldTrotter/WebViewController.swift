//
//  WebViewController.swift
//  WorldTrotter
//
//  Created by Bart Bartel on 10/29/16.
//  Copyright © 2016 Bart Bartel. All rights reserved.
//

import UIKit
import WebKit

class WebViewController: UIViewController {
    
    var webView: WKWebView!
    
    override func loadView() {
        
        webView = WKWebView()
        
        view = webView
        
        let url = URL(string: "http://facebook.com")!
        webView.load(URLRequest(url: url))
        
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        // Do any additional setup after loading the view.
        //view.backgroundColor = UIColor.red // bad bad, don't access views here
        title = "WebView"
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        print("WebView: warning")
        // Dispose of any resources that can be recreated.
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        print("WebView will appear")
    }
    
}

