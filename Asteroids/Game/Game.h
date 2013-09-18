//
//  Game.h
//  Asteroids
//
//  Created by Anton Katekov on 18.09.13.
//  Copyright (c) 2013 KatekovAnton. All rights reserved.
//

#ifndef __Asteroids__Game__
#define __Asteroids__Game__

#include <iostream>

class GameController;

class Game {
    
    GameController *_gameController;
    
public:
    
    void Init();
    
    static Game* SharedGame();
    
};

#endif /* defined(__Asteroids__Game__) */
