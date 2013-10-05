//
//  GameController.h
//  Asteroids
//
//  Created by Anton Katekov on 18.09.13.
//  Copyright (c) 2013 KatekovAnton. All rights reserved.
//

#ifndef __Asteroids__GameController__
#define __Asteroids__GameController__

#include <iostream>
#include "GameShipDelegate.h"
#include "GameShipBulletDelegate.h"
#include "miniPrefix.h"
#include "MAXAnimationDelegate.h"

class GameShip;
class GameShipBullet;

class GameController : public GameShipDelegate, public GameShipBulletDelegate, public MAXAnimationDelegate {
    
    GameShip *_ship;
    USimpleContainer<GameShipBullet*> *_bullets;
    
    MAXAnimationBase *_createAsteroidTimer;
    
public:
    
    GameController();
    ~GameController();
    
    void SetMoveVectorChanged(float x, float y);
    void SetRotationVectorChanged(float x, float y);
    
#pragma mark - MAXAnimationDelegate
    virtual void OnAnimationStart(MAXAnimationBase* animation);
    virtual void OnAnimationUpdate(MAXAnimationBase* animation);
    virtual void OnAnimationFinish(MAXAnimationBase* animation);
    
#pragma mark - GameShipDelegate
    virtual void GameShipFireing(GameShip *sender);
    virtual void GameShipDidCollide(GameShip *sender);
    
#pragma mark - GameShipBulletDelegate
    virtual void GameShipBulletDidFinishExistance(GameShipBullet *sender);
    
};

#endif /* defined(__Asteroids__GameController__) */
