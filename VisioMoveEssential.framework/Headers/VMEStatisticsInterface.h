/*
 * Copyright (c) Visioglobe SAS. All rights reserved.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */
#import <Foundation/Foundation.h>


#pragma mark - VMEStatisticsInterface

/**
 * Interface protocol for enabling statistics logging and fine graining the
 * type of data to be logged:
 * - Camera
 * - Location
 * - Interest
 *
 * The logged statistics will be sent to the Visioglobe statistics server.
 *
 * @version 1.5
 */
@protocol VMEStatisticsInterface <NSObject>

/**
 * Set the statistics logging.  This attribute is the main switch for logging
 * statistics.
 *
 * If enabled, then the requested statistics will be logged. If disabled, none
 * of the requested statistics will be logged.
 *
 * @param pEnabled YES to enable, NO to disable it. Default is NO.
 *
 * @note Will be ignored if called before VMEMapView::loadMap.
 *
 * @version 1.5
 *
 * <b>Example</b>
 * @code
 * [self.mapView setStatisticsLog:YES];
 * @endcode
 */
-(void) setStatisticsLog:(BOOL) pEnabled;

/**
 * Set the statistics camera logging.  If enabled, the camera's ground focus
 * position will be logged at regular intervals during the end users interactions
 * with the map.
 *
 * @param pEnabled YES to enable, NO to disable it.  Default is NO.
 *
 * @note VMEStatisticsInterface::setStatisticsLog: must be enabled before
 * any logging will occur.
 *
 * @note Will be ignored if called before VMEMapView::loadMap.
 *
 * @version 1.5
 *
 * <b>Example</b>
 * @code
 * [self.mapView setStatisticsLogCamera:YES];
 * @endcode
 
 */
-(void) setStatisticsLogCamera:(BOOL) pEnabled;

/**
 * Set the statistics location logging.  If enabled, the location received from
 * VMELocationInterface::updateLocation: will be logged at regular intervals
 * while location updates are received.
 *
 * @param pEnabled YES to enable, NO to disable it.  Default is YES.
 *
 * @note VMEStatisticsInterface::setStatisticsLog: must be enabled before
 * any logging will occur.
 *
 * @note Will be ignored if called before VMEMapView::loadMap.
 *
 * @version 1.5
 *
 * <b>Example</b>
 * @code
 * [self.mapView setStatisticsLogLocation:YES];
 * @endcode
 */
-(void) setStatisticsLogLocation:(BOOL) pEnabled;

/**
 * Set the statistics interest logging.  If enabled, the user's map interests will
 * be logged.  Interests include:
 * - selected places
 * - route information (origin and destinations)
 *
 * @param pEnabled YES to enable, NO to disable it.  Default is YES.
 *
 * @note VMEStatisticsInterface::setStatisticsLog: must be enabled before
 * any logging will occur.
 *
 * @note Will be ignored if called before VMEMapView::loadMap.
 *
 * @version 1.5
 *
 * <b>Example</b>
 * @code
 * [self.mapView setStatisticsLogInterest:YES];
 * @endcode
 */
-(void) setStatisticsLogInterest:(BOOL) pEnabled;


/**
 * See VMEStatisticsInterface::setStatisticsLog: for more info on what this returns.
 *
 * @return Whether enabled or not.
 *
 * @note This method should be called within or after VMELifeCycleListener::mapDidLoad:
 * because it can be enabled via the application parameters.
 *
 * @version 1.5
 *
 * <b>Example</b>
 * @code
 * BOOL isEnabled = [self.mapView isStatisticsLog];
 * @endcode
 *
 */
-(BOOL) isStatisticsLog;

/**
 * See VMEStatisticsInterface::setStatisticsLogCamera: for more info on what this returns.
 *
 * @return Whether enabled or not.
 *
 * @note This method should be called within or after VMELifeCycleListener::mapDidLoad:
 * because it can be enabled via the application parameters.
 *
 * @version 1.5
 *
 * <b>Example</b>
 * @code
 * BOOL isEnabled = [self.mapView isStatisticsLogCamera];
 * @endcode
 */
-(BOOL) isStatisticsLogCamera;

/**
 * See VMEStatisticsInterface::setStatisticsLogLocation: for more info on what this returns.
 *
 * @return Whether enabled or not.
 *
 * @note This method should be called within or after VMELifeCycleListener::mapDidLoad:
 * because it can be enabled via the application parameters.
 *
 * @version 1.5
 *
 * <b>Example</b>
 * @code
 * BOOL isEnabled = [self.mapView isStatisticsLogLocation];
 * @endcode
 */
-(BOOL) isStatisticsLogLocation;

/**
 * See VMEStatisticsInterface::setStatisticsLogInterest: for more info on what this returns.
 *
 * @return Whether enabled or not.
 *
 * @note This method should be called within or after VMELifeCycleListener::mapDidLoad:
 * because it can be enabled via the application parameters.
 *
 * @version 1.5
 *
 * <b>Example</b>
 * @code
 * BOOL isEnabled = [self.mapView isStatisticsLogInterest];
 * @endcode
 */
-(BOOL) isStatisticsLogInterest;

@end

