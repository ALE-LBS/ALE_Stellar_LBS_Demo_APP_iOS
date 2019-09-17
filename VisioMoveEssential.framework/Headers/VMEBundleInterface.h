/*
 * Copyright (c) Visioglobe SAS. All rights reserved.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#pragma mark - VMEBundleInterface

/**
 * Controls how the map bundle is accessed.
 * Regroups a lot of methods previously exposed directly by the VMEMapView class.
 */
@protocol VMEBundleInterface <NSObject>

/**
 * @return The path of the map bundle
 * @see For more info VMEBundleInterface::setMapPath
 * @version 1.0
 */
-(NSString*) getMapPath;

/**
 * Sets the path of the map bundle to be used.
 * @param pMapPath The directory path of the embedded map bundle, relative to the main bundle.
 *
 * @version 1.0
 */
-(void) setMapPath:(NSString*) pMapPath;

/**
 * @returns The online map's hash.
 * @see For more info VMEBundleInterface::setMapHash
 * @version 1.0
 */
-(NSString*) getMapHash;

/**
 * Set the online map's hash.
 *
 * @param pMapHash The map hash to set.
 *
 * @note The hash is used for retrieving the map from a map server.
 *
 * @version 1.0
 */
-(void) setMapHash:(NSString*) pMapHash;

/**
 * @returns The embedded map's secret code.
 * @see For more info VMEBundleInterface::setMapSecretCode
 * @version 1.0
 */
-(int) getMapSecretCode;

/**
 * Set the embedded map's secret code.
 *
 * @param pMapSecretCode The map's secret code to set.
 *
 * @note The secret code is used to salt the map's license.  Before authorizing
 * the loading of the map, the secret code is validated with the map's license.
 *
 * @version 1.0
 * @version 1.9 Parameter type changed from NSString* to int
 */
-(void) setMapSecretCode:(int) pMapSecretCode;

/**
 * @returns The map server url.
 * @see For more info VMEBundleInterface::setMapServerURL
 * @version 1.0
 */
-(NSString*) getMapServerURL;

/**
 * Sets the map server url.
 *
 * @param pMapServerURL The map server url to set.  Passing nil will set the default map server path.
 *
 * By default the map server URL is "https://mapserver.visioglobe.com"
 *
 * @version 1.0
 */
-(void) setMapServerURL:(NSString*) pMapServerURL;

/**
 * @returns A BOOL to indicate whether a prompt is displayed to the user to download online maps
 * @see For more info VMEBundleInterface::setPromptUserToDownloadMap:
 *
 * @version 1.9
 */
-(BOOL) getPromptUserToDownloadMap;

/**
 * Determines whether to prompt the user before downloading an online map.
 *
 * @param pEnable If YES, the user will be prompted.  Otherwise the online map will be
 * downloaded automatically.
 *
 * By default the user will be prompted.
 *
 * @version 1.9
 */
-(void) setPromptUserToDownloadMap:(BOOL) pEnable;
@end


