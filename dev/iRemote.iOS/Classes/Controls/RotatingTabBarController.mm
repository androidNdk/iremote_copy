/**
 * Copyright (c) 2013 Egor Pushkin. All rights reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#import "RotatingTabBarController.h"

// Persistent UI config.
#include "Common/Common.h"
#include "../State/UIConfig.h"

@implementation RotatingTabBarController

/**
 * IMPORTANT NOTES:
 * - Current implementation depends on the fact that all root controllers are
 *   navigation controllers.
 * - Tab bar view class name must contain 'UITabBar'.
 * - Transition view class name must contain 'UITransitionView'. 
 */

#pragma mark Views finder

- (UIView *)findView:(NSString *)name forParent:(UIView *)parent {    
    if ( NSNotFound != [[parent description] rangeOfString:name].location ) {
        return parent;        
    }
    for ( UIView *view in parent.subviews ) {
        UIView *matchingView = [self findView:name forParent:view];
        if ( nil != matchingView )
            return matchingView;
    }        
    return nil;
}

- (UIView *)findView:(NSString *)name {
    return [self findView:name forParent:[UIApplication sharedApplication].keyWindow]; 
}

#pragma mark Bars manipulation

- (void)rememberScreenLayout {
    // Find tab bar related views.
    UIView *transView = [self findView:@"UITransitionView"];    
    // Remember initial frame of transition view. 
    if ( CGRectEqualToRect(portraitTransitionViewFrame, CGRectZero) ) {
        portraitTransitionViewFrame = CGRectMake( 
            0.0f, 0.0f, transView.frame.size.width, transView.frame.size.height);          
    }
}

- (void)showBars {
    // Check whether controller is not yet ready to show bars.
    // This occurs, when bars are shown, before it was hidden.
    if ( CGRectEqualToRect(portraitTransitionViewFrame, CGRectZero) )
        return;
        
    // Show navigation bar with animation.    
    UINavigationController *navigationController = (UINavigationController *)self.selectedViewController;
    [navigationController setNavigationBarHidden:NO animated:YES];        
    
    // Find tab bar related views.    
    UIView *transView = [self findView:@"UITransitionView"];
    UIView *tabbar = [self findView:@"UITabBar"];
    
    // Restore frame of transition view.
    transView.frame = portraitTransitionViewFrame;
    // Show tab bar with animation.
    [UIView beginAnimations:nil context:nil];
    [UIView setAnimationDuration:0.4f];
    tabbar.frame = CGRectMake( 
        tabbar.frame.origin.x,
        480.0f - tabbar.frame.size.height, 
        tabbar.frame.size.width,
        tabbar.frame.size.height);
    [UIView commitAnimations];      
}

- (void)hideBars {
    // Hide navigation bar with animation.
    UINavigationController *navigationController = (UINavigationController *)self.selectedViewController;
    [navigationController setNavigationBarHidden:YES animated:YES];        
    
    // Find tab bar related views.
    UIView *transView = [self findView:@"UITransitionView"];
    UIView *tabbar = [self findView:@"UITabBar"];    
    
    // Specify new size for transition view. This must be done to fit the entire
    // screen, including space allocated for tab bar. System still treats this
    // space as occupied, even when tab bar is hidden programmatically.
    transView.frame = CGRectMake(0.0f,  0.0f, 480.0f, 320.0f);     
    
    // Hide tab bar with animation.
    [UIView beginAnimations:nil context:nil];
    [UIView setAnimationDuration:0.4f];
    tabbar.frame = CGRectMake( 
        tabbar.frame.origin.x,
        480.0f + tabbar.frame.size.height, 
        tabbar.frame.size.width,
        tabbar.frame.size.height);
    [UIView commitAnimations];
}

#pragma mark Initialization section

- (id)initWithCoder:(NSCoder*)coder {
    if ((self = [super initWithCoder:coder])) {
        self.delegate = self;
        portraitTransitionViewFrame = CGRectZero;
    }
    return self;
}

#pragma mark Rotation section

- (void)willRotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration {
    [super willRotateToInterfaceOrientation:toInterfaceOrientation duration:duration];
    if ( UIInterfaceOrientationPortrait != toInterfaceOrientation 
        && UIInterfaceOrientationPortraitUpsideDown != toInterfaceOrientation ) {
        [self rememberScreenLayout];
    }
}

- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation {    
    [super didRotateFromInterfaceOrientation:fromInterfaceOrientation];     
    if ( UIInterfaceOrientationPortrait == self.interfaceOrientation
        || UIInterfaceOrientationPortraitUpsideDown == self.interfaceOrientation ) {
        [self showBars];
    } else {
        [self hideBars];        
    }        
}

/**
 * This method specifies, which orientations are supported for particular controller.
 * TODO: UIInterfaceOrientationPortraitUpsideDown is not supported for now due
 * to unexpected behavior on the devices.
 */
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Check whether auto rotation is enabled globally.
    if ( !RemotePC::UIConfig::Instance().Autorotation() )
        return
            ( UIInterfaceOrientationPortrait == interfaceOrientation );
    // Check whether auto rotation is enabled for the current controller.
    // Touch Pad.
    if ( 0 == self.selectedIndex ) 
        return (
            ( UIInterfaceOrientationPortrait == interfaceOrientation )
            /* || ( UIInterfaceOrientationPortraitUpsideDown == interfaceOrientation ) */
            || ( UIInterfaceOrientationLandscapeLeft == interfaceOrientation )
            || ( UIInterfaceOrientationLandscapeRight == interfaceOrientation )
        );
    // Keyboard.
    else if ( 3 == self.selectedIndex )
        // This means that the screen remains unchanged, nomatter how 
        // device orientation changes.
        return NO;
    // Other.
    else
        return
            ( ( UIInterfaceOrientationPortrait == interfaceOrientation )
            /* || ( UIInterfaceOrientationPortraitUpsideDown == interfaceOrientation ) */ );    
}

@end