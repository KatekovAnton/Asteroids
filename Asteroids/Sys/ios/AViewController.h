//
//  AViewController.h
//  Asteroids
//
//  Created by Anton Katekov on 04.09.13.
//  Copyright (c) 2013 KatekovAnton. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>

struct DisplayDelegateAdapter;

@class GLSurface;

@interface AViewController : UIViewController<UIGestureRecognizerDelegate> {
    
@private
    GLSurface               *_glView;
    
    id _pan;
    id _pinch;
    id _tap;
    
    struct DisplayDelegateAdapter *_delegate;
    NSSet* _touches;
    UIEvent* _event;
    
    BOOL _canhandleTap;
    
    NSTimeInterval lastTapTime;
    
    int _capturedLeft;
    int _capturedRight;
    
}

@property (nonatomic, assign) GLuint depthFormat;
@property (nonatomic, assign) GLuint pixelFormat;

- (void)setDelegate:(void*)delegate;

+ (AViewController *)instance;

@end
