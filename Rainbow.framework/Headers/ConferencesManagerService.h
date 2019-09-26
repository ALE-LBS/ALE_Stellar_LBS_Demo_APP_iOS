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

#import "Conference.h"
#import "ConfEndpoint.h"
#import "ConferenceParticipant.h"
#import "Room.h"

// Delay in seconds before the beginning of the scheduled meeting we are allowed to join
#define kMeetingJoinBeforeStartIntervalInMinutes 10  // 10 mn before

// Delay in minutes before the beginning of the scheduled meeting when the server auto start it
#define kMeetingServerAutoStartInMinutes 0 // 0 mn before

FOUNDATION_EXPORT NSString *const kConferencesManagerDidAddConference;
FOUNDATION_EXPORT NSString *const kConferencesManagerDidUpdateConference;
FOUNDATION_EXPORT NSString *const kConferencesManagerDidRemoveConference;
FOUNDATION_EXPORT NSString *const kConferencesManagerDidAllConferencesLoad;

FOUNDATION_EXPORT NSString *const kConferencesManagerDidUpdateOpenInvite;

FOUNDATION_EXPORT NSString *const kConferenceKey;
FOUNDATION_EXPORT NSString *const kConferenceChangedAttributesKey;

FOUNDATION_EXPORT NSString *const ConferenceManagerErrorDomainAttach;
FOUNDATION_EXPORT NSString *const ConferenceManagerErrorDomainStart;
FOUNDATION_EXPORT NSString *const ConferenceManagerErrorDomainJoin;
FOUNDATION_EXPORT NSString *const ConferenceManagerErrorDomainSnapshot;

FOUNDATION_EXPORT int const kJoinErrorLeaderHasNotJoinedYet;
FOUNDATION_EXPORT int const kJoinErrorTenMinutesBefore;

@interface ConferencesManagerService : NSObject

typedef void (^ConferenceManagerCreateConferenceCompletionHandler) (NSError *error);
typedef void (^ConferenceManagerUpdateConferenceCompletionHandler) (NSError *error);
typedef void (^ConferenceManagerFetchConferenceSnapshotCompletionHandler) (NSError *error);
typedef void (^ConferenceManagerDeleteConferenceCompletionHandler) (NSError *error);
typedef void (^ConferenceManagerJoinConferenceCompletionHandler) (NSError *error);
typedef void (^ConferenceManagerStartConferenceCompletionHandler) (NSError *error);
typedef void (^ConferenceManagerStartAndJoinConferenceCompletionHandler) (NSError *error);
typedef void (^ConferenceManagerTerminateConferenceCompletionHandler) (NSError *error);
typedef void (^ConferenceManagerInviteParticipantToJoinConferenceCompletionHandler) (NSError *error);
typedef void (^ConferenceManagerDisconnectParticipantCompletionHandler) (NSError *error);
typedef void (^ConferenceManagerCancelInvitationToJoinConferenceCompletionHandler) (NSError *error);
typedef void (^ConferenceManagerAuthorizedPhoneNumbersCompletionHandler) (NSError *error, NSString *language, NSString *country, NSArray<PhoneNumber *> *shortList, NSArray<PhoneNumber *> *phoneNumberList);
typedef void (^ConferenceManagerResetMyOpenInviteCompletionHandler) (NSError *error);
typedef void (^ConferenceManagerArchiveMyOpenInviteCompletionHandler) (NSError *error);

@property (nonatomic, readonly) NSArray<Conference *> *conferences;

@property (nonatomic, readonly) NSArray<PhoneNumber *> *dialInNumbers;
@property (nonatomic, readonly) NSArray<PhoneNumber *> *dialInNumbersShortList;

@property (nonatomic, readonly) BOOL hasWebRTCInstantConference;
@property (nonatomic, readonly) BOOL hasPstnInstantConference;
@property (nonatomic, readonly) BOOL hasJoinedConference;

/**
 * my personal OpenInvite room
 */
@property (nonatomic, strong) NSString *myOpenInviteRoomTitle;

/**
 * my personal OpenInvite room
 */
@property (nonatomic, readonly) Room *myOpenInviteRoom;

/**
 * my personal OpenInvite ID
 */
@property (nonatomic, readonly) NSString *myOpenInviteId;

/**
 *  webRTC conference end point
 */
-(ConfEndpoint *) webRTCConferenceEndPoint;

-(ConfEndpoint *) pstnInstantConferenceEndPoint;

/**
 *  Refresh (parameter `myOpenInviteRoom`) and return the current active personal meeting of the connected user.
 *  This method only searches among the user meetings (there is no request to server).
 */
-(Room *) findMyPersonalMeetingRoom;

/**
 *  Create a conference room for the given room with a start date and a endDate
 *  @param  room                the room in which we want to create a conference
 *  @param  startDate           the starting date of the meeting
 *  @param  endDate             the end date of the meeting
 *  @param  completionHandler   use in return of the create action
 */
-(void) createConferenceForRoom:(Room *) room startDate:(NSDate *) startDate endDate:(NSDate*) endDate completionHandler:(ConferenceManagerCreateConferenceCompletionHandler) completionHandler;

/**
 *  Update the given conference with the new startDate and the new endDate
 *  @param  room                The room in which we want to update a conference
 *  @param  startDate           The new starting date
 *  @param  endDate             The new end date
 *  @param  completionHandler   use in return of the update action
 */
-(void) updateConferenceForRoom:(Room *) room startDate:(NSDate *) startDate endDate:(NSDate *) endDate completionHandler:(ConferenceManagerUpdateConferenceCompletionHandler) completionHandler;

