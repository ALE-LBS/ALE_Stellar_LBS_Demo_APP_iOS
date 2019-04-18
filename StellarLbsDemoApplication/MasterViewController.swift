//
//  ViewController.swift
//  StellarLbsDemoApplication
//
//  Created by Jerome Elleouet on 28/02/2018.
//  Copyright © 2018 ALE. All rights reserved.
//

import UIKit

class MasterViewController: UIViewController , UIGestureRecognizerDelegate{
    
    @IBOutlet weak var segmentedControl: UISegmentedControl!
    var locationHandle:LocationHandle? = nil
    
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        //askPermissions()
        setupView()
        locationHandle = LocationHandle.init(masterViewController: self)
        /*let alert = UIAlertController(title: "Did you bring your towel?", message: "It's recommended you bring your towel before continuing.", preferredStyle: .alert)
        alert.addAction(UIAlertAction(title: "Yes", style: .default, handler: nil))
        alert.addAction(UIAlertAction(title: "No", style: .cancel, handler: nil))
        OperationQueue.main.addOperation { //adding to operation queue (display when it's possible)
            self.present(alert, animated: true)
        }*/
    }
    
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        let OASKey = readPList(key: "OAS-Brest")
        if  OASKey != "Error"{
            locationHandle?.initLocation(key: OASKey)
        }
        else{
            //ERROR, no key found
        }
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    
    // Multi View Controller Tutorial from https://cocoacasts.com/managing-view-controllers-with-container-view-controllers/
    lazy var mapWizeController: MapWizeController = {
        //Load Storyboard
        let storyboard = UIStoryboard(name: "Main", bundle: Bundle.main)
        //Instanciate View Controller
        var viewController = storyboard.instantiateViewController(withIdentifier: "MapWizeController") as! MapWizeController
        //Add View Controller as Child View Controller
        self.add(asChildViewController:viewController)
        return viewController
    }()
    
    lazy var visioGlobeController: VisioGlobeController = {
        let storyboard = UIStoryboard(name: "Main", bundle: Bundle.main)
        var viewController = storyboard.instantiateViewController(withIdentifier: "VisioGlobeController") as! VisioGlobeController
        self.add(asChildViewController:viewController)
        return viewController
    }()
    
    private func setupSegmentedControl(){
        segmentedControl.removeAllSegments()
        segmentedControl.insertSegment(withTitle: "Mapwize", at: 0, animated: true)
        segmentedControl.insertSegment(withTitle: "Visioglobe", at: 1, animated: true)
        segmentedControl.addTarget(self, action: #selector( selectionDidChange(_:)) , for: .valueChanged)
    }
    
    @objc func selectionDidChange(_ sender: UISegmentedControl){
        updateView()
    }
    
    private func add(asChildViewController viewController:UIViewController){
        addChild(viewController)
        view.addSubview(viewController.view)
        viewController.view.frame = view.bounds
        viewController.view.autoresizingMask = [.flexibleWidth, .flexibleHeight]
        viewController.didMove(toParent: self)
    }
    
    private func remove(asChildViewController viewController:UIViewController){
        viewController.willMove(toParent: nil)
        viewController.view.removeFromSuperview()
        viewController.removeFromParent()
    }
    
    private func updateView(){
        if segmentedControl.selectedSegmentIndex == 0 {
            locationHandle?.setMapSelected(mapSelected: Map.MapWize)
            remove(asChildViewController: visioGlobeController)
            add(asChildViewController: mapWizeController)
        }else{
            locationHandle?.setMapSelected(mapSelected: Map.BrestVisio)
            remove(asChildViewController: mapWizeController)
            add(asChildViewController: visioGlobeController)
        }
    }
    
    private func setupView(){
        setupSegmentedControl()
        updateView()
    }
    
    private func askPermissions(){
        NSLog("Permissions")
        let locationManager = CLLocationManager()
        switch CLLocationManager.authorizationStatus(){
        case .restricted:
            NSLog("Location Permission Restricted");
            locationManager.requestWhenInUseAuthorization()
            locationManager.requestAlwaysAuthorization()
        case .denied:
            NSLog("Location Permission Denied");
            locationManager.requestWhenInUseAuthorization()
            locationManager.requestAlwaysAuthorization()
        case .notDetermined:
            NSLog("Location Permission not Determined");
            locationManager.requestWhenInUseAuthorization()
            locationManager.requestAlwaysAuthorization()
        case .authorizedAlways:
            NSLog("Location Permission Authorized Always");
            locationManager.requestWhenInUseAuthorization()
        case .authorizedWhenInUse:
            NSLog("Location Permission Authoried When In Use");
            locationManager.requestAlwaysAuthorization()
        @unknown default:
            NSLog("Location Permission Unkown")
            locationManager.requestWhenInUseAuthorization()
            locationManager.requestAlwaysAuthorization()
        }
    }
    
    //Read Keys.plist
    private func readPList(key: String) -> String{
        var keys: [String:String]?
        if let path = Bundle.main.path(forResource: "Keys", ofType: "plist") { //if file exists
            keys = NSDictionary(contentsOfFile: path) as? [String : String]//keys is the file content
            for k in keys!{
                if(k.key == key){
                    return keys![key]!
                }
            }
            NSLog("Key not found, showing alert message")
            let alertMessage = UIAlertController(title: "Key not found", message: "Update Keys.plist file", preferredStyle: UIAlertController.Style.alert)
            alertMessage.addAction(UIAlertAction(title: "Exit", style: UIAlertAction.Style.destructive, handler:{ (action:UIAlertAction!) -> Void in
                exit(0)
            }))
            self.present(alertMessage, animated: true, completion: nil)
            return "Error"
        }else{
            let alertMessage = UIAlertController(title: "Invalid Key", message: "Keys.plist file must be missing", preferredStyle: UIAlertController.Style.alert)
            alertMessage.addAction(UIAlertAction(title: "Exit", style: UIAlertAction.Style.destructive, handler:{ (action:UIAlertAction!) -> Void in
                exit(0)
            }))
            present(alertMessage,animated: true,completion: nil)
        }
        return "Error"
        //random error, see log files
    }
    
    //Display an alert box
    func displayMessage(title: String, message: String){
        let message = UIAlertController(title: title, message: message, preferredStyle: .alert)
        message.addAction(UIAlertAction(title:"OK", style: .default, handler: {(action:UIAlertAction!) -> Void in exit(0)}))
        OperationQueue.main.addOperation {
            self.present(message,animated: true, completion: nil)
        }
    }
}
