/*
 * Copyright (c) Visioglobe SAS. All rights reserved.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#import <Foundation/Foundation.h>
#import "VMEPosition.h"
#import "VMEAnchorMode.h"

/**
 * A protocol for adding an overlay view above the map.
 *
 * An overlay view displays content (usually text, buttons or images) in a popup
 * view above the map, at a given location.
 *
 * The content of the info view can be tailored completely.
 *
 * An info view may be anchored to either a latitude/longitude or a place.
 *
 * An info view will move automatically with the map when the map is panned.  The
 * info view will be automatically hidden and displayed based on whether it's
 * position is visible within the scene.
 *
 * You may need to move the camera to be able to see the info view.  For example,
 * the info view won't be visible if the floor that it's anchored to isn't visible.
 *
 * @note Adding too many overlays (> 10) to the map will undermine map rendering
 * performance. Where possible, favour the use of:
 *   - VMEPlaceInterface::addPlaceID:imageURL:data:position: and
 *   - VMEPlaceInterface::addPlaceID:imageURL:data:position:size:anchorMode:altitudeMode:displayMode:orientation:visibilityRamp:
 *
 * @version 1.1
 */
@protocol VMEOverlayViewInterface <NSObject>
/**
 * Adds a native overlay view above the map that's associated with a position.
 *
 * @param overlayViewID The id to given to overlay view.  Must be unique.
 * @param view The native view to added to the map.
 * @param position The position to which the overlay view will be anchored.
 * @return YES if the overlay was added to the map, otherwise NO.
 *
 * @note By default the anchor mode will be set to VMEAnchorModeBottomCenter.
 *
 @code
 View* lView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 200, 100)];
 VMEPosition* lPos = [[VMEPosition alloc] initWithLatitude:45.740876918853147
 longitude:4.8805385544669795
 altitude:3
 buildingID:@"B3"
 floorID:@"B3-UL01"];
 [self.mapView addOverlayViewID:@"info_overlay_id" view:lView position:lPos];
 @endcode
 *
 * @see addOverlayViewID:view:position:anchorMode:
 * @version 1.1
 */
-(BOOL) addOverlayViewID:(NSString*)overlayViewID view:(UIView*)view position:(VMEPosition*)position;

/**
 * Adds a native overlay view above the map that's associated with a position.
 *
 * @param overlayViewID The id to given to overlay view.  Must be unique.
 * @param view The native view to added to the map.
 * @param position The position to which the overlay view will be anchored.  The
 * bottom center of the view will be tied to the position.
 * @param anchorMode The part of the view to be anchored to the map.
 * @return YES if the overlay was added to the map, otherwise NO.
 *
 @code
 View* lView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 200, 100)];
 VMEPosition* lPos = [[VMEPosition alloc] initWithLatitude:45.740876918853147
 longitude:4.8805385544669795
 altitude:3
 buildingID:@"B3"
 floorID:@"B3-UL01"];
 [self.mapView addOverlayViewID:@"info_overlay_id" view:lView position:lPos anchorMode:VMEAnchorModeCenterLeft];
 @endcode
 * @version 1.14
 */
-(BOOL) addOverlayViewID:(NSString*)overlayViewID view:(UIView*)view position:(VMEPosition*)position anchorMode:(VMEAnchorMode)anchorMode;

/**
 * Adds a native overlay view above the map that's associated with a place.
 *
 * @param overlayViewID The id to given to overlay view.  Must be unique.
 * @param view The native view to added to the map.
 * @param placeID The view will be anchored to the center point of the place
 * with this ID.  The bottom center of the view will be tied to the place.
 * @return YES if the overlay was added to the map, otherwise NO.
 *
 * @note By default the anchor mode will be set to VMEAnchorModeBottomCenter.
 *
 @code
 View* lView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 200, 100)];
 [self.mapView addOverlayViewID:@"info_overlay_id" view:lView placeID:@"B2-LL01-ID0008"];
 @endcode
 * @version 1.1
 */
-(BOOL) addOverlayViewID:(NSString*)overlayViewID view:(UIView*)view placeID:(NSString*)placeID;

/**
 * Adds a native overlay view above the map that's associated with a place.
 *
 * @param overlayViewID The id to given to overlay view.  Must be unique.
 * @param view The native view to added to the map.
 * @param placeID The view will be anchored to the center point of the place
 * with this ID.
 * @param anchorMode The part of the view to be anchored to the map.
 * @return YES if the overlay was added to the map, otherwise NO.
 *
 @code
 View* lView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 200, 100)];
 [self.mapView addOverlayViewID:@"info_overlay_id" view:lView placeID:@"B2-LL01-ID0008" anchorMode:VMEAnchorModeCenterLeft];
 @endcode
 * @version 1.14
 */
-(BOOL) addOverlayViewID:(NSString*)overlayViewID view:(UIView*)view placeID:(NSString*)placeID anchorMode:(VMEAnchorMode)anchorMode;

/**
 * Sets the position of the overlay view
 *
 * @param overlayViewID The id of the overlay view
 * @param position The position to update
 *
 * @version 1.1
 */
-(BOOL) setOverlayViewID:(NSString*)overlayViewID position:(VMEPosition*)position;

/**
 * Sets the place of the overlay view
 *
 * @param overlayViewID The id of the overlay view
 * @param placeID The place id to update
 *
 * @version 1.1
 */
-(BOOL) setOverlayViewID:(NSString*)overlayViewID placeID:(NSString*)placeID;

/**
 * Removes the overlay view from the map.
 *
 * @param overlayViewID The id of the overlay view to remove.
 *
 * @version 1.1
 */
-(BOOL) removeOverlayViewID:(NSString*)overlayViewID;
@end
