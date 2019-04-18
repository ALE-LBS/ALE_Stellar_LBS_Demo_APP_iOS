/*
 * Copyright (c) Visioglobe SAS. All rights reserved.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */
#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "VMEPosition.h"
#import "VMEMacros.h"

@class VMEMapView;

#pragma mark - VMERouteRequest

/**
 * The route request type determines the parameter to use when calculating the route 
 *
 * @version 1.2
 */
typedef NS_ENUM(NSInteger, VMERouteRequestType)
{
    /**
     * Indicates a request for a route that optimizes distance.
     *
     * @version 1.2
     */
    VMERouteRequestTypeShortest,
    /**
     * Indicates a request for a route that optimizes time.
     *
     * @version 1.2
     */
    VMERouteRequestTypeFastest
};

/**
 * The different ways to interpret multiple destinations, these options
 * do not change the behavior if there is only one destination.
 *
 * For optimal routes there is a practical limit on 5-6 destinations.
 *
 * @version 1.2
 */
typedef NS_ENUM(NSInteger, VMERouteDestinationsOrder)
{
    /**
     * Indicates that the destinations should be traversed in order
     *
     * @version 1.2
     */
    VMERouteDestinationsOrderInOrder,
    /**
     * Indicates that the destinations should be traversed in the order
     * that minimizes the overall distance or time: e.g. travelling salesman order
     *
     * @version 1.2
     */
    VMERouteDestinationsOrderOptimal,
    /**
     * Indicates that the destinations should be traversed in the order
     * that minimizes the overall distance or time: e.g. travelling salesman order,
     * but always finish on the last routing node of mDestinations.  For example,
     * you enter a shop, you visit the different stands and you finish at the exit.
     *
     * @version 1.2
     */
    VMERouteDestinationsOrderOptimalFinishOnLast,
    /**
     * Indicates that one destination should be returned, the one that is closest (be fastest or shortest).
     *
     * @version 1.2
     */
    VMERouteDestinationsOrderClosest
};

/**
 * Represents a route request to VMEComputeRouteInterface
 *
 * @version 1.0
 */
@interface VMERouteRequest : NSObject <NSCopying>

/**
 * Instantiates a route request.
 *
 * @note By default:
 *  - VMERouteRequest::requestType is set to VMERouteRequestTypeFastest
 *  - VMERouteRequest::destinationsOrder is set to VMERouteDestinationsOrderInOrder
 *  - VMERouteRequest::isAccessible is set to NO.
 *
 * @version 1.7
 */
-(instancetype) init;

/**
 * Instantiates a route request.
 *
 * @param requestType Determines the type of request
 * @param destinationsOrder Determines the visiting order of the destination objects
 * 
 * @note By default:
 *  - VMERouteRequest::isAccessible is set to NO.
 *
 * @version 1.2
 */
-(instancetype) initWithRequestType:(VMERouteRequestType) requestType
                  destinationsOrder:(VMERouteDestinationsOrder) destinationsOrder;

/**
 * Instantiates a route request.
 *
 * @param requestType Determines the type of request
 * @param destinationsOrder Determines the visiting order of the destination objects
 * @param isAccessible Determines if route will be accessible.
 *
 * @version 1.2
 */
-(instancetype) initWithRequestType:(VMERouteRequestType) requestType
                 destinationsOrder:(VMERouteDestinationsOrder) destinationsOrder
                         accessible:(BOOL) isAccessible;

/**
 *
 * @returns The origin of the route.  The origin may be one of the following types:
 *  - VMEPosition - The physical position within the map
 *  - NSString - The id of a place within the map.
 *
 * @version 1.0
 */
-(id) getOrigin;
/**
 * Sets the origin of the route.
 *
 * @param origin The origin may be one of the following types:
 *  - VMEPosition - The physical position within the map
 *  - NSString - The id of a place within the map.
 *
 *
 * @version 1.2
 */
-(void) setOrigin:(id) origin;

