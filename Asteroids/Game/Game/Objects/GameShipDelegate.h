//
//  GameShipDelegate.h
//  Asteroids
//
//  Created by Anton Katekov on 28.09.13.
//  Copyright (c) 2013 KatekovAnton. All rights reserved.
//

#ifndef __Asteroids__GameShipDelegate__
#define __Asteroids__GameShipDelegate__

#include <iostream>

class GameShip;

class GameShipDelegate {
    
public:
    
    virtual void GameShipFireing(GameShip *sender) = 0;
    virtual void GameShipDidCollide(GameShip *sender) = 0;
    
};

#endif /* defined(__Asteroids__GameShipDelegate__) */
