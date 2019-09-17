//
//  PeopleTracker.swift
//  StellarLbsDemoApplication
//
//  Created by Vincent Aymonin on 20/05/2019.
//  Copyright © 2019 ALE. All rights reserved.
//

import Foundation

public class PeopleTracker{
    //send location to OAS cloud
    static func recordLocation(siteId:String,user:String,lon:String,lat:String,alt:String){
        let url:URL = URL(string: "https://www.omniaccess-stellar-lbs.com/nao_trackables/record_location.json?site_id=\(siteId)&auth_token=zycAscknktBEy6iXyHrxE5YfD5JPLQ")!
        var request:URLRequest = URLRequest(url: url)
        request.httpMethod = "POST"
        request.setValue("application/x-www-form-urlencoded", forHTTPHeaderField: "Content-Type")
        let postData = NSMutableData(data: "nao_trackable[name]=\(user)".data(using: String.Encoding.utf8)!)
        postData.append("&nao_trackable[lon]=\(lon)".data(using: String.Encoding.utf8)!)
        postData.append("&nao_trackable[lat]=\(lat)".data(using: String.Encoding.utf8)!)
        postData.append("&nao_trackable[alt]=\(alt)".data(using: String.Encoding.utf8)!)
        request.httpBody = postData as Data
        URLSession.shared.dataTask(with: request).resume()
        
    }
    
}
