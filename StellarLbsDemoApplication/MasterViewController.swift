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
    var OASKey: String!
    //var siteId: String!
    var siteId: [String] = [] //TODO Get site id from response
    var username: String!
    
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
        viewController.masterViewController = self
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
        guard OASKey != nil else{
            errorQuitApp(title: "Not Connected", message: "Can't retrieve the API Key, the app will quit")
            return
        }
        locationHandle?.initLocation(key: OASKey)
        switch mapSelected{
        case .Education:
                visioGlobeController.changeMap(mapHash: "m5cc12aefcc1596ca7baeb77819136677fa04fa1b")
            case .ColombesVisio:
                visioGlobeController.changeMap(mapHash: "mb5cdba08b03f74907aef5eb16a56fec41a35435c")
            case .ColombesMapWize:
                mapWizeController.changeMap(coordinates: CLLocationCoordinate2D(latitude: 48.933940, longitude: 2.253306))
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
    
    @IBAction func displayMapSelection(_ sender: Any?){
        let message = UIAlertController(title: "Select Map", message: "Select your map", preferredStyle: .actionSheet)
        message.addAction(UIAlertAction(title: "Education", style: .default, handler: { (action:UIAlertAction!) -> Void in
            self.changeMap(asChildViewController: self.visioGlobeController, mapSelected: Map.Education)}))
        message.addAction(UIAlertAction(title:"Transportation", style: .default, handler: {(action:UIAlertAction!) -> Void in
            self.changeMap(asChildViewController: self.visioGlobeController, mapSelected: Map.Transportation)}))
        message.addAction(UIAlertAction(title:"Hospitality", style: .default, handler: {(action:UIAlertAction!) -> Void in
            self.changeMap(asChildViewController: self.visioGlobeController, mapSelected: Map.Hospitality)}))
        message.addAction(UIAlertAction(title:"Healthcare", style: .default, handler: {(action:UIAlertAction!) -> Void in
            self.changeMap(asChildViewController: self.visioGlobeController, mapSelected: Map.Healthcare)}))
        message.addAction(UIAlertAction(title:"EBC Colombes 3D", style: .default, handler: {(action:UIAlertAction!) -> Void in
            self.changeMap(asChildViewController: self.visioGlobeController, mapSelected: Map.ColombesVisio)}))
        message.addAction(UIAlertAction(title: "EBC Colombes 2D", style: .default, handler: {(action:UIAlertAction!) -> Void in
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
            self.errorQuitApp(title: "Error", message: "This app needs to acces to your location, please authorize in configuration")
        default:
            NSLog("oui")
        }
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
    
    func copyEmulationFile(){
        if let path = Bundle.main.path(forResource: "colombes", ofType: "gwl") {
            NSLog("Emulation File Exists")
            //let newPath = FileManager.default.urls(for: .applicationSupportDirectory, in:.localDomainMask)
            let newPath = NSURL(fileURLWithPath: NSSearchPathForDirectoriesInDomains(.applicationSupportDirectory, .userDomainMask, true)[0])
            let dataPath = newPath.appendingPathComponent("data")
            let replayPath = dataPath!.appendingPathComponent("replay")
            do{
                try FileManager.default.createDirectory(atPath: dataPath!.path, withIntermediateDirectories: true, attributes: nil)
                try FileManager.default.createDirectory(atPath: replayPath.path, withIntermediateDirectories: true, attributes: nil)
            }catch{
                NSLog("Unable to create directories")
            }
            do{
                let gwlPath = replayPath.appendingPathComponent("colombes.gwl")
                if(!FileManager.default.fileExists(atPath: gwlPath.path)){
                    NSLog("GWL File missing, creating....")
                    try FileManager.default.copyItem(atPath: path, toPath: gwlPath.path)
                }else{
                    NSLog("GWL File already exists")
                }
            }
            catch (let error){
                NSLog("Unable to copy file: " + error.localizedDescription)
            }
        }else{
            NSLog("Emulation file doesn't exists")
        }
    }
    
    func deleteEmulationFile(){
        if let path = Bundle.main.path(forResource: "colombes", ofType: "gwl") {
            NSLog("Emulation File Exists")
            //let newPath = FileManager.default.urls(for: .applicationSupportDirectory, in:.localDomainMask)
            let newPath = NSURL(fileURLWithPath: NSSearchPathForDirectoriesInDomains(.applicationSupportDirectory, .userDomainMask, true)[0])
            let dataPath = newPath.appendingPathComponent("data")
            let replayPath = dataPath!.appendingPathComponent("replay")
            do{
                try FileManager.default.createDirectory(atPath: dataPath!.path, withIntermediateDirectories: true, attributes: nil)
                try FileManager.default.createDirectory(atPath: replayPath.path, withIntermediateDirectories: true, attributes: nil)
            }catch{
                NSLog("Unable to create directories")
            }
            do{
                let gwlPath = replayPath.appendingPathComponent("colombes.gwl")
                if(!FileManager.default.fileExists(atPath: gwlPath.path)){
                    NSLog("GWL File missing")
                    try FileManager.default.copyItem(atPath: path, toPath: gwlPath.path)
                }else{
                    NSLog("GWL File exists, deleting....")
                    try FileManager.default.removeItem(at: gwlPath  )
                }
            }
            catch (let error){
                NSLog("Unable to copy file: " + error.localizedDescription)
            }
        }else{
            NSLog("Emulation file doesn't exists")
        }
    }
}




