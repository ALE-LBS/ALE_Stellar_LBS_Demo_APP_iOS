//
//  Location.h
//  Rainbow
//
//  Created by Alaa Bzour on 2/18/19.
//  Copyright © 2019 ALE. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface Location : NSObject
/**
 * Location Latitude name
 */
@property (readonly)  float latitude;
/**
 * Location longitude name
 */
@property (readonly)  float longitude;
/**
 * Location city
 */
@property (readonly) NSString *city;
/**
 * Location country
 */
@property (readonly) NSString *country;
/**
 * Location state
 */
@property (readonly) NSString *state;
/**
 * Location ZIP
 */
@property (readonly) NSString *zip;
/**
 * Location street
 */
@property (readonly) NSString *street;
@end
