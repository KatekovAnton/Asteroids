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
#include "GameShipBullet.h"

GameController::GameController()
:_bullets(new USimpleContainer<GameShipBullet*>(10))
{
    _ship = new GameShip();
    _ship->SetPosition(Vector2Make(Display::currentDisplay()->GetDisplayWidth()/2, Display::currentDisplay()->GetDisplayHeight()/2));
    _ship->Show();
    _ship->_delegate = this;
}

GameController::~GameController()
{
    _ship->Hide();
    for (int i = 0; i < _bullets->GetCount(); i++) {
        GameShipBullet* bullet = _bullets->objectAtIndex(i);
        bullet->Hide();
        delete bullet;
    }
    delete _bullets;
    delete _ship;
}

void GameController::SetMoveVectorChanged(float x, float y)
{
    _ship->MoveShipInDirection(x, y);
}

void GameController::SetRotationVectorChanged(float x, float y)
{
    _ship->SetShipDirection(x, y);
}

#pragma mark - GameShipDelegate

void GameController::GameShipFireing(GameShip *sender)
{
    Vector3 v = sender->GetDirectionVector(NULL);
    GameShipBullet *bullet = new GameShipBullet(Vector2Make(v.x * 5, v.y * 5));
    
    v = _ship->GetBulletStartPosition();
    bullet->SetPosition(Vector2Make(v.x, v.y));
    bullet->Show();
    bullet->_delegate = this;
    _bullets->addObject(bullet);
    
}

void GameController::GameShipDidCollide(GameShip *sender)
{}

#pragma mark - GameShipBulletDelegate

void GameController::GameShipBulletDidFinishExistance(GameShipBullet *sender)
{
    _bullets->removeObject(sender);
    sender->Hide();
    delete sender;
}
