//
//  GameShip.h
//  Asteroids
//
//  Created by Anton Katekov on 18.09.13.
//  Copyright (c) 2013 KatekovAnton. All rights reserved.
//

#ifndef __Asteroids__GameShip__
#define __Asteroids__GameShip__

#include <iostream>
#include "GameObject.h"
#include "ObjectControlledBehaviorModelDelegate.h"

class GameShip : public GameObject, public ObjectControlledBehaviorModelDelegate {
    
    Vector3 _moveVector;
    Vector3 _directionVector;
    
public:
    
    GameShip();
    virtual ~GameShip();
    virtual void SetPosition(Vector2 position);
    
    void MoveShipInDirection(float x, float y);
    void SetShipDirection(float x, float y);
    
#pragma mark - ObjectControlledBehaviorModelDelegate
        
    virtual Vector3 GetMoveVector(void *sender);
    virtual Vector3 GetDirectionVector(void *sender);
    virtual void OnObjectCollidedToObject(void *sender, void *collider);
    
};

#endif /* defined(__Asteroids__GameShip__) */
