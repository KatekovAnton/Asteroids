//
//  GameShipBullet.h
//  Asteroids
//
//  Created by Anton Katekov on 18.09.13.
//  Copyright (c) 2013 KatekovAnton. All rights reserved.
//

#ifndef __Asteroids__GameShipBullet__
#define __Asteroids__GameShipBullet__

#include <iostream>
#include "GameObject.h"
#include "ObjectControlledBehaviorModelDelegate.h"
#include "MAXAnimationDelegate.h"
#include "GameShipBulletDelegate.h"

class GameShipBullet : public GameObject, public ObjectControlledBehaviorModelDelegate, public MAXAnimationDelegate  {
    
    Vector3 _direction;
    Vector3 _movement;
    MAXAnimationBase *_existTimer;
    
public:
    
    GameShipBulletDelegate *_delegate;
    
    GameShipBullet(Vector2 direction);
    virtual ~GameShipBullet();
    
#pragma mark - ObjectControlledBehaviorModelDelegate
    virtual Vector3 GetMoveVector(void *sender);
    virtual Vector3 GetDirectionVector(void *sender);
    virtual void OnObjectCollidedToObject(void *sender, void *collider);
    virtual void* GetOwner();

#pragma mark - MAXAnimationDelegate
    virtual void OnAnimationStart(MAXAnimationBase* animation);
    virtual void OnAnimationUpdate(MAXAnimationBase* animation);
    virtual void OnAnimationFinish(MAXAnimationBase* animation);
    
};

#endif /* defined(__Asteroids__GameShipBullet__) */
