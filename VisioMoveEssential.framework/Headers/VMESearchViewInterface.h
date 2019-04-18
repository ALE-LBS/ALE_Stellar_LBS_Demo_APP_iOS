/*
 * Copyright (c) Visioglobe SAS. All rights reserved.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */
#import <Foundation/Foundation.h>

#pragma mark - VMESearchViewCallback
/**
 * Callback protocol for receiving search view results.  See VMESearchViewInterface
 * for displaying the search view.
 *
 * @version 1.0
 */
@protocol VMESearchViewCallback <NSObject>

/**
 * Notified when a place was selected from the search view
 * @param mapView The map view who received the original request
 * @param placeID The id of the place selected.
 *
 * @version 1.0
 */
-(void) searchView:(VMEMapView*)mapView didSelectPlaceID:(NSString*)placeID;

/**
 * Notified when the search view was cancelled
 * @param mapView The map view who received the original request.
 *
 * @version 1.0
 */
-(void) searchViewDidCancel:(VMEMapView*)mapView;

@end

#pragma mark - VMESearchViewInterface

/**
 * Interface protocol for displaying the search view.
 *
 * @version 1.0
 */
@protocol VMESearchViewInterface <NSObject>

/**
 * Request to show the search view.
 * @param title The title to display within the seach view.
 * @param callback The callback to invoke with the result.  Pass nil if you do
 * not need to be informed of the result.
 *
 * @version 1.0
 *
 * <b>Example</b>
 @code
[self.mapView showSearchViewWithTitle:@"My Title" callback:nil];
 @endcode
 */
-(void) showSearchViewWithTitle:(NSString*) title callback:(id<VMESearchViewCallback>) callback;
@end

