//
//  EngineWireframe.h
//  Asteroids
//
//  Created by Anton Katekov on 18.09.13.
//  Copyright (c) 2013 KatekovAnton. All rights reserved.
//

#ifndef __Asteroids__EngineWireframe__
#define __Asteroids__EngineWireframe__

#include <iostream>
#include "Math.h"
#include "EngineMesh.h"

class EngineWireframe : public EngineMesh {
    
    int _lineCount;
    
public:
    
    EngineWireframe(int verticesCount, Vector3 *vertices);
    
    virtual void Render() const;
    
};

#endif /* defined(__Asteroids__EngineWireframe__) */
