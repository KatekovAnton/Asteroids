//
//  ADrawPrimitives.cpp
//  Asteroids
//
//  Created by Anton Katekov on 11.02.13.
//  Copyright (c) 2013 AntonKatekov. All rights reserved.
//

#include "ADrawPrimitives.h"
#include "miniPrefix.h"
#include "Shader.h"
#include "Display.h"

ADrawPrimitives* _sharedADrawPrimitives = NULL;

ADrawPrimitives::ADrawPrimitives()
{
    _shader = new Shader("ShaderLine.vsh", "ShaderLine.fsh");//UNIFORM_VECTOR1 for color UNIFORM_PROJECTION_MATRIX for projection
    
    float _displayScale = Display::currentDisplay()->GetDisplayScale();
    MRect bounds = RectMake(0, 0, Display::currentDisplay()->GetDisplayWidth()/_displayScale, Display::currentDisplay()->GetDisplayHeight()/_displayScale);
    float _scalex = 1.0/bounds.size.width;
    float _scaley = 1.0/bounds.size.height;
    
    
    Matrix4 scalematr = Matrix4MakeScale(_scalex, _scaley, 1);
    scalematr.m30 = -1;
    scalematr.m31 = -1;
    _projectionMatrix = scalematr;
    
    vertices[0].z = 1;
    vertices[0].w = 1;
    vertices[1].z = 1;
    vertices[1].w = 1;
    
    _color = Vector4Make(1, 1, 1, 1);
}

ADrawPrimitives::~ADrawPrimitives()
{
    delete _shader;
}

ADrawPrimitives* ADrawPrimitives::SharedDrawPrimitives()
{
    if (!_sharedADrawPrimitives)
        _sharedADrawPrimitives = new ADrawPrimitives();
    return _sharedADrawPrimitives;
}

void ADrawPrimitives::Begin()
{
    glUseProgram(_shader->GetProgram());
    _shader->SetMatrixValue(UNIFORM_PROJECTION_MATRIX, _projectionMatrix.m);
    _shader->SetVector4Value(UNIFORM_VECTOR1, (float*)&_color);
    
    glEnableVertexAttribArray(ATTRIB_VERTEX);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)vertices);
}

void ADrawPrimitives::BindColor(const Vector4& color)
{
    _color = color;
    _shader->SetVector4Value(UNIFORM_VECTOR1, (float*)&_color);
}

void ADrawPrimitives::DrawLine(const Vector2& from, const Vector2& to)
{
    vertices[0].x = from.x;
    vertices[0].y = from.y;
    vertices[1].x = to.x;
    vertices[1].y = to.y;
    
    glDrawArrays(GL_LINES, 0, 2);
}

void ADrawPrimitives::DrawCircle( const Vector2& center, float radius, float angle, unsigned int segments, bool drawLineToCenter, float scaleX, float scaleY)
{
    int additionalSegment = 1;
    if (drawLineToCenter)
        additionalSegment++;
    
    const float coef = 2.0f * (float)M_PI/segments;
    
    GLfloat *vertices = (GLfloat*)calloc( sizeof(GLfloat)*2*(segments+2), 1);
    if( ! vertices )
        return;
    
    for(unsigned int i = 0;i <= segments; i++) {
        float rads = i*coef;
        GLfloat j = radius * cosf(rads + angle) * scaleX + center.x;
        GLfloat k = radius * sinf(rads + angle) * scaleY + center.y;
        
        vertices[i*2] = j;
        vertices[i*2+1] = k;
    }
    vertices[(segments+1)*2] = center.x;
    vertices[(segments+1)*2+1] = center.y;
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)vertices);
    glDrawArrays(GL_LINE_STRIP, 0, (GLsizei) segments+additionalSegment);
    
    free( vertices );
    
}

void ADrawPrimitives::DrawCircle( const Vector2& center, float radius, float angle, unsigned int segments, bool drawLineToCenter)
{
    DrawCircle(center, radius, angle, segments, drawLineToCenter, 1.0f, 1.0f);
}


