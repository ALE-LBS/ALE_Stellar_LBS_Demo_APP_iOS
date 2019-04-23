//
//  LocationProvider.swift
//  StellarLbsDemoApplication
//
//  Created by Jerome Elleouet on 08/03/2018.
//  Copyright © 2018 ALE. All rights reserved.
//

import Foundation
import MapwizeForMapbox

//
class OASLocationProvider: ILIndoorLocationProvider {
    
    var isDispatchStarted:Bool = false
    
    override init!() {
        //self.addDelegate(self)
    }
    
    func supportFloor() -> Bool{
        return false
    }
    
    override func start(){
        NSLog("Location Provider Start")
        self.dispatchDidStart()
        self.isDispatchStarted = true
    }
    
    override func stop(){
        NSLog("Location Provider Stop")
        self.dispatchDidStop()
        self.isDispatchStarted = false
    }
    
    override func isStarted() -> Bool{
        return self.isDispatchStarted
    }
    
    func setLocation(indoorLocation:ILIndoorLocation){
        NSLog(String(indoorLocation.latitude))
        NSLog(String(indoorLocation.longitude))
        self.dispatchDidUpdate(indoorLocation)
    }
    
}
