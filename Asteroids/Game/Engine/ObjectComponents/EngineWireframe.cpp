//
//  EngineWireframe.cpp
//  Asteroids
//
//  Created by Anton Katekov on 18.09.13.
//  Copyright (c) 2013 KatekovAnton. All rights reserved.
//

#include "EngineWireframe.h"

EngineWireframe::EngineWireframe(int verticesCount, Vector3 *vertices)
:_lineCount(verticesCount)
{
    int vs = sizeof(vertexStruct) * verticesCount;
    vertexStruct *verticesStructured = reinterpret_cast<vertexStruct*>(malloc(vs));
    memset(verticesStructured, 0, vs);
    for (int i = 0; i < verticesCount; i++) {
        verticesStructured[i].position[0] = vertices[i].x;
        verticesStructured[i].position[1] = vertices[i].y;
        verticesStructured[i].position[2] = vertices[i].z;
    }
    
    Init(verticesStructured, vs, NULL, 0);
}

void EngineWireframe::Render() const
{
    glDrawArrays(GL_LINES, 0, _lineCount);
}

