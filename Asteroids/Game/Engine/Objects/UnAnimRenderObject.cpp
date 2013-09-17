//
//  UnAnimRenderObject.cpp
//  Asteroids
//
//  Created by Katekov Anton on 11/3/12.
//
//

#include "UnAnimRenderObject.h"
#include "EngineMesh.h"
#include "AEngine.h"

UnAnimRenderObject::UnAnimRenderObject(shared_ptr<EngineMesh> mesh):RenderObject() {
    _mesh = mesh;
}

void UnAnimRenderObject::Render() {
    _mesh->Bind();
    _mesh->Render();
    _mesh->Unbind();
}

UnAnimRenderObject::~UnAnimRenderObject() {

    
}