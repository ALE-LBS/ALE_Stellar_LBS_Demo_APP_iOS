//
//  LoginViewController.swift
//  StellarLbsDemoApplication
//
//  Created by Vincent Aymonin on 18/04/2019.
//  Copyright © 2019 ALE. All rights reserved.
//

import UIKit
import Rainbow

class LoginViewController:UIViewController, UITextFieldDelegate{
    
    @IBOutlet weak var loginField: UITextField!
    @IBOutlet weak var passwordField: UITextField!
    @IBOutlet weak var connectButton: UIButton!
    @IBOutlet weak var rainbowButton: UIButton!
    @IBOutlet weak var rainbowStatusUILabel: UILabel!
    
    var rainbowMail: String!
    var rainbowPassword: String!
    
    var isConnectedToRainbow: Bool = false {
        didSet {
            if self.isConnectedToRainbow {
                DispatchQueue.main.async {
                    self.rainbowStatusUILabel.text = "Connected"
                }
            }else{
                DispatchQueue.main.async {
                    self.rainbowStatusUILabel.text = "Disconnected"
                }
            }
        }
    }
    
    var masterViewController: MasterViewController!
    
    let preferences = UserDefaults.standard
    let rainbowMailKey = "RainbowMail"
    let rainbowPasswordKey = "RainbowPassword"
    let eDemoLoginKey = "eDemoLogin"
    let eDemoPasswordKey = "eDemoPassword"
    
    override func viewDidLoad() {
        super.viewDidLoad()
        loginField.delegate = self
        loginField.tag = 0
        passwordField.delegate = self
        passwordField.tag = 1
    }
    
