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
    let lastUserPosition:ILIndoorLocation? = nil
    
    override init!() {
        //self.addDelegate(self)
    }
    
    func supportFloor() -> Bool{
        return false
    }
    
    func getLastUserPositionMWZ() -> MWZLatLngFloor{
        return MWZLatLngFloor.init(latitude: lastUserPosition?.latitude ?? 0, longitude: lastUserPosition?.longitude ?? 0)
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
        self.dispatchDidUpdate(indoorLocation)
    }
    
}
