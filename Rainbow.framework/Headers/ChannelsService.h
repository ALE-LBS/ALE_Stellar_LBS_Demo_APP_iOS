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
#import "Channel.h"
#import "ChannelItem.h"
#import "ChannelUser.h"
#import "ChannelItemImage.h"
#import "FileSharingService.h"

/**
 * Constant for "channel"
 */
FOUNDATION_EXPORT NSString *const kChannelKey;

/**
 * Constant for "channelItem"
 */
FOUNDATION_EXPORT NSString *const kChannelItemKey;

/**
 * Constant for changed keys
 */
FOUNDATION_EXPORT NSString *const kChangedKeys;

/**
 * Constant for when all channels are loaded from the cache
 */
FOUNDATION_EXPORT NSString *const kChannelsServiceDidEndLoadingChannelsFromCache;

/**
 * Constant for when all channels items are loaded from the cache
 */
FOUNDATION_EXPORT NSString *const kChannelsServiceDidEndLoadingChannelsItemsFromCache;

/**
 * Constant for when all channels are fetched from server
 */
FOUNDATION_EXPORT NSString *const kChannelsServiceDidEndFetchingChannelsFromServer;

/**
 * Constant for when all channels items are fetched from the server
 */
FOUNDATION_EXPORT NSString *const kChannelsServiceDidEndFetchingChannelsItemsFromServer;

/**
 * Constant for channel add notifications
 */
FOUNDATION_EXPORT NSString *const kChannelsServiceDidAddChannel;

/**
 * Constant for channel remove notifications
 */
FOUNDATION_EXPORT NSString *const kChannelsServiceDidRemoveChannel;

/**
 * Constant for channel update notifications
 */
FOUNDATION_EXPORT NSString *const kChannelsServiceDidUpdateChannel;

/**
 * Constant for received channel's new item notifications
 */
FOUNDATION_EXPORT NSString *const kChannelsServiceDidReceiveItem;

/**
 * Constant for received channel's update item notifications
 */
FOUNDATION_EXPORT NSString *const kChannelsServiceDidUpdateItem;

/**
 * Constant for retracted channel's item notifications
 */
FOUNDATION_EXPORT NSString *const kChannelsServiceDidRetractItem;

/**
 * Constant for channel create notifications
 */
FOUNDATION_EXPORT NSString *const kChannelsServiceDidCreateChannel;

/**
 * Constant for channel deletion notifications
 */
FOUNDATION_EXPORT NSString *const kChannelsServiceDidDeleteChannel;

/**
 * Constant when the count of invitations changes
 */
FOUNDATION_EXPORT NSString *const kChannelsServiceDidUpdateInvitationsCount;

/**
 * Constant when the count of new items changes
 */
FOUNDATION_EXPORT NSString *const kChannelsServiceDidUpdateNewItemsCount;

/**
 * Channel description
 */
@interface ChannelInformation : NSObject
@property (nonatomic, readonly) NSString *name;
@property (nonatomic, readonly) NSString *channelDescription;
@property (nonatomic, readonly) NSString *id;
@property (nonatomic, readonly) ChannelUserType userType;
@property (nonatomic, readonly) NSString *creatorId;
@end

#define MAX_ITEMS_IN_CHANNEL 100

/**
 * Manager channels
 */
@interface ChannelsService : NSObject

typedef void (^ChannelsServiceCompletionHandler) (NSError *error);
typedef void (^ChannelsServiceGetMyChannelsCompletionHandler) (NSArray<ChannelInformation *> *channelInformations, NSError *error);
typedef void (^ChannelsServiceFetchChannelInformationsCompletionHandler) (NSArray<ChannelInformation *> *channelInformations, NSError *error);
typedef void (^ChannelsServiceFetchChannelsCompletionHandler) (NSArray<Channel *> *channels, NSError *error);
typedef void (^ChannelsServiceGetChannelCompletionHandler) (Channel *channel, NSError *error);
typedef void (^ChannelsServiceGetItemsCompletionHandler) (NSArray<ChannelItem *> *items, NSError *error);
typedef void (^ChannelsServiceGetUsersCompletionHandler) (NSArray<ChannelUser *> *users, NSError *error);

/**
 * All channels managed by the ChannelsService
 * At login time this array is filled automatically and updated with
 * subscribed channel update notifications.
 */
@property (nonatomic, readonly) NSArray *channels;

@property (nonatomic, readonly) NSArray *channelsItems;

@property (nonatomic, assign) BOOL hasNewItems;

@property (nonatomic, assign) BOOL hasInvitations;

