//
//  GameAsteroidDelegate.h
//  Asteroids
//
//  Created by Anton Katekov on 06.10.13.
//  Copyright (c) 2013 KatekovAnton. All rights reserved.
//

#ifndef Asteroids_GameAsteroidDelegate_h
#define Asteroids_GameAsteroidDelegate_h

class GameAsteroid;

class GameAsteroidDelegate {
    
public:
    
    virtual void GameAsteroidDidFinishExistance(GameAsteroid *sender) = 0;
    
};

#endif
