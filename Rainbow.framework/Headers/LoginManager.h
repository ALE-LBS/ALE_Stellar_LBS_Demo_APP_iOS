/*
 * Rainbow
 *
 * Copyright (c) 2016, ALE International
 * All rights reserved.
 *
 * ALE International Proprietary Information
 *
 * Contains proprietary/trade secret information which is the property of
 * ALE International and must not be made available to, or copied or used by
 * anyone outside ALE International without its written authorization
 *
 * Not to be disclosed or used except in accordance with applicable agreements.
 */

#import <Foundation/Foundation.h>

/**
 *  @name Login manager Notifications
 * These notifications are dispatched during the connection step to Rainbow. 
 */

/**
 * This constant represents the name of an event fired when the user try to log-in
 * :nodoc:
 */
FOUNDATION_EXPORT NSString *const kLoginManagerWillLogin;

/** 
    This constant represents the name of an event fired when the user has successfully logged-in to Rainbow
        
    - Since: 1.0
*/
FOUNDATION_EXPORT NSString *const kLoginManagerDidLoginSucceeded;

/** 
    This constant represents the name of an event fired when the user has been successfully logged-out from Rainbow
    Contains an `NSObject`which is nil in case of success otherwise an `NSError` object
        
    - Since: 1.0
*/
FOUNDATION_EXPORT NSString *const kLoginManagerDidLogoutSucceeded;

/** 
    This constant represents the name of an event fired when the connection to Rainbow has been lost
        
    - Since: 1.0
*/
FOUNDATION_EXPORT NSString *const kLoginManagerDidLostConnection;

/** 
    This constant represents the name of an event fired when the connection to Rainbow has been retrieved after a connection lost or after application has been killed
        
    - Since: 1.0
*/
FOUNDATION_EXPORT NSString *const kLoginManagerDidReconnect;

/** 
    This constant represents the name of an event fired when the user failed to authenticate to Rainbow
    Contains an `NSObject`which is nil in case of success otherwise an `NSError` object
        
    - Since: 1.0
*/
FOUNDATION_EXPORT NSString *const kLoginManagerDidFailedToAuthenticate;

/** 
    This constant represents the name of an event fired when the SDK is ready to connect to a specific host.
    Contains an `NSObject` of type `Server`
        
    - Since: 1.0
*/
FOUNDATION_EXPORT NSString *const kLoginManagerDidChangeServer;

// Login manager notification sent when user is changed
FOUNDATION_EXPORT NSString *const kLoginManagerDidChangeUser;

/** 
    This constant represents the name of an event fired when the SDK try to connect to a specific host (after 5s).
        
    - Since: 1.0
*/
FOUNDATION_EXPORT NSString *const kLoginManagerTryToReconnect;

/**
 *  Completion handler for registration process
 *
 *  @param jsonResponse the server json answer in dictionary format
 *  @param error        the returned error in case of error
 */
typedef void(^LoginManagerRegistrationCompletionHandler)(NSDictionary *jsonResponse, NSError *error);

/**
 *  Completion handler for SAML login process
 *
 *  @param type the server json answer in dictionary format
 *  @param loginUrl the login url return by IDP
 *  @param headersParameters    the required headers to build the authentication request
 *  @param error    the returned error in case of error
 */
typedef void(^LoginManagerSAMLLoginCompletionHandler)(NSString *type, NSURL *loginUrl, NSDictionary *headersParameters, NSError *error);

/**
 *
 * Provides methods and events to manage the connection and the authentication to Rainbow
 * 
 * The LoginManager provide a means by which the user can connect or reconnect to the Rainbow platform as well as to disconnect.
 * 
 * These mechanisms are asynchronous. In order to know the status of these requests, you need to use the `NSNotificationCenter` and add observers to the notifications you want to be notified.
 *
 * Notifications sent:
 * - `kLoginManagerDidChangeServer`
 * - `kLoginManagerDidLoginSucceeded`
 * - `kLoginManagerDidFailedToAuthenticate`
 * - `kLoginManagerDidReconnect`
 * - `kLoginManagerDidLogoutSucceeded`
 * - `kLoginManagerDidLostConnection`
 */
@interface LoginManager : NSObject
/**
 *  @name LoginManager properties
 */

/**
 *  @name Properties
 */

/**
 *  Auto-login status. `YES` by default to renew automatically the Rainbow token when possible elsewhere set to `NO`, when the user disconnects manually from Rainbow
 */
@property (nonatomic, readonly) BOOL autoLogin;

/**
 *  Connection status, `YES` when connection with server is enabled
 */
@property (nonatomic, readonly) BOOL isConnected;

/**
 *  Login status, `YES` if the login success at least one time
 */
@property (nonatomic, readonly) BOOL loginDidSucceed;

/**
 *  Rainbow server version. Return a float value of the Rainbow server API version, eg: 15.0
 * :nodoc:
 */
@property (nonatomic, readonly) NSNumber *serverApiVersion;

/**
 *  @name Methods
 */

/**
 *  Connect the user to Rainbow. 
 *  This method is asynchronous, monitor LoginManager notifications for success or failure.
 *
 *  Notifications sent :
 *
 *  - `kLoginManagerDidLoginSucceeded`
 *
 *  - `kLoginManagerDidFailedToAuthenticate`
 *
 *  - `kLoginManagerTryToReconnect` 
 *
 *  - `kLoginManagerDidReconnect` 
 */
-(void) connect;

