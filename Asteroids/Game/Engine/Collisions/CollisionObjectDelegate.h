//
//  CollisionObjectDelegate.h
//  Asteroids
//
//  Created by Anton Katekov on 06.10.13.
//  Copyright (c) 2013 KatekovAnton. All rights reserved.
//

#ifndef Asteroids_CollisionObjectDelegate_h
#define Asteroids_CollisionObjectDelegate_h

#include "miniPrefix.h"

class CollisionObjectDelegate {
    
public:
    
    virtual Matrix4 GetCollisionObjectTransformMatrix() = 0;
    
};

#endif