/**
 *  TODO
 */
@property (nonatomic, readwrite) int channelItemDaysToLive;

#pragma mark - Getter methods

/**
 *  Get a channel by its id
 *  @param  channelId           the channel id
 */
-(Channel *) getChannel:(NSString *)channelId;

/**
 *  Return a channel item by its identifier (stored locally)
 *  @param  channelItemId       The identifier of the item
 */
-(ChannelItem *) getChannelItem:(NSString *)channelItemId;

#pragma mark - Refresh methods

/**
 *  Refresh the list of channels (force latest items to be refreshed)
 *  @param  block               completion block
 */
-(void) refreshChannelsListWithCompletionBlock:(void(^)(NSError *error)) block;

/**
 *  Refresh the list of the latest items of all channels subscribed
 *  @param  block               completion block
 */
-(void) refreshLatestItemsListWithCompletionBlock:(void(^)(NSError *error)) block;

#pragma mark - Create channel methods

/**
 *  Create a channel in closed mode
 *  @param  name                the channel name
 *  @param  description         the optional channel description, pass nil if not used
 *  @param  category            the optional channel category, pass nil if not used
 *  @param  maxItems            the optional max items to persist in the channel, pass -1 for default
 *  @param  autoprov            auto provisioning members with the channel's company users
 *  @param  completionHandler   completion handler
 */
-(void) createClosedChannel:(NSString *)name description:(NSString *)description category:(NSString *)category maxItems:(int)maxItems autoprov:(BOOL)autoprov completionHandler:(ChannelsServiceGetChannelCompletionHandler) completionHandler;

/**
 *  Create a channel in public mode
 *  @param  name                the channel name
 *  @param  description         the optional channel description, pass nil if not used
 *  @param  category            the optional channel category, pass nil if not used
 *  @param  maxItems            the optional max items to persist in the channel, pass -1 for default
 *  @param  completionHandler   completion handler
 */
-(void) createPublicChannel:(NSString *)name description:(NSString *)description category:(NSString *)category maxItems:(int)maxItems completionHandler:(ChannelsServiceGetChannelCompletionHandler) completionHandler;


#pragma mark - Create channel method (internal use only)

-(void) createChannelWithMode:(ChannelMode)mode name:(NSString *)name description:(NSString *)description category:(NSString *)category maxItems:(int)maxItems completionHandler:(ChannelsServiceGetChannelCompletionHandler) completionHandler;

#pragma mark - Update channel methods (name, description, category, avatar)

/**
 *  Update the channel name, description and / or category.
 *  If one of these parameters is not set (nil), the value will not be updated
 *
 *  @param  channelId           the channel identifier
 *  @param  name                the new channel name
 *  @param  description         the bew channel description
 *  @param  category            the new channel category
 *  @param  completionHandler   completion handler
 */
-(void) updateChannel:(NSString *) channelId name:(NSString *) name description:(NSString *) description category:(NSString *) category completionHandler:(ChannelsServiceCompletionHandler) completionHandler;

/**
 *  Update or delete channel's avatar image
 *  @param  channelId           the channel Id
 *  @param  avatar              the new avatar image, if nil the avatar image is deleted
 *  @param  completionHandler   completion handler
 */
-(void)updateChannel:(NSString *)channelId avatar:(UIImage *)avatar completionHandler:(ChannelsServiceCompletionHandler) completionHandler;

#pragma mark - Delete channel method

/**
 *  Delete a channel
 *  @param  channelId           the channel id
 *  @param  completionHandler   completion handler
 */
-(void) deleteChannel:(NSString *)channelId completionHandler: (ChannelsServiceCompletionHandler) completionHandler;

#pragma mark - Users manangement methods

/**
 *  Add or update a list of users to the type 'member' in a channel
 *  @param  channel             the channel
 *  @param  members             the list of rainbow users identifiers
 *  @param  completionHandler   completion handler
 */
-(void) addMembersToChannel:(Channel *) channel members:(NSArray *) members completionHandler:(void(^)(NSError *error)) completionHandler;

/**
 *  Add or update a list of users to the type 'publisher' in a channel
 *  @param  channel             the channel
 *  @param  publishers          the list of rainbow users identifiers
 *  @param  completionHandler   completion handler
 */
-(void) addPublishersToChannel:(Channel *) channel publishers:(NSArray *) publishers completionHandler:(void(^)(NSError *error)) completionHandler;

/**
 *  Remove a list of users in a channel
 *  @param  channel             the channel
 *  @param  removedUsers        the list of rainbow users identifiers
 *  @param  completionHandler   completion handler
 */
