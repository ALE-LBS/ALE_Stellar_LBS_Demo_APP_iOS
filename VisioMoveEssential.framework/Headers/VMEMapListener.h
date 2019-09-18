/*
 * Copyright (c) Visioglobe SAS. All rights reserved.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

@class VMEMapView;
@class VMESceneContext;

#pragma mark - VMEMapListener
/**
 * Map listener to be notified of map related events occuring
 * on the VMEMapView object.
 *
 @code
 - (void)viewDidLoad {
   [super viewDidLoad];
   [self.mapView setMapListener:(VMEMapListener*)self];
   [self.mapView loadMap];
 }
 @endcode
 *
 * @version 1.0
 */
@protocol VMEMapListener <NSObject>

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
