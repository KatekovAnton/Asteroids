//
//  GameObject.cpp
//  Asteroids
//
//  Created by Anton Katekov on 18.09.13.
//  Copyright (c) 2013 KatekovAnton. All rights reserved.
//

#include "GameObject.h"
#include "SimpleWireframeObject.h"
#include "AEngine.h"

GameObject::GameObject()
:_object(NULL), _isShowing(false)
{}

GameObject::~GameObject()
{
    delete _object;
}

void GameObject::Show()
{
    if (_isShowing) 
        return;
    
    engine->AddUnit(_object);
}

void GameObject::Hide()
{
    if (!_isShowing)
        return;
    
    engine->RemoveUnit(_object);
}

void GameObject::SetPosition(Vector2 position)
{
    _object->SetPosition(Vector3Make(position.x, position.y, 0));
}
