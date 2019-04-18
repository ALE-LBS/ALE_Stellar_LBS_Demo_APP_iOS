/*
 * Copyright (c) Visioglobe SAS. All rights reserved.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */
#import "VMEPosition.h"
#import "VMEMacros.h"
@class VMEMapView;
@class VMERouteResult;
@class VMEPlace;
@class VMECategory;

#pragma mark - VMEPlaceOrientation
/**
 * @brief VMEPlaceOrientation represents an orientation element that may be
 * associated with a place object.
 *
 * It encapsulates some logic for controlling the camera's heading. It should only
 * be constructed using the factory helper methods below.
 * @version 1.1
 */
@interface  VMEPlaceOrientation : NSObject
/**
 * Place is always camera facing.
 *
 * @version 1.2
 */
+(instancetype)placeOrientationFacing;
/**
 * Place is flat on ground and facing camera
 *
 * @version 1.2
 */
+(instancetype)placeOrientationFlat;
/**
 * Place is flat on ground and has a fixed heading
 *
 * @version 1.2
 */
+(instancetype)placeOrientationFixedWithHeading:(float)heading;

@end


#pragma mark - VMEPlaceAnchorMode
/**
 * This enum defines the possible anchor modes.
 * An anchor mode determines how an place object is
 * anchored to a given position.
 *
 * @version 1.1
 */
typedef NS_ENUM(NSInteger, VMEPlaceAnchorMode) {
    /**
     * Anchor to the top left.
     *
     * @version 1.1
     */
    VMEPlaceAnchorModeTopLeft,
    /**
     * Anchor to the top center
     *
     * @version 1.1
     */
    VMEPlaceAnchorModeTopCenter,
    /**
     * Anchor to the top right
     *
     * @version 1.1
     */
    VMEPlaceAnchorModeTopRight,
    /**
     * Anchor to the center left
     *
     * @version 1.1
     */
    VMEPlaceAnchorModeCenterLeft,
    /**
     * Anchor to the center
     *
     * @version 1.1
     */
    VMEPlaceAnchorModeCenter,
    /**
     * Anchor to the center right
     *
     * @version 1.1
     */
    VMEPlaceAnchorModeCenterRight,
    /**
     * Anchor to the bottom left
     *
     * @version 1.1
     */
    VMEPlaceAnchorModeBottomLeft,
    /**
     * Anchor to the bottom center
     *
     * @version 1.1
     */
    VMEPlaceAnchorModeBottomCenter,
    /**
     * Anchor to the bottom right
     *
     * @version 1.1
     */
    VMEPlaceAnchorModeBottomRight

};


#pragma mark - VMEPlaceAltitudeMode
/**
 * This enum defines the possible altitude modes. An altitude mode determines
 * how the altitude is interpreted.
 *
 * @version 1.1
 */
typedef NS_ENUM(NSInteger, VMEPlaceAltitudeMode) {
    /**
     * The altitude is interpreted relative to the terrain.
     *
     * @version 1.1
     */
    VMEPlaceAltitudeModeRelative,
    /**
     * The altitude is interpreted as the height above the WGS84 ellipsoid
     *
     * @version 1.1
     */
    VMEPlaceAltitudeModeAbsolute
};


#pragma mark - VMEPlaceDisplayMode
/**
 * This enum defines the possible display modes. A display mode determines
 * how the point is displayed within the map.
 *
 * @version 1.1
 */
typedef NS_ENUM(NSInteger, VMEPlaceDisplayMode) {
    /**
     * The place will obscured when located behind map surfaces.
     *
     * @version 1.1
     */
    VMEPlaceDisplayModeInlay,
    /**
     * The place is displayed on top of all map surfaces, regardless of whether
     * they are physical infront of the place.
     *
     * @version 1.1
     */
    VMEPlaceDisplayModeOverlay
};


#pragma mark - VMEPlaceVisibilityRamp
/**
 * An object that controls the place's visibility as a function of the camera's
 * altitude.
 *
 * @version 1.1
 */
