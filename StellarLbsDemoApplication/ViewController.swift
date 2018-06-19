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

class ViewController: UIViewController, NAOLocationHandleDelegate, NAOSensorsDelegate, NAOSyncDelegate, MWZMapwizePluginDelegate, MGLMapViewDelegate, NAOGeofencingHandleDelegate , UIGestureRecognizerDelegate{
    
    @IBOutlet var mapView: MGLMapView!
    @IBOutlet weak var navigationTitle: UINavigationItem!
    var pickerData: [String] = [String]()
    var mapWizePlugin:MapwizePlugin!
    var poleStarLocationProvider:PoleStarLocationProvider = PoleStarLocationProvider.init()
    var locationHandle: NAOLocationHandle!
    var geofenceHandle: NAOGeofencingHandle!
    let locationManager = CLLocationManager()
    
    //I.E. GeoNotification
    func didFire(_ alert: NaoAlert!) {
        NSLog("geofence")
        if(alert.rules.isEmpty == false){
            NSLog("not empty")
            NSLog("entergeofence")
            if(alert.content.starts(with: "http")){
                NSLog("http")
                //start browser
                UIApplication.shared.open(URL.init(string: alert.content)!, options: [:], completionHandler: nil)
            }
        }
        
    }
    
    func didSynchronizationSuccess() {
        NSLog("didSynchronizationSuccess")
        locationHandle.start()
        geofenceHandle.start()
    }
    
    func didSynchronizationFailure(_ errorCode: DBNAOERRORCODE, msg message: String!) {
        NSLog("didSynchronizationFailure")
    }
    
    func requiresWifiOn() {
        NSLog("requiresWifiOn")
    }
    
    func requiresBLEOn() {
        NSLog("requiresBLEOn")
    }
    
    func requiresLocationOn() {
        NSLog("requiresLocationOn")
    }
    
    func requiresCompassCalibration() {
        NSLog("requiresCompassCalibration")
    }
    
    func didFailWithErrorCode(_ errCode: DBNAOERRORCODE, andMessage message: String!) {
        NSLog("didFailWithErrorCode")
    }
    
    func didLocationChange(_ location: CLLocation!) {
        NSLog("didLocationChange")
        if(location.timestamp.timeIntervalSinceNow > -10.0){ //deleting cached positions
            let indoorLocation:ILIndoorLocation = ILIndoorLocation.init(provider: poleStarLocationProvider, latitude: location.coordinate.latitude, longitude: location.coordinate.longitude, floor: 0) //Creation of the indoorLocation
            poleStarLocationProvider.setLocation(indoorLocation: indoorLocation)
            navigationTitle.title = location.coordinate.latitude.description + " " + location.coordinate.longitude.description
        }
    }
    
    func didLocationStatusChanged(_ status: DBTNAOFIXSTATUS) {
        NSLog("didLocationStatusChanged")
        if(status==DBTNAOFIXSTATUS.NAO_FIX_AVAILABLE){
            NSLog("NAO fix available")
        }
        if(status==DBTNAOFIXSTATUS.NAO_FIX_UNAVAILABLE){
            NSLog("NAO fix unavailable")
        }
        if(status==DBTNAOFIXSTATUS.NAO_OUT_OF_SERVICE){
            NSLog("NAO out of service")
        }
        if(status==DBTNAOFIXSTATUS.NAO_TEMPORARY_UNAVAILABLE){
            NSLog("NAO temporary unavailable")
        }
        //TODO Find why emulation works and real positionning doesn't
        //Most of the time error message is NAO TEMPORARY UNAVAILABLE
        //Idk if bluetooth doesn't work properly or if permissions is missing (see how to ask permission)
        //TODO Find a way to store log file
    }

    func askPermissions(){
        NSLog("Permissions")
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
        }
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        askPermissions()
        let alert = UIAlertController(title: "Did you bring your towel?", message: "It's recommended you bring your towel before continuing.", preferredStyle: .alert)
        
        alert.addAction(UIAlertAction(title: "Yes", style: .default, handler: nil))
        alert.addAction(UIAlertAction(title: "No", style: .cancel, handler: nil))
        
        self.present(alert, animated: true)
        
        //mapPicker.delegate = self
        //mapPicker.dataSource = self
        mapView.setCenter(CLLocationCoordinate2D(latitude: 48.44159, longitude: -4.41268), zoomLevel: 17, animated: false)
        mapWizePlugin = MapwizePlugin.init(mapView, options: MWZOptions.init())
        mapWizePlugin.delegate = self
        mapWizePlugin.mapboxDelegate = self
    }
    
    override func viewDidAppear(_ animated: Bool) {
        let OASKey = readPList(key: "OAS-Brest")
        if  OASKey != "Error"{
            locationHandle = NAOLocationHandle.init(key: OASKey, delegate: self, sensorsDelegate: self)
            geofenceHandle = NAOGeofencingHandle.init(key: OASKey, delegate: self, sensorsDelegate: self)
            locationHandle.synchronizeData(self)
            geofenceHandle.synchronizeData(self)
        }
        else{
            //ERROR
        }
    }
    
    
    func mapwizePluginDidLoad(_ mapwizePlugin: MapwizePlugin!) {
        NSLog("mapwizePluginDidLoad")
        mapWizePlugin.setIndoorLocationProvider(poleStarLocationProvider)
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
            let alertMessage = UIAlertController(title: "Key not found", message: "Update Keys.plist file", preferredStyle: UIAlertControllerStyle.alert)
            alertMessage.addAction(UIAlertAction(title: "Exit", style: UIAlertActionStyle.destructive, handler:{ (action:UIAlertAction!) -> Void in
                exit(0)
            }))
            self.present(alertMessage, animated: true, completion: nil)
            return "Error"
        }else{
            let alertMessage = UIAlertController(title: "Invalid Key", message: "Keys.plist file must be missing", preferredStyle: UIAlertControllerStyle.alert)
            alertMessage.addAction(UIAlertAction(title: "Exit", style: UIAlertActionStyle.destructive, handler:{ (action:UIAlertAction!) -> Void in
                exit(0)
            }))
            present(alertMessage,animated: true,completion: nil)
        }
        return "Error"
        //random error, see log files
    }
}
