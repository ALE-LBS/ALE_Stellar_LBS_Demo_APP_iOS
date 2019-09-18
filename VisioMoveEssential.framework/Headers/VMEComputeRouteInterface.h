/*
 * Copyright (c) Visioglobe SAS. All rights reserved.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */
#import "VMERouteResult.h"
#import "VMERouteRequest.h"

@class VMEMapView;

#pragma mark - VMEComputeRouteCallback

/**
 * Callback protocol for receiving compute route results.  For computing a route
 * see VMEComputeRouteInterface.
 *
 * @version 1.0
 */
@protocol VMEComputeRouteCallback <NSObject>
/**
 * Notified when compute route was successful
 * @param mapView The map view who received the compute route request
 * @param routeRequest The original route request object.
 * @param routeResult The results of the route request.
 * @return YES if the route should be added to the map, otherwise NO.
 *
 * @version 1.2
 */
@required
-(BOOL) computeRouteDidFinish:(VMEMapView*)mapView
                   parameters:(VMERouteRequest*)routeRequest
                       result:(VMERouteResult*)routeResult;

/**
 * Notified when compute route failed.
 * @param mapView The map view who received the compute route request
 * @param routeRequest The original route request object.
 * @param error A localized error string indicating the reason for the failure.
 *
 * @version 1.0
 */
@required
-(void) computeRouteDidFail:(VMEMapView*)mapView
                 parameters:(VMERouteRequest*)routeRequest
                      error:(NSString*) error;
@end


#pragma mark - VMEComputeRouteInterface
/**
 * Protocol for requesting a route.
 *
 * @version 1.0
 */
@protocol VMEComputeRouteInterface <NSObject>

/**
 * Requests that a route be computed.
 * @param routeRequest The route request
 * @param callback The callback to invoke with the result.
 *
 * @version 1.0
 * @version 1.2 The callback parameter is now required by this method in order
 * to handle the result.
 *
 * <b>Example</b>
 @code
 VMERouteRequest* lRouteRequest = [[VMERouteRequest alloc] initWithRequestType:VMERouteRequestTypeFastest
                                                             destinationsOrder:VMERouteDestinationsOrderOptimal];
 [lRouteRequest setOriginWithPlaceID:@"B1-UL00-ID0039"];
 [lRouteRequest addDestinations:@[@"B4-UL04-ID0005", @"B3-LL01-ID0004"]];
 
 [self.mMapView computeRoute:lRouteRequest callback:self];
 @endcode
 */
-(void) computeRoute:(VMERouteRequest*)routeRequest callback:(id<VMEComputeRouteCallback>)callback;

/**
 * @returns An array of all modality names that are present
 * within the map’s routing network.
 *
 * <b>Example</b>
 @code
 NSArray* lModalities = [self.mMapView getModalities];
 @endcode
 *
 * @version 1.6
 */
-(NSArray*) getModalities;

/**
 * @returns An array of all attribute names that are present
 * within the map’s routing network.
 *
 * <b>Example</b>
 @code
 NSArray* lAttributes = [self.mMapView getAttributes];
 @endcode
 *
 * @version 1.6
 */
-(NSArray*) getAttributes;

/**
 * Sets the modalities that will be excluded from the routing
 * network when a route is computed.
 *
 * @param pModalities An array of modality names to be
 * excluded.  If nil or empty, then any previously excluded
 * modalities will be removed.
 *
 * @note The set excluded modalities will be used in addition
 * to the accessible excluded modalities if the user chooses an
 * accessible route.
 *
 * <b>Example</b>
 @code
 NSArray *lModalities = [[NSArray alloc] initWithObjects:@"UserProfile1", @"UserProfile2", nil];
 [self.mMapView setExcludedModalities:lModalities];
 @endcode
 *
 *
 * @version 1.6
 */
-(void) setExcludedModalities:(NSArray*)pModalities;

/**
 * Sets the attributes that will be excluded from the routing
 * network when a route is computed.
 *
 * @param pAttributes An array of attribute names to be
 * excluded.  If nil or empty, then any previously excluded
 * attributes will be removed.
 *
 * @note The set excluded attributes will be used in addition
 * to the accessible excluded attributes if the user chooses an
 * accessible route.
 *
 * <b>Example</b>
 @code
 NSArray *lAttributes = [[NSArray alloc] initWithObjects:@"UserProfile1", @"UserProfile2", nil];
 [self.mMapView setExcludedAttributes:lAttributes];
 @endcode
 *
 * @version 1.6
 */
-(void) setExcludedAttributes:(NSArray*)pAttributes;

@end

