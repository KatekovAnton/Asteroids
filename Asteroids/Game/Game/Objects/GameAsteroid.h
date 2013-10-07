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
#include "GameAsteroidDelegate.h"
#include "MAXAnimationBase.h"
#include "MAXAnimationDelegate.h"

class GameAsteroid : public GameObject, public ObjectControlledBehaviorModelDelegate, public MAXAnimationDelegate {
    
    Vector3 _moveVector;
    Vector3 _directionVector;
    MAXAnimationBase *_existTimer;
    
    bool _isLarge;
    float _random;
    float _rotationRandom;
    float _startTime;
    
public:
    bool GetIsLarge() const {return _isLarge;}
    GameAsteroidDelegate *_delegate;
    
    GameAsteroid(bool large);
    virtual ~GameAsteroid();

    void CalculateParameters(bool moveToCenter, Vector3 direction, float randomMuliplier);
    
#pragma mark - ObjectControlledBehaviorModelDelegate
    virtual Vector3 GetMoveVector(void *sender);
    virtual Vector3 GetDirectionVector(void *sender);
    virtual void OnObjectCollidedToObject(void *sender, void *collider);
    virtual void *GetOwner();
    
#pragma mark - MAXAnimationDelegate
    virtual void OnAnimationStart(MAXAnimationBase* animation);
    virtual void OnAnimationUpdate(MAXAnimationBase* animation);
    virtual void OnAnimationFinish(MAXAnimationBase* animation);
    
};

#endif /* defined(__Asteroids__GameAsteroid__) */
