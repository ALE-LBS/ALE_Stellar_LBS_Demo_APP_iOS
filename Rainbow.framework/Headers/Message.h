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
#import "Peer.h"
#import "Contact.h"
#import "File.h"
#import "CallLog.h"
#import "NomadicStatus.h"
#define kMessageCallLogEventTypeKey @"eventType"
#define kMessageCallLogEventDateKey @"eventDate"
#define kMessageCallLogEventDurationKey @"eventDuration"

/**
 *  The different message types
 */
typedef NS_ENUM(NSInteger, MessageType) {
    /**
     *  Type unknown
     */
    MessageTypeUnknown = 0,
    /**
     *  Type chat
     */
    MessageTypeChat,
    /**
     *  Type Group chat
     */
    MessageTypeGroupChat,
    /**
     *  Type WebRTC
     */
    MessageTypeWebRTC,
    /**
     *  Type WebRTC Start
     */
    MessageTypeWebRTCStart,
    /**
     *  Type WebRTC Ringing
     */
    MessageTypeWebRTCRinging,
    /**
     *  Type File Transfer
     */
    MessageTypeFileTransfer,
    /**
     *  Type Group chat event
     */
    MessageTypeGroupChatEvent,
    /**
     *  Type channel
     */
    MessageTypeChannel,
    
    MessageTypeCallRecordingStart,
    MessageTypeCallRecordingStop,
    
    MessageTypeCallServiceNomadicStatus
};

/**
 *  The different message delivery states
 */
typedef NS_ENUM(NSInteger, MessageDeliveryState) {
    /**
     *  State sent
     */
    MessageDeliveryStateSent = 0,
    /**
     *  State delivered
     */
    MessageDeliveryStateDelivered,
    /**
     *  State received
     */
    MessageDeliveryStateReceived,
    /**
     *  State read
     */
    MessageDeliveryStateRead,
    /**
     *  State failed
     */
    MessageDeliveryStateFailed
};

/**
 * The different kind of group chat events 'invitation’,  ‘welcome’, ‘join’, ‘leave’ or ‘close'
 */
typedef NS_ENUM(NSInteger, MessageGroupChatEventType) {
    /**
     *  Not a group chat event
     */
    MessageGroupChatEventNone = 0,
    /**
     *  Type invitation
     */
    MessageGroupChatEventInvitation,
    /**
     *  Type welcome
     */
    MessageGroupChatEventWelcome,
    /**
     *  Type join
     */
    MessageGroupChatEventJoin,
    /**
     *  Type leave
     */
    MessageGroupChatEventLeave,
    /**
     *  Type close
     */
    MessageGroupChatEventClose,
    /**
     *  Type conference add
     */
    MessageGroupChatEventConferenceAdd,
    /**
     *  Type conference remove
     */
    MessageGroupChatEventConferenceRemove,
    /**
     *  Type conference reminder
     */
    MessageGroupChatEventConferenceReminder
};

/**
 *  Message object.
 *  It represents a message exchanged between me and somebody else.
 *  The structure is quite simple, except for the distinction 
 *  between peer and via objects.
 */
@class Location;
@interface Message : NSObject
/**
 *  The message type
 *  @see MessageType
 */
@property (nonatomic, readonly) MessageType type;

/**
 *  The message peer. This is the real person I'm chatting with.
 *  In any case (P2P or Room conversation), this is the "Contact" instance
 *  of the real remote person I'm chatting with.
 *  @see Peer
 */
@property (nonatomic, readonly) Peer *peer;

/**
 *  The message via. This is the intermediate entity I'm chatting with.
 *  In case of P2P conversation, this is the same as the peer.
 *  But in case of Room conversation, this is the "Room" instance
 *  which is the intermediate between me and the remote real persons.
 *  @see Peer
 */
@property (nonatomic, readonly) Peer *via;

