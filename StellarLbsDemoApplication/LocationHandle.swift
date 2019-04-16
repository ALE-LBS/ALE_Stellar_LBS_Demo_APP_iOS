//
//  LocationDelegate.swift
//  StellarLbsDemoApplication
//
//  Created by Vincent Aymonin on 15/04/2019.
//  Copyright © 2019 ALE. All rights reserved.
//

class LocationDelegate: NSObject, NAOSensorsDelegate, NAOLocationHandleDelegate, NAOGeofencingHandleDelegate{
    
    var locationHandle : NAOLocationHandle?
    var geofencingHandle : NAOGeofencingHandle?
    
    func initLocation(_ key:String){
        locationHandle = NAOLocationHandle.init(key: key, delegate: self, sensorsDelegate: self)
        geofencingHandle = NAOGeofencingHandle.init(key: key, delegate: self, sensorsDelegate: self)
    }
    
    //NAOGeofencingHandleDelegate
    func didFire(_ alert: NaoAlert!) {
        <#code#>
    }
    
    //NAOLocationHandleDelegate
    func didFailWithErrorCode(_ errCode: DBNAOERRORCODE, andMessage message: String!) {
        <#code#>
    }
    
    func didLocationChange(_ location: CLLocation!) {
        <#code#>
    }
    
    func didLocationStatusChanged(_ status: DBTNAOFIXSTATUS) {
        <#code#>
    }
    
    //NAOSensorDelegate
    func requiresWifiOn() {
        let alert = UIAlertController(title: "This app requires Wifi", message: "This app requires Wifi on to continue", preferredStyle: .alert)
        alert.addAction(UIAlertAction(title: "OK", style: .default, handler: nil))
    }
    
    func requiresBLEOn() {
        let alert = UIAlertController(title: "This app requires Bluetooth", message: "This app requires Bluetooth on to continue", preferredStyle: .alert)
        alert.addAction(UIAlertAction(title: "OK", style: .default, handler: nil))
    }
    
    func requiresLocationOn() {
        let alert = UIAlertController(title: "This app requires Location", message: "This app needs to access your location", preferredStyle: .alert)
        alert.addAction(UIAlertAction(title: "OK", style: .default, handler: nil))
    }
    
    func requiresCompassCalibration() {
        let alert = UIAlertController(title: "Compass Calibration Required", message: "You need to recalibrate the compass", preferredStyle: .alert)
        alert.addAction(UIAlertAction(title: "OK", style: .default, handler: nil))
    }
    
    
    
}
