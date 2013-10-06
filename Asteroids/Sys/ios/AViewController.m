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
#include "DisplayDelegate.h"

AViewController      *_g_Controller = nil;

typedef struct DisplayDelegateAdapter {
    DisplayDelegate    *_delegate;
} DisplayDelegateAdapter;

@interface AViewController ()

@end

static int const _maxTouchesCount = 10;

@implementation AViewController

- (void)loadView {
    UIScreen *screen = [UIScreen mainScreen];  // Dispose of any resources that can be recreated.
    self.view = [[GLSurface alloc] initWithFrame:screen.bounds andDepthFormat:_depthFormat andPixelFormat:_pixelFormat];
    [self.view setMultipleTouchEnabled:YES];
    _glView = (GLSurface *)self.view;
    
    _capturedLeft = 0;
    _capturedRight = 0;
//    {
//        UIPanGestureRecognizer *gr = [[[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(onPan:)] autorelease];
//        [gr setMaximumNumberOfTouches:2];
//        [gr setMinimumNumberOfTouches:1];
//        [self.view addGestureRecognizer:gr];
//    }
}

- (UIStatusBarStyle)preferredStatusBarStyle
{
    return UIStatusBarStyleLightContent;
}

+ (AViewController *)instance {
    if (!_g_Controller) {
        _g_Controller = [[AViewController alloc] init];
    }
    return _g_Controller;
}

- (id)init
{
    if (self = [super init]) {
        _delegate = nil;
    }
    return self;
}

- (void)setDelegate:(void*)delegate
{
    if (_delegate) {
        delete _delegate;
    }
    _delegate = new DisplayDelegateAdapter();
    _delegate->_delegate = (DisplayDelegate*)delegate;
}

- (CGRect)rectLeft
{
    return CGRectMake(0, self.view.frame.size.width - 100, 100, 100);
}

- (CGRect)rectRight
{
    return CGRectMake(self.view.frame.size.height - 100, self.view.frame.size.width - 100, 100, 100);
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    
    _touches = touches;
    _event = event;
    _canhandleTap = YES;
    int ids[_maxTouchesCount] = {0};
    float xs[_maxTouchesCount] = {0.0f};
    float ys[_maxTouchesCount] = {0.0f};
    
    int i = 0;
    for (UITouch *touch in touches) {
        if (i >= _maxTouchesCount)
            break;
        
        ids[i] = (int)touch;
        xs[i] = [touch locationInView: [touch view]].x;
        ys[i] = [touch locationInView: [touch view]].y;
        ++i;
    }

    CGRect rectLeft = [self rectLeft];
    CGRect rectRight = [self rectRight];
    
    BOOL foundLeft = NO;
    BOOL foundRight = NO;
    for (int t = 0; t < i; t ++) {
        if (CGRectContainsPoint(rectLeft, CGPointMake(xs[t], ys[t])))
        {
            CGPoint vector = CGPointMake(xs[t] - (rectLeft.origin.x + rectLeft.size.width / 2), ys[t] - (rectLeft.origin.y + rectLeft.size.height / 2));
            if (_delegate)
                _delegate->_delegate->MoveVectorChanged(vector.x, vector.y);
            
            foundLeft = YES;
            _capturedLeft = ids[t];
        }
        if (CGRectContainsPoint(rectRight, CGPointMake(xs[t], ys[t])))
        {
            CGPoint vector = CGPointMake(xs[t] - (rectRight.origin.x + rectRight.size.width / 2), ys[t] - (rectRight.origin.y + rectRight.size.height / 2));
            if (_delegate)
                _delegate->_delegate->RotationVectorChanged(vector.x, vector.y);
            foundRight = YES;
            _capturedRight = ids[t];
        }
    }
    if (!foundLeft)
        _delegate->_delegate->MoveVectorChanged(0, 0);
    if (!foundRight)
        _delegate->_delegate->RotationVectorChanged(0, 0);
    
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event {
 
    int ids[_maxTouchesCount] = {0};
    float xs[_maxTouchesCount] = {0.0f};
    float ys[_maxTouchesCount] = {0.0f};
    
    int i = 0;
    for (UITouch *touch in touches) {
        if (i >= _maxTouchesCount)
            break;
        
        ids[i] = (int)touch;
        xs[i] = [touch locationInView: [touch view]].x;
        ys[i] = [touch locationInView: [touch view]].y;
        ++i;
    }
    
    CGRect rectLeft = [self rectLeft];
    CGRect rectRight = [self rectRight];
    

    for (int t = 0; t < i; t ++) {
        if (CGRectContainsPoint(rectLeft, CGPointMake(xs[t], ys[t])))
            _delegate->_delegate->MoveVectorChanged(0, 0);
        if (CGRectContainsPoint(rectRight, CGPointMake(xs[t], ys[t])))
            _delegate->_delegate->RotationVectorChanged(0, 0);
        if (ids[t] == _capturedRight)
        {
            _capturedRight =0;
            _delegate->_delegate->RotationVectorChanged(0, 0);
        }
        if (ids[t] == _capturedLeft)
        {
            _capturedLeft =0;
            _delegate->_delegate->MoveVectorChanged(0, 0);
        }
    }
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {

    int ids[_maxTouchesCount] = {0};
    float xs[_maxTouchesCount] = {0.0f};
    float ys[_maxTouchesCount] = {0.0f};
    
    int i = 0;
    for (UITouch *touch in touches) {
        if (i >= _maxTouchesCount)
            break;
        
        ids[i] = (int)touch;
        xs[i] = [touch locationInView: [touch view]].x;
        ys[i] = [touch locationInView: [touch view]].y;
        ++i;
    }
    
    CGRect rectLeft = [self rectLeft];
    CGRect rectRight = [self rectRight];
    
    
    for (int t = 0; t < i; t ++) {
        if (CGRectContainsPoint(rectLeft, CGPointMake(xs[t], ys[t])))
            _delegate->_delegate->MoveVectorChanged(0, 0);
        if (CGRectContainsPoint(rectRight, CGPointMake(xs[t], ys[t])))
            _delegate->_delegate->RotationVectorChanged(0, 0);
        
        if (ids[t] == _capturedRight)
        {
            _capturedRight =0;
            _delegate->_delegate->RotationVectorChanged(0, 0);
        }
        if (ids[t] == _capturedLeft)
        {
            _capturedLeft =0;
            _delegate->_delegate->MoveVectorChanged(0, 0);
        }
    }
    
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {

    int ids[_maxTouchesCount] = {0};
    float xs[_maxTouchesCount] = {0.0f};
    float ys[_maxTouchesCount] = {0.0f};
    
    int i = 0;
    for (UITouch *touch in touches) {
        if (i >= _maxTouchesCount)
            break;
        
        ids[i] = (int)touch;
        xs[i] = [touch locationInView: [touch view]].x;
        ys[i] = [touch locationInView: [touch view]].y;
        ++i;
    }
    
    CGRect rectLeft = [self rectLeft];
    CGRect rectRight = [self rectRight];
    
    BOOL foundLeft = NO;
    BOOL foundRight = NO;
    for (int t = 0; t < i; t ++) {
        if (CGRectContainsPoint(rectLeft, CGPointMake(xs[t], ys[t])) || _capturedLeft == ids[t])
        {
            CGPoint vector = CGPointMake(xs[t] - (rectLeft.origin.x + rectLeft.size.width / 2), ys[t] - (rectLeft.origin.y + rectLeft.size.height / 2));
            if (_delegate)
                _delegate->_delegate->MoveVectorChanged(vector.x, vector.y);
            
            foundLeft = YES;
        }
        if (CGRectContainsPoint(rectRight, CGPointMake(xs[t], ys[t])) || _capturedRight == ids[t])
        {
            CGPoint vector = CGPointMake(xs[t] - (rectRight.origin.x + rectRight.size.width / 2), ys[t] - (rectRight.origin.y + rectRight.size.height / 2));
            if (_delegate)
                _delegate->_delegate->RotationVectorChanged(vector.x, vector.y);
            foundRight = YES;
        }
    }
    if (!foundLeft && _capturedLeft == 0)
        _delegate->_delegate->MoveVectorChanged(0, 0);
    if (!foundRight && _capturedRight == 0)
        _delegate->_delegate->RotationVectorChanged(0, 0);
}


@end
