//
//  ADrawPrimitives.h
//  Asteroids
//
//  Created by Anton Katekov on 11.02.13.
//  Copyright (c) 2013 AntonKatekov. All rights reserved.
//

#ifndef __MAX__ADrawPrimitives__
#define __MAX__ADrawPrimitives__

#include <iostream>
#include "miniPrefix.h"

class Shader;

class ADrawPrimitives {
    
    Shader* _shader;
    Matrix4 _projectionMatrix;
    
    Vector4 vertices[2];
    
public:
    
    Vector4 _color;
    
    
    
    ADrawPrimitives();
    ~ADrawPrimitives();
    
    static ADrawPrimitives* SharedDrawPrimitives();
    
    void Begin();
    void BindColor(const Vector4& color);
    void DrawLine(const Vector2& from, const Vector2& to);
    
    void DrawCircle( const Vector2& center, float radius, float angle, unsigned int segments, bool drawLineToCenter, float scaleX, float scaleY);
    void DrawCircle( const Vector2& center, float radius, float angle, unsigned int segments, bool drawLineToCenter);
};

#endif /* defined(__MAX__ADrawPrimitives__) */
