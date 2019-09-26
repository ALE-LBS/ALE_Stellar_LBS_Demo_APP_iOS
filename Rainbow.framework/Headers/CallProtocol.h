/*
 * Rainbow
 *
 * Copyright (c) 2016-2017, ALE International
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
#import "Peer.h"

/**
 * Call status
 */
typedef NS_ENUM(NSInteger, CallStatus) {
    /**
     *  Call is ringing
     */
    CallStatusRinging = 0,
    /**
     *  Call is accepted, we can proceed and establish
     */
    CallStatusConnecting,
    /**
     *  Call is declined.
     */
    CallStatusDeclined,
    /**
     *  Call has not been accepted/decline in time.
     */
    CallStatusTimeout,
    /**
     *  Call has been canceled
     */
    CallStatusCanceled,
    /**
     *  Call has been established
     */
    CallStatusEstablished,
    /**
     *  Call has been hangup
     */
    CallStatusHangup,
    /**
     *  Call has been held by the user
     */
    CallStatusHeldByUser,
    /**
     *  Call has been held by the remote
     */
    CallStatusHeldByRemote,
};

typedef NS_ENUM(NSInteger, CallCapabilities) {
    CallCapabilitiesAnswer = 1 << 0,
    CallCapabilitiesHangup = 1 << 1,
    CallCapabilitiesMute = 1 << 2,
    CallCapabilitiesSpeaker = 1 << 3,
    CallCapabilitiesVideo = 1 << 4,
    CallCapabilityAddCall = 1 << 5,
    
    CallCapabilitiesAll = CallCapabilitiesAnswer | CallCapabilitiesHangup | CallCapabilitiesMute | CallCapabilitiesSpeaker | CallCapabilitiesVideo
};


@protocol CallProtocol <NSObject>

@property (nonatomic, readonly) BOOL isMediaPillarCall;
@property (nonatomic, readonly) BOOL isCellularCall;
@property (nonatomic, readonly) BOOL isRtcCall;

-(NSString*) callRef;
-(Peer *) peer;
-(BOOL) isIncoming;
-(CallStatus) status;
-(NSDate *) connectionDate;
-(CallCapabilities) capabilities;

@end
