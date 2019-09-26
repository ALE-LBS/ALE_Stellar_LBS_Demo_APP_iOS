//
//  ChannelImage.h
//  Rainbow
//
//  Created by Le Trong Nghia Huynh on 13/02/2019.
//  Copyright © 2019 ALE. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIImage.h>

@interface ChannelItemImage : NSObject

/**
 *  The ID of the image
 */
@property (nonatomic, readonly) NSString *rainbowId;

/**
 *  The image object
 */
@property (nonatomic, readwrite) UIImage *image;

@property (nonatomic, assign) BOOL isOriginalFile;

-(instancetype) initWithRainbowId:(NSString *) rainbowId;

@end
