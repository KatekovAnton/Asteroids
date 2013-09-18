//
//  Display.h
//  Asterids
//
//  Created by Katekov Anton on 10/18/12.
//
//

#ifndef __Asterids__Display__
#define __Asterids__Display__
#include "GlobalConstants.h"
#include <iostream>

class Display {
    static Display * _current;
    
public:
    static Display * currentDisplay();
    
    virtual void  InitGLSurface(unsigned int depthFormat, unsigned int pixelFormat);
    
    virtual GLfloat GetDisplayHeight();
    virtual GLfloat GetDisplayWidth();
    
    virtual GLfloat GetDisplayScale();
    
    virtual void SwapBuffers();
    
    void SetViewPortInPoints(float x , float y , float w , float h);
    void SetScissorInPoints(float x , float y , float w , float h);

};

#endif /* defined(__Asterids__Display__) */
