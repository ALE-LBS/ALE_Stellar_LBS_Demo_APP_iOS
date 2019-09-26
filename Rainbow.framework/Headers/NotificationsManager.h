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

FOUNDATION_EXPORT NSString * _Nullable const kNotificationsManagerHandleNotification;

/**
 *  Purpose of this class is to deal with all push notifications
 */
@interface NotificationsManager : NSObject
/**
 *  Register for user notifications
 *  @discussion ask to the platform to display notification with following types UIUserNotificationTypeAlert | UIUserNotificationTypeBadge | UIUserNotificationTypeSound and also some categories to allow user to interact directly with the notification
 */
-(void) registerForUserNotificationsSettingsWithCompletionHandler:(void (^_Nullable)(BOOL granted, NSError *__nullable error))completionHandler;

/**
 *  Did register for remote notifications with device token
 *  @discussion You must invoke this method when the platform give you the push token generated
 *  @param deviceToken  token retreived from the platform
 *
 */
-(void) didRegisterForRemoteNotificationsWithDeviceToken:(NSData *_Nullable) deviceToken;


/**
 *  Handle Notification
 *  @discussion You must invoke this method when the platform inform you that the user has interacted with the presented notification
 *  @param identifier   identifier of the notification
 *  @param userInfo     user informations contained in the notification
 *  @param responseInfo response informations contained in the notification if the user interact with the notification
 */
-(void) handleNotificationWithIdentifier:(NSString *_Nullable)identifier withUserInfo:(NSDictionary *_Nullable)userInfo withResponseInformation:(NSDictionary *_Nullable) responseInfo;
/**
 *  Did receive notification
 *  @discussion You must invoke this method when the platform inform you that the user has interacted with the presented notification.
 *  @param userInfo user informations contained in the notification
 */
-(void) didReceiveNotificationWithUserInfo:(NSDictionary *_Nullable) userInfo;

/**
 *  Did receive notification
 *  @discussion You must invoke this method when the platform inform you that the user has received notification.
 *  @param userInfo user informations contained in the notification
 */
-(void) saveNotificationWithUserInfo:(NSDictionary *_Nonnull) userInfo;

@end
