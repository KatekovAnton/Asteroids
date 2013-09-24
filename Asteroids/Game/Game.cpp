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
#include "Display.h"

Game *sharedInstance = NULL;

Game* Game::SharedGame()
{
    if (!sharedInstance) {
        sharedInstance = new Game();
    }
    return sharedInstance;
}

Game::Game()
:_gameController(NULL)
{}

void Game::Init()
{
    engine->Init();
    _gameController = new GameController();
    Display::currentDisplay()->SetDelegate(this);
}

#pragma mark - DisplayDelegate

void Game::MoveVectorChanged(float x, float y)
{
    if (_gameController)
        _gameController->SetMoveVectorChanged(x, -y);
}

void Game::RotationVectorChanged(float x, float y)
{
    if (_gameController)
        _gameController->SetRotationVectorChanged(x, y);
}
