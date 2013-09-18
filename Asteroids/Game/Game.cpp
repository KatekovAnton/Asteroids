//
//  Game.cpp
//  Asteroids
//
//  Created by Anton Katekov on 18.09.13.
//  Copyright (c) 2013 KatekovAnton. All rights reserved.
//

#include "Game.h"
#include "GameController.h"
#include "AEngine.h"

Game *sharedInstance = NULL;

Game* Game::SharedGame()
{
    if (!sharedInstance) {
        sharedInstance = new Game();
    }
    return sharedInstance;
}

void Game::Init()
{
    engine->Init();
    _gameController = new GameController();
}
