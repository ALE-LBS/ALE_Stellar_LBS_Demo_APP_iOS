/*
 * Copyright (c) Visioglobe SAS. All rights reserved.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */
#import "VMEPosition.h"
#import "VMEManeuverType.h"

/**
 * A segment describes a part of a computed route.
 *
 * @version 1.17
 */
@interface VMESegment : NSObject <NSCopying>

/**
 * Instantiates a segment object.
 *
 * @param maneuverType The maneuver that describes the end of the segment.
 * @param duration The duration (seconds) of the segment.
 * @param length The length (metres) of the segment.
 * @param path An array of positions that make up the segment
 *
 * @version 1.17
 */
-(instancetype)initWithManeuver:(VMEManeuverType)maneuverType
                       duration:(double)duration
                         length:(double)length
                           path:(NSArray<VMEPosition*>*)path;

/**
 * The path of the segment.
 *
 * @version 1.17
 */
@property (readonly) NSArray<VMEPosition*>* path;
/**
 * The duration (seconds) of the segment.
 *
 * @version 1.17
 */
@property (readonly) double duration;
/**
 * The length (metres) of the segment.
 *
 * @version 1.17
 */
@property (readonly) double length;
/**
 * The maneuver type of the segment.
 *
 * @version 1.17
 */
@property (readonly) VMEManeuverType maneuverType;
@end
