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
    Hide();
    delete _object;
}

void GameObject::Show()
{
    if (_isShowing) 
        return;
    
    _isShowing = true;
    engine->AddUnit(_object);
}

void GameObject::Hide()
{
    if (!_isShowing)
        return;
    
    _isShowing = false;
    engine->RemoveUnit(_object);
}

void GameObject::SetPosition(Vector2 position)
{
    _object->SetPosition(Vector3Make(position.x, position.y, 0));
}