/**
 * Request a conference snapshot
 *
 *  @param conference           the conference that we want the snapshot
 *  @param completionHandler    the completionHandler use to return error in case there is one
 */
-(void) fetchConferenceSnapshot:(Conference *) conference completionBlock:(ConferenceManagerFetchConferenceSnapshotCompletionHandler) completionHandler;

/**
 * Delete a conference
 *
 * @param conference        the conference to delete
 * @param completionHandler the block called at the completion
 */
-(void) deleteConference:(Conference *) conference completionBlock:(ConferenceManagerDeleteConferenceCompletionHandler) completionHandler;

/**
 * disconnect the conference participant using its participant id
 *
 * @param participant       the participant to disconnect
 * @param conference        the conference where we can find the participant
 */
-(void) disconnectParticipant:(ConferenceParticipant *) participant inConference:(Conference *) conference;

/**
 * disconnect the conference participant using its participant id with a completion handler
 *
 * @param participant       the participant to disconnect
 * @param conference        the conference where we can find the participant
 * @param completionHandler the block called at the completion
 */
-(void) disconnectParticipant:(ConferenceParticipant *) participant inConference:(Conference *) conference completionBlock:(ConferenceManagerDisconnectParticipantCompletionHandler) completionHandler;

/**
 * mute the given participant in the given conference
 *
 * @param participant       the participant to mute
 * @param conference        the conference where the participant is attending
 */
-(void) muteParticipant:(ConferenceParticipant *) participant inConference:(Conference *) conference;

/**
 * unmute the given participant in the given conference
 *
 * @param participant       the participant to unmute
 * @param conference        the conference where the participant is attending
 */
-(void) unmuteParticipant:(ConferenceParticipant *) participant inConference:(Conference *) conference;

/**
 * mute All participants in the given conference
 *
 * @param conference        the conference where all participants must be muted
 */
-(void) muteAllParticipantsInConference:(Conference *) conference;

/**
 * mute All participants in the given conference
 *
 * @param conference        the conference where all participants must be muted
 */
-(void) unmuteAllParticipantsInConference:(Conference *) conference;

/**
 * Initiate, if needed, a audio conference then join it
 *
 * @param room              the room to join (with the correct conference)
 * @param phoneNumber       phone number in E.164 format
 * @param role              the role in the conference : member or moderator
 * @param completionHandler the block called at the completion
 */
-(void) startAndJoinConferenceWithRoom:(Room *) room dialOut:(BOOL) dialOut phoneNumber:(NSString *) phoneNumber role:(ParticipantRole)role completionBlock:(ConferenceManagerStartAndJoinConferenceCompletionHandler)completionHandler;

/**
 * Terminate a audio conference
 *
 * @param conference        the conference to terminate
 * @param completionHandler the block called at the completion
 */
-(void) terminateConference:(Conference *) conference completionHandler:(ConferenceManagerTerminateConferenceCompletionHandler) completionHandler;

/**
 *  Invite given participants to join the given conference
 *  @param  participants        Array of Participant to invite
 *  @param  conference          Conference where participants are invited
 *  @param  room                Room where participants are invited
 *  @param  completionHandler   The block invoked when the invitations are sent
 */
-(void) inviteParticipants:(NSArray <Participant *> *) participants toJoinConference:(Conference *) conference inRoom:(Room *) room completionBlock:(ConferenceManagerInviteParticipantToJoinConferenceCompletionHandler) completionHandler;

/**
 *  Cancel invitations for the given conference sent to given participant list
 *  @param  participants        Array of Participant to sent a cancel notification
 *  @param  conference          Conference where participants are invited
 *  @param  room                Room where participants are invited
 *  @param  completionHandler   The block invoked when the invitations are cancelled
 */
-(void) cancelInvitationSentToParticipants:(NSArray <Participant *> *) participants toConference:(Conference *) conference inRoom:(Room *) room completionBlock:(ConferenceManagerCancelInvitationToJoinConferenceCompletionHandler) completionHandler;

/**
 *  Return an array of ConferenceParticipant from the room participant list
 *  @param room                 The room from which we want the participant list
 */
-(NSArray<ConferenceParticipant*> *) createConferenceParticipantsFromRoom: (Room*) room;

/**
 *  Subscribe to a video shared by a publisher in a conference
 *  @param  conferencePublisher The conference publisher we want to subscribe to
 *  @param  conference          The conference
 */
-(void) subscribeToVideoSharedByConferencePublisher:(ConferencePublisher *) conferencePublisher inConference:(Conference *) conference;

/**
 *  Unsubscribe to a video shared by a publisher in a conference
 *  @param  conferencePublisher The conference publisher we want to unsubscribe from
 *  @param  conference          The conference
 */
-(void) unsubscribeToVideoSharedBy:(ConferencePublisher *) conferencePublisher inConference:(Conference *) conference;

/**
 * Check if the given contact is in participant list of the conference
 * @param  contact              The contact to search
 * @param  conference           The conference in which the contact is searched
 */
-(bool) hasContact:(Contact *)contact joinedConference: (Conference *)conference;

/**
 * Check if myUser is in participant list of the conference
 * @param  conference           The conference in which the contact is searched
 */
-(bool) hasMyUserJoinedConference: (Conference *)conference;

/**
 *  Create a new open invite ID
 *  @param  completionHandler   The block invoked when the invitation id has been reset
 */
-(void) resetMyOpenInviteIdWithCompletionHandler:(ConferenceManagerResetMyOpenInviteCompletionHandler)completionHandler;

@end
