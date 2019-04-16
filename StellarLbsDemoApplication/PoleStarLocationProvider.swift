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
class PoleStarLocationProvider: ILIndoorLocationProvider {
    
    var isStartedVar = false
    
    func supportFloor() -> Bool{
        return false
    }
    
    override func start(){
        isStartedVar = true
    }
    
    override func stop(){
        isStartedVar = false
    }
    
    override func isStarted() -> Bool{
        return isStartedVar
    }
    
    func setLocation(indoorLocation:ILIndoorLocation){
        if(isStartedVar){
            self.dispatchDidUpdate(indoorLocation)
        }
    }
    
}
