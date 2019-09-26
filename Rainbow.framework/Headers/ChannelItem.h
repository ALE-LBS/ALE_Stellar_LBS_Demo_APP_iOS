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
#import "Contact.h"

/**
 *  The channel item Type
 */
typedef NS_ENUM(NSInteger, ChannelItemType) {
    ChannelItemTypeUndefined = 0,
    /**
     *  The message can only contains text and <a> tag for URL
     */
    ChannelItemTypeBasic,
    /**
     *  The message can contain HTML tags
     */
    ChannelItemTypeHtml,
    /**
     *  The message can contain anything (CPaaS only)
     */
    ChannelItemTypeData,
    /**
     *  The message can contain markdown tags
     */
    ChannelItemTypeMarkdown
};

@interface ChannelItem : NSObject

/**
 *  The ID of the item
 */
@property (nonatomic, readonly) NSString *itemId;

/**
 *  The channel ID where the item was published
 */
@property (nonatomic, readonly) NSString *channelId;

/**
 *  The publisher
 */
@property (nonatomic, readonly) Contact *contact;

/**
 * The type of the item, it can be:
 * - urn:xmpp:channels
 * - urn:xmpp:channels:simple
 */
@property (nonatomic, readonly) ChannelItemType type;

/**
 *  The date of the message
 */
@property (nonatomic, readonly) NSDate *date;

/**
 *  The date of the last edition of the message
 */
@property (nonatomic, readonly) NSDate *editionDate;

/**
 *  The text message of the item's payload
 */
@property (nonatomic, readonly) NSString *message;

/**
 *  The title of the item's payload
 */
@property (nonatomic, readonly) NSString *title;

/**
 *  An optional URL of the item's payload
 */
@property (nonatomic, readonly) NSString *url;

/**
 *  The list of images of the item (if available)
 */
@property (nonatomic, readonly) NSArray *images;

/**
 *  The list of attachments of the item (if available)
 */
@property (nonatomic, readonly) NSArray *attachments;

/**
 *  The youtube video identifier (if available)
 */
@property (nonatomic, readonly) NSString *youtubeVideoId;

@property (nonatomic, assign) BOOL isNew;

@end
