//
//  ios_display.h
//  Asterids
//
//  Created by Katekov Anton on 10/18/12.
//
//

#ifndef __Asterids__ios_display__
#define __Asterids__ios_display__

#include <iostream>
#include "Display.h"

class iosDisplay : public Display {
    float m_obScreenSizeWidth;
    float m_obScreenSizeHeigth;
    // resolution size, it is the size appropriate for the app resources.
    float m_obDesignResolutionSizeWidth;
    float m_obDesignResolutionSizeHeigth;
    
public:
    
    iosDisplay();
    
    virtual void InitGLSurface(unsigned int depthFormat, unsigned int pixelFormat);
    
    virtual float GetDisplayHeight();
    virtual float GetDisplayWidth();
    virtual float GetDisplayScale();
    
    virtual void    SwapBuffers();
    
    virtual bool    isOpenGLReady();
    virtual bool    setContentScaleFactor(float contentScaleFactor);
    
    
    virtual void setIMEKeyboardState(bool bOpen);
};

#endif /* defined(__Asterids__ios_display__) */
