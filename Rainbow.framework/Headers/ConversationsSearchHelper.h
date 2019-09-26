/*
 * Rainbow
 *
 * Copyright (c) 2018, ALE International
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

#import "ConversationsManagerService.h"
#import "RoomsService.h"

FOUNDATION_EXPORT NSString *const kSearchDidFoundResultsInConversations;
FOUNDATION_EXPORT NSString *const kSearchDidFoundResultsInAConversation;
FOUNDATION_EXPORT NSString *const kSearchDidFoundMessagesInAConversation;

@interface SearchMessageConversationResult : Conversation
@property (nonatomic) int occurences;
-(instancetype) initWithConversation:(Conversation*)conversation;
@end

@interface ConversationsSearchHelper : NSObject
-(void) searchConversationsWithText:(NSString *) textToSearch;
-(void) searchInConversationWithPeer:(Peer *)peer textToSearch:(NSString *) textToSearch;
-(void) searchMessagesWithPeer:(Peer*)peer beforeAndAfter:(NSUInteger)timestamp;
-(void) searchMessagesWithPeer:(Peer*)peer fromTimestamp:(NSUInteger)timestamp before:(BOOL)searchBefore max:(int)max fromJID:(NSString * _Nullable)fromJid;
-(void) searchMessageWithPeer:(Peer*)peer atTimestamp:(NSUInteger)timestamp fromJID:(NSString * _Nullable)fromJid;
@end
