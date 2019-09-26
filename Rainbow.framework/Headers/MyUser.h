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
#import <UIKit/UIKit.h>
#import "Server.h"
#import "Contact.h"
#import "NomadicStatus.h"
#import "CallForwardStatus.h"
#import "MediaPillarStatus.h"
#import "Peer.h"

// User notification sent when features has been updated
FOUNDATION_EXPORT NSString *const kMyUserFeatureDidUpdate;
// Notification sent when there is an update of profiles for the logged user
FOUNDATION_EXPORT NSString *const kMyUserProfilesDidUpdate;
// User notification sent when nomadic status has been updated
FOUNDATION_EXPORT NSString *const kMyUserNomadicStatusDidUpdate;
// User notification sent when call forward status changed
FOUNDATION_EXPORT NSString *const kMyUserCallForwardDidUpdate;
// User notification sent when PBX voicemail count changed
FOUNDATION_EXPORT NSString *const kMyUserVoicemailCountDidUpdate;

/**
 *  Completion handler invoked when uploading a image to be used as the user's avatar
 *  @param error    The error returned by the server or nil
 */
typedef void (^MyUserAvatarUploadCompletionHandler)(NSError *error);

/**
 *  All informations about the currenlty logged user
 */
@interface MyUser : NSObject
/**
 *  @name MyUser properties
 */
/** username of the logged user */
@property (nonatomic, readonly) NSString *username;
/** password of the logged user */
@property (nonatomic, readonly) NSString *password;
/** Server where the logged user is connected 
 *  @see Server
 */
@property (nonatomic, readonly) Server *server;
/** Contact object that represent the logged user
 * @see Contact
 */
@property (nonatomic, readonly) Contact *contact;
/** Boolean value to known if the user is correclyt initialized on server side */
@property (nonatomic, readonly) BOOL isInitialized;

// Boolean value to known if the user is in the default company
@property (nonatomic, readonly) BOOL isInDefaultCompany;

// Roles attributed to the user
@property (nonatomic, readonly) NSArray *roles;

// Check if the connected user is a "simple" user, not an admin or a superadmin
@property (nonatomic, readonly) BOOL isUser;

// Check if the connected user is a guest
@property (nonatomic, readonly) BOOL isGuest;

// Check if the user is allowed to use webRTC on mobile
@property (nonatomic, readonly) BOOL isAllowedToUseWebRTCMobile;

// Check if the user is allowed to participate in webRTC call
@property (nonatomic, readonly) BOOL isAllowedToParticipateInWebRTCConference;

// Check if the user is allowed to use telephony conference
@property (nonatomic, readonly) BOOL isAllowedToUseTelephonyConference;

// Check if the user is allowed to use the dial out in conference
@property (nonatomic, readonly) BOOL isAllowedToUseDialOutConference;

// Check if the user is under a dial-in only bundle
@property (nonatomic, readonly) BOOL isUserDialInOnlyBundle;

// Check if the user is allowed to use the webRTC Telephony conference
@property (nonatomic, readonly) BOOL isAllowedToUseWebRTCTelephonyConference;

// Check if the user is allowed to participate in telephony conference
@property (nonatomic, readonly) BOOL isAllowedToParticipateInTelephonyConference;

// Check if the user is allowed to use webRTC Video on mobile
@property (nonatomic, readonly) BOOL isAllowedToUseWebRTCMobileVideo;

// Check if the user is allow to use active directory search
@property (nonatomic, readonly) BOOL isAllowedToSearchInActiveDirectory;

// Check if the user is allow to use PBX phonebook search
@property (nonatomic, readonly) BOOL isAllowedToSearchInPBXPhonebook;

@property (nonatomic, readonly) BOOL isAllowedToParticipateInWebRTCMobile;

// Check if the user is allowed to use telephony nomadic mode
@property (nonatomic, readonly) BOOL isAllowedToUseTelephonyNomadicMode;

