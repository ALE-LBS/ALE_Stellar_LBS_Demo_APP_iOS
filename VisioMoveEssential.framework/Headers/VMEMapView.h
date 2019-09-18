/*
 * Copyright (c) Visioglobe SAS. All rights reserved.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */
#import <UIKit/UIKit.h>

#import <VisioMoveEssential/VMEBuildingListener.h>
#import <VisioMoveEssential/VMEComputeRouteInterface.h>
#import <VisioMoveEssential/VMEStatisticsInterface.h>
#import <VisioMoveEssential/VMELifeCycleListener.h>
#import <VisioMoveEssential/VMELocationInterface.h>
#import <VisioMoveEssential/VMEMapInterface.h>
#import <VisioMoveEssential/VMEMapListener.h>
#import <VisioMoveEssential/VMEOverlayViewInterface.h>
#import <VisioMoveEssential/VMEPlaceAltitudeMode.h>
#import <VisioMoveEssential/VMEPlaceAnchorMode.h>
#import <VisioMoveEssential/VMEPlaceDisplayMode.h>
#import <VisioMoveEssential/VMEPlaceInterface.h>
#import <VisioMoveEssential/VMEPlaceListener.h>
#import <VisioMoveEssential/VMESearchViewInterface.h>
#import <VisioMoveEssential/VMEStatisticsInterface.h>
#import <VisioMoveEssential/VMEBundleInterface.h>
#import <VisioMoveEssential/VMEViewControlInterface.h>
#import <VisioMoveEssential/VMEStyleInterface.h>

/**
 * This is the main class of VisioMove Essential for iOS and is the entry point
 * for all methods related to the map.
 *
 * The map view can be created either with the initWithFrame: method or within 
 * a nib.
 *
 * VMEMapView can only be read and modified from the main thread, similar
 * to all UIKit objects. Calling these methods from another thread will result in
 * an exception or undefined behavior.
 *
 * @version 1.0
 */
IB_DESIGNABLE
@interface VMEMapView : UIView
< VMEComputeRouteInterface
, VMELocationInterface
, VMEMapInterface
, VMEOverlayViewInterface
, VMEPlaceInterface
, VMESearchViewInterface
, VMEStatisticsInterface
, VMEBundleInterface
, VMEViewControlInterface
, VMEStyleInterface>

#pragma mark - Static methods

/**
 * Retrieve the current version of VisioMove Essential (iOS).
 *
 * @version 1.0
 */
+(NSString*) getVersion;

/**
 * Retrieves the minimum version string major.minor.patch of the data that this 
 * SDK can handle.  
 *
 * In other words, the map bundle must have been generated with
 * at least this SDK version, otherwise it will not be loaded.  You can find the 
 * sdk_version that a map bundle was generated with within its descriptor.json file.
 *
 * @version 1.0
 */
+(NSString*) getMinDataSDKVersion;

#pragma mark - Methods

/**
 * Use this constructor to create the VMEMapView programatically
 *
 * @version 1.0
 */
-(instancetype) initWithFrame:(CGRect)frame;

/**
 * Loads the map using the current map configuration.  If the map is already loaded,
 * this will reload the map.
 * This method must be called at least once in order for the map to be loaded.
 *
 * @note If the map is already loaded, then VMEMapView::unloadMap should be called before calling
 * this method again.
 *
 * @version 1.0
 */
-(void) loadMap;

/**
 * Unloads the current map.
 *
 * Unloading the map will undo any API calls made since the creation of the map.
 * @note Only call once the previous map has finished loading.
 *
 * @version 1.9
 */
-(void) unloadMap;

#pragma mark - IBOutlets
/**
 * The map listener delegate to receive map related notifications.
 *
 * @version 1.0
 */
@property (nonatomic, weak) IBOutlet id<VMEMapListener> mapListener;
/**
 * The map listener delegate to receive life cycle related notifications.
 *
 * @version 1.12
 */
@property (nonatomic, weak) IBOutlet id<VMELifeCycleListener> lifeCycleListener;
/**
 * The map listener delegate to receive place related notifications.
 *
 * @version 1.12
 */
@property (nonatomic, weak) IBOutlet id<VMEPlaceListener> placeListener;

/**
 * The map listener delegate to receive building related notifications.
 *
 * @version 1.17
 */
@property (nonatomic, weak) IBOutlet id<VMEBuildingListener> buildingListener;

@property (nonatomic) IBInspectable NSString *mapPath;
@property (nonatomic) IBInspectable int mapSecretCode;
@property (nonatomic) IBInspectable NSString *mapHash;
@property (nonatomic) IBInspectable NSString *mapServerURL;

@end
