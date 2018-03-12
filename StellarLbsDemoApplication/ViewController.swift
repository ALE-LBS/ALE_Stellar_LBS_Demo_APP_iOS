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

class ViewController: UIViewController, NAOLocationHandleDelegate, NAOSensorsDelegate, NAOSyncDelegate, MWZMapwizePluginDelegate, MGLMapViewDelegate {
    
    var mapWizePlugin:MapwizePlugin!
    var mapView = MGLMapView()
    var provider:PoleStarLocationProvider = PoleStarLocationProvider.init()
    var locationHandle: NAOLocationHandle! = nil
    
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
        locationHandle = NAOLocationHandle.init(key: "emulator", delegate: self, sensorsDelegate: self)
        locationHandle.synchronizeData(self)
        locationHandle.start()
        mapView = MGLMapView(frame: view.bounds)
        mapView.autoresizingMask = [.flexibleWidth, .flexibleHeight]
        mapView.setCenter(CLLocationCoordinate2D(latitude: 48.44159, longitude: -4.41268), zoomLevel: 17, animated: false)
        mapView.showsUserHeadingIndicator = false
        mapWizePlugin = MapwizePlugin.init(mapView, options: MWZOptions.init())
        mapWizePlugin.delegate = self
        mapWizePlugin.mapboxDelegate = self
        view.addSubview(mapView)
        // Do any additional setup after loading the view, typically from a nib.
    }
    
    func mapwizePluginDidLoad(_ mapwizePlugin: MapwizePlugin!) {
        mapWizePlugin.setIndoorLocationProvider(provider)
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

