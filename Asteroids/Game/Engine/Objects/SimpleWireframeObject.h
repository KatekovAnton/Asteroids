//
//  SimpleWireframeObject.h
//  Asteroids
//
//  Created by Anton Katekov on 18.09.13.
//  Copyright (c) 2013 KatekovAnton. All rights reserved.
//

#ifndef __Asteroids__SimpleWireframeObject__
#define __Asteroids__SimpleWireframeObject__

#include <iostream>
#include "PivotObject.h"

class RenderObject;
class Material;
class ObjectBehaviourModel;

class SimpleWireframeObject : public PivotObject {
    
    RenderObject        *_renderAspect;
    Vector4             _color;
    
public:
    
    SimpleWireframeObject(RenderObject *renderObject, ObjectBehaviourModel *behaviorModel, Vector4 color);
    virtual ~SimpleWireframeObject();
    
    virtual RenderObject * GetRenderAspect();
    virtual Material * GetMaterial();
    
    
    virtual void Draw(Shader* shader);
    virtual void Frame(double time);
    
};

#endif /* defined(__Asteroids__SimpleWireframeObject__) */
