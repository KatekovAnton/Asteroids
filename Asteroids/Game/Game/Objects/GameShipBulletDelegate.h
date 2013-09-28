//
//  GameShipBulletDelegate.h
//  Asteroids
//
//  Created by Anton Katekov on 28.09.13.
//  Copyright (c) 2013 KatekovAnton. All rights reserved.
//

#ifndef Asteroids_GameShipBulletDelegate_h
#define Asteroids_GameShipBulletDelegate_h

class GameShipBullet;

class GameShipBulletDelegate {
    
public:
    
    virtual void GameShipBulletDidFinishExistance(GameShipBullet *sender) = 0;
    
};

#endif
