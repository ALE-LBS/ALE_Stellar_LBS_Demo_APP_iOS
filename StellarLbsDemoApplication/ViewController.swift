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

class ViewController: UIViewController, NAOLocationHandleDelegate, NAOSensorsDelegate, NAOSyncDelegate, MWZMapwizePluginDelegate, MGLMapViewDelegate, NAOGeofencingHandleDelegate, UIPickerViewDelegate, UIPickerViewDataSource , UIGestureRecognizerDelegate{

    let maps = ["Brest","IBM","Buenos Aires"]
    @IBOutlet weak var mapPicker: UIPickerView!
    @IBOutlet weak var mapPickerView: UIView!
    @IBOutlet weak var showMenuButton: UIBarButtonItem!
    @IBOutlet weak var mapSelectionButton: UIBarButtonItem!
    @IBOutlet var mapView: MGLMapView!
    var pickerData: [String] = [String]()    
    var mapWizePlugin:MapwizePlugin!
    var provider:PoleStarLocationProvider = PoleStarLocationProvider.init()
    var locationHandle:NAOLocationHandle! = nil
    var geofenceHandle:NAOGeofencingHandle! = nil
    
    
    
    func numberOfComponents(in pickerView: UIPickerView) -> Int {
        return 1
    }
    
    func pickerView(_ pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {
        return maps.count
    }
    
    func pickerView(_ pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int) -> String? {
        return maps[row]
    }
    
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
        NSLog(location.coordinate.latitude.description)
        NSLog(location.coordinate.longitude.description)
        let indoorLocation:ILIndoorLocation = ILIndoorLocation.init(provider: provider, latitude: location.coordinate.latitude, longitude: location.coordinate.longitude, floor: 0)
        provider.setLocation(indoorLocation: indoorLocation)
    }
    
    func didLocationStatusChanged(_ status: DBTNAOFIXSTATUS) {
        NSLog("didLocationStatusChanged")
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        mapPicker.delegate = self
        mapPicker.dataSource = self
        loadNaoClients(key: readPropertyList(key: "NaoBrestKey"))
        mapView.setCenter(CLLocationCoordinate2D(latitude: 48.44159, longitude: -4.41268), zoomLevel: 17, animated: false)
        mapWizePlugin = MapwizePlugin.init(mapView, options: MWZOptions.init())
        mapWizePlugin.delegate = self
        mapWizePlugin.mapboxDelegate = self
        // Do any additional setup after loading the view, typically from a nib.
    }
    
    
    func mapwizePluginDidLoad(_ mapwizePlugin: MapwizePlugin!) {
        mapWizePlugin.setIndoorLocationProvider(provider)
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    func readPropertyList(key: String) -> String{
        //add properties in Info.plist
        let result:String = Bundle.main.object(forInfoDictionaryKey: key) as! String
        return result
    }
    
    @IBAction func showMenu(_ sender: Any) {
        mapPickerView.isHidden = false
        locationHandle.stop()
        geofenceHandle.stop()
    }
    
    @IBAction func mapSelected(_ sender: Any){
        mapPickerView.isHidden = true
        NSLog(String(mapPicker.selectedRow(inComponent: 0)))
        if(mapPicker.selectedRow(inComponent: 0) == 0){
            loadNaoClients(key: readPropertyList(key: "NaoBrestKey"))
            mapView.setCenter(CLLocationCoordinate2D(latitude: 48.44159, longitude: -4.41268), zoomLevel: 17, animated: false)
        }
        if(mapPicker.selectedRow(inComponent: 0) == 1){
            loadNaoClients(key: readPropertyList(key: "NaoIbmKey"))
            mapView.setCenter(CLLocationCoordinate2D(latitude: 48.9063873, longitude: 2.262095), zoomLevel: 17, animated: false)
        }
        if(mapPicker.selectedRow(inComponent: 0) == 2){
            loadNaoClients(key: readPropertyList(key: "NaoArgentinaKey"))
            mapView.setCenter(CLLocationCoordinate2D(latitude: -34.526517, longitude: -58.470869), zoomLevel: 17, animated: false)
        }
        
    }
    
    func loadNaoClients(key: String){
        locationHandle = NAOLocationHandle.init(key: key, delegate: self, sensorsDelegate: self)
        locationHandle.synchronizeData(self)
        locationHandle.start()
        geofenceHandle = NAOGeofencingHandle.init(key: key, delegate: self, sensorsDelegate: self)
        geofenceHandle.synchronizeData(self)
        geofenceHandle.start()
    }


}

