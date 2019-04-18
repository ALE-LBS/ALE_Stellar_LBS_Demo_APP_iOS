/*
 * Copyright (c) Visioglobe SAS. All rights reserved.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */
#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <VisioMoveEssential/VisioMoveEssential.h>


#pragma mark - VMELocationInterface
/**
 * A protocol for updating the current physical location within the map
 *
 * @version 1.0
 */
@protocol VMELocationInterface <NSObject>

/**
 * Updates the uses current physical location within the map.
 *
 * @param update The location update to apply.  If nil is passed, then the current
 * location will be removed from the map.
 *
 * @note Calls to this method before VMELifeCycleListener::mapDidLoad: is called
 * will be ignored.
 *
 * @version 1.0
 * @version 1.2 Change update parameter from CLLocation to VMELocation.
 *
 * <b>Example</b>
 @code
 #pragma mark - CLLocationManagerDelegate
 - (void)locationManager:(CLLocationManager *)manager didUpdateLocations:(NSArray *)locations
 {
     CLLocation* lCLLocation = locations.lastObject;
     VMELocation* lVMELocation = [self.mapView createLocationFromLocation:lCLLocation];
     [self.mapView updateLocation:lVMELocation];
 }
 @endcode
 */
-(void) updateLocation:(VMELocation*)update;


/**
 * Takes a native location object and converts it to a VisioMove Essential object
 * Uses the geo-fences within the map bundle to determine if the location falls
 * within a building and if so, what floor.
 *
 * @note The CLLocation's floor property is currently ignored.  Please use the
 * altitude property to determine the physical floor.
 *
 * @note By setting the CLLocation's verticalAccuracy to -1, the VMELocation
 * will be forced to the outside (independent of whether it falls within a
 * building's geo-fence).
 *
 * @note This method will return nil if called prior to VMELifeCycleListener::mapDidLoad:.
 *
 * @param location A location object.  The 'altitude' attribute will be used to
 * determine the correct floor.
 *
 * @return A VMELocation indicating the location within the venue, or nil if the
 * location is invalid or does exist not within the venue.
 *
 * @version 1.2
 */
-(VMELocation*) createLocationFromLocation:(CLLocation*) location;

/**
 * Takes a native location object and converts it to a VisioMove Essential object
 * Uses the geo-fences within the map bundle to determine if the location falls
 * within a builing and if so, what floor.
 *
 * @note By setting the CLLocation's verticalAccuracy to -1, the VMEPosition
 * will be forced to the outside (independent of whether it falls within a
 * building's geo-fence).
 *
 * @note This method will return nil if called prior to VMELifeCycleListener::mapDidLoad:.
 *
 * @param location A location object.  The 'altitude' attribute will be used to
 * determine the correct floor.
 *
 * @return A VMEPosition indicating the location within the venue, or nil if the
 * location is invalid or does not exist within the venue.
 *
 * @version 1.2
 */
-(VMEPosition*) createPositionFromLocation:(CLLocation*) location;

@end

