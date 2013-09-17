//
//  UnAnimRenderObject.h
//  Asteroids
//
//  Created by Katekov Anton on 11/3/12.
//
//

#ifndef __Asteroids__UnAnimRenderObject__
#define __Asteroids__UnAnimRenderObject__

#include <iostream>
#include "RenderObject.h"

class EngineMesh;

class UnAnimRenderObject : public RenderObject {
    
    shared_ptr<EngineMesh>          _mesh;
    
public:
    
    UnAnimRenderObject(shared_ptr<EngineMesh> mesh);
    ~UnAnimRenderObject();
    
    virtual void Render();
};

#endif /* defined(__Asteroids__UnAnimRenderObject__) */