/**
 *  Connection method using a Rainbow credential token
 *
 *  @param token the Rainbow credential token to try
 *
 *  This method is asynchronous, monitor LoginManager notifications for success or failure.
 *
 *  Notifications sent :
 *
 *  - `kLoginManagerDidLoginSucceeded`
 *
 *  - `kLoginManagerDidFailedToAuthenticate`
 *
 *  - `kLoginManagerTryToReconnect` 
 *
 *  - `kLoginManagerDidReconnect` 
 */
-(void) connectWithToken:(NSString *)token;

/**
 *  Logout and disconnect the connected user from Rainbow
 *  This method is asynchronous, monitor LoginManager notifications for success or failure.
 *
 *  Note: This method should not be called from the Main thread
 *
 *  Notifications sent :
 *
 *  - `kLoginManagerDidLogoutSucceeded`
 */
-(void) disconnect;

/**
 *  Clean all saved credentials username & password from the keychain
 */
-(void) resetAllCredentials;

/**
 *  Change the password associated to the connected user
 *
 *  @param oldPassword        Previous user password.
 *  @param password           New user password
 *  @param completionHandler  Called when the action has been performed.
 */
-(void) sendChangePassword:(NSString *) oldPassword newPassword:(NSString *) password completionHandler:(LoginManagerRegistrationCompletionHandler) completionHandler;

/**
 *  Set the username and password of the user to log in
 *
 *  @param username The username (loginEmail) of the Rainbow user
 *  @param password The password of the user
 *
 *  - Note: Username and password given to this method are automatically saved in the device keychain.
 */
-(void) setUsername:(NSString *) username andPassword:(NSString *) password;

/**
 *  This API allows to send a self-register email to a user. A temporary user token is generated and send in the email body. This token is required in the self register validation workflow
 *  :nodoc:
 *  @param emailAddress      Email of the user requesting a self-register email with a temporary token
 *  @param completionHandler called when we got a server answer.
 */
-(void) sendNotificationForEnrollmentTo:(NSString *) emailAddress completionHandler:(LoginManagerRegistrationCompletionHandler) completionHandler;

/**
 *  This api allows a user to self register in Rainbow application.
 *  :nodoc:
 *  @param loginEmail        User email address (used for login).
 *  @param password          User password.
 *  @param temporaryCode     User temporary token.
 *  @param completionHandler called when we got a server answer.
 */
-(void) sendSelfRegisterRequestWithLoginEmail:(NSString *) loginEmail password:(NSString *) password temporaryCode:(NSString *) temporaryCode completionHandler:(LoginManagerRegistrationCompletionHandler) completionHandler;

/**
 * This api allow a user to complete the registration process in Rainbow application after receiving an invitation email with an invitationID.
 *  :nodoc:  
 *  @param loginEmail        User email address (used for login).
 *  @param password          User password.
 *  @param invitationID      Invitation ID received by email
 *  @param completionHandler called when we got a server answer.
 */
-(void) sendSelfRegisterRequestWithLoginEmail:(NSString *) loginEmail password:(NSString *) password invitationId:(NSString *) invitationId completionHandler:(LoginManagerRegistrationCompletionHandler) completionHandler;

/**
 * This api allow a user to complete the registration process in Rainbow application after receiving an invitation email with an invitationID.
 *  :nodoc: 
 *  @param loginEmail        User email address (used for login).
 *  @param password          User password.
 *  @param invitationID      Invitation ID received by email
 *  @param visibility        Visibility
 *  @param completionHandler called when we got a server answer.
 */
-(void) sendSelfRegisterRequestWithLoginEmail:(NSString *) loginEmail password:(NSString *) password invitationId:(NSString *) invitationId visibility:(NSString *) visibility completionHandler:(LoginManagerRegistrationCompletionHandler) completionHandler;

/**
 * This api allow a user to complete the registration process in Rainbow application after receiving an invitation email with an invitationID.
 *  :nodoc: 
 *  @param loginEmail        User email address (used for login).
 *  @param password          User password.
 *  @param joinCompanyInvitationId      Invitation ID received by email for joining a specific company
 *  @param completionHandler called when we got a server answer.
 */
-(void) sendSelfRegisterRequestWithLoginEmail:(NSString *) loginEmail password:(NSString *) password joinCompanyInvitationId:(NSString *) joinCompanyInvitationId completionHandler:(LoginManagerRegistrationCompletionHandler) completionHandler;

/**
 *  This api allows a user to reset his Rainbow password.
 *  He will receive an email with an activation code.
 *  :nodoc:
 *  @param loginEmail        User email address
 *  @param completionHandler called when we got a server answer.
 */
-(void) sendResetPasswordEmailWithLoginEmail:(NSString *) loginEmail completionHandler:(LoginManagerRegistrationCompletionHandler) completionHandler;

/**
 *  This api allows a user to reset his Rainbow password.
 *  :nodoc:
 *  @param loginEmail        User email address
 *  @param password          new user password
 *  @param temporaryCode     User temporary token received by email
 *  @param completionHandler called when we got a server answer.
 */
-(void) sendResetPasswordWithLoginEmail:(NSString *) loginEmail password:(NSString *) password temporaryCode:(NSString *) temporaryCode completionHandler:(LoginManagerRegistrationCompletionHandler) completionHandler;

/**
 *  This api allows a user to delete his Rainbow account.
 *  :nodoc:
 */
-(void) deleteMyAccount;

/**
 *  This api allows to know the URL to perform a login.
 *  :nodoc:
 *  @param uid                User unique identifier (typicaly the login email).
 *  @param completionHandler  The server json answer in dictionary format.
 */
-(void) getUserAuthenticationURLs:(NSString *) uid completionHandler:(LoginManagerSAMLLoginCompletionHandler) completionHandler;

@end
