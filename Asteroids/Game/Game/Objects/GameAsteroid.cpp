//
//  GameAsteroid.cpp
//  Asteroids
//
//  Created by Anton Katekov on 18.09.13.
//  Copyright (c) 2013 KatekovAnton. All rights reserved.
//

#include "GameAsteroid.h"
#include "SimpleWireframeObject.h"
#include "UnAnimRenderObject.h"
#include "EngineWireframe.h"
#include "ObjectControlledBehaviorModel.h"
#include "MAXAnimationPrefix.h"
#include "CollisionObject.h"
#include "MyRandom.h"
#include "AEngine.h"

GameAsteroid::GameAsteroid(bool large)
:_delegate(NULL), _isLarge(large)
{
    _random = nextFloatMinMax(0, M_2_PI);
    _rotationRandom = nextFloatMinMax(-1, 1);
    shared_ptr<EngineWireframe> wf = nullptr;
    CollisionObject *collisionObject = NULL;
    
    Vector3 vertices[10];
    int count = 10;
    if (_isLarge)
    {
        vertices[0].x = -10; vertices[0].y = 10; vertices[0].z = 0;
        vertices[1].x = 12; vertices[1].y = 13; vertices[1].z = 0;
        
        vertices[2].x = 12; vertices[2].y = 13; vertices[2].z = 0;
        vertices[3].x = 10; vertices[3].y = -10; vertices[3].z = 0;
        
        vertices[4].x = 10; vertices[4].y = -10; vertices[4].z = 0;
        vertices[5].x = -8; vertices[5].y = -12; vertices[5].z = 0;
        
        vertices[6].x = -8; vertices[6].y = -12; vertices[6].z = 0;
        vertices[7].x = -15; vertices[7].y = 0; vertices[7].z = 0;
        
        vertices[8].x = -15; vertices[8].y = 0; vertices[8].z = 0;
        vertices[9].x = -10; vertices[9].y = 10; vertices[9].z = 0;
    }
    else
    {
        count = 6;
        vertices[0].x = 5; vertices[0].y = 10; vertices[0].z = 0;
        vertices[1].x = -6; vertices[1].y = 7; vertices[1].z = 0;
        
        vertices[2].x = -6; vertices[2].y = 7; vertices[2].z = 0;
        vertices[3].x = 10; vertices[3].y = -10; vertices[3].z = 0;
        
        vertices[4].x = 10; vertices[4].y = -10; vertices[4].z = 0;
        vertices[5].x = 5; vertices[5].y = 10; vertices[5].z = 0;
    }
    wf = shared_ptr<EngineWireframe>(new EngineWireframe(count, vertices));
    Vector4 *points = new Vector4[count];
    for (int i = 0; i < count; i++) {
        points[i].x = vertices[i].x;
        points[i].y = vertices[i].y;
        points[i].z = vertices[i].z;
        points[i].w = 1;
    }
    collisionObject = new CollisionObject(points, count);
    collisionObject->_owner_w = this;
    
    
    UnAnimRenderObject *_renderObject = new UnAnimRenderObject(wf);
    ObjectControlledBehaviorModel *_behaviourModel = new ObjectControlledBehaviorModel(collisionObject, this, true);
    
    SimpleWireframeObject *object = new SimpleWireframeObject(_renderObject, _behaviourModel, Vector4Make(1, 1, 1, 1));
    this->_object = object;
    
    _directionVector = Vector3Make(1, 0, 0);
    
    _startTime = engine->FullTime();
    
    
    _existTimer = new MAXAnimationWait(5);
    _existTimer->_delegate = this;
    MAXAnimationManager::SharedAnimationManager()->AddAnimation(_existTimer);
}

GameAsteroid::~GameAsteroid()
{}

void GameAsteroid::CalculateParameters(bool moveToCenter, Vector3 direction, float randomMuliplier)
{
    Vector2 toCenter = Vector2Make(0, 0);
    if (moveToCenter) {
        Vector2 center = _delegate->FieldCenter();
        Vector2 position = GetPosition();
        toCenter = Vector2Subtract(center, position);
        toCenter = Vector2Normalize(toCenter);
    }
    Vector2 random = Vector2Make(cosf(_random), sinf(_random));
    
    
    _moveVector = Vector3Make(toCenter.x * 2.0 + random.x *randomMuliplier + direction.x  , toCenter.y * 2.0 + random.y * randomMuliplier + direction.y, 0);
    
}

#pragma mark - ObjectControlledBehaviorModelDelegate

Vector3 GameAsteroid::GetMoveVector(void *sender)
{
    return _moveVector;
}

Vector3 GameAsteroid::GetDirectionVector(void *sender)
{
    float elapsed = engine->FullTime() - _startTime;
    float rotation = elapsed * _rotationRandom;
    return Vector3Make(cosf(rotation), sinf(rotation), 0);
}

void GameAsteroid::OnObjectCollidedToObject(void *sender, void *collider)
{
    //sende == this;
    //collider is bullet
    
    _delegate->GameAsteroidDidCollideWithBullet(this);
    
}

void *GameAsteroid::GetOwner()
{
    return this;
}

#pragma mark - MAXAnimationDelegate

void GameAsteroid::OnAnimationStart(MAXAnimationBase* animation)
{}

void GameAsteroid::OnAnimationUpdate(MAXAnimationBase* animation)
{}

void GameAsteroid::OnAnimationFinish(MAXAnimationBase* animation)
{
    if (_delegate && animation == _existTimer)
    {
        _existTimer = NULL;
        _delegate->GameAsteroidDidFinishExistance(this);
    }
}
