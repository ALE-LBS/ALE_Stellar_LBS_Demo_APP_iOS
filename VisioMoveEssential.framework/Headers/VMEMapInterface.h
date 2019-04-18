/*
 * Copyright (c) Visioglobe SAS. All rights reserved.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */
#import <Foundation/Foundation.h>
#import <VisioMoveEssential/VMECameraUpdate.h>
#import <VisioMoveEssential/VMESceneUpdate.h>
#import <VisioMoveEssential/VMEAnimationCallback.h>
#import "VMEMacros.h"

#pragma mark - VMEMapInterface
/**
 * @brief A protocol for controlling the camera and the scene.
 *
 * @version 1.0
 */
@protocol VMEMapInterface <NSObject>
/**
 * Repositions the camera according to the instructions defined in the update. 
 * The update is instantaneous.
 *
 * @see VMECameraUpdate for the available update constructors.
 *
 * @param update The update to apply.
 *
 * @version 1.2
 *
 * <b>Example</b>
 @code
 VMECameraUpdate* lUpdate = [VMECameraUpdate cameraUpdateWithBuilderBlock:^(VMECameraUpdateBuilder *builder) {
    builder.targets = [NSArray arrayWithObject:@"B2-UL00"];
    builder.heading = [VMECameraHeading cameraHeadingCurrent];
    builder.viewMode = VMEViewModeFloor;
 }];

 [self.mapView updateCamera:lUpdate];
 @endcode
 */
-(void) updateCamera:(VMECameraUpdate*)update;

/**
 * Animates the movement of the camera from the current position to the position 
 * defined in the update.
 *
 * @see VMECameraUpdate for the available update constructors.
 *
 * @param update The update to apply.
 *
 * @version 1.2
 *
 * <b>Example</b>
 @code
 VMECameraUpdate* lUpdate = [VMECameraUpdate cameraUpdateWithBuilderBlock:^(VMECameraUpdateBuilder *builder) {
    builder.targets = [NSArray arrayWithObject:@"B2-UL00"];
    builder.heading = [VMECameraHeading cameraHeadingForPlaceID:@"B2"];
    builder.viewMode = VMEViewModeFloor;
 }];
 [self.mapView animateCamera:lUpdate];
 @endcode
 */
-(void) animateCamera:(VMECameraUpdate*)update;

/**
 * Animates the movement of the camera from the current position to the position
 * defined in the update.
 *
 * @see VMECameraUpdate for the available update constructors.
 *
 * @param update The update to apply.
 * @param duration The duration (in seconds) of the camera animation.
 * @param callback The callback to be notified of any animation events.  Can pass
 * nil if indifferent to animation events.
 *
 * @version 1.7
 *
 * <b>Example</b>
 @code
 VMECameraUpdate* lUpdate = [VMECameraUpdate cameraUpdateWithBuilderBlock:^(VMECameraUpdateBuilder *builder) {
    builder.targets = [NSArray arrayWithObject:@"B2-UL00"];
    builder.heading = [VMECameraHeading cameraHeadingForPlaceID:@"B2"];
    builder.viewMode = VMEViewModeFloor;
 }];
 [self.mapView animateCamera:lUpdate duration:1.5 listener:self];
 @endcode
 */
-(void) animateCamera:(VMECameraUpdate*)update duration:(float)duration callback:(id<VMEAnimationCallback>)callback;

/**
 * Updates the change of scene from the current scene to the scene
 * defined in the update.  The update is instantaneous.
 *
 * @see VMESceneUpdate for the available update constructors.
 *
 * @param update The update to apply.
 *
 * @version 1.2
 *
 * <b>Example</b>
 @code
 VMESceneUpdate* lUpdate = [VMESceneUpdate sceneUpdateForViewMode:VMEViewModeFloor
                                                          floorID:@"B2-UL00"];
 [self.mapView updateScene:lUpdate];
 @endcode
 */
-(void) updateScene:(VMESceneUpdate*)update;

/**
 * Animates the change of scene from the current scene to the scene
 * defined in the update.
 *
 * @see VMESceneUpdate for the available update constructors.
 *
 * @param update The update to apply.
 *
 * @version 1.2
 *
 * <b>Example</b>
 @code
 VMESceneUpdate* lUpdate = [VMESceneUpdate sceneUpdateForViewMode:VMEViewModeFloor
                                                          floorID:@"B2-UL00"];
 [self.mapView animateScene:lUpdate];
 @endcode
 */
-(void) animateScene:(VMESceneUpdate*)update;

@end

