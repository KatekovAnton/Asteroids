//
//  Display.h
//  Asteroids
//
//  Created by Katekov Anton on 10/18/12.
//
//

#ifndef __Asteroids__Display__
#define __Asteroids__Display__
#include "GlobalConstants.h"
#include <iostream>

class DisplayDelegate;

class Display {
    static Display * _current;
    
public:
    static Display * currentDisplay();
    
    virtual void  InitGLSurface(unsigned int depthFormat, unsigned int pixelFormat);
    
    virtual GLfloat GetDisplayHeight();
    virtual GLfloat GetDisplayWidth();
    
    virtual GLfloat GetDisplayScale();
    
    virtual void SwapBuffers();
    
    virtual void SetDelegate(DisplayDelegate *delegate) = 0;
    
    void SetViewPortInPoints(float x , float y , float w , float h);
    void SetScissorInPoints(float x , float y , float w , float h);

};

#endif /* defined(__Asteroids__Display__) */
