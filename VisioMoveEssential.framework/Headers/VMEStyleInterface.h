/*
 * Copyright (c) Visioglobe SAS. All rights reserved.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#pragma mark - VMEBundleInterface

/**
 * A protocol for customising the map's style.
 * @version 1.13
 */
@protocol VMEStyleInterface <NSObject>

/**
 * Overrides the map's default font (currently DejaVuSans.ttf).
 *
 * @note Should be called within the VMELifeCycleListener::mapDidInitializeEngine: notification.
 *
 * @param filePath The TrueType Font file (*.ttf) to load. The font will be searched locally in the map bundle's "config" directory otherwise use an absolute path.
 * @returns YES if the font file was set successfully, otherwise NO.
 *
 * @version 1.13
 * <b>Example</b>
 * @code
#pragma - VMELifeCycleListener
-(void) mapDidInitializeEngine:(VMEMapView *)mapView {
    NSString* lFontFile = [[NSBundle mainBundle] pathForResource:@"font.name.here" ofType:@"ttf"];
    [mapView setMapFont:lFontFile];
}
 * @endcode
 */
-(BOOL) setMapFont:(NSString*)filePath;
@end


