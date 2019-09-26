//
//  InitialViewController.swift
//  StellarLbsDemoApplication
//
//  Created by Vincent Aymonin on 18/04/2019.
//  Copyright © 2019 ALE. All rights reserved.
//

import UIKit

class LoginViewController:UIViewController{
    
    @IBOutlet weak var loginField: UITextField!
    @IBOutlet weak var passwordField: UITextField!
    @IBOutlet weak var connectButton: UIButton!
    
    var masterViewController: MasterViewController!
    
    //Request from https://stackoverflow.com/questions/48285694/swift-json-login-rest-with-post-and-get-response-example/48306950#48306950
    @IBAction func connect(){
        if(!loginField.text!.isEmpty || !passwordField.text!.isEmpty){
            masterViewController.username = loginField.text
            //******************************TO DELETE************************************************************
            if(loginField.text == "a" && passwordField.text == "a"){ //Hardcoded credentials
                self.masterViewController.copyEmulationFile()
                self.masterViewController.OASKey = "Kz_sOzcwujXlPdF4U_eRfw@eu" //Dev Key
                self.masterViewController.navigationButton.isEnabled = true
                UIApplication.shared.sendAction(masterViewController.navigationButton.action!, to:masterViewController.navigationButton.target, from: self, for: nil)
            //***************************************************************************************************
            }else{
                //Building request
                let endpoint: String = "https://demoaccess.al-mydemo.com/LBS/"+loginField.text!+"/"+passwordField.text!
                let encodedEndpoint: String = endpoint.addingPercentEncoding(withAllowedCharacters: .urlHostAllowed)!
                NSLog("Encoded URL: " + encodedEndpoint)
                let url: URL = URL(string: endpoint)!
                let urlRequest: URLRequest = URLRequest(url: url)
                let config: URLSessionConfiguration = URLSessionConfiguration.default
                let session: URLSession = URLSession(configuration: config)
                let request = session.dataTask(with: urlRequest) {
                    (data, response, error) in
                    //Handle errors
                    guard error == nil else {
                        NSLog("Error received from endpoint")
                        return
                    }
                    //Check if data have been received
                    guard let responseData = data else {
                        NSLog("Did not received any data")
                        return
                    }
                    do{
                        NSLog(String(decoding: responseData, as: UTF8.self))
                        //Convert response to JSON
                        guard let responseJson = try JSONSerialization.jsonObject(with: responseData, options: []) as? [String: Any] else {
                            NSLog("Error converting data to JSON (Guard)")
                            return
                        }
                        //Extract the key from JSON Response
                        guard let responseKey = responseJson["key"] as? String else {
                            NSLog("Could not retrieve the key")
                            return
                        }
                        self.masterViewController.OASKey = responseKey
                        guard let responseSiteId = responseJson["sites"] as? [String] else {
                            NSLog("Could not retrive the site Id")
                            return
                        }
                        for id in responseSiteId {
                            self.masterViewController.siteId.append(id)
                        }
                        
                        self.masterViewController.copyEmulationFile()
                        self.masterViewController.navigationButton.isEnabled = true
                        UIApplication.shared.sendAction(self.masterViewController.navigationButton.action!, to:self.masterViewController.navigationButton.target, from: self, for: nil)
                    }
                    catch{
                        NSLog("Error converting data to JSON (Exception)")
                        return
                    }
                }
                //Send the request
                request.resume()

            }
        }else{
            NSLog("Empty Fields, Connection Failed")
        }

    }
}
