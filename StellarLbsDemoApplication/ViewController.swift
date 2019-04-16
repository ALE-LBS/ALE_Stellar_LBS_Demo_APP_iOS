//
//  ViewController.swift
//  StellarLbsDemoApplication
//
//  Created by Jerome Elleouet on 28/02/2018.
//  Copyright © 2018 ALE. All rights reserved.
//

import UIKit
import Mapbox
import MapwizeForMapbox

class ViewController: UIViewController, MWZMapwizePluginDelegate, MGLMapViewDelegate , UIGestureRecognizerDelegate{
    
    var locationHandle = LocationHandle.init()

    func askPermissions(){
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
    
    override func viewDidLoad() {
        super.viewDidLoad()
        //askPermissions()
        let alert = UIAlertController(title: "Did you bring your towel?", message: "It's recommended you bring your towel before continuing.", preferredStyle: .alert)
        alert.addAction(UIAlertAction(title: "Yes", style: .default, handler: nil))
        alert.addAction(UIAlertAction(title: "No", style: .cancel, handler: nil))
        OperationQueue.main.addOperation { //adding to operation queue (display when it's possible)
            self.present(alert, animated: true)
        }
    }
    
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        let OASKey = readPList(key: "OAS-Brest")
        if  OASKey != "Error"{
            locationHandle.initLocation(key: OASKey)
        }
        else{
            //ERROR, no key found
        }
    }
    
    
    func mapwizePluginDidLoad(_ mapwizePlugin: MapwizePlugin!) {
        NSLog("mapwizePluginDidLoad")
       // mapWizePlugin.setIndoorLocationProvider(poleStarLocationProvider)
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    //Read Keys.plist
    func readPList(key: String) -> String{
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
    
    static func displayMessage(title: String, message: String){
        let message = UIAlertController(title: title, message: message, preferredStyle: .alert)
        message.addAction(UIAlertAction(title:"OK", style: .default, handler: {(action:UIAlertAction!) -> Void in exit(0)}))
        OperationQueue.main.addOperation {
            present(message,animated: true, completion: nil)
        }
    }
}
