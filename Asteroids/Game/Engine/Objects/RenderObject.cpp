//
//  RenderObject.cpp
//  Asteroids
//
//  Created by Katekov Anton on 11/1/12.
//
//

#include "RenderObject.h"


RenderObject::RenderObject() {
    additionalOpacity = 1.0;
    pictureTehnique = string();
    shadowTehnique = string();
    isAnimated = false;
    isShadowCaster = false;
    isShadowReceiver = false;
    
    isVisible = false;
    isTransparent = false;
    isSelfIllumination = false;
}

RenderObject::~RenderObject() {
}

