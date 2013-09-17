//
//  RenderObject.h
//  Asteroids
//
//  Created by Katekov Anton on 11/1/12.
//
//

#ifndef __Asteroids__RenderObject__
#define __Asteroids__RenderObject__

#include <iostream>

class Material;

using namespace std;

class RenderObject {
public:
    string          pictureTehnique;
    string          shadowTehnique;
    
    bool            isAnimated;
    bool            isShadowReceiver;
    bool            isShadowCaster;
    
    bool            isVisible;
    bool            isTransparent;
    bool            isSelfIllumination;
    
    float           additionalOpacity;
    
    
    RenderObject();
    virtual ~RenderObject();
    
    virtual void Render() = 0;
};



#endif /* defined(__Asteroids__RenderObject__) */