// Check if the user is allowed to use telephony call forward
@property (nonatomic, readonly) BOOL isAllowedToUseTelephonyCallForward;

// Check if the user is allowed to use telephony webRTC to PSTN
@property (nonatomic, readonly) BOOL isAllowedToUseTelephonyWebRTCtoPSTN;

// Check if the user is allowed to use telephony webRTC with MediaPillar
@property (nonatomic, readonly) BOOL isAllowedToUseTelephonyWebRTCGateway;

// Check if the user is allowed to use telephony voice mail
@property (nonatomic, readonly) BOOL isAllowedToUseTelephonyVoiceMail;

// Check if the user is allowed to use telephony in general
@property (nonatomic, readonly) BOOL isAllowedToUseTelephony;

// Check if the user is allowed to use the promote / demote in bubble feature
@property (nonatomic, readonly) BOOL isAllowedToUsePromoteDemoteFeature;

// Check if the user is allowed to use android tv
@property (nonatomic, readonly) BOOL isAllowedToUseAndroidTv;

// Check if the user can share his current location
@property (nonatomic, readonly) BOOL isAllowedToShareCurrentLocation;

// Check if the user can create a channel
@property (nonatomic, readonly) BOOL isAllowedToCreateChannel;

// Check if the user can create a public channel (opposed to company channel)
@property (nonatomic, readonly) BOOL isAllowedToCreatePublicChannel;

// Check if the user can create closed / restricted channel
@property (nonatomic, readonly) BOOL isAllowedToCreateClosedChannel;

// Check if the user can invite all members from his company to a channel
@property (nonatomic, readonly) BOOL isAllowedToInviteAllCompanyMembersInChannel;

// Maximum number of participant in room
@property (nonatomic, readonly) NSInteger maxNumberOfParticipantPerRoom;

// Maximum number of WebRTC participants in room
@property (nonatomic, readonly) NSInteger maxNumberOfWebRTCParticipantsPerRoom;

// Maximum number of favorite conversations
@property (nonatomic, readonly) NSInteger maxFavoriteConversationsCount;

// Name of profile associated to user
@property (nonatomic, readonly) NSArray *profilesName;

// Check if the user can create conference. Change when PGI server is ready.
@property (nonatomic, readonly) BOOL isReadyToCreateConference;

// The Application ID string
@property (nonatomic, readonly) NSString *appID;

// The secret key associated to the AppID
@property (nonatomic,readonly) NSString *secretKey;

// The application token received from server
@property (nonatomic,readonly) NSString *appToken;

// The telephony nomadic status
@property (nonatomic,readonly) NomadicStatus *nomadicStatus;

// is Nomadic activated
@property (nonatomic,readonly) BOOL isNomadicModeActivated;

//
@property (nonatomic,readonly) CallForwardStatus *callForwardStatus;

//
@property (nonatomic,readonly) NSString *voiceMailNumber;

// Number of new voicemails
@property (nonatomic, readonly) NSInteger voiceMailCount;

// The telephony mediapillar status
@property (nonatomic,readonly) MediaPillarStatus *mediaPillarStatus;

// A telephony choice when in presence DND
@property (nonatomic, readwrite) BOOL shouldDeflectToVmIfDnd;

// Check if the user can retreive the MediaPillar jid.
//@property (nonatomic, readonly) BOOL isAvailableThroughMediaPillar;

/**
 * Upload an image to be used as the user avatar
 *
 * @param image                 the new image to use as the avatar
 * @param completionHandler     the completion handler invoked when the operation is done
 */
-(void) setAvatar:(UIImage *)image withCompletionHandler:(MyUserAvatarUploadCompletionHandler) completionHandler;

// Highest service plan (Enterprise / Business / Essential)
-(NSString *) getServicePlan;

// Check if the user token validity
@property (nonatomic, readonly) BOOL isTokenValid;

/**
 *  Return authentication type value as a string eg: @"RAINBOW", @"SAML"
 */
@property (nonatomic, readonly) NSString *authenticationType;

@end
