//
//  GameController.cpp
//  Asteroids
//
//  Created by Anton Katekov on 18.09.13.
//  Copyright (c) 2013 KatekovAnton. All rights reserved.
//

#include "GameController.h"
#include "GameShip.h"
#include "Display.h"

GameController::GameController()
{
    _ship = new GameShip();
    _ship->SetPosition(Vector2Make(Display::currentDisplay()->GetDisplayWidth()/2, Display::currentDisplay()->GetDisplayHeight()/2));
    _ship->Show();
}

GameController::~GameController()
{
    _ship->Hide();
    delete _ship;
}

void GameController::SetMoveVectorChanged(float x, float y)
{
    _ship->MoveShipInDirection(x, y);
}

void GameController::SetRotationVectorChanged(float x, float y)
{
    if (x ==0 && y == 0)
        return;
    _ship->SetShipDirection(x, y);
}
