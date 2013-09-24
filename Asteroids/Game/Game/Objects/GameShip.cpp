//
//  GameShip.cpp
//  Asteroids
//
//  Created by Anton Katekov on 18.09.13.
//  Copyright (c) 2013 KatekovAnton. All rights reserved.
//

#include "GameShip.h"
#include "SimpleWireframeObject.h"
#include "UnAnimRenderObject.h"
#include "EngineWireframe.h"
#include "ObjectControlledBehaviorModel.h"

using namespace std;

GameShip::GameShip()
{
    Vector3 vertices[8];
    vertices[0].x = 0; vertices[0].y = 10; vertices[0].z = 0;
    vertices[1].x = 10; vertices[1].y = -10; vertices[1].z = 0;
    
    
    vertices[2].x = 10; vertices[2].y = -10; vertices[2].z = 0;
    vertices[3].x = 0; vertices[3].y = 0; vertices[3].z = 0;
    
    vertices[4].x = 0; vertices[4].y = 0; vertices[4].z = 0;
    vertices[5].x = -10; vertices[5].y = -10; vertices[5].z = 0;
    
    vertices[6].x = -10; vertices[6].y = -10; vertices[6].z = 0;
    vertices[7].x = 0; vertices[7].y = 10; vertices[7].z = 0;
    
    shared_ptr<EngineWireframe> wf(new EngineWireframe(8, vertices));
    UnAnimRenderObject *_renderObject = new UnAnimRenderObject(wf);
    
    ObjectControlledBehaviorModel *_behaviourModel = new ObjectControlledBehaviorModel(this);
  
    SimpleWireframeObject *object = new SimpleWireframeObject(_renderObject, _behaviourModel, Vector4Make(1, 1, 1, 1));
    this->_object = object;
    
    _moveVector = Vector3Make(0, 0, 0);
    _directionVector = Vector3Make(1, 0, 0);
    
}

GameShip::~GameShip()
{
    
}

void GameShip::SetPosition(Vector2 position)
{
    this->_object->SetPosition(Vector3Make(position.x, position.y, 0));
}

void GameShip::MoveShipInDirection(float x, float y)
{
    _moveVector.x = x;
    _moveVector.y = y;
}

void GameShip::SetShipDirection(float x, float y)
{
    _directionVector.x = x;
    _directionVector.y = y;
    _directionVector.z = 0;
    
    _directionVector = Vector3Normalize(_directionVector);
}

#pragma mark - ObjectControlledBehaviorModelDelegate

Vector3 GameShip::GetMoveVector(void *sender)
{
    return _moveVector;
}

Vector3 GameShip::GetDirectionVector(void *sender)
{
    return _directionVector;
}

void GameShip::OnObjectCollidedToObject(void *sender, void *collider)
{}
