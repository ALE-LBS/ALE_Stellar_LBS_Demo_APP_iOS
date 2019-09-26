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
#import <Contacts/CNContact.h>
#import "Contact.h"
#import "Presence.h"
#import "Invitation.h"

FOUNDATION_EXPORT NSString *const kContactKey;
FOUNDATION_EXPORT NSString *const kChangedAttributesKey;

FOUNDATION_EXPORT NSString *const kContactsManagerServiceDidEndLoadingContactsFromCaches;
FOUNDATION_EXPORT NSString *const kContactsManagerServiceDidEndLoadingContactsVcardCache;
FOUNDATION_EXPORT NSString *const kContactsManagerServiceDidEndPopulatingMyNetwork;
FOUNDATION_EXPORT NSString *const kContactsManagerServiceDidAddContact;
FOUNDATION_EXPORT NSString *const kContactsManagerServiceDidUpdateContact;
FOUNDATION_EXPORT NSString *const kContactsManagerServiceDidRemoveContact;
FOUNDATION_EXPORT NSString *const kContactsManagerServiceDidRemoveAllContacts;
FOUNDATION_EXPORT NSString *const kContactsManagerServiceDidInviteContact;
FOUNDATION_EXPORT NSString *const kContactsManagerServiceDidFailedToInviteContact;
FOUNDATION_EXPORT NSString *const kContactsManagerServiceDidUpdateMyContact;
FOUNDATION_EXPORT NSString *const kContactsManagerServiceDidAcceptInvitation;
FOUNDATION_EXPORT NSString *const kContactsManagerServiceDidChangeContactDisplayUserSettings;
FOUNDATION_EXPORT NSString *const kContactsManagerServiceLocalAccessGrantedNotification;
FOUNDATION_EXPORT NSString *const kContactsManagerServiceDidReceiveCreateConfUserActivated;

FOUNDATION_EXPORT NSString *const kContactsManagerServiceClickToCallMobile;

FOUNDATION_EXPORT NSString *const kContactsManagerServiceDidAddInvitation;
FOUNDATION_EXPORT NSString *const kContactsManagerServiceDidUpdateInvitation;
FOUNDATION_EXPORT NSString *const kContactsManagerServiceDidRemoveInvitation;
FOUNDATION_EXPORT NSString *const kContactsManagerServiceDidUpdateInvitationPendingNumber;

/**
 *  The mode for method searchRemoteContactsWithPattern:rainbowUsersOnly:(BOOL) rainbowUsersOnly searchMode:(SearchRemoteContactsMode) searchMode withCompletionHandler:(ContactsManagerServiceSearchRemoteContactsCompletionHandler) completionHandler
 */
typedef NS_ENUM(NSInteger, SearchRemoteContactsMode) {
    /**
     *  Search Rainbow contacts in all companies
     */
    SearchRemoteContactsModeAll = 0,
    /**
     *  Search Rainbow contacts in user company only
     */
    SearchRemoteContactsModeUserCompanyOnly,
    /**
     *  Search Rainbow contacts in all companies except user company
     */
    SearchRemoteContactsModeUserCompanyExcluded

};

/**
 *  Search completion handler invoked when a searching a remote contact return
 *
 *  @param searchPattern pattern searched
 *  @param foundContacts list of contacts found
 */
typedef void (^ContactsManagerServiceSearchRemoteContactsCompletionHandler)(NSString *searchPattern, NSArray<Contact *>* foundContacts);
/**
 *  Completion handler invoked when loading an avatar in High Resolution
 *  @param receivedData    Data representing the high resolution avatar
 *  @param error    Error return in case of error while retrieving avatar
 */
typedef void (^ContactsManagerServiceLoadHiResAvatarCompletionHandler)(NSData *receivedData, NSError *error);

/**
 *  Search completion handler invoked when a searching a remote contact return
 *
 *  @param foundContact contact found
 */
typedef void (^ContactsManagerServiceSearchRemoteContactCompletionHandler)(Contact *foundContact);

@class ContactsManagerService;
/**
 *  This protocol should be implemented by any class that wants to be informed about contacts added, updated or deleted by the ContactsService
 */
@protocol ContactsManagerServiceDelegate <NSObject>
@required
/**
 *  Invoked when a new contact is added in the contacts manager service
 *
 *  @param contactService the contact manager that invoke this delegate
 *  @param addedContact the contact that was added
 *  @see Contact
 */
-(void) contactsService:(ContactsManagerService *) contactService didAddContact:(Contact *) addedContact;

/**
 *  Invoked when a contact is updated in the contacts manager service
 *
 *  @param contactService the contact manager that invoke this delegate
 *  @param updatedContact the contact that was updated
 *  @param changedKeys all the contact attributes which have changed
 *  @see Contact
 */
