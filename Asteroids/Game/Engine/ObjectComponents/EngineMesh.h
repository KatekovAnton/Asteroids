//
//  EngineMesh.h
//  Asteroids
//
//  Created by Katekov Anton on 11/3/12.
//
//

#ifndef __Asteroids__EngineMesh__
#define __Asteroids__EngineMesh__

#include <iostream>
#include "Math.h"

using namespace std;

class EngineMesh {
    
    bool _disposed;
    
    GLuint          _indexBuffer;
    GLuint          _vertexBuffer;
    
    long            _vSize;
    long            _iSize;
    long            _primitivesCount;
    
public:
    
    EngineMesh();
    EngineMesh(void * vertices, long vSize, void *indices, long iSize);

    
    ~EngineMesh();

    void Bind() const;
    void Render() const;
    void Unbind() const;
    
    
    virtual void Dispose();
    virtual void LoadFromBuffer(char *buffer, unsigned int bufferLength);
    
    
    static shared_ptr<EngineMesh> CreateCube(void);
    static shared_ptr<EngineMesh> CreateFullscreenQuad(void);
    static shared_ptr<EngineMesh> CreateUnitQuad(void);
    
    static shared_ptr<EngineMesh> CreateScaledQuad(float sidex, float sidey);
    
};

#endif /* defined(__Asteroids__EngineMesh__) */

