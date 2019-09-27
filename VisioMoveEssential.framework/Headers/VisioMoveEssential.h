/*
 * Copyright (c) Visioglobe SAS. All rights reserved.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#import <UIKit/UIKit.h>

#import <VisioMoveEssential/VMEAnchorMode.h>
#import <VisioMoveEssential/VMEAnimationCallback.h>
#import <VisioMoveEssential/VMEBuildingListener.h>
#import <VisioMoveEssential/VMEBundleInterface.h>
#import <VisioMoveEssential/VMECameraHeading.h>
#import <VisioMoveEssential/VMECameraUpdate.h>
#import <VisioMoveEssential/VMECameraUpdateBuilder.h>
#import <VisioMoveEssential/VMECategory.h>
#import <VisioMoveEssential/VMEComputeRouteInterface.h>
#import <VisioMoveEssential/VMELifeCycleListener.h>
#import <VisioMoveEssential/VMELocation.h>
#import <VisioMoveEssential/VMELocationInterface.h>
#import <VisioMoveEssential/VMEMacros.h>
#import <VisioMoveEssential/VMEManeuverType.h>
#import <VisioMoveEssential/VMEMapInterface.h>
#import <VisioMoveEssential/VMEMapListener.h>
#import <VisioMoveEssential/VMEMapView.h>
#import <VisioMoveEssential/VMEOverlayViewInterface.h>
#import <VisioMoveEssential/VMEPlace.h>
#import <VisioMoveEssential/VMEPlaceAltitudeMode.h>
#import <VisioMoveEssential/VMEPlaceAnchorMode.h>
#import <VisioMoveEssential/VMEPlaceDisplayMode.h>
#import <VisioMoveEssential/VMEPlaceInterface.h>
#import <VisioMoveEssential/VMEPlaceListener.h>
#import <VisioMoveEssential/VMEPosition.h>
#import <VisioMoveEssential/VMERouteRequest.h>
#import <VisioMoveEssential/VMERouteResult.h>
#import <VisioMoveEssential/VMESegment.h>
#import <VisioMoveEssential/VMESceneContext.h>
#import <VisioMoveEssential/VMESceneUpdate.h>
#import <VisioMoveEssential/VMESearchViewInterface.h>
#import <VisioMoveEssential/VMEStatisticsInterface.h>
#import <VisioMoveEssential/VMEStyleInterface.h>
#import <VisioMoveEssential/VMEViewMode.h>

#define VME_VERSION_STRING @"1.17.3"
#define VME_MIN_DATA_SDK_VERSION_STRING @"2.1.3"