/**
 * @returns An ordered array containing the following types:
 *  - VMEPosition - The physical position within the map
 *  - NSString - The id of a place within the map.
 *
 * @version 1.0
 */
-(NSArray*) getDestinations;

/**
 * Adds a destination to the end of the destinations array’s content.
 *
 * @param destination The destination may be one of the following types:
 *  - VMEPosition - The physical position within the map
 *  - NSString - The id of a place within the map
 *
 * @return YES if the destination was added successfully, otherwise NO.
 *
 * @version 1.0
 * @version 1.2 Now returns a BOOL and the destination parameter was made generic.
 */
-(BOOL) addDestination:(id) destination;

/**
 * Adds the objects contained in the given array to the end of the destinations
 * array’s content.
 *
 * @param destinations The destinations array may contain the following object 
 * types:
 *  - VMEPosition - The physical position within the map
 *  - NSString - The id of a place within the map.
 *
 * @return YES if one or more of the destination entries where valid, otherwise NO.
 *
 * @version 1.0
 * @version 1.2 Change return type to BOOL
 */
-(BOOL) addDestinations:(NSArray*) destinations;

/**
 * Remove all destinations objects from the destination array.
 *
 * @version 1.2
 */
-(void) removeAllDestinations;

/**
 * Remove destination object at the given index
 *
 * @param index Index of destination to remove.
 *
 * @version 1.2
 */
-(void) removeDestinationAtIndex:(NSUInteger)index;

/**
 * Replace destination object at the given index with the given position
 *
 * @param index Index of destination to replace.
 * @param destination The object to add to the destination.  The destination may
 * be one of the following types:
 *  - VMEPosition - The physical position within the map
 *  - NSString - The id of a place within the map.
 *
 * @return YES if the replace occurred successfully, otherwise NO.
 *
 * @version 1.2
 */
-(BOOL) replaceDestinationAtIndex:(NSUInteger)index withDestination:(id)destination;

/**
 * Determines if this object is equal to another VMERouteRequest object.
 *
 * @param routeRequest The object to compare self to.
 * @returns YES if the objects are equal, otherwise NO.
 *
 * @version 1.2
 */
-(BOOL) isEqualToRouteRequest:(VMERouteRequest*) routeRequest;

/**
 * Requests that the computed route is accessible.
 * @see Refer the map's "App Configuration" within VisioMapEditor to determine
 * what routing attributes/modalities are filtered when enabled.
 *
 * @version 1.0
 */
@property (nonatomic) BOOL isAccessible;
/**
 * Determines the destination visiting order.
 *
 * @version 1.2
 */
@property (nonatomic) VMERouteDestinationsOrder destinationsOrder;
/**
 * Determines how the route should be optimized.
 *
 * @version 1.2
 */
@property (nonatomic) VMERouteRequestType requestType;

@end


#pragma mark - VMERouteResult
/**
 * Contains information related to a computed route.
 *
 * @version 1.2
 */
@interface VMERouteResult : NSObject <NSCopying>
/**
 * Instantiates a route result object.
 *
 * @param destinations An array of destinations in the order that they will be visited.
 * @param duration The duration (seconds) of the route.
 * @param length The length (metres) of the route.
 *
 * @version 1.2
 */
-(instancetype) initWithDestinations:(NSArray*) destinations
                            duration:(double) duration
                              length:(double) length;
/**
 * Determines if this object is equal to another VMERouteResult object.
 *
 * @param routeResult The object to compare self to.
 * @returns YES if the objects are equal, otherwise NO.
 *
 * @version 1.2
 */
-(BOOL) isEqualToRouteResult:(VMERouteResult*) routeResult;

/**
 * The duration (seconds) of the route
 *
 * @version 1.2
 */
@property (readonly) double duration;
/**
 * The length (metres) of the route
 *
 * @version 1.2
 */
@property (readonly) double length;
/**
 * An array of destinations in the order that they will be visited.  If there
 * was an invalid origin or destination in the request, it will be removed from 
 * this array.
 *
 * @version 1.2
 */
@property (readonly) NSArray* destinations;
@end


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