-(void) removeUsersFromChannel:(Channel *) channel removedUsers:(NSArray *) users completionHandler:(void(^)(NSError *error)) completionHandler;

#pragma mark - Fetch channels methods (by category, most followed and most recents)

/**
 *  Fetch channels for a given category
 *  @param  number              The number of channels to be fetched
 *  @param  category            The category to be fetched 
 *  @param  completionHandler   Completion handler
 */
-(void) fetchChannels:(int) number forCategory:(NSString *) category ignoreSubscribed:(BOOL) ignoreSubscribed completionHandler: (ChannelsServiceFetchChannelsCompletionHandler) completionHandler;

/**
 *  Fetch the most followed channels
 *  @param  number              The number of channels to be fetched
 *  @param  ignoreSubscribed    Ignore the subscribed channels or not
 *  @param  completionHandler   Completion handler
 */
-(void) fetchMostFollowedChannels:(int) number ignoreSubscribed:(BOOL) ignoreSubscribed completionHandler: (ChannelsServiceFetchChannelsCompletionHandler) completionHandler;

/**
 *  Fetch the most recent channels
 *  @param  number              The number of channels to be fetched
 *  @param  ignoreSubscribed    Ignore the subscribed channels or not
 *  @param  completionHandler   Completion handler
 */
-(void) fetchMostRecentChannels:(int) number ignoreSubscribed:(BOOL) ignoreSubscribed completionHandler: (ChannelsServiceFetchChannelsCompletionHandler) completionHandler;

#pragma mark - Search methods

/**
 *  Fetch channels on server from the name in parameter
 *  @param  name                the part of channels name to search
 *  @param  limit               allow to specify a limit to the number of channels to retrieve, pass 0 for the default (100)
 *  @param  completionHandler   completion handler
 */
-(void)fetchChannelsByName:(NSString *)name limit:(NSInteger)limit completionHandler:(ChannelsServiceFetchChannelsCompletionHandler) completionHandler;

/**
 *  Fetch channel informations from channel whose description match a given substring
 *  @param  description         the part of channels description to search
 *  @param  limit               allow to specify a limit to the number of channels to retrieve, pass -1 for the default (100)
 *  @param  completionHandler   completion handler
 */
-(void) fetchChannelsByDescription:(NSString *)description limit:(NSInteger)limit completionHandler:(ChannelsServiceFetchChannelInformationsCompletionHandler) completionHandler;

#pragma mark - Fetch channel items methods

/**
 *  Fetch a number of items for one channel before a certain date (if nil, we just fetch the latest items).
 *  The items fetched ARE NOT stored in cache either in memory and will be fetched every time.
 *  @param  channel             the channel
 *  @param  beforeDate          the date reference
 *  @param  number              the number of items fetched
 *  @param  completionHandler   completion handler
 */
-(void) fetchItemsForChannel:(Channel *) channel beforeDate:(NSDate *) beforeDate number:(int) number completionHandler:(ChannelsServiceGetItemsCompletionHandler) completionHandler;

/**
 *  Fetch a number of items for all subscribed channels before a certain date (if nil, we just fetch the latest items).
 *  The items fetched ARE NOT stored in cache either in memory and will be fetched every time.
 *  @param  beforeDate          the before date (generally the last message)
 *  @param  number              the number of items fetched
 *  @param  completionHandler   completion handler
 */
-(void) fetchLatestItemsListBeforeDate:(NSDate *) beforeDate number:(int) number completionHandler:(ChannelsServiceGetItemsCompletionHandler) completionHandler;

#pragma mark - Message management methods (add, update, delete)

/**
 *  Publish an item to a channel
 *
 *  @param  channel             the channel
 *  @param  type                the type of the channel item (ChannelItemTypeBasic, ChannelItemTypeHtml, ChannelItemTypeData, ChannelItemTypeMarkdown)
 *  @param  message             the message text (optional)
 *  @param  title               a message title (optional)
 *  @param  url                 a link url (optional)
 *  @param  images              a list of Rainbow images identifier (NSString) or ChannelItemImage object (optional)
 *  @param  attachments         a list of Rainbow attachments identifiers (NSString) or File object (optional)
 *  @param  youtubeVideoId      a video youtube identifier (optional)
 *  @param  completionHandler   completion handler
 */
-(void)addItemToChannel:(Channel *)channel type:(ChannelItemType)type message:(NSString *)message title:(NSString *)title url:(NSString *)url images:(NSArray *)images attachments:(NSArray *)attachments youtubeVideoId:(NSString *)youtubeVideoId completionHandler:(ChannelsServiceCompletionHandler) completionHandler;

