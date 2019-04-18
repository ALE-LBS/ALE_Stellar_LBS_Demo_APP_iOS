/*
 * Copyright (c) Visioglobe SAS. All rights reserved.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#import <Foundation/Foundation.h>
#import <VisioMoveEssential/VMECameraHeading.h>
#import <VisioMoveEssential/VMEViewMode.h>
#import <VisioMoveEssential/VMEPosition.h>
#import "VMEMacros.h"
@class VMECameraUpdateBuilder;

/**
 * @brief Represents a camera update that can be applied to the VMEMapView.
 *
 * An immutable class that aggregates all camera update parameters such as
 * targets, padding, min/max altitude, and heading.
 *
 * Use the provided constructors to instantiate different types of camera updates.
 * A camera update will update the camera's viewpoint and if necessary will also
 * update the scene so that the viewpoint is focused on the correct building/floor.
 *
 * @version 1.0
 */
@interface VMECameraUpdate : NSObject

/**
 * Constructs a VMECameraUpdate.
 *
 * @param builderBlock The builder block responsible for building the object.
 *
 * @version 1.7
 */
+ (instancetype)cameraUpdateWithBuilderBlock:(void (^)(VMECameraUpdateBuilder *))builderBlock;

/**
 * Constructs a VMECameraUpdate.
 *
 * @param builder The builder responsible for building the object.
 *
 * @version 1.7
 */
- (instancetype)initWithBuilder:(VMECameraUpdateBuilder *)builder;

/**
 * An array of targets for the camera to focus on.
 *
 * A target may be one of the following:
 *  - footprint ID (NSString)
 *  - building ID (NSString)
 *  - floor ID (NSString)
 *  - place ID (NSString)
 *  - position (VMEPosition)
 *
 * @version 1.7
 */
@property (nonatomic, readonly, copy) NSArray* targets;
/**
 * The view mode to apply to the scene.
 *
 * @version 1.7
 */
@property (nonatomic, readonly) VMEViewMode viewMode;
/**
 * The heading to be applied to the camera.
 *
 * @version 1.7
 */
@property (nonatomic, readonly, copy) VMECameraHeading* heading;
/**
 * The padding height (in pixels) between the view's top edge and the camera's
 * bounding box.
 *
 * @version 1.7
 */
@property (nonatomic, readonly) CGFloat paddingTop;
/**
 * The padding height (in pixels) between the view's bottom edge and the camera's
 * bounding box.
 *
 * @version 1.7
 */
@property (nonatomic, readonly) CGFloat paddingBottom;
/**
 * The padding width (in pixels) between the view's left edge and the camera's
 * bounding box.
 *
 * @version 1.7
 */
@property (nonatomic, readonly) CGFloat paddingLeft;
/**
 * The padding width (in pixels) between the view's right edge and the camera's
 * bounding box.
 *
 * @version 1.7
 */
@property (nonatomic, readonly) CGFloat paddingRight;
/**
 * The minimum altitude for the camera.  If the best fitting is below this
 * altitude, the camera will be moved back.
 *
 * @version 1.7
 */
@property (nonatomic, readonly) double minAltitude;
/**
 * The maximum altitude for the camera.  If the best fitting is below this
 * altitude, the camera will be moved back.
 *
 * @version 1.7
 */
@property (nonatomic, readonly) double maxAltitude;

@end
