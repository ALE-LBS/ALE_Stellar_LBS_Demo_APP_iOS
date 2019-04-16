//
//  LocationDelegate.swift
//  StellarLbsDemoApplication
//
//  Created by Vincent Aymonin on 15/04/2019.
//  Copyright © 2019 ALE. All rights reserved.
//

class LocationHandle: NSObject, NAOSensorsDelegate, NAOLocationHandleDelegate, NAOGeofencingHandleDelegate, NAOSyncDelegate{
    
    var locationHandle : NAOLocationHandle?
    var geofencingHandle : NAOGeofencingHandle?
    var masterViewController: MasterViewController?
    
    init(masterViewController:MasterViewController?) {
        super.init()
        self.masterViewController = masterViewController
    }
    
    func initLocation(key:String){
        locationHandle = NAOLocationHandle.init(key: key, delegate: self, sensorsDelegate: self)
        geofencingHandle = NAOGeofencingHandle.init(key: key, delegate: self, sensorsDelegate: self)
        locationHandle!.synchronizeData(self)
        geofencingHandle!.synchronizeData(self)
    }
    
    //NAOSyncDelegate
    func didSynchronizationSuccess() {
        locationHandle!.start()
        geofencingHandle!.start()
    }
    
    func didSynchronizationFailure(_ errorCode: DBNAOERRORCODE, msg message: String!) {
        var error:String
        switch errorCode {
        case DBNAOERRORCODE.INVALID_API_KEY:
            error = "Invalid Api Key"
        case DBNAOERRORCODE.INTERNAL_ERROR:
            error = "Internal Error"
        case DBNAOERRORCODE.DATA_SYNCHRO:
            error = "Unable to synchronize data"
        case DBNAOERRORCODE.GENERIC_ERROR:
            error = "Generic error"
        case DBNAOERRORCODE.SERVICE_LIFECYCLE:
            error = "Problem occured during instanciation/termination"
        case DBNAOERRORCODE.UNSUPPORTED_OS:
            error = "Unsupported OS"
        default:
            error = "Error"
        }
        NSLog("Synchronization Failure: " + error)
    }
    
    //NAOGeofencingHandleDelegate
    func didFire(_ alert: NaoAlert!) {
        NSLog("didFire")
        if(alert.content.starts(with: "http")){
            NSLog("Alert starts with http")
            UIApplication.shared.open(URL.init(string: alert.content)!, options: convertToUIApplicationOpenExternalURLOptionsKeyDictionary([:]), completionHandler: nil)
        }
    }
    
    // Helper function inserted by Swift 4.2 migrator.
    fileprivate func convertToUIApplicationOpenExternalURLOptionsKeyDictionary(_ input: [String: Any]) -> [UIApplication.OpenExternalURLOptionsKey: Any] {
        return Dictionary(uniqueKeysWithValues: input.map { key, value in (UIApplication.OpenExternalURLOptionsKey(rawValue: key), value)})
    }
    
    //NAOLocationHandleDelegate
    func didFailWithErrorCode(_ errCode: DBNAOERRORCODE, andMessage message: String!) {
        var error:String
        switch errCode {
        case DBNAOERRORCODE.INVALID_API_KEY:
            error = "Invalid Api Key"
        case DBNAOERRORCODE.INTERNAL_ERROR:
            error = "Internal Error"
        case DBNAOERRORCODE.DATA_SYNCHRO:
            error = "Unable to synchronize data"
        case DBNAOERRORCODE.GENERIC_ERROR:
            error = "Generic error"
        case DBNAOERRORCODE.SERVICE_LIFECYCLE:
            error = "Problem occured during instanciation/termination"
        case DBNAOERRORCODE.UNSUPPORTED_OS:
            error = "Unsupported OS"
        default:
            error = "Error"
        }
        NSLog("Location Failed: " + error)
    }
    
    func didLocationChange(_ location: CLLocation!) {
        NSLog("didLocationChange")
        NSLog("latitude: " + location.coordinate.latitude.description)
        NSLog("longitude: " + location.coordinate.longitude.description)
    }
    
    func didLocationStatusChanged(_ status: DBTNAOFIXSTATUS) {
        switch status {
        case DBTNAOFIXSTATUS.NAO_FIX_AVAILABLE:
            NSLog("NAO FIX AVAILABLE")
        case DBTNAOFIXSTATUS.NAO_OUT_OF_SERVICE:
            NSLog("NAO OUT OF SERVICE")
        case DBTNAOFIXSTATUS.NAO_FIX_UNAVAILABLE:
            NSLog("NAO FIX UNAVAILABLE")
        case DBTNAOFIXSTATUS.NAO_TEMPORARY_UNAVAILABLE:
            NSLog("NAO FIX TEMPORARY UNAVAILABLE")
        default:
            NSLog("didLocationStatusChanged")
        }
    }
    
    //NAOSensorDelegate
    func requiresWifiOn() {
        masterViewController!.displayMessage(title: "Wifi Required", message: "This app requires Wifi ON")
    }
    
    func requiresBLEOn() {
        masterViewController!.displayMessage(title: "Bluetooth Required", message: "This app requires Blutooth ON")
    }
    
    func requiresLocationOn() {
        masterViewController!.displayMessage(title: "Location Services Required", message: "The app needs to access your location")
    }
    
    func requiresCompassCalibration() {
        masterViewController!.displayMessage(title: "Compass Calibration Required", message: "Youu need to recalibrate the compass")
    }
}
