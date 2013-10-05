//
//  GameAsteroid.h
//  Asteroids
//
//  Created by Anton Katekov on 18.09.13.
//  Copyright (c) 2013 KatekovAnton. All rights reserved.
//

#ifndef __Asteroids__GameAsteroid__
#define __Asteroids__GameAsteroid__

#include <iostream>
#include "GameObject.h"
#include "ObjectControlledBehaviorModelDelegate.h"

class GameAsteroid : public GameObject, public ObjectControlledBehaviorModelDelegate {
    
    Vector3 _moveVector;
    Vector3 _directionVector;
    
public:
    
    GameAsteroid(bool large);
    virtual ~GameAsteroid();

#pragma mark - ObjectControlledBehaviorModelDelegate
    virtual Vector3 GetMoveVector(void *sender);
    virtual Vector3 GetDirectionVector(void *sender);
    virtual void OnObjectCollidedToObject(void *sender, void *collider);
    
};

#endif /* defined(__Asteroids__GameAsteroid__) */
