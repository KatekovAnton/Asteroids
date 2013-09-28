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

class GameShip;
class GameShipBullet;

class GameController : public GameShipDelegate, public GameShipBulletDelegate {
    
    GameShip *_ship;
    USimpleContainer<GameShipBullet*> *_bullets;
    
public:
    
    GameController();
    ~GameController();
    
    void SetMoveVectorChanged(float x, float y);
    void SetRotationVectorChanged(float x, float y);
    
#pragma mark - GameShipDelegate
    virtual void GameShipFireing(GameShip *sender);
    virtual void GameShipDidCollide(GameShip *sender);
    
#pragma mark - GameShipBulletDelegate
    virtual void GameShipBulletDidFinishExistance(GameShipBullet *sender);
    
};

#endif /* defined(__Asteroids__GameController__) */
