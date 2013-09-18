//
//  SimpleObject.cpp
//  Asteroids
//
//  Created by Anton Katekov on 18.09.13.
//  Copyright (c) 2013 KatekovAnton. All rights reserved.
//

#include "SimpleObject.h"
#include "PivotObject.h"

SimpleObject::SimpleObject(RenderObject *renderObject, ObjectBehaviourModel *behaviorModel, Material *material)
:PivotObject(behaviorModel)
{
}

SimpleObject::~SimpleObject()
{
    delete _renderAspect;
    delete _material;
}

RenderObject *SimpleObject::GetRenderAspect()
{
    return _renderAspect;
}

Material *SimpleObject::GetMaterial()
{
    return _material;
}

void SimpleObject::Frame(double time)
{}