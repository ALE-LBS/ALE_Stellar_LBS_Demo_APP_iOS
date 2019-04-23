//
//  ViewController.swift
//  StellarLbsDemoApplication
//
//  Created by Jerome Elleouet on 28/02/2018.
//  Copyright © 2018 ALE. All rights reserved.
//

import UIKit

class MasterViewController: UIViewController , UIGestureRecognizerDelegate{
    
    @IBOutlet weak var navigationButton: UIBarButtonItem!
    var locationHandle:LocationHandle? = nil
    
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        askPermissions()
        setupView() //TODO map selection closes permissions ask
        locationHandle = LocationHandle.init(masterViewController: self)
    }
    
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
//******************** Bug **********************
//        let OASKey = readPList(key: "OAS-Brest")
//        if  OASKey != "Error"{
//            locationHandle?.initLocation(key: OASKey)
//        }
//        else{
//            //ERROR, no key found
//        }
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    
    // Adapted Multi View Controller Tutorial from https://cocoacasts.com/managing-view-controllers-with-container-view-controllers/
    lazy var mapWizeController: MapWizeController = {
        //Load Storyboard
        let storyboard = UIStoryboard(name: "Main", bundle: Bundle.main)
        //Instanciate View Controller
        var viewController = storyboard.instantiateViewController(withIdentifier: "MapWizeController") as! MapWizeController
        //Add View Controller as Child View Controller
        //self.add(asChildViewController:viewController)
        return viewController
    }()
    
    lazy var visioGlobeController: VisioGlobeController = {
        let storyboard = UIStoryboard(name: "Main", bundle: Bundle.main)
        var viewController = storyboard.instantiateViewController(withIdentifier: "VisioGlobeController") as! VisioGlobeController
        //self.add(asChildViewController:viewController)
        return viewController
    }()
    
    lazy var initialViewController: InitialViewController = {
        let storyboard = UIStoryboard(name: "Main", bundle: Bundle.main)
        var viewController = storyboard.instantiateViewController(withIdentifier: "InitialViewController") as! InitialViewController
        self.add(asChildViewController:viewController)
        return viewController
    }()
    
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
    
    private func removeAll(){
        self.children.forEach{ child in
            self.remove(asChildViewController: child)
        }
    }
    
    private func setView(asChildViewController viewController:UIViewController, mapSelected:Map){
        switch mapSelected{
        case .BrestVisio:
            visioGlobeController.changeMap(mapHash: "m940afbf14e55c904955df9d0b64218238b0e749d")
        case .ColombesVisio:
            visioGlobeController.changeMap(mapHash: "mb5cdba08b03f74907aef5eb16a56fec41a35435c")
        case .ColombesMapWize:
            mapWizeController.changeMap(coordinates: CLLocationCoordinate2D(latitude: 48.933940, longitude: 2.253306))
        case .BrestMapWize:
            mapWizeController.changeMap(coordinates: CLLocationCoordinate2D(latitude: 48.441637506411176, longitude: -4.4127606743614365))
        case .Transportation:
            visioGlobeController.changeMap(mapHash: "mf9e95e83efab408fcd749aff3ddceb20e43c37cc")
        case .Hospitality:
            visioGlobeController.changeMap(mapHash: "mfb77589730a6f9b8d4b098b012189b2c84e2f83a")
        case .Healthcare:
            visioGlobeController.changeMap(mapHash: "m3d398a4c9b3c83e5faac2dd980d8749bf7b262e2")
        }
        locationHandle?.setMapSelected(mapSelected)
        removeAll()
        add(asChildViewController: viewController)
    }
    
    @IBAction func displayMapSelection(_ sender: Any?) {
        let message = UIAlertController(title: "Select Map", message: "Select your map", preferredStyle: .actionSheet)
        message.addAction(UIAlertAction(title:"Brest VisioGlobe", style: .default, handler: {(action:UIAlertAction!) -> Void in
            self.setView(asChildViewController: self.visioGlobeController, mapSelected: Map.BrestVisio)}))
        message.addAction(UIAlertAction(title:"Colombes VisioGlobe", style: .default, handler: {(action:UIAlertAction!) -> Void in
            self.setView(asChildViewController: self.visioGlobeController, mapSelected: Map.ColombesVisio)}))
        message.addAction(UIAlertAction(title:"Transportation VisioGlobe", style: .default, handler: {(action:UIAlertAction!) -> Void in
            self.setView(asChildViewController: self.visioGlobeController, mapSelected: Map.Transportation)}))
        message.addAction(UIAlertAction(title:"Hospitality VisioGlobe", style: .default, handler: {(action:UIAlertAction!) -> Void in
            self.setView(asChildViewController: self.visioGlobeController, mapSelected: Map.Hospitality)}))
        message.addAction(UIAlertAction(title:"Healthcare VisioGlobe", style: .default, handler: {(action:UIAlertAction!) -> Void in
            self.setView(asChildViewController: self.visioGlobeController, mapSelected: Map.Healthcare)}))
        message.addAction(UIAlertAction(title: "Brest Mapwize", style: .default, handler: {(action:UIAlertAction!) -> Void in
            self.setView(asChildViewController: self.mapWizeController, mapSelected: Map.BrestMapWize)}))
        message.addAction(UIAlertAction(title: "Colombes Mapwize", style: .default, handler: {(action:UIAlertAction!) -> Void in
            self.setView(asChildViewController: self.mapWizeController, mapSelected: Map.ColombesMapWize)}))
        OperationQueue.main.addOperation {
            self.present(message,animated: true, completion: nil)
        }
    }
    
    private func setupInitialView(){
        removeAll()
        add(asChildViewController: initialViewController)
    }
    
    private func setupView(){
        setupInitialView()
        displayMapSelection(nil)
    }
    
    //***********************************************************
    
    
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
