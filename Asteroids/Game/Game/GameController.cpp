//
//  GameController.cpp
//  Asteroids
//
//  Created by Anton Katekov on 18.09.13.
//  Copyright (c) 2013 KatekovAnton. All rights reserved.
//

#include "GameController.h"
#include "GameShip.h"

GameController::GameController()
{
    _ship = new GameShip();
    _ship->Show();
}

GameController::~GameController()
{
    _ship->Hide();
    delete _ship;
}

void GameController::SetMoveVectorChanged(float x, float y)
{}

void GameController::SetRotationVectorChanged(float x, float y)
{}
