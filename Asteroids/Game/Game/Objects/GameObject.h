//
//  GameObject.h
//  Asteroids
//
//  Created by Anton Katekov on 18.09.13.
//  Copyright (c) 2013 KatekovAnton. All rights reserved.
//

#ifndef __Asteroids__GameObject__
#define __Asteroids__GameObject__

#include <iostream>
#include "Math.h"

class SimpleWireframeObject;

class GameObject {
    
protected:
    
    SimpleWireframeObject *_object;
    bool _isShowing;
    
public:
    
    GameObject();
    virtual ~GameObject();
    
    void Show();
    void Hide();
    
    Vector2 GetPosition();
    virtual void SetPosition(Vector2 position);
    
};

#endif /* defined(__Asteroids__GameObject__) */