-(void) contactsService:(ContactsManagerService *) contactService didUpdateContact:(Contact *) updatedContact withChangedKeys:(NSArray<NSString *> *) changedKeys;

/**
 *  Invoked when a contact is removed in the contacts manager service
 *
 *  @param contactService the contact manager that invoke this delegate
 *  @param removedContact the contact that was removed
 *  @see Contact
 */
-(void) contactsService:(ContactsManagerService *) contactService didRemoveContact:(Contact *) removedContact;

@end

/**
 *  Manage all contacts used in Rainbow
 *  Deal with contacts from server, deal with contact from the device
 *  Merge contacts to avoid presenting duplicates entries
 *
 *  Contacts Manager service available notifications
 *   - kContactsManagerServiceDidAddContact: `notification sent when a contact is added, the created contact in notification object`
 *   - kContactsManagerServiceDidUpdateContact: `notification sent when a contact is update, a dict with contact and changed keys in notification object`
 *   - kContactsManagerServiceDidRemoveContact: `notification sent when a contact is removed, the removed contact in notification object`
 *   - kContactsManagerServiceDidInviteContact: `notification sent when a contact is invited, the invited contact in notification object`
 *   - kContactsManagerServiceDidFailedToInviteContact: `notification sent when the invitation failed, the invited contact in notification object`
 *   - kContactsManagerServiceDidUpdateMyContact: `notification sent when the currently logged user contact is updated`
 *   - kContactsManagerServiceDidChangeContactDisplayUserSettings: `notification sent when device contact display parameter is changed`
 *   - kContactsManagerServiceLocalAccessGrantedNotification: `notification sent when the addressBook access is granted`
 *   - kContactsManagerServiceDidAddInvitation: `notification a new invitation is added (could be a sent or received one), notification object is the invitation`
 *   - kContactsManagerServiceDidUpdateInvitation: `notification an invitation is updated (status changed), notification object is the invitation`
 */
@interface ContactsManagerService : NSObject

/**
 *  @name ContactsManager delegate
 */

/**
*  Delegate, see `ContactsManagerServiceDelegate` for details
*  @see ContactsManagerServiceDelegate
*/
@property (nonatomic, assign) id<ContactsManagerServiceDelegate> delegate;

/**
 *  @name ContactsManager properties
 */

/**
 *  List of contacts managed by Contacts Service Manager
 *  @see Contact
 */
@property (nonatomic, readonly) NSArray <Contact *> *contacts;

/**
 *  All contacts identified as a rainbow user
 *  @see Contact
 */
@property (nonatomic, readonly) NSArray<Contact *> *myNetworkContacts;

/**
 *  @return `YES` if the contact is in my network
 *  @param contact The contact to be checked if he is in my network
 */
-(BOOL) isTheContactInMyNetwork:(Contact *)contact;

/**
 *  @return `YES` if the local addressBook has been unlocked by the user
 otherwise @return `NO`
 *
 */
@property (nonatomic, readonly) BOOL localDeviceAccessGranted;

/**
 *  @return `YES` if the application already required the access to the addressBook.
 *  see `localDeviceAccessGranted` to know if the user allow or it or not.
 */
@property (nonatomic, readonly) BOOL localDeviceAccessAlreadyRequired;

/**
 *  Return the display order setting set in the device
 *
 *  this method requires addressBook access, if address book access is not granted, it will request it, if user refuse this method will return `YES`
 *  @return `YES` if the settings is set to display firstName first.
 */
@property (nonatomic, readonly) BOOL displayFirstNameFirst;

/**
 *  Return the sort order setting set in the device
 *
 *  this method requires addressBook access, if address book access is not granted, it will request it, if user refuse this method will return `NO`
 *  @return `YES` if the sort order is set to first name.
 */
@property (nonatomic, readonly) BOOL sortByFirstName;

/**
 *  Number of pending invitations
 */
@property (nonatomic) NSInteger totalNbOfPendingInvitations;

/**
 *  @return `YES` if the contacts manager has finished loading the Roster
 */
@property (nonatomic, readonly) BOOL endPopulatingRoster;

/**
 *  @return `YES` if the minimal presences from the cache has been loaded
 */
@property (nonatomic, readonly) BOOL minimalPresencesCacheLoaded;

/**
 *  @return `YES` if all contacts from the caches have been loaded
 */
@property (nonatomic, readonly) BOOL allContactsCacheLoaded;

/**
 *  @name ContactsManager methods
 */

/**
 *  Ask to unlock the local AddressBook
 */
-(void) requestAddressBookAccess;

