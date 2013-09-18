//
//  AAppDelegate.h
//  Asteroids
//
//  Created by Anton Katekov on 04.09.13.
//  Copyright (c) 2013 KatekovAnton. All rights reserved.
//

#import <UIKit/UIKit.h>

@class AViewController;

@interface AAppDelegate : UIResponder <UIApplicationDelegate>{
     NSTimeInterval lastTime;
}

@property (strong, nonatomic) UIWindow *window;

@property (strong, nonatomic) AViewController *viewController;

@end
