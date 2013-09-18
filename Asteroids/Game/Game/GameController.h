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

class GameShip;

class GameController {
    
    GameShip *_ship;
    
public:
    
    GameController();
    ~GameController();

};

#endif /* defined(__Asteroids__GameController__) */