@interface VMEPlaceVisibilityRamp : NSObject
/**
 * Creates a visibility ramp object with some default values.
 *
 * @note When using this method, the other properties of the object are initialized
 * to appropriate values. See the property default values for more info.
 *
 * @version 1.1
 */
-(instancetype)init;
/**
 * Creates a visibility ramp object with a user defined ramp.
 *
 * @param startVisible Distance in meters at which it starts becoming visible.
 * @param fullyVisible Distance in meters at which it is fully visible.
 * @param startInvisible Distance in meters at which it starts to become invisible.
 * @param fullyInVisible Distance in meters at which it is fully invisible.
 *
 * @version 1.1
 */
-(instancetype)initWithStartVisible:(double)startVisible
                       fullyVisible:(double)fullyVisible
                     startInvisible:(double)startInvisible
                     fullyInVisible:(double)fullyInVisible;

/**
 * Distance in meters at which it starts becoming visible. If set to 0.0, it is
 * always visble no matter how close you are.
 *
 * The default value of this property is 2.0.
 *
 * @version 1.1
 */
@property (nonatomic) double startVisible;
/**
 * Distance in meters at which it is fully visible. If set to 0.0, it is always
 * visible when you are close.
 *
 * The default value of this property is 5.0.
 *
 * @version 1.1
 */
@property (nonatomic) double fullyVisible;
/**
 * Distance in meters at which it starts to become invisible.
 *
 * The default value of this property is 3000.
 *
 * @version 1.1
 */
@property (nonatomic) double startInvisible;
/**
 * Distance in meters at which it is fully invisible. If set to a very large
 * value, it will never fade out.
 *
 * The default value of this property is 5000.
 *
 * @version 1.1
 */
@property (nonatomic) double fullyInvisible;
@end


#pragma mark - VMEPlaceSize
/**
 * An object that determines the size of the place within the map
 * @version 1.1
 */
@interface VMEPlaceSize : NSObject
/**
 * Create an place size object with a scale
 *
 * @param scale The scale in meters to apply to the place.
 *
 * @version 1.1
 */
-(instancetype)initWithScale:(float)scale;
/**
 * Create an place size object with a scale and a constant size distance.
 *
 * @param scale The scale in meters to apply to the place.
 * @param constantSizeDistance Controls the distance at which the place does not
 * become bigger as you approach it
 *
 * @version 1.1
 */
-(instancetype)initWithScale:(float)scale
        constantSizeDistance:(float)constantSizeDistance;
/**
 * Controls the distance at which the place does not become bigger as you approach
 * it. When the camera is within this distance of the place, the visible size of
 * the place on the screen will be the same as what it looked like when it was
 * constantSizeDistance meters away. If set to 0.0, the size of the place will be
 * determined by scale, regardless of it's distance from the camera.
 *
 * Default value is set to 0.
 *
 * @version 1.1
 */
@property (nonatomic) float constantSizeDistance;
/**
 * The scale in meters to apply to the place.
 *
 * @version 1.1
 */
@property (nonatomic) float scale;
@end

/**
 * An object that defines the criteria for performing a place query.
 *
 * @version 1.8
 */
@interface VMEPlaceFilter : NSObject
/**
 * The target is the center point around which the filter parameters will be applied.
 *
 * @version 1.8
 */
@property (nonatomic, strong, readonly) id target;
/**
 * Restricts the place results to this array of place ids.
 * Useful when only interested in a certain group of places (e.g. near by restaurants)
 *
 * @version 1.8
 */
@property (nonatomic, strong) NSArray<NSString*>* restrictToPlaceIDs;
/**
 * Restricts the place results to the target's layer.
 * By default, this is YES.
 *
 * @version 1.8
 */
@property (nonatomic) BOOL restrictToTargetLayer;
/**
 * Defines the distance (in meters) within which to return place results.
 * The distance between the target and place is computed using the routing
 * network.
 * By default, there is no restricted radius.
 *
 * @version 1.8
 */
