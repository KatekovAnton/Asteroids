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
    
public:
    
    GameShip();
    virtual ~GameShip();
    
#pragma mark - ObjectControlledBehaviorModelDelegate
        
    virtual Vector3 GetMoveVector(void *sender);
    virtual void OnObjectCollidedToObject(void *sender, void *collider);
    
};

#endif /* defined(__Asteroids__GameShip__) */
