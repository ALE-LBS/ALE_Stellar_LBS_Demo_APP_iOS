//
//  ViewController.swift
//  StellarLbsDemoApplication
//
//  Created by Jerome Elleouet on 28/02/2018.
//  Copyright © 2018 ALE. All rights reserved.
//

import UIKit

class MasterViewController: UIViewController , UIGestureRecognizerDelegate, CLLocationManagerDelegate{
    
    @IBOutlet weak var navigationButton: UIBarButtonItem!
    var locationHandle:LocationHandle? = nil
    var locationManager:CLLocationManager = CLLocationManager.init()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        locationManager.delegate = self
        setupView()
    }
    
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
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
        return viewController
    }()
    
    lazy var visioGlobeController: VisioGlobeController = {
        let storyboard = UIStoryboard(name: "Main", bundle: Bundle.main)
        var viewController = storyboard.instantiateViewController(withIdentifier: "VisioGlobeController") as! VisioGlobeController
        return viewController
    }()
    
    lazy var initialViewController: InitialViewController = {
        let storyboard = UIStoryboard(name: "Main", bundle: Bundle.main)
        var viewController = storyboard.instantiateViewController(withIdentifier: "InitialViewController") as! InitialViewController
        viewController.setNavigationButton(navigationButton)
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
    
    private func changeMap(asChildViewController viewController:UIViewController, mapSelected:Map){
        if(locationHandle == nil){
            locationHandle = LocationHandle.init(masterViewController:self)
        }
        switch mapSelected{
        case .Emulator:
            locationHandle?.initLocation(key: "emulator")
            visioGlobeController.changeMap(mapHash: "mb5cdba08b03f74907aef5eb16a56fec41a35435c")
        case .BrestVisio:
            locationHandle?.initLocation(key: readPList(key: "OAS-Brest"))
            visioGlobeController.changeMap(mapHash: "m940afbf14e55c904955df9d0b64218238b0e749d")
        case .ColombesVisio:
            locationHandle?.initLocation(key: readPList(key: "OAS-Colombes"))
            visioGlobeController.changeMap(mapHash: "mb5cdba08b03f74907aef5eb16a56fec41a35435c")
        case .ColombesMapWize:
            locationHandle?.initLocation(key: readPList(key: "OAS-Colombes"))
            mapWizeController.changeMap(coordinates: CLLocationCoordinate2D(latitude: 48.933940, longitude: 2.253306))
        case .BrestMapWize:
            locationHandle?.initLocation(key: readPList(key: "OAS-Brest"))
            mapWizeController.changeMap(coordinates: CLLocationCoordinate2D(latitude: 48.441637506411176, longitude: -4.4127606743614365))
        case .Transportation:
            locationHandle?.initLocation(key: readPList(key: "OAS-Colombes"))
            visioGlobeController.changeMap(mapHash: "mf9e95e83efab408fcd749aff3ddceb20e43c37cc")
        case .Hospitality:
            locationHandle?.initLocation(key: readPList(key: "OAS-Colombes"))
            visioGlobeController.changeMap(mapHash: "mfb77589730a6f9b8d4b098b012189b2c84e2f83a")
        case .Healthcare:
            locationHandle?.initLocation(key: readPList(key: "OAS-Colombes"))
            visioGlobeController.changeMap(mapHash: "m3d398a4c9b3c83e5faac2dd980d8749bf7b262e2")
        }
        locationHandle?.setMapSelected(mapSelected)
        removeAll()
        add(asChildViewController: viewController)
    }
    
    @IBAction func displayMapSelection(_ sender: Any?){
        let message = UIAlertController(title: "Select Map", message: "Select your map", preferredStyle: .actionSheet)
        message.addAction(UIAlertAction(title:"Emulation", style: .default, handler: {(action:UIAlertAction!) -> Void in
            self.changeMap(asChildViewController: self.visioGlobeController, mapSelected: Map.Emulator)}))
        message.addAction(UIAlertAction(title:"Brest VisioGlobe", style: .default, handler: {(action:UIAlertAction!) -> Void in
            self.changeMap(asChildViewController: self.visioGlobeController, mapSelected: Map.BrestVisio)}))
        message.addAction(UIAlertAction(title:"Colombes VisioGlobe", style: .default, handler: {(action:UIAlertAction!) -> Void in
            self.changeMap(asChildViewController: self.visioGlobeController, mapSelected: Map.ColombesVisio)}))
        message.addAction(UIAlertAction(title:"Transportation VisioGlobe", style: .default, handler: {(action:UIAlertAction!) -> Void in
            self.changeMap(asChildViewController: self.visioGlobeController, mapSelected: Map.Transportation)}))
        message.addAction(UIAlertAction(title:"Hospitality VisioGlobe", style: .default, handler: {(action:UIAlertAction!) -> Void in
            self.changeMap(asChildViewController: self.visioGlobeController, mapSelected: Map.Hospitality)}))
        message.addAction(UIAlertAction(title:"Healthcare VisioGlobe", style: .default, handler: {(action:UIAlertAction!) -> Void in
            self.changeMap(asChildViewController: self.visioGlobeController, mapSelected: Map.Healthcare)}))
        message.addAction(UIAlertAction(title: "Brest Mapwize", style: .default, handler: {(action:UIAlertAction!) -> Void in
            self.changeMap(asChildViewController: self.mapWizeController, mapSelected: Map.BrestMapWize)}))
        message.addAction(UIAlertAction(title: "Colombes Mapwize", style: .default, handler: {(action:UIAlertAction!) -> Void in
            self.changeMap(asChildViewController: self.mapWizeController, mapSelected: Map.ColombesMapWize)}))
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
    }
    
    //***********************************************************
    
    func locationManager(_ manager: CLLocationManager, didChangeAuthorization status: CLAuthorizationStatus) {
        switch status.self {
        case .authorizedAlways:
            NSLog("Delegate Location Permission Authorized Always")
        case .authorizedWhenInUse:
            NSLog("Delegate Location Permission Authoried When In Use")
            self.displayMessage(title: "Error", message: "This app needs to acces to your location when in background")
        case .denied:
            NSLog("Delegate Location Permission Denied")
            self.errorQuitApp(title: "Error", message: "This app needs to acces to your location, please authorize in configuration")
        case .notDetermined:
            locationManager.requestAlwaysAuthorization()
        case .restricted:
            self.errorQuitApp(title: "Error", message: "This app needs to acces to your location, please authorize in configuration")        default:
            NSLog("oui")
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
    
    //Display an alert box that quit the app
    func errorQuitApp(title: String, message: String){
        let message = UIAlertController(title: title, message: message, preferredStyle: .alert)
        message.addAction(UIAlertAction(title:"OK", style: .default, handler: {(action:UIAlertAction!) -> Void in exit(0)}))
        OperationQueue.main.addOperation {
            self.present(message,animated: true, completion: nil)
        }
    }
    
    //Display a message to the user
    func displayMessage(title: String, message: String){
        let message = UIAlertController(title: title, message: message, preferredStyle: .alert)
        message.addAction(UIAlertAction(title:"OK", style: .default, handler: nil ))
        OperationQueue.main.addOperation {
            self.present(message,animated: true, completion: nil)
        }
    }

}
