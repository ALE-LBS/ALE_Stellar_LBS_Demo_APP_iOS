/*
 * Rainbow
 *
 * Copyright (c) 2017, ALE International
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
#import "File.h"
#import "Conversation.h"

FOUNDATION_EXPORT NSString *const kFileSharingServiceDidUpdateUploadedBytesSent;
FOUNDATION_EXPORT NSString *const kFileSharingServiceDidUpdateDownloadedBytes;
FOUNDATION_EXPORT NSString *const kFileSharingServiceDidUpdateFile;
FOUNDATION_EXPORT NSString *const kFileSharingServiceDidRemoveFile;

typedef void (^FileSharingComplionHandler) (File *file, NSError *error);
typedef void (^FileSharingMaxDataSizeComplionHandler) (NSUInteger maxChunkSizeDownload,NSUInteger maxChunkSizeUpload, NSError *error);
typedef void (^FileSharingDataLoadSharedFilesWithPeerComplionHandler) (NSArray<File *> *files, NSError *error);
typedef void (^FileSharingRefreshSharedFileListComplionHandler) (NSArray<File *> *files , NSUInteger offset , NSUInteger total, NSError *error);
typedef void (^FileSharingFilterComplionHandler) (NSArray<File *> *files , NSError *error);
typedef void (^FileSharingProgressHandler) (File* file, double progressPercent);

/**
 * Manage file sharing in the cloud
 */
@interface FileSharingService : NSObject

/**
 *  @name FileSharingService properties
 */

/**
 * File sharing current consumption size (in octet)
 */
@property (readonly) NSInteger currentSize;

/**
 * File sharing quota for the connected user value in GB
 */
@property (readonly) NSInteger maxQuotaSize;

/**
 * Cache of `File` objects
 */
@property (readonly) NSArray<File *> *files;

/**
 *  @name FileSharingService public methods
 */

/**
 *  Create a `File`handler for a temporary file
 *
 *  @param  fileName            the file name of the temporary file
 *  @param  data                the content of the file
 *  @param  url                 the URL of the file
 *  @return                     The `File` object
 */
-(File *) createTemporaryFileWithFileName:(NSString *) fileName andData:(NSData *) data andURL:(NSURL *)url;

/**
 *  Fetch more informations about a `File`
 *
 *  @param  file                the `File` to fetch informations about
 *  @param  completionHandler   the completion handler
 */
-(void) fetchFileInformation:(File *) file completionHandler:(FileSharingComplionHandler) completionHandler;

/**
 *  Download data for a `File`
 *
 *  @param  file                the `File` to download
 *  @param  completionHandler   the completion handler
 */
-(void) downloadDataForFile:(File *) file withCompletionHandler:(FileSharingComplionHandler) completionHandler;

/**
 *  Download data for a `File` with a progression handler
 *
 *  @param  file                the `File` to download
 *  @param  completionHandler   the completion handler
 *  @param  progressHandler     the download progression handler
 */
-(void) downloadDataForFile:(File *) file withCompletionHandler:(FileSharingComplionHandler) completionHandler progressHandler:(FileSharingProgressHandler) progressHandler;

/**
 *  Transfer a file
 *
 *  @param  file                the `File` to transfer
 *  @param  completionHandler   the completion handler
 */
-(void) transferFile:(File *)file  withCompletionHandler:(FileSharingComplionHandler) completionHandler;

/**
 *  Download the thumbnail data
 *
 *  @param  file                the `File` to download the thumbnail for
 *  @param  completionHandler   the completion handler
 */
-(void) downloadThumbnailDataForFile:(File *) file withCompletionHandler:(FileSharingComplionHandler) completionHandler;

/**
 *  Delete a file
 *
 *  @param  file                the `File` to delete
 */
-(void) deleteFile:(File *) file;

/**
 *  Load a list of `File` shared with a `Peer`
 *  If `peer` is `nil` all received files are listed.
 *  If `peer` is a `Room` all files received in that room are listed.
 *  If `peer` is a `Contact` all files shared in the conversation with that contact are listed.
 *
 *  @param  peer                the peer
 *  @param  offset              the number of files to skip at the beginning
 *  @param  completionHandler   the completion handler
 */
-(void) loadSharedFilesWithPeer:(Peer *) peer fromOffset :(NSUInteger)offset completionHandler:(FileSharingDataLoadSharedFilesWithPeerComplionHandler)completionHandler;

/**
 *  Remove a viewer from the file
 *
 *  @param  peer                the peer
 *  @param  file                the file
 *  @param  completionHandler   the completion handler
 */
-(void) removeViewer:(Peer *) peer fromFile:(File *) file completionHandler:(FileSharingComplionHandler) completionHandler;

/**
 *  Refresh the shared file list
 *
 *  @param  offset              the number of files to skip at the beginning
 *  @param  limit               the limit number
 *  @param  typeMIME            the MIME type of files to consider
 *  @param  completionHandler   the completion handler
 */
-(void) refreshSharedFileListFromOffset :(NSInteger)offset withLimit:(NSInteger)limit withTypeMIME:(FilterFileType)typeMIME withCompletionHandler:(FileSharingRefreshSharedFileListComplionHandler) completionHandler;

/**
 *  Search in the `files` array for a `File` object with the given Rainbow ID
 *
 *  @param  rainbowID           the Rainbow ID
 *  @return                     the `File` object
 */
-(File *) getFileByRainbowID:(NSString *) rainbowID;

@end
