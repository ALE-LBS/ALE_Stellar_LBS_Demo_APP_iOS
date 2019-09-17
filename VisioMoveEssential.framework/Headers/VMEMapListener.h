/*
 * Copyright (c) Visioglobe SAS. All rights reserved.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

@class VMEMapView;
@class VMEPosition;
@class VMESceneContext;

#pragma mark - VMEMapListener
/**
 * Listener protocol to be notified of life cycle events sent by
 * VMEMapView.
 *
 * @version 1.0
 */
@protocol VMEMapListener <NSObject>

/**
 * Notify the listener that the map view is ready to receive place updates.
 * @param mapView The originantor of the notification
 *
 * @note Use this notification as the trigger to update the maps place data using
 * VMEPlaceInterface::updatePlaceData:
 *
 * @version 1.0
 * @deprecated Deprecated in 1.12.  Replaced with VMELifeCycleListener::mapReadyForPlaceUpdate:
 */
@optional
-(void) mapReadyForPlaceUpdate:(VMEMapView*)mapView VME_DEPRECATED_MSG("Please use VMELifeCycleListener::mapReadyForPlaceUpdate:");

/**
 * Notifies the listener that the map has been loaded.
 * @param mapView The originantor of the notification
 *
 * @version 1.0
 * @deprecated Deprecated in 1.12.  Replaced with VMELifeCycleListener::mapDidLoad:
 */
@optional
-(void) mapDidLoad:(VMEMapView*)mapView VME_DEPRECATED_MSG("Please use VMELifeCycleListener::mapDidLoad:");


/**
 * Notifies the listener that a place has been selected.
 *
 * @param mapView The originator of the notification
 * @param placeID The ID of the place selected
 * @param position The physical position where the select event took place 
 * within the map.
 * @return YES if the listener consumes the event, NO otherwise.
 *
 * @note Applies to:
 * - static places
 * - dynaimic places
 *
 * @version 1.1
 * @deprecated Deprecated in 1.12.  Replaced with VMEPlaceListener::map:didSelectPlace:withPosition:
 */
@optional
-(BOOL) map:(VMEMapView*)mapView didSelectPlace:(NSString*)placeID withPosition:(VMEPosition*)position VME_DEPRECATED_MSG("VMEPlaceListener::map:didSelectPlace:withPosition:");

/**
 * Notifies the listener that the map's scene or view mode has changed.
 *
 * @param mapView The originator of the notification
 * @param scene The maps's scene
 * @param viewMode The map's view mode
 *
 * @version 1.9
 */
@optional
-(void) map:(VMEMapView*)mapView sceneDidUpdate:(VMESceneContext*)scene withMode:(VMEViewMode)viewMode;
@end
