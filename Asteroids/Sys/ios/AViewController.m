//
//  AViewController.m
//  Asteroids
//
//  Created by Anton Katekov on 04.09.13.
//  Copyright (c) 2013 KatekovAnton. All rights reserved.
//

#import "AViewController.h"
#import "GLSurface.h"
#include <OpenGLES/ES2/gl.h>
#include "DisplayPinchDelegate.h"

AViewController      *_g_Controller = nil;

typedef struct DisplayPinchDelegateAdapter {
    DisplayPinchDelegate    *_delegate;
} DisplayPinchDelegateAdapter;

@interface AViewController ()

@end

@implementation AViewController

- (void)loadView {
    UIScreen *screen = [UIScreen mainScreen];  // Dispose of any resources that can be recreated.
    self.view = [[GLSurface alloc] initWithFrame:screen.bounds andDepthFormat:_depthFormat andPixelFormat:_pixelFormat];
    _glView = (GLSurface *)self.view;
}

+ (AViewController *)instance {
    if (!_g_Controller) {
        _g_Controller = [[AViewController alloc] init];
    }
    return _g_Controller;
}

@end
