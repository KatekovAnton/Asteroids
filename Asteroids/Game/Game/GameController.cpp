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
#include "MAXAnimationPrefix.h"
#include "GameAsteroid.h"

GameController::GameController()
:_bullets(new USimpleContainer<GameShipBullet*>(10)), _createAsteroidTimer(NULL), _asteroids(new USimpleContainer<GameAsteroid*>(10))
{
    _ship = new GameShip();
    _ship->SetPosition(Vector2Make(Display::currentDisplay()->GetDisplayWidth()/2, Display::currentDisplay()->GetDisplayHeight()/2));
    _ship->Show();
    _ship->_delegate = this;
    
    GameAsteroid *asteroid = new GameAsteroid(true);
    asteroid->SetPosition(Vector2Make(Display::currentDisplay()->GetDisplayWidth()/2 - 200, Display::currentDisplay()->GetDisplayHeight()/2));
    asteroid->Show();
    asteroid->_delegate = this;
    _asteroids->addObject(asteroid);
    
    
    MAXAnimationWait *timerCreateAsteroid = new MAXAnimationWait(1);
    timerCreateAsteroid->_delegate = this;
    MAXAnimationManager::SharedAnimationManager()->AddAnimation(timerCreateAsteroid);
    _createAsteroidTimer = timerCreateAsteroid;
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
    
    for (int i = 0; i < _asteroids->GetCount(); i++) {
        GameAsteroid* asteroid = _asteroids->objectAtIndex(i);
        asteroid->Hide();
        delete asteroid;
    }
    delete _asteroids;
    
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

#pragma mark - MAXAnimationDelegate

void GameController::OnAnimationStart(MAXAnimationBase* animation)
{}

void GameController::OnAnimationUpdate(MAXAnimationBase* animation)
{}

void GameController::OnAnimationFinish(MAXAnimationBase* animation)
{
    if (animation == _createAsteroidTimer) {
        _createAsteroidTimer = NULL;
        
    }
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

#pragma mark - GameAsteroidDelegate

void GameController::GameAsteroidDidFinishExistance(GameAsteroid *sender)
{
    
}

