//
//  CollisionObject.h
//  Asteroids
//
//  Created by Anton Katekov on 29.09.13.
//  Copyright (c) 2013 KatekovAnton. All rights reserved.
//

#ifndef __Asteroids__CollisionObject__
#define __Asteroids__CollisionObject__

#include <iostream>
#include "miniPrefix.h"
#include "CollisionObjectDelegate.h"

class CollisionObject {
    
    Vector4     *_points;
    int         _count;
    Matrix4     _previousPosition;
    
public:
    
    bool GetIsPoint() const {return _count == 1;}
    
    void *_owner_w;
    CollisionObjectDelegate *_delegate_w;
    
    CollisionObject(Vector4 *points, int count);
    ~CollisionObject();
    
    void Start();
    void Update();
    
    Matrix4 GetCollisionObjectPreviousTransform() { return _previousPosition; }
    Matrix4 GetCollisionObjectTransform() { return _delegate_w?_delegate_w->GetCollisionObjectTransformMatrix():Matrix4Identity; }
    Vector4 *GetCollisionObjectPoints() { return _points; }
    int GetCollisionObjectPointsCount() { return _count; }
    
};

#endif /* defined(__Asteroids__CollisionObject__) */