/**
 *  Accept a received invitation
 *  This will do nothing for a sent invitation
 *  or for invitation not pending
 *
 *  @param invitation The invitation to accept
 */
-(void) acceptInvitation:(Invitation *) invitation;

/**
 *  Decline a received invitation
 *  This will do nothing for a sent invitation
 *  or for invitation not pending
 *
 *  @param invitation The invitation to decline
 */
-(void) declineInvitation:(Invitation *) invitation;

/**
 *  Send a invitation to join Raibow to the given contact
 *
 *  We can invite contact based on is work email address
 *  Invitation send or failure is notified posting a notification monitor `kContactsManagerServiceDidInviteContact ` or `kContactsManagerServiceDidFailedToInviteContact`
 *  @param contact The contact to invite
 *  @see Contact
 */
-(void) inviteContact:(Contact *) contact;

/**
 *  Send a invitation to join Raibow to the given contact
 *
 *  We can invite contact based on is phone number
 *  Invitation send or failure is notified posting a notification monitor `kContactsManagerServiceDidInviteContact ` or `kContactsManagerServiceDidFailedToInviteContact`
 *  @param contact The contact to invite
 *  @param completionHandler method executed after the update is done, error is field in case of error during update process
 *  @see Contact
 */
-(void) inviteContact:(Contact *) contact withPhoneNumber:(NSString *) phoneNumber withCompletionHandler:(void(^)(Invitation *invitation))completionHandler;

/**
 *  Delete an invitation already sent to a contact
 *  This method is synchronous don't invoke it on mainThread
 *  @param invitation The invitation that we want to delete
 */
-(void) deleteInvitationWithID:(Invitation *) invitation;

/**
*  Cancel an invitation already sent to a contact
*  This method is synchronous don't invoke it on mainThread
*  @param invitation The invitation that we want to cancel
*/
-(void) cancelInvitation:(Invitation *) invitation;

/**
 *  Remove the given contact from my network, this method will send a presence unsubscription for the given contact, AND a presence unsubscription for the contact telephony presence
 *
 *  @param contact the given contact to remove from our network
 *  @see Contact
 */
-(void) removeContactFromMyNetwork:(Contact *) contact;

/**
 *  Change the user presence
 *
 *  @param presence New presence to set
 *  @see Presence
 */
-(void) changeMyPresence:(Presence *) presence;

/**
 *  Refresh the logged user vcard
 */
-(void) refreshMyVcard;

/**
 *  Update the vCard for the given contact, by doing a request to the server.
 *
 *  NB: To delete the user avatar, insert the key `photo` with an empty string value to the parameter `fields`
 *
 *  @param fields  all field to update for my contact
 *  @param completionBlock method executed after the update is done, error is field in case of error during update process
 */
-(void) updateUserWithFields:(NSDictionary*)fields withCompletionBlock:(void(^)(NSError* error)) completionBlock;

/**
 *  Get the contact last activity date. Once the value is updated in the contact itself,
 *  A notification is triggered.
 *
 *  @param contact The contact concerned
 *  @see Contact
 */
-(void) getLastActivityForContact:(Contact *)contact;

#pragma mark - Search
/**
 *  Search contact in local device with given pattern
 *
 *  @param pattern the searched pattern
 *
 *  @return Array of contacts that match the given pattern
 *  @see Contact
 */
-(NSArray<Contact *> *) searchContactsWithPattern:(NSString *) pattern;

/**
 *  Search contact in adressbook with given pattern
 *
 *  @param pattern the searched pattern
 *
 *  @return Array of contacts that match the given pattern
 *  @see Contact
 */
-(NSArray<Contact *> *) searchAdressBookWithPattern:(NSString *) pattern;

/**
 *  Search contact on server side by jid
 *  @discussion This method search asynchronously on the server for the given list of contacts jids.
 *  Notifications `kContactsManagerServiceDidAddContact` or `kContactsManagerServiceDidUpdateContact` are triggered when the contact informations is created or updated
 *
 *  @param contactsJids list of jids to search on server side
 */
-(void) populateVcardForContactsJids:(NSArray <NSString *> *) contactsJids;

/**
 *  Load a contact avatar.
 *
 *  @param contact The contact to update
 *  @see Contact
 */
-(void) populateAvatarForContact:(Contact*) contact;

/**
 *  Load a contact avatar at a highest predefined resolution
 *
 *  @param contact The contact which the photo will be loaded
 *  @see Contact
 */
-(void) loadHiResAvatarForContact:(Contact*) contact withCompletionBlock:(ContactsManagerServiceLoadHiResAvatarCompletionHandler) completionHandler;

