//
//  MapWizeController.swift
//  StellarLbsDemoApplication
//
//  Created by Vincent Aymonin on 16/04/2019.
//  Copyright © 2019 ALE. All rights reserved.
//

import UIKit
import Mapbox
import MapwizeForMapbox

class MapWizeController: UIViewController, MWZMapwizePluginDelegate, MGLMapViewDelegate {
    
    var mapwizePlugin:MapwizePlugin!
    var locationProvider:OASLocationProvider = OASLocationProvider.init()
    var isLocationProviderSet:Bool=false
    var mglMapView:MGLMapView?
    var selectedCoordinates:CLLocationCoordinate2D?
    var lastPlace:MWZPlace? = nil
    
    func changeMap(coordinates:CLLocationCoordinate2D){
        selectedCoordinates=coordinates
        setupMap()
    }
    
    func setupMap(){
        //MapBox
        let url = URL(string: "https://outdoor.mapwize.io/styles/mapwize/style.json?key=98d7bc53090ecc4da62e09269332fe5b")
        mglMapView = MGLMapView(frame: view.bounds, styleURL: url)
        mglMapView!.autoresizingMask = [.flexibleWidth, .flexibleHeight]
        mglMapView!.setCenter(selectedCoordinates!, animated: false)
        mglMapView!.setZoomLevel(17, animated: false)
        view.addSubview(mglMapView!)
        //MapWize
        mapwizePlugin = MapwizePlugin(mglMapView, options:MWZOptions())
        mapwizePlugin.delegate = self
        mapwizePlugin.mapboxDelegate = self
    }
    
    func plugin(_ plugin: MapwizePlugin!, didTap clickEvent: MWZClickEvent!) {
        NSLog("didTap")
        switch clickEvent.eventType {
        case MAP_CLICK:
            NSLog("Map Click")
        case PLACE_CLICK:
            NSLog("Place Click")
            mapwizePlugin.removeMarkers()
            mapwizePlugin.addMarker(coreLocationToMapwize(clickEvent.place.center()))
            let button = createButton(text: "Go", x: 10, y: Int(view.bounds.maxY-80), width: 50, height: 50)
            lastPlace = clickEvent.place
            button.addTarget(self, action: #selector(getDirection), for: .touchUpInside)
            mglMapView?.addSubview(button)
        case VENUE_CLICK:
            NSLog("Venue Click")
        default:
            NSLog("")
        }
        
    }
    
    @objc func getDirection(){
        mapwizePlugin.grantAccess("PINchfWpknqcXjAE", success: {
            NSLog("API Success")
            MWZApi.signin("98087bcfa9f1a716913591a5f3c8212a", success: {
                NSLog("Sign In Success")
            }, failure: { (r) in
                NSLog("Sign In Failure")
            })
        }) { (r) in
            NSLog("API Failure")
        }
        
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        //Location Provider
        locationProvider.start()
    }
    
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
    }
    
    
    
    //Tell Indoor Location Provider to update the location on the map
    func setUserPosition(_ coordinates: CLLocationCoordinate2D, floor:Int){
        if(!isLocationProviderSet){
            mapwizePlugin.setIndoorLocationProvider(locationProvider)
            isLocationProviderSet=true
        }
        if(locationProvider.isDispatchStarted){
            let indoorLocation = ILIndoorLocation.init(provider: locationProvider, latitude: coordinates.latitude, longitude: coordinates.longitude, floor: 0)!
            locationProvider.setLocation(indoorLocation: indoorLocation)
        }
    }
    
    func coreLocationToMapwize(_ location:CLLocationCoordinate2D) -> MWZLatLngFloor{
        return MWZLatLngFloor.init(latitude: location.latitude, longitude: location.longitude, floor: 0)
    }
    
    func createButton(text:String, x:Int, y:Int, width:Int, height:Int) -> UIButton{
        let button = UIButton(type: .custom)
        button.frame = CGRect(x: x, y: y, width: width, height: height)
        button.layer.cornerRadius = 0.5 * button.bounds.size.width
        button.autoresizingMask = [.flexibleLeftMargin, .flexibleBottomMargin]
        button.setTitleColor(UIColor.black, for: .normal)
        button.backgroundColor = .white
        button.layer.shadowColor = UIColor(red: 0, green: 0, blue: 0, alpha: 0.3).cgColor
        button.layer.shadowOffset = CGSize(width: 0, height: 3)
        button.layer.shadowOpacity = 1.0
        button.layer.shadowRadius = 10.0
        button.layer.masksToBounds = false
        button.setTitle(text, for: .normal)
        return button
    }
}
