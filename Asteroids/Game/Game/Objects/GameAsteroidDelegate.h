//
//  GameAsteroidDelegate.h
//  Asteroids
//
//  Created by Anton Katekov on 06.10.13.
//  Copyright (c) 2013 KatekovAnton. All rights reserved.
//

#ifndef Asteroids_GameAsteroidDelegate_h
#define Asteroids_GameAsteroidDelegate_h

#include "miniPrefix.h"

class GameAsteroid;

class GameAsteroidDelegate {
    
public:
    
    virtual void GameAsteroidDidFinishExistance(GameAsteroid *sender) = 0;
    virtual void GameAsteroidDidCollideWithBullet(GameAsteroid *sender) = 0;
    virtual Vector2 FieldCenter() = 0;
    
};

#endif
