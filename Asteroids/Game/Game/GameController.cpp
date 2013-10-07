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
#include "MyRandom.h"
#include "CollisionEngine.h"

GameController::GameController()
:_bullets(new USimpleContainer<GameShipBullet*>(10)), _createAsteroidTimer(NULL), _asteroids(new USimpleContainer<GameAsteroid*>(10))
{
    _ship = new GameShip();
    _ship->SetPosition(Vector2Make(Display::currentDisplay()->GetDisplayWidth()/2, Display::currentDisplay()->GetDisplayHeight()/2));
    _ship->Show();
    _ship->_delegate = this;
    
    GameAsteroid *asteroid = new GameAsteroid(true);
    asteroid->SetPosition(Vector2Make(210, 200));
    asteroid->Show();
    asteroid->_delegate = this;
    asteroid->CalculateParameters(true, Vector3Make(0, 0, 0), 1);
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

GameAsteroid *GameController::CreateRandomAsteroid()
{
    Vector2 center = FieldCenter();
    float r = Vector2Length(center);
    float random = nextFloatMinMax(-M_PI, M_PI);
    Vector2 pos = Vector2Make(cosf(random), sinf(random));
    pos = Vector2Add(center, Vector2MultiplyScalar(pos, r/2));
    GameAsteroid *res = CreateAsteroid(true, pos);
    res->SetPosition(pos);
    return res;
}

GameAsteroid *GameController::CreateAsteroid(bool large, Vector2 pos)
{
    GameAsteroid *asteroidNew = new GameAsteroid(large);
    asteroidNew->SetPosition(Vector2Add(pos, Vector2Make(10, 10)));
    asteroidNew->_delegate = this;
    return asteroidNew;
}

void GameController::UpdateCollisions()
{
    CollisionEngine::SharedCollisionEngine()->UpdateCollisions();
    
    for (int i = 0; i < _collidedAsteroids.GetCount(); i++) {
        GameAsteroid *asteroid = _collidedAsteroids.objectAtIndex(i);
        Vector2 pos = asteroid->GetPosition();
        bool large = asteroid->GetIsLarge();
        Vector3 direction = asteroid->GetMoveVector(NULL);
        GameAsteroidDidFinishExistance(asteroid);
        
        if (large)
        {
            {
                GameAsteroid *asteroidNew = CreateAsteroid(false, Vector2Add(pos, Vector2Make(10, 10)));
                _asteroids->addObject(asteroidNew);
                asteroidNew->CalculateParameters(false, direction, 1);
                asteroidNew->Show();
            }
            {
                GameAsteroid *asteroidNew = CreateAsteroid(false, Vector2Add(pos, Vector2Make(-10, 10)));
                _asteroids->addObject(asteroidNew);
                asteroidNew->CalculateParameters(false, direction, 1);
                asteroidNew->Show();
            }
            {
                GameAsteroid *asteroidNew = CreateAsteroid(false, Vector2Add(pos, Vector2Make(10, -10)));
                _asteroids->addObject(asteroidNew);
                asteroidNew->CalculateParameters(false, direction, 1);
                asteroidNew->Show();
            }
        }
        
    }
    
    _collidedAsteroids.clear();
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
        GameAsteroid *asteroidNew = CreateRandomAsteroid();
        _asteroids->addObject(asteroidNew);
        asteroidNew->CalculateParameters(true, Vector3Make(0, 0, 0), 1);
        asteroidNew->Show();
        
        MAXAnimationWait *timerCreateAsteroid = new MAXAnimationWait(1);
        timerCreateAsteroid->_delegate = this;
        MAXAnimationManager::SharedAnimationManager()->AddAnimation(timerCreateAsteroid);
        _createAsteroidTimer = timerCreateAsteroid;
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
{
    
}

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
    _asteroids->removeObject(sender);
    sender->Hide();
    delete sender;
}

void GameController::GameAsteroidDidCollideWithBullet(GameAsteroid *sender)
{
    if (_collidedAsteroids.indexOf(sender) == -1)
        _collidedAsteroids.addObject(sender);
    else
    {
        int a = 0;
        a++;
        }
}

Vector2 GameController::FieldCenter()
{
    return Vector2Make(Display::currentDisplay()->GetDisplayWidth()/2, Display::currentDisplay()->GetDisplayHeight()/2);
}
