//
//  SimpleObject.h
//  Asteroids
//
//  Created by Anton Katekov on 18.09.13.
//  Copyright (c) 2013 KatekovAnton. All rights reserved.
//

#ifndef __Asteroids__SimpleObject__
#define __Asteroids__SimpleObject__

#include <iostream>
#include "PivotObject.h"

class RenderObject;
class Material;
class ObjectBehaviourModel;

class SimpleObject : public PivotObject {
    
    RenderObject        *_renderAspect;
    Material            *_material;
public:
    
    SimpleObject(RenderObject *renderObject, ObjectBehaviourModel *behaviorModel, Material *material);
    virtual ~SimpleObject();
    
    virtual RenderObject * GetRenderAspect();
    virtual Material * GetMaterial();
    
    
    virtual void Frame(double time);
    
};

#endif /* defined(__Asteroids__SimpleObject__) */
