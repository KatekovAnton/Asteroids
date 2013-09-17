//
//  RenderSystem.h
//  Asteroids
//
//  Created by Katekov Anton on 10/18/12.
//
//

#ifndef __Asteroids__RenderSystem__
#define __Asteroids__RenderSystem__

#include "GlobalConstants.h"
#include <iostream>

class Display;

class RenderSystem {
    Display             *_deviceDisplay;
    
public:
    
    RenderSystem();
    
    Display * GetDisplay();
    
    
    void InitOpenGL();
    
    void EndFrame();
};

#endif /* defined(__Asteroids__RenderSystem__) */
