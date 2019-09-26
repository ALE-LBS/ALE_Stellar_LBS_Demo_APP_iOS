//
//  RainbowTV.h
//  Rainbow
//
//  Created by Le Trong Nghia Huynh on 07/06/2019.
//  Copyright © 2019 ALE. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface RainbowTV : NSObject

@property (nonatomic, readonly) NSString *name;

@property (nonatomic, readonly) NSString *location;

@property (nonatomic, readonly) NSString *locationDetail;

@property (nonatomic, readonly) NSString *roomName;

-(NSDictionary *) dictionaryRepresentation;

@end
