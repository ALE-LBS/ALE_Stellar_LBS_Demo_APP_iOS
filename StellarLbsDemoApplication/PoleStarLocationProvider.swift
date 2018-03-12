//
//  LocationProvider.swift
//  StellarLbsDemoApplication
//
//  Created by Jerome Elleouet on 08/03/2018.
//  Copyright © 2018 ALE. All rights reserved.
//

import Foundation
import MapwizeForMapbox

class PoleStarLocationProvider: ILIndoorLocationProvider {
    
    func supportFloor() -> Bool{
        return false
    }
    
    override func start(){
        //code
    }
    
    override func stop(){
        //code
    }
    
    override func isStarted() -> Bool{
        return true
    }
    
    func setLocation(indoorLocation:ILIndoorLocation){
        self.dispatchDidUpdate(indoorLocation)
    }
    
}
