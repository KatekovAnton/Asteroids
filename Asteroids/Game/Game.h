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
#include "DisplayDelegate.h"

class GameController;

class Game : public DisplayDelegate {
    
    GameController *_gameController;
    
public:
    
    void Init();
    
    Game();
    
    static Game* SharedGame();
    
#pragma mark - DisplayDelegate
    
    virtual void MoveVectorChanged(float x, float y);
    virtual void RotationVectorChanged(float x, float y);
    
};

#endif /* defined(__Asteroids__Game__) */
