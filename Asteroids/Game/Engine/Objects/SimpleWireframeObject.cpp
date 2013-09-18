//
//  SimpleWireframeObject.cpp
//  Asteroids
//
//  Created by Anton Katekov on 18.09.13.
//  Copyright (c) 2013 KatekovAnton. All rights reserved.
//

#include "SimpleWireframeObject.h"
#include "PivotObject.h"
#include "RenderObject.h"
#include "Shader.h"

SimpleWireframeObject::SimpleWireframeObject(RenderObject *renderObject, ObjectBehaviourModel *behaviorModel, Vector4 color)
:PivotObject(behaviorModel), _color(color), _renderAspect(renderObject)
{
}

SimpleWireframeObject::~SimpleWireframeObject()
{
    delete _renderAspect;
}

RenderObject *SimpleWireframeObject::GetRenderAspect()
{
    return _renderAspect;
}

Material *SimpleWireframeObject::GetMaterial()
{
    return NULL;
}

void SimpleWireframeObject::Draw(Shader* shader)
{
    shader->SetVector4Value(UNIFORM_VECTOR1, _color.v);
    PivotObject::Draw(shader);
}

void SimpleWireframeObject::Frame(double time)
{}