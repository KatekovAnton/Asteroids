//
//  ios_display.cpp
//  Asterids
//
//  Created by Katekov Anton on 10/18/12.
//
//

#include "ios_display.h"
#import "AAppDelegate.h"
#import "AViewController.h"

iosDisplay::iosDisplay() {
    
    if(![[UIApplication sharedApplication] isStatusBarHidden])
    {
        m_obScreenSizeWidth = [UIScreen mainScreen].bounds.size.height * [UIScreen mainScreen].scale;
        m_obScreenSizeHeigth = ([UIScreen mainScreen].bounds.size.width) * [UIScreen mainScreen].scale;
    }
    else
    {
        m_obScreenSizeWidth = [UIScreen mainScreen].bounds.size.width * [UIScreen mainScreen].scale;
        m_obScreenSizeHeigth = [UIScreen mainScreen].bounds.size.height * [UIScreen mainScreen].scale;
    }
    
    if (m_obScreenSizeWidth < m_obScreenSizeHeigth) {
        float t = m_obScreenSizeWidth;
        m_obScreenSizeWidth = m_obScreenSizeHeigth;
        m_obScreenSizeHeigth = t;
        
    }
    
    m_obDesignResolutionSizeWidth = m_obScreenSizeWidth;
    m_obDesignResolutionSizeHeigth = m_obScreenSizeHeigth;

}

void iosDisplay::InitGLSurface(unsigned int depthFormat, unsigned int pixelFormat) {
    
    UIScreen *iphoneScreen = [UIScreen mainScreen];
   
    UIWindow *window = [[UIWindow alloc] initWithFrame:iphoneScreen.bounds];
  
    [AViewController instance].pixelFormat = pixelFormat;
    [AViewController instance].depthFormat = depthFormat;
    
    window.rootViewController = [AViewController instance];
    [window makeKeyAndVisible];
}

GLfloat iosDisplay::GetDisplayHeight() {
    float result = m_obScreenSizeHeigth;//[[ViewController instance] view].layer.bounds.size.height * [UIScreen mainScreen].scale;
    return result;
}

GLfloat iosDisplay::GetDisplayWidth() {
    float result = m_obScreenSizeWidth;//[[ViewController instance] view].layer.bounds.size.width * [UIScreen mainScreen].scale;
    return result;
}

GLfloat iosDisplay::GetDisplayScale()
{
    return [UIScreen mainScreen].scale;
}

void iosDisplay::SwapBuffers() {
    EAGLContext* context = [EAGLContext currentContext];
    
    [context presentRenderbuffer:GL_RENDERBUFFER];
}

bool iosDisplay::isOpenGLReady() {
    return [AViewController instance].view != nil;
}

bool iosDisplay::setContentScaleFactor(float contentScaleFactor) { 
    return true;
}

void iosDisplay::setIMEKeyboardState(bool bOpen) {
    if (bOpen) {
        [[AViewController instance].view becomeFirstResponder];
    } else
        [[AViewController instance].view resignFirstResponder];
}


