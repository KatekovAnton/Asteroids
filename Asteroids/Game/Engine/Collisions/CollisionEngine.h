//
//  CollisionEngine.h
//  Asteroids
//
//  Created by Anton Katekov on 29.09.13.
//  Copyright (c) 2013 KatekovAnton. All rights reserved.
//

#ifndef __Asteroids__CollisionEngine__
#define __Asteroids__CollisionEngine__

#include <iostream>
#include "miniPrefix.h"

class CollisionObject;

#define CollisionPair pair<CollisionObject*, CollisionObject*>

class CollisionEngine {
    
    USimpleContainer<CollisionObject*>  *_objectPoints;
    USimpleContainer<CollisionObject*>  *_objectMeshes;
    
    USimpleContainer<CollisionPair>     *_collidedObjects;
    
    USimpleContainer<Vector4> *_pointBuffer;
    
    USimpleContainer<int> collidedPoints;
    
public:
    
    static CollisionEngine* SharedCollisionEngine();
    
    CollisionEngine();
    ~CollisionEngine();
    
    void AddObject(CollisionObject *object);
    void RemoveObject(CollisionObject *object);
    
    void CalculateCollisions();
    
};

#endif /* defined(__Asteroids__CollisionEngine__) */