/**
 *  Search for contact on remote server with given pattern, and invoke completionHandler when finished.
 *
 *  @param pattern           the searched pattern
 *  @param completionHandler the completion handler to invoked when the search is ended. Return an `nil` array in case of error, or if no result found
 *  @see ContactsManagerServiceSearchRemoteContactsCompletionHandler
 */
-(void) searchRemoteContactsWithPattern:(NSString *) pattern withCompletionHandler:(ContactsManagerServiceSearchRemoteContactsCompletionHandler) completionHandler;

/**
 *  Search for contact on remote server with given pattern, and invoke completionHandler when finished.
 *  The method can search :
 *  - in Rainbow contacts (in user company, in other companies or both)
 *  - in all active directories
 *  - in PBX phonebook
 *
 *  @param  pattern             the searched pattern
 *  @param  limitPerCategory    the limit of fetched users for each category of search
 *  @param  rainbowUsersOnly    search only for rainbow users (not AD / PBX)
 *  @param  searchMode          search mode for Rainbow users
 *  @param  completionHandler the completion handler to invoked when the search is ended. Return an `nil` array in case of error, or if no result found
 *  @see ContactsManagerServiceSearchRemoteContactsCompletionHandler
 */
-(void) searchRemoteContactsWithPattern:(NSString *) pattern limitPerCategory:(int) limitPerCategory rainbowUsersOnly:(BOOL) rainbowUsersOnly searchMode:(SearchRemoteContactsMode) searchMode withCompletionHandler:(ContactsManagerServiceSearchRemoteContactsCompletionHandler) completionHandler;

/**
 *  Search for contact on remote server with given jid, and invoke completionHandler when finished.
 *
 *  @param contactJid        the searched contact jid
 *  @param completionHandler the completion handler to invoked when the search is ended. Return `nil` in case of error, or if no result found
 *  @see ContactsManagerServiceSearchRemoteContactCompletionHandler
 */
-(void) searchRemoteContactWithJid:(NSString *) contactJid withCompletionHandler:(ContactsManagerServiceSearchRemoteContactCompletionHandler) completionHandler;

/**
 * Retrieve all contacts details from server
 * Notification `kContactsManagerServiceDidUpdateContact` will be sent when the server infos will be received
 *
 * @param theContact contact that we must retrieve details
 */
-(void) fetchRemoteContactDetail:(Contact *) theContact;

/**
 *
 * @param theContact contact that we must retrieve the automatic reply message
 */
-(void) fetchCalendarAutomaticReply:(Contact *) theContact;


/**
 *  Return the user country code in valid format
 *
 *  @return Country code as string (eg FRA)
 */
+(NSString *) currentCountryCode;


/**
 * Return the contact that is dedicated to support
 *
 * @return contact that is dedicated to support
 */
-(Contact *) getSupportBot;

/**
 * Return the contact that has the specified email
 *
 * @return contact
 */
-(Contact *) searchLocalContactWithEmailString: (NSString *)emailString;

/**
 * Return the rainbow contact that has the specified email
 *
 * @return contact
 */
-(Contact *) searchRainbowContactWithEmailString:(NSString *)emailString;

/**
 * Return a contact created from a standard CNContact
 *
 * @return contact
 */
+(Contact *) createContactFromCNContact:(CNContact *) person;

/**
 *  Send invitations to join Raibow to multiple contacts at a time
 *
 *  We can invite a list of CNContact (contact from adressbook) based on work email
 *  @param contacts The contacts list to invite
 *  @see Contact
 */
-(void) inviteCNContacts:(nonnull NSArray<CNContact*> *) contacts withCompletionHandler:(void(^)(BOOL success))completionHandler;

/**
 *  Send invitations by email to a list of email string
 *
 *  @see Contact
 */
-(void) inviteByEmails:(nonnull NSArray<NSString *> *) emails withCompletionHandler:(void(^)(BOOL success))completionHandler;

/**
 *  Send an invitation by email
 *
 *  @see Contact
 */
-(void) inviteByEmail:(NSString *_Nonnull) email withCompletionHandler:(void(^)(Invitation * _Nullable invitation))completionHandler;

/**
 *  Send an invitation by phone number
 *
 *  @see Contact
 */
-(void) inviteByPhoneNumber:(NSString *_Nonnull) phoneNumber withCompletionHandler:(void(^)(Invitation * _Nullable invitation))completionHandler;


#pragma mark - Suggestions

/**
 *
 */
-(void) suggestedContactsWithCompletionHandler:(void(^_Nonnull)(NSArray<Contact*> * _Nonnull contactList))completionHandler;
-(void) createOrUpdateRainbowContactFromSuggested:(Contact *)suggestedContact;


#pragma mark - Rainbow TVs

-(void) fetchAllTVs:(void(^)(NSArray *rainbowTVs, NSError *error)) block;

@end