    func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        if let nextTextField = textField.superview?.viewWithTag(textField.tag+1) as? UITextField {
            nextTextField.becomeFirstResponder()
        }else{
            textField.resignFirstResponder()
        }
        return false
    }
    
    //Request from https://stackoverflow.com/questions/48285694/swift-json-login-rest-with-post-and-get-response-example/48306950#48306950
    @IBAction func connectToEDemo(){
        UIApplication.shared.sendAction(#selector(UIResponder.resignFirstResponder), to: nil, from: nil, for: nil)
        if(!loginField.text!.isEmpty || !passwordField.text!.isEmpty){
            masterViewController.username = loginField.text
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
                NSLog(String(decoding: responseData, as: UTF8.self))
                do{
                    let statusCode = (response as? HTTPURLResponse)?.statusCode
                    guard statusCode == 200 else {
                        guard let errorJson = try JSONSerialization.jsonObject(with: responseData, options: []) as? [String: Any] else{
                            NSLog("Error converting data to JSON (Guard)")
                            return
                        }
                        let errorString: String = errorJson["status"] as? String ?? "Unknown Error"
                        let alertBox = UIAlertController.init(title: "Error", message: errorString, preferredStyle: .alert)
                        alertBox.addAction(UIAlertAction.init(title: "OK", style: .destructive, handler: nil))
                        DispatchQueue.main.async {
                            self.present(alertBox,animated: true, completion: nil)
                        }
                        return
                    }
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
                    //Display map selection (send action from the Map button in the navBar)
                    self.preferences.set(self.loginField.text, forKey: self.eDemoLoginKey)
                    self.preferences.set(self.passwordField.text, forKey: self.eDemoPasswordKey)
                    UIApplication.shared.sendAction(self.masterViewController.navigationButton.action!, to:self.masterViewController.navigationButton.target, from: self, for: nil)
                }
                catch{
                    NSLog("Error converting data to JSON (Exception)")
                    return
                }
            }
            //Send the request
            request.resume()
        }else{
            NSLog("Empty Fields, Connection Failed")
        }
    }
    
    func setMasterViewController(viewController: MasterViewController){
        self.masterViewController = viewController
    }
    
    //Save account if login succeded
    @objc func didLogin(notification: NSNotification) {
        self.isConnectedToRainbow = true
        preferences.set(rainbowMail, forKey: rainbowMailKey)
        preferences.set(rainbowPassword, forKey: rainbowPasswordKey)
        guard preferences.synchronize() == true else{
            //handle error ???
            return
        }
    }
    
    @objc func didReconnect(notification: NSNotification) {
        self.isConnectedToRainbow = true
    }
    
    @objc func failedToLogin(notification: NSNotification) {
        self.isConnectedToRainbow = false
    }
    
    @IBAction func connectToRainbow(){
        var savedMail:String?
        var savedPassword:String?
        //Setting up login box
        let alertBox = UIAlertController(title: "Rainbow Authentication", message: "Please enter your account", preferredStyle: .alert)
        //Setting up email field + getting saved email
        alertBox.addTextField { (emailTextField) in
            emailTextField.placeholder = "Mail address"
            emailTextField.keyboardType = .emailAddress
            emailTextField.textContentType = .emailAddress
            savedMail = self.preferences.object(forKey: self.rainbowMailKey) as? String ?? ""
            if !savedMail!.isEmpty {
                emailTextField.text = savedMail
            }
        }
        //Setting up password field + getting saved password
        alertBox.addTextField { (passwordTextField) in
            passwordTextField.textContentType = .password
            passwordTextField.placeholder = "Password"
            passwordTextField.isSecureTextEntry = true
            savedPassword = self.preferences.object(forKey: self.rainbowPasswordKey) as? String ?? ""
            if !savedPassword!.isEmpty {
                passwordTextField.text = savedPassword
            }
        }
        //Cancel button
        alertBox.addAction(UIAlertAction(title: "Cancel", style: .destructive, handler: nil))
        //Connect button
        alertBox.addAction(UIAlertAction(title: "Connect", style: .default, handler: {(action) in
            self.rainbowMail = alertBox.textFields![0].text ?? ""
            self.rainbowPassword = alertBox.textFields![1].text ?? ""
            //Reconnect only if the account is different
            if(self.rainbowMail != savedMail || self.rainbowPassword != savedPassword){
                NSLog("Rainbow: connect")
                ServicesManager.sharedInstance()?.loginManager.setUsername(self.rainbowMail, andPassword: self.rainbowPassword)
                ServicesManager.sharedInstance()?.loginManager.connect()
            }
        }))
        self.present(alertBox, animated: true, completion: nil)
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        //Setting observers
        NotificationCenter.default.addObserver(self, selector: #selector(self.failedToLogin(notification:)), name: NSNotification.Name(kLoginManagerDidFailedToAuthenticate), object: nil)
        NotificationCenter.default.addObserver(self, selector: #selector(LoginViewController.didLogin(notification:)), name: NSNotification.Name(kLoginManagerDidLoginSucceeded), object: nil)
        NotificationCenter.default.addObserver(self, selector: #selector(LoginViewController.didLogin(notification:)), name: NSNotification.Name(kLoginManagerDidReconnect), object: nil)
        //Getting account from preferences and connecting
        let savedRainbowPassword: String = self.preferences.object(forKey: self.rainbowPasswordKey) as? String ?? ""
        let savedRainbowMail: String = self.preferences.object(forKey: self.rainbowMailKey) as? String ?? ""
        if !savedRainbowPassword.isEmpty && !savedRainbowMail.isEmpty {
            ServicesManager.sharedInstance().loginManager.setUsername(savedRainbowMail, andPassword: savedRainbowPassword)
            ServicesManager.sharedInstance().loginManager.connect()
        }
        //Retrieving saved eDemo credentials
        let savedEDemoLogin: String = self.preferences.object(forKey: self.eDemoLoginKey) as? String ?? ""
        let savedEDemoPassword: String = self.preferences.object(forKey: self.eDemoPasswordKey) as? String ?? ""
        if !savedEDemoLogin.isEmpty && !savedEDemoPassword.isEmpty {
            loginField.text = savedEDemoLogin
            passwordField.text = savedEDemoPassword
        }
        //Setting up textfields (forced light theme)
        loginField.attributedPlaceholder = NSAttributedString.init(string: "Login", attributes: [NSAttributedString.Key.foregroundColor: UIColor.lightGray])
        loginField.layer.borderColor = UIColor.lightGray.cgColor
        loginField.layer.borderWidth = 0.4
        passwordField.attributedPlaceholder = NSAttributedString.init(string: "Password", attributes: [NSAttributedString.Key.foregroundColor: UIColor.lightGray])
        passwordField.layer.borderColor = UIColor.lightGray.cgColor
        passwordField.layer.borderWidth = 0.4
    }
}
