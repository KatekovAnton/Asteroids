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
#include "MAXAnimationDelegate.h"
#include "GameShipDelegate.h"

class GameShip : public GameObject, public ObjectControlledBehaviorModelDelegate, public MAXAnimationDelegate {
    
    Vector3 _moveVector;
    Vector3 _directionVector;
    
    bool _fireing;
    MAXAnimationBase *_fireTimer;
    
public:
    
    GameShipDelegate *_delegate;
    
    GameShip();
    virtual ~GameShip();
    virtual void SetPosition(Vector2 position);
    
    void MoveShipInDirection(float x, float y);
    void SetShipDirection(float x, float y);
    
    Vector3 GetBulletStartPosition();
    
#pragma mark - ObjectControlledBehaviorModelDelegate
    virtual Vector3 GetMoveVector(void *sender);
    virtual Vector3 GetDirectionVector(void *sender);
    virtual void OnObjectCollidedToObject(void *sender, void *collider);
    
#pragma mark - MAXAnimationDelegate
    virtual void OnAnimationStart(MAXAnimationBase* animation);
    virtual void OnAnimationUpdate(MAXAnimationBase* animation);
    virtual void OnAnimationFinish(MAXAnimationBase* animation);
    
};

#endif /* defined(__Asteroids__GameShip__) */
