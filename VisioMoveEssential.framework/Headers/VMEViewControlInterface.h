/*
 * Copyright (c) Visioglobe SAS. All rights reserved.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */
#pragma mark - VMEViewControlInterface

/**
 * An interface protocol for controlling the SDK's view elements.
 *
 * @version 1.9
 */
@protocol VMEViewControlInterface <NSObject>

/**
 * Control whether the selector view is visible.  If the selector view is not visible, it will
 * be the integrator's responsibility to provide a floor change mechanism.
 *
 * @param pVisible If YES, then the selector view will be visible.  Otherwise, the selector
 * view will be hidden.
 * @version 1.9
 */
-(void) setSelectorViewVisible:(BOOL)pVisible;

/**
 * @return A BOOL indicating whether the selector view is visible or not.
 * @see For more info VMEViewControlInterface::setSelectorViewVisible:
 * @version 1.9
 */
-(BOOL) getSelectorViewVisible;

@end

