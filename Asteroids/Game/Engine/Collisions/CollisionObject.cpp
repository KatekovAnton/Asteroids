//
//  CollisionObject.cpp
//  Asteroids
//
//  Created by Anton Katekov on 29.09.13.
//  Copyright (c) 2013 KatekovAnton. All rights reserved.
//

#include "CollisionObject.h"

CollisionObject::CollisionObject(Vector4 *points, int count)
:_points(points), _count(count), _delegate_w(NULL), _owner_w(NULL)
{
    
}

CollisionObject::~CollisionObject()
{
    free(_points);
}

void CollisionObject::Start()
{
    _previousPosition = GetCollisionObjectTransform();
}

void CollisionObject::Update()
{
    _previousPosition = GetCollisionObjectTransform();
}
