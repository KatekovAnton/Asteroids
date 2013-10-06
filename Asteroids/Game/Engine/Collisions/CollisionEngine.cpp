//
//  CollisionEngine.cpp
//  Asteroids
//
//  Created by Anton Katekov on 29.09.13.
//  Copyright (c) 2013 KatekovAnton. All rights reserved.
//

#include "CollisionEngine.h"
#include "CollisionObject.h"

static CollisionEngine *_staticCollisionEngine = NULL;

bool intersection(Vector4 start1, Vector4 end1, Vector4 start2, Vector4 end2, Vector4 *out_intersection)
{
    Vector4 dir1 = Vector4Subtract(end1, start1);
    Vector4 dir2 = Vector4Subtract(end2, start2);
    
    //считаем уравнения прямых проходящих через отрезки
    float a1 = -dir1.y;
    float b1 = +dir1.x;
    float d1 = -(a1*start1.x + b1*start1.y);
    
    float a2 = -dir2.y;
    float b2 = +dir2.x;
    float d2 = -(a2*start2.x + b2*start2.y);
    
    //подставляем концы отрезков, для выяснения в каких полуплоскотях они
    float seg1_line2_start = a2*start1.x + b2*start1.y + d2;
    float seg1_line2_end = a2*end1.x + b2*end1.y + d2;
    
    float seg2_line1_start = a1*start2.x + b1*start2.y + d1;
    float seg2_line1_end = a1*end2.x + b1*end2.y + d1;
    
    //если концы одного отрезка имеют один знак, значит он в одной полуплоскости и пересечения нет.
    if (seg1_line2_start * seg1_line2_end >= 0 || seg2_line1_start * seg2_line1_end >= 0)
        return false;
    
    float u = seg1_line2_start / (seg1_line2_start - seg1_line2_end);
    *out_intersection = Vector4Add(start1, Vector4MultiplyScalar(dir1, u));
    
    return true;
}

CollisionEngine* CollisionEngine::SharedCollisionEngine()
{
    if (!_staticCollisionEngine)
        _staticCollisionEngine = new CollisionEngine();
    
    return _staticCollisionEngine;
}

CollisionEngine::CollisionEngine()
:_objectMeshes(new USimpleContainer<CollisionObject*>(10)), _objectPoints(new USimpleContainer<CollisionObject*>(10)), _collidedObjects(new USimpleContainer<CollisionPair>(10)), _pointBuffer(new USimpleContainer<Vector4>(10))
{
}

CollisionEngine::~CollisionEngine()
{
    delete _objectMeshes;
    delete _objectPoints;
    delete _collidedObjects;
    delete _pointBuffer;
}

void CollisionEngine::AddObject(CollisionObject *object)
{
    if (object->GetIsPoint())
        _objectPoints->addObject(object);
    else
        _objectMeshes->addObject(object);
    
    object->Start();
}

void CollisionEngine::RemoveObject(CollisionObject *object)
{
    if (object->GetIsPoint())
        _objectPoints->removeObject(object);
    else
        _objectMeshes->removeObject(object);
}

void CollisionEngine::CalculateCollisions()
{
    _collidedObjects->clear();
    
    //calc
    collidedPoints.clear();
    for (int j = 0; j < _objectMeshes->GetCount(); j++)
    {
        CollisionObject *mesh = _objectMeshes->objectAtIndex(j);
        memcpy(_pointBuffer->GetArrayPointer(), mesh->GetCollisionObjectPoints(), sizeof(mesh->GetCollisionObjectPoints()) * mesh->GetCollisionObjectPointsCount());
        for (int i = 0; i < _objectPoints->GetCount(); i++)
        {
            if (collidedPoints.indexOf(i) != -1)
                continue;
            
            CollisionObject *point = _objectPoints->objectAtIndex(i);
            Vector4 point1 = Vector4MakeWithVector3(Matrix4GetTranslation(point->GetCollisionObjectPreviousTransform()), 1);
            Vector4 point2 = Vector4MakeWithVector3(Matrix4GetTranslation(point->GetCollisionObjectTransform()), 1);
            point1 = point2;
            
            
        }
    }
    
    
    //updateObjects
    for (int i = 0; i < _objectPoints->GetCount(); i++)
        _objectPoints->objectAtIndex(i)->Update();
    
    for (int i = 0; i < _objectMeshes->GetCount(); i++)
        _objectMeshes->objectAtIndex(i)->Update();
    
}