@property (nonatomic) double radius;
/**
 * Instantiates a route request
 *
 * @param placeID The place id to use as the target
 *
 * @version 1.8
 */
-(instancetype)initWithPlaceID:(NSString*)placeID;
/**
 * Instantiates a route request
 *
 * @param position The position to use as the target
 *
 * @version 1.8
 */
-(instancetype)initWithPosition:(VMEPosition*)position;

-(BOOL) isEqualToPlaceFilter:(VMEPlaceFilter*) placeFilter;
@end

/**
 * A protocol to receive place filter query notifications.
 *
 * @version 1.8
 */
@protocol VMEPlaceFilterCallback <NSObject>
/**
 * This method be will called by the SDK once the place filter query has completed.
 *
 * @param mapView The map view who received the original request
 * @param filter The original place filter used for the query.
 * @param results An array of VMERouteResult objects sorted by distance in
 * ascending order.  The list may be empty if the filter matched with no results.
 *
 * @version 1.8
 */
-(void)placeFilterDidFinish:(VMEMapView*)mapView
                 parameters:(VMEPlaceFilter*)filter
                    results:(NSArray<VMERouteResult*>*)results;
@end

#pragma mark - VMEPlaceInterface

/**
 * Interface protocol for managing places within the map.
 *
 * Places are POI's within the map.  Using the methods in this interface, it's possible to perform
 * certain actions to the place, such changing it's associated data.
 *
 * Depending on the type of place, some actions may not be possible.  For example, only a place that
 * is a surface can have it's color set.
 *
 * Places can be either:
 * - static - Static places are created within VisioMapEditor by assigning an ID to either a surface
 * or an icon.  When the map is built that are embedded within the map bundle.
 * - dynamic - Dynamic places are icons that added to the map at run time.  It's not currently
 *             possible to create a route to or from a dynamic place.
 *
 * @version 1.1
 */
@protocol VMEPlaceInterface <NSObject>

/**
 * Update the place data content within the map.
 *
 * @note Should be called within the VMELifeCycleListener::mapDidInitializeEngine: notification.
 *
 * @param data An NSDictionary object that contains the updated place data.  For
 * the expected format, please see @ref placeDataFormat.
 *
 * @note Applies to:
 * - static places
 *
 * @version 1.0
 *
 * <b>Example</b>
 @code
-(void) mapDidInitializeEngine:(VMEMapView *)mapView
{
    NSString *path = [[NSBundle mainBundle] pathForResource:@"visio_island_cms_update" ofType:@"json"];
    NSData *returnedData = [[NSFileManager defaultManager] contentsAtPath:path];

    if(NSClassFromString(@"NSJSONSerialization"))
    {
        NSError *error = nil;
        id object = [NSJSONSerialization
                     JSONObjectWithData:returnedData
                     options:0
                     error:&error];

        if(error == nil
           && [object isKindOfClass:[NSDictionary class]])
        {
            NSDictionary *results = object;
            [mapView updatePlaceData:[results valueForKeyPath:@"locale.en"]];
        }
    }
}
 @endcode
 */
-(void) updatePlaceData:(NSDictionary*) data;

/**
 * Updates the place data associated with a place ID.
 *
 * @param placeID The place ID who's data is to change
 * @param data The data that will be used to update the place.  For the expected 
 * format, please see @ref placeDataFormat.  Pass nil to remove the data from map.
 *
 * @note For best performance, use updatePlaceData to populate the initial place
 * data.
 *
 * @return YES if the places data was updated, otherwise NO.
 *
 * @note Applies to:
 * - dynamic places
 * - static places
 *
 * @version 1.1
 */
-(BOOL) setPlaceID:(NSString*)placeID data:(NSDictionary*)data;

/**
 * Update the place's color.
 *
 * @param placeID The place ID
 * @param color The color to apply to the place.
 *
 * @return YES if the places color was updated, otherwise NO.
 *
 * @note Applies to:
 * - static places
 * - dynamic places
 *
 * @version 1.1
 * @version 1.7 Now also applies to static place icons and dynamic places.
 */
-(BOOL) setPlaceID:(NSString*)placeID color:(UIColor *)color;

/**
 * Reset the place's color back to it's initial value.
 *
 * @param placeID The place ID
 *
 * @return YES if the places color was reset, otherwise NO.
 *
 * @note Applies to:
 * - static places
 * - dynamic places
 *
 * @version 1.1
 * @version 1.8 Now also applies to icons and dynamic places.
 */
-(BOOL) resetPlaceIDColor:(NSString*)placeID;

/**
 * Set a group of place colors in one call.
 *
 * The color update is batched.  The map will be non-responsive while the surface
 * colors are being set.
 *
 * @param placeIDToColor A dictionary of placeID to color.
 * @return YES if all place colors were updated, otherwise NO.
 *
 * @note Applies to:
 * - static places
 * - dynamic places
 *
 @code
 NSMutableDictionary<NSString*, UIColor*>* lPlaceToColor = [[NSMutableDictionary alloc] init];
 [lPlaceToColor setObject:[UIColor redColor] forKey:@"B1-UL-001"];
 [lPlaceToColor setObject:[UIColor redColor] forKey:@"B1-UL-002"];
 [self.mapView setPlaceIDColors:lPlaceToColor];
 @endcode
 *
 * @version 1.15
 */
-(BOOL) setPlaceColor:(NSDictionary<NSString*, UIColor*>*)placeIDToColor;

/**
 * Reset a group of places to their original colors in one call.
 *
 * The color reset is batched.  The map will be non-responsive while the surface
 * colors are being reset.
 *
 * @param placeIDs An array of placeIDs to be reset.
 * @return YES if all places were reset, otherwise NO.
 *
 * @note Applies to:
 * - static places
 * - dynamic places
 *
 * @version 1.15
 */
-(BOOL) resetPlaceColor:(NSArray<NSString*>*)placeIDs;


/**
 * Adds a dynamic place to the map.
 *
 * @param placeID The ID of the place.  If the ID corresponds to an existing dynamic
 * place, then it will be replaced.  If the ID corresponds with a static place ID,
 * then this call will fail.
 * @param imageURL A URL that references an image that will be used to represent
 * the place within the map.  Secure http (i.e. https) is not currently supported.
 * @param data A data object for populating the place information. For the expected
 * format, please see @ref placeDataFormat.
 * @param position The place's position within the map
 * @param size Controls the place's size
 * @param anchorMode Determines how the place will be anchored to the map.
 * @param altitudeMode Determines how to interpret the altitude attribute of the
 * position parameter.
 * @param displayMode Determines how the place is displayed
 * @param orientation Controls the place's orientation
 * @param visibilityRamp Controls the place's visibility
 *
 * @return YES if the place was successfully added to the map, otherwise NO.
 *
 * @note Will only work if called during or after the
 * VMELifeCycleListener::mapDidLoad: method.  It will not work if called within the
 * VMELifeCycleListener::mapDidInitializeEngine:.
 *
 * @note Applies to:
 * - dynamic places
 *
 @code

 VMEPosition* lPos = [[VMEPosition alloc] initWithLatitude:45.74131
                                                 longitude:4.88216
                                                  altitude:0.0
                                                buildingID:nil
                                                   floorID:nil];

 NSDictionary *placeData = [NSDictionary dictionaryWithObjectsAndKeys:
                            @"Cat tracker", @"name",
                            @"https://en.wikipedia.org/wiki/Cat", @"description",
                            @"http://www.clipartbest.com/cliparts/aTe/K4e/aTeK4en8c.png", @"icon",
                            @[@"2", @"3", @"99"], @"categories",
                            nil];

 NSURL* lIconUrl = [NSURL URLWithString:@"http://www.clipartbest.com/cliparts/aTe/K4e/aTeK4en8c.png"];

 [self.mapView addPlaceID:@"cat_tracker_id"
                 imageURL:lIconUrl
                     data:placeData
                 position:lPos
                     size:[[VMEPlaceSize alloc] initWithScale:50.0]
               anchorMode:VMEPlaceAnchorModeBottomCenter
             altitudeMode:VMEPlaceAltitudeModeRelative
              displayMode:VMEPlaceDisplayModeOverlay
              orientation:[VMEPlaceOrientation placeOrientationFacing]
           visibilityRamp:[[VMEPlaceVisibilityRamp alloc] init]
  ];
 @endcode
 *
 * @version 1.1
 */
-(BOOL) addPlaceID:(NSString*)placeID
          imageURL:(NSURL*)imageURL
              data:(NSDictionary*)data
          position:(VMEPosition*)position
              size:(VMEPlaceSize*)size
        anchorMode:(VMEPlaceAnchorMode)anchorMode
      altitudeMode:(VMEPlaceAltitudeMode)altitudeMode
       displayMode:(VMEPlaceDisplayMode)displayMode
       orientation:(VMEPlaceOrientation*)orientation
    visibilityRamp:(VMEPlaceVisibilityRamp*)visibilityRamp;

/**
 * Adds a dynamic place to the map.
 *
 * @param placeID The ID of the place.  If the ID corresponds to an existing dynamic
 * place, then it will be replaced.  If the ID corresponds with a static place ID,
 * then this call will fail.
 * @param imageURL A URL that references an image that will be used to represent
 * the place within the map. Secure http (i.e. https) is not currently supported.
 * @param data A data object for populating the place information. For the expected
 * format, please see @ref placeDataFormat.
 * @param position The place's position within the map
 *
 * @return YES if the place was successfully added to the map, otherwise NO.
 *
 * @note When using this method, the other properties of the object are initialized
 * to appropriate values:
 * - size is set to 20.0
 * - anchorMode is set to VMEPlaceAnchorModeBottomCenter
 * - altitudeMode is set to VMEPlaceAltitudeModeAbsolute
 * - displayMode is set to VMEPlaceDisplayModeOverlay
 * - orientation is set using @c [VMEPlaceOrientation placeOrientationFacing]
 * - visibilityRamp is set using @c [[VMEPlaceVisibilityRamp alloc] init]]
 *
 * @see VMEPlaceInterface::addPlaceID:imageURL:data:position:size:anchorMode:altitudeMode:displayMode:orientation:visibilityRamp:
 *
 * @note Applies to:
 * - dynamic places
 *
 @code

 VMEPosition* lPos = [[VMEPosition alloc] initWithLatitude:45.74131
                                                 longitude:4.88216
                                                  altitude:0.0
                                                buildingID:nil
                                                   floorID:nil];

 NSDictionary *placeData = [NSDictionary dictionaryWithObjectsAndKeys:
                            @"Cat tracker", @"name",
                            @"https://en.wikipedia.org/wiki/Cat", @"description",
                            @"http://www.clipartbest.com/cliparts/aTe/K4e/aTeK4en8c.png", @"icon",
                            @[@"2", @"3", @"99"], @"categories",
                            nil];

 NSURL* lIconUrl = [NSURL URLWithString:@"http://www.clipartbest.com/cliparts/aTe/K4e/aTeK4en8c.png"];

 [self.mapView addPlaceID:@"cat_tracker_id"
                 imageURL:lIconUrl
                     data:placeData
                 position:lPos];
  ];
 @endcode
 *
 * @version 1.1
 */
-(BOOL) addPlaceID:(NSString*)placeID
          imageURL:(NSURL*)imageURL
              data:(NSDictionary*)data
          position:(VMEPosition*)position;


