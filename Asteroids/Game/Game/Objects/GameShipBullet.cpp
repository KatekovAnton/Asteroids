//
//  GameShipBullet.cpp
//  Asteroids
//
//  Created by Anton Katekov on 18.09.13.
//  Copyright (c) 2013 KatekovAnton. All rights reserved.
//

#include "GameShipBullet.h"
#include "SimpleWireframeObject.h"
#include "UnAnimRenderObject.h"
#include "EngineWireframe.h"
#include "ObjectControlledBehaviorModel.h"
#include "MAXAnimationPrefix.h"

GameShipBullet::GameShipBullet(Vector2 direction)
:_direction(Vector3Make(direction.x, direction.y, 0)), _movement(Vector3Make(direction.x, -direction.y, 0)), _delegate(NULL)
{
    Vector3 vertices[2];
    vertices[0].x = 0; vertices[0].y = 0; vertices[0].z = 0;
    vertices[1].x = 0; vertices[1].y = 10; vertices[1].z = 0;
    
    

    
    shared_ptr<EngineWireframe> wf(new EngineWireframe(2, vertices));
    UnAnimRenderObject *_renderObject = new UnAnimRenderObject(wf);
    
    ObjectControlledBehaviorModel *_behaviourModel = new ObjectControlledBehaviorModel(this, false);
    
    SimpleWireframeObject *object = new SimpleWireframeObject(_renderObject, _behaviourModel, Vector4Make(1, 1, 1, 1));
    this->_object = object;
    
    _existTimer = new MAXAnimationWait(10);
    _existTimer->_delegate = this;
    MAXAnimationManager::SharedAnimationManager()->AddAnimatedObject(_existTimer);
}

GameShipBullet::~GameShipBullet()
{
    if (_existTimer) {
        _existTimer->_delegate = NULL;
    }
}

#pragma mark - ObjectControlledBehaviorModelDelegate

Vector3 GameShipBullet::GetMoveVector(void *sender)
{
    return Vector3MultiplyScalar(_movement, 30);// _movement;
}

Vector3 GameShipBullet::GetDirectionVector(void *sender)
{
    return _direction;
}

void GameShipBullet::OnObjectCollidedToObject(void *sender, void *collider)
{}

#pragma mark - MAXAnimationDelegate

void GameShipBullet::OnAnimationStart(MAXAnimationBase* animation)
{}

void GameShipBullet::OnAnimationUpdate(MAXAnimationBase* animation)
{}

void GameShipBullet::OnAnimationFinish(MAXAnimationBase* animation)
{
    if (_delegate && animation == _existTimer)
    {
        _existTimer = NULL;
        _delegate->GameShipBulletDidFinishExistance(this);
    }
}
