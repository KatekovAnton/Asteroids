//
//  ObjectControlledBehaviorModelDelegate.h
//  Asteroids
//
//  Created by Anton Katekov on 18.09.13.
//  Copyright (c) 2013 KatekovAnton. All rights reserved.
//

#ifndef Asteroids_ObjectControlledBehaviorModelDelegate_h
#define Asteroids_ObjectControlledBehaviorModelDelegate_h

#include "Math.h"

class ObjectControlledBehaviorModelDelegate {
    
public:
    
    virtual Vector3 GetMoveVector(void *sender) = 0;
    virtual Vector3 GetDirectionVector(void *sender) = 0;
    virtual void OnObjectCollidedToObject(void *sender, void *collider) = 0;
    
};

#endif
