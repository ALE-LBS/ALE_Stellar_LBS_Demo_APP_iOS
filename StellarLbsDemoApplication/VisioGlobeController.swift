//
//  VisioGlobeController.swift
//  StellarLbsDemoApplication
//
//  Created by Vincent Aymonin on 16/04/2019.
//  Copyright © 2019 ALE. All rights reserved.
//

import UIKit
import VisioMoveEssential

class VisioGlobeController: UIViewController {

    @IBOutlet weak var mapView: VMEMapView!
    var searchViewCallback: VMESearchViewCallback = VisioGlobeSearchViewCallback.init()
    var mapHash:String?
    
    func setMapHash(_ mapHash: String){
        self.mapHash=mapHash
    }
    
    func reload(mapHash:String){
        if(mapView != nil){
            mapView.unloadMap()
            self.setMapHash(mapHash)
            mapView.setMapHash(mapHash)
            mapView.loadMap()
        }
    }//TODO Rethink (find a way to set maphash at launch)
    
    override func viewDidLoad() {
        mapView.setMapHash(mapHash)
        mapView.loadMap()
        mapView.showSearchView(withTitle: "Search", callback: searchViewCallback)
    }
    
    func setUserPosition(_ coordinates:CLLocation){
        NSLog("VGController: lat: " + coordinates.coordinate.latitude.description + " long: " + coordinates.coordinate.longitude.description)
        mapView.update(mapView.createLocation(from: coordinates))
    }
}

class VisioGlobeSearchViewCallback: NSObject, VMESearchViewCallback{
    
    func search(_ mapView: VMEMapView!, didSelectPlaceID placeID: String!) {
        NSLog("Place selected: " + placeID)
    }
    
    func searchViewDidCancel(_ mapView: VMEMapView!) {
        NSLog("SearchViewDidCancel")
    }
    
    
}
