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
    
    override func viewDidLoad() {
        super.viewDidLoad()
        //MapBox
        let url = URL(string: "https://outdoor.mapwize.io/styles/mapwize/style.json?key=98d7bc53090ecc4da62e09269332fe5b")
        mglMapView = MGLMapView(frame: view.bounds, styleURL: url)
        mglMapView!.autoresizingMask = [.flexibleWidth, .flexibleHeight]
        NSLog(mglMapView!.centerCoordinate.latitude.description + " " + mglMapView!.centerCoordinate.longitude.description)
        mglMapView!.setCenter(CLLocationCoordinate2D(latitude: 48.441637506411176, longitude: -4.4127606743614365),zoomLevel: 17, animated: false)
        NSLog(mglMapView!.centerCoordinate.latitude.description + " " + mglMapView!.centerCoordinate.longitude.description)
        view.addSubview(mglMapView!)
        //MapWize
        mapwizePlugin = MapwizePlugin(mglMapView, options:MWZOptions())
        mapwizePlugin.delegate = self
        mapwizePlugin.mapboxDelegate = self
        //LocationProvider
        locationProvider.start()
    }
    
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        mglMapView!.setCenter(CLLocationCoordinate2D(latitude: 48.441637506411176, longitude: -4.4127606743614365),zoomLevel: 17, animated: false)
    }
    
    //Tell Indoor Location Provider to update the location on the map
    func setUserPosition(_ coordinates: CLLocationCoordinate2D){
        if(!isLocationProviderSet){
            mapwizePlugin.setIndoorLocationProvider(locationProvider)
            isLocationProviderSet=true
        }
        if(locationProvider.isDispatchStarted){
            let indoorLocation = ILIndoorLocation.init(provider: locationProvider, latitude: coordinates.latitude, longitude: coordinates.longitude, floor: 0)!
            locationProvider.setLocation(indoorLocation: indoorLocation)
        }
    }
}
