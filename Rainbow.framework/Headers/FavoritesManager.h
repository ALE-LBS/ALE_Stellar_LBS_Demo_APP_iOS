/*
 * Rainbow
 *
 * Copyright (c) 2019, ALE International
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
 * Constant for favorite create notifications
 */
FOUNDATION_EXPORT NSString *const kFavoritesDidCreate;
/**
 * Constant for favorite update notifications
 */
FOUNDATION_EXPORT NSString *const kFavoritesDidUpdate;
/**
 * Constant for favorite delete notifications
 */
FOUNDATION_EXPORT NSString *const kFavoritesDidDelete;

/**
 *  Completion handler invoked when user favorites api is invoked
 *  @param error    The error returned by the server or nil
 */
typedef void (^FavoritesManagerCompletionHandler)(NSError *error);

typedef NS_ENUM(NSInteger, FavoriteType) {
    FavoriteTypeUnknown = 0,
    FavoriteTypeUser,
    FavoriteTypeRoom,
    FavoriteTypeBot
};

/*
 Favorite object as exposed by server api
 */
@interface Favorite : NSObject
/**
 *  Favorite id
 */
@property (nonatomic, readonly) NSString *favoriteId;
/**
 *  Peer id associated to this favorite
 */
@property (nonatomic, readonly) NSString *peerId;
/**
 *  Type of favorite as defined by FavoriteType
 */
@property (nonatomic, readonly) FavoriteType type;

-(NSDictionary *) dictionaryRepresentation;
@end

/*
 Favorites Manager
 */
@interface FavoritesManager : NSObject

/**
 *  Local list of Peer object defined as favorites
 */
-(NSArray<Peer*>*) favorites;

/**
 *  Return a favorite from the defined peer id
 *  @param  peerId          the peer id to find if set as favorite
 *  @return  Favorite       the favorite object found or nil
 */
-(Favorite *) getFavoriteByPeerId: (NSString *) peerId;

/**
 *  Fetch all favorites from server, stored as Peer objects in local property favorites
 *  @param  completionHandler   completion handler
 */
-(void) getAllFavoritesWithCompletionHandler:(FavoritesManagerCompletionHandler) completionHandler;

/**
 *  Create a favorite with peer that will be added at the end of the list
 *  @param  peer                the peer object to use as favorite
 *  @param  completionHandler   completion handler
 */
-(void) createFavorite: (Peer *) peer completionHandler:(FavoritesManagerCompletionHandler) completionHandler;

/**
 *  Create a favorite with peer that will be added at a predefined position
 *  @param  peer                the peer object to use as favorite
 *  @param  newPosition         the favorite position in the list
 *  @param  completionHandler   completion handler
 */
-(void) createFavorite: (Peer *) peer atPosition:(NSUInteger) newPosition completionHandler:(FavoritesManagerCompletionHandler) completionHandler;

/**
 *  Update a favorite with peer to a new position
 *  @param  peer                the peer object to use as favorite
 *  @param  newPosition         the new favorite position in the list
 *  @param  completionHandler   completion handler
 */
-(void) updateFavorite: (Peer *) peer toPosition:(NSUInteger) newPosition completionHandler:(FavoritesManagerCompletionHandler) completionHandler;

/**
 *  Delete a favorite with peer from the list
 *  @param  peer                the peer object to use as favorite
 *  @param  completionHandler   completion handler
 */
-(void) deleteFavorite: (Peer *) peer completionHandler:(FavoritesManagerCompletionHandler) completionHandler;

/**
 *  Check if a Peer can be managed in favorites list
 *  @param  peer       the peer object to use as favorite
 *  @return BOOL       return YES if Peer can be handled as favorite, otherwise NO
 */
-(BOOL) isValidForFavorite:(Peer *) peer;
@end