/**
 *  Update an item
 *  The message, title, url, imagesIds, attachmentsIds and youtubeVideoId parameters are managed as following. If you want to:
 *      - update the field --> set a correct value (non empty string or list with items)
 *      - ignore the field --> set a nil parameter
 *      - delete the field --> set the empty value (empty string or empty list)
 *
 *  @param  channelItem         the channel item
 *  @param  type                the type of the channel item: ChannelItemTypeBasic (default), ChannelItemTypeHtml, ChannelItemTypeData, ChannelItemTypeMarkdown
 *  @param  message             the message text (optional)
 *  @param  title               a message title (optional)
 *  @param  url                 a link url (optional)
 *  @param  images              a list of Rainbow images identifier (NSString) or ChannelItemImage object (optional)
 *  @param  attachments         a list of Rainbow attachments identifiers (NSString) or File object (optional)
 *  @param  youtubeVideoId      a video youtube identifier (optional)
 *  @param  completionHandler   completion handler
 */
-(void) updateItem:(ChannelItem *)channelItem type:(ChannelItemType)type message:(NSString *)message title:(NSString *)title url:(NSString *)url images:(NSArray *)images attachments:(NSArray *)attachments youtubeVideoId:(NSString *)youtubeVideoId completionHandler:(ChannelsServiceCompletionHandler) completionHandler;

/**
 *  Delete a channel item
 *  @param channelItem          the channel item
 *  @param completionHandler    completion handler
 */
-(void) deleteItem:(ChannelItem *)channelItem completionHandler:(ChannelsServiceCompletionHandler) completionHandler;

#pragma mark - Files in channels

/**
 *  Load or download the image for a ChannelItemImage
 *  @param  itemImage           The ChannelItemImage object(s) that you can find in each ChannelItem (property images)
 *  @param  forceOriginalFile   If set to YES, the original file will be loaded or downloaded. If NO, the original file will be loaded if in cache, otherwise the thumbnail will be loaded or downloaded.
 *  @param  block               The block with a UIImage as a parameter
 */
-(void) loadItemImageWith:(ChannelItemImage *) itemImage forceOriginalFile:(BOOL) forceOriginalFile completionBlock:(void(^)(UIImage *image)) block;

/**
 *  Upload a file object on the Rainbow Sharing for a channel
 *  If the file has already a rainbowID, we consider the file as already uploaded so the rainbowID is just returned
 *  @param  file                the file to upload
 *  @param  channel             the channel to upload on
 *  @param  block               the handler with 2 params (rainbowID and error)
 */
-(void) uploadFile:(File *) file forChannel:(Channel *) channel completionHandler:(void(^)(NSString *rainbowID, NSError *error)) block;

#pragma mark - Subscription methods

/**
 *  Subscribe to a channel
 *  @param  channel             the channel to subscribe
 *  @param  completionHandler   completion handler
 */
-(void) subscribeToChannel:(Channel *)channel completionHandler:(ChannelsServiceCompletionHandler) completionHandler;

/**
 *  Unsubscribe to a channel
 *  @param  channel             the channel to unsubscribe
 *  @param  completionHandler   completion handler
 */
-(void) unsubscribeToChannel:(Channel *)channel completionHandler:(ChannelsServiceCompletionHandler) completionHandler;

#pragma mark - Invitations management methods

/**
 *  Accept an invitation to join a channel
 *  @param  channel     the channel to join
 */
-(void) acceptInvitation:(Channel *) channel;

/**
 *  Decline an invitation to join a channel
 *  @param  channel     the channel to join
 */
-(void) declineInvitation:(Channel *) channel;

#pragma mark - Get channel's user list

/**
 *  Get the first page of the channel users list
 *  @param  channel             the channel
 *  @param  completionHandler   completion handler
 */
-(void)getFirstUsersFromChannel:(Channel *)channel completionHandler:(ChannelsServiceGetUsersCompletionHandler) completionHandler;

/**
 *  Get a page of the channel users list starting at a given index
 *  @param  channel             the channel
 *  @param  index               start index in the channel user list
 *  @param  completionHandler   completion handler
 */
-(void)getNextUsersFromChannel:(Channel *)channel atIndex:(NSInteger)index completionHandler:(ChannelsServiceGetUsersCompletionHandler) completionHandler;

#pragma mark - Others

/**
 *  Acknowledge a channel item (the isNew property will then be set at NO)
 *  @param  item        the channel item to acknowledge
 */
-(void) markItemAsRead:(ChannelItem *) item;

@end