/** Message unique ID */
@property (nonatomic, readonly) NSString *messageID;
/** Message Body */
@property (nonatomic, readonly) NSString *body;
/** Message Body in markdown style */
@property (nonatomic, readonly) NSString *bodyInMarkdown;
/** Url of the image if the body starts with /img and has a correct url as parameter*/
@property (nonatomic, readonly) NSString *imageUrl;
/** Url of the static gif image if the body starts with /img and has a correct url as parameter */
@property (nonatomic, readonly) NSString *staticGifUrl;
/** Message timestamp */
@property (nonatomic, readonly) NSDate *timestamp;
/** Message date, it is a alias for the timestamp property */
@property (nonatomic, readonly) NSDate *date;
/** Boolean value set to `YES` if the message is outgoing */
@property (nonatomic, readonly) BOOL isOutgoing;
/** Boolean value set to `YES` if the message is a composing message */
@property (nonatomic, readonly) BOOL isComposing;
/** Boolean value set to `YES` if the message has been deleted */
@property (nonatomic, readonly) BOOL isDeleted;

/**
 *  The message delivery state
 *  @see MessageDeliveryState
 */
@property (nonatomic, readonly) MessageDeliveryState state;

/**
 * if the message type is MessageTypeGroupChatEvent this is the type of the group chat
 * event
 */
@property (nonatomic, readonly) MessageGroupChatEventType groupChatEventType;

/**
 * if the message type is MessageTypeGroupChatEvent this is the peer (contact or room)
 * for the event
 */
@property (nonatomic, readonly) Peer *groupChatEventPeer;

/**
 * Boolean set to `YES` if this message has been presented in push
 */
@property (nonatomic, readonly) BOOL hasBeenPresentedInPush;

/**
 * Boolean set to `YES` if this message has been resent
 */
@property (nonatomic, readonly) BOOL isResentMessage;

/**
 * The message ID of the replaced message if this message is a replacement message
 * for a previously sent message in the XEP-0308 sense
 */
@property (nonatomic, readonly) NSString *replacedMessageID;

/**
 * The date of the replacement message if this one has been edited
 * See XEP-0308 for more details
 */

@property (nonatomic, readonly) NSDate *replacedDate;

/**
 * if the message type is MessageTypeWebRTC this object describe the event
 */
@property (nonatomic, readonly) CallLog *callLog;

/**
 * if the message contains location Info this object describe all information about the location
 */

// change to Class Location.h
@property (nonatomic, readonly) Location *location;


/**
 * Attachment found in the message
 * `nil` if this message have no attachment
 */
@property (nonatomic, readonly) File *attachment;

/**
 * Nomadic status found in the message
 * `nil` if this message have no status
 */
@property (nonatomic, readonly) NomadicStatus *nomadicStatus;

/**
 * Message id of the original message this message is a reply of
 * `nil` if this message is not a reply
 */
@property (nonatomic, readonly) NSString *answeredMessageId;

/**
 * Message timestamp of the original message this message is a reply of
 * `nil` if this message is not a reply
 */
@property (nonatomic, readonly) NSString *answeredMessageTimestamp;

/**
 * Original Message this message is a reply of
 * `nil` if this message is not a reply or not already found in history
 */
@property (nonatomic, readonly) Message *answeredMessage;

/**
 *  Returns the delivery date for a given state, or nil.
 *
 *  @param state The state
 *
 *  @return The date when this state happened
 */
-(NSDate *) deliveryDateForState:(MessageDeliveryState) state;

/**
 *  Returns the MessageGroupChatEventType value from a string.
 *
 *  @eventName the event name as found in the xmpp message :
 *  'invitation’,  ‘welcome’, ‘join’, ‘leave’ or ‘close'
 *
 *  @return The corresponding enum value, MessageGroupChatEventNone if the string is not a valid one
 */

+(MessageGroupChatEventType) messageGroupChatEventTypeFromString:(NSString *)eventName;

/**
 *  Returns the MessageDeliveryState string from enum.
 *
 *  @return The corresponding String value
 */
+(NSString *) stringForDeliveryState:(MessageDeliveryState) deliveryState;
@end