/**
 * Update the place's position.
 *
 * @param placeID The place ID
 * @param position The place's new position
 * @param animated Determines whether the change should be animated.
 *
 * @return YES if the place's position was updated, otherwise NO.
 *
 * @note Applies to:
 * - dynamic places
 *
 * @version 1.1
 */
-(BOOL) setPlaceID:(NSString*)placeID position:(VMEPosition*)position animated:(BOOL)animated;

/**
 * Update the place's size.
 *
 * @param placeID The place ID
 * @param size The place's new size
 * @param animated Determines whether the change should be animated.
 *
 * @return YES if the place's size was updated, otherwise NO.
 *
 * @note Applies to:
 * - dynamic places
 *
 * @version 1.1
 */
-(BOOL) setPlaceID:(NSString*)placeID size:(VMEPlaceSize*)size animated:(BOOL)animated;

/**
 * Remove the place from the map.
 *
 * @param placeID The ID of the place to be removed.
 *
 * @return YES if the place was removed, otherwise NO.
 *
 * @note Applies to:
 * - dynamic places
 *
 * @version 1.1
 */
-(BOOL) removePlaceID:(NSString*)placeID;

/**
 * Queries all place IDs within the map.  
 *
 * @note Can be called during or after the 
 * VMELifeCycleListener::mapDidInitializeEngine: notification
 *
 * @return An array of place IDs within the map.  Will return an empty array if 
 * called before the map has correctly loaded.
 *
 * @note Applies to:
 * - static places
 * - dynamic places
 *
 * @version 1.4
 */
-(NSArray<NSString*>*) queryAllPlaceIDs;

/**
 * Queries the map for places matching the filter.
 *
 * @param filter The place filter to be applied to the map.
 * @param callback The callback object to be notified of the results
 * 
 * @note Applies to:
 * - static places
 * - dynamic places
 *
 @code
 -(void) queryPlacesExample
 {
    VMEPlaceFilter* lFilter = [[VMEPlaceFilter alloc] initWithPlaceID:@"404"];
    lFilter.restrictToTargetLayer = false;
    lFilter.restrictToPlaceIDs = NSArray arrayWithObjects:@"411", @"413", @"206", nil];
    [self.mapView queryPlacesWithFilter:lFilter callback:self];
 }
 
 -(void)placeFilterDidFinish:(VMEMapView*)mapView
                  parameters:(VMEPlaceFilter*)filter
                     results:(NSArray<VMERouteResult*>*)results
 {
    for (VMERouteResult* lResult in results) {
        NSLog(@"%fm from %@", lResult.length, lResult.destinations.firstObject);
    }
 }

 @endcode
 * @version 1.8
 */
-(void) queryPlacesWithFilter:(VMEPlaceFilter*)filter
                     callback:(id<VMEPlaceFilterCallback>)callback;

/**
 * Returns a requested place.
 *
 * @param placeID The ID of the place to return.
 * @return A place object that corresponds to the place ID, or null if ID doesn't exist.
 *
 * @note Can be called during or after the
 * VMEMapListener::mapDidLoad: notification.
 *
 * * @note Applies to:
 * - static places
 * - dynamic places
 *
 * @version 1.10
 */
-(VMEPlace*) getPlace:(NSString*)placeID;

/**
 * Queries all category IDs within the map.
 *
 * @note Can be called during or after the
 * VMEMapListener::mapDidLoad: notification
 *
 * @return An array of category IDs within the map.  Will return an empty array if
 * called before the map has correctly loaded.
 *
 * @version 1.10
 */
-(NSArray<NSString*>*) queryAllCategoryIDs;

/**
 * Returns a requested category.
 *
 * @param categoryID The ID of the category to return.
 * @return A category object that corresponds to the category ID, or null if ID doesn't exist.
 *
 * @note Can be called during or after the
 * VMEMapListener::mapDidLoad: notification.
 *
 * @version 1.10
 */
-(VMECategory*) getCategory:(NSString*)categoryID;

@end
