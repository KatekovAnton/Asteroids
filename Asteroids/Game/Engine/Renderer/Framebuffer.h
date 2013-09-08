//
//  Framebuffer.h
//  MAX
//
//  Created by Anton Katekov on 15.02.13.
//  Copyright (c) 2013 AntonKatekov. All rights reserved.
//

#ifndef __MAX__Framebuffer__
#define __MAX__Framebuffer__

#include <iostream>
#include "miniPrefix.h"

struct Viewport {
    float x;
    float y;
    float w;
    float h;
};

class Framebuffer {
    GLuint _fbo;
    GLuint _colorTexture; 
    GLint _lastfbo;
    GLfloat	oldClearColor_[4];
    
    void initFB(Vector2 sz);
    
    float _w, _h;
    Viewport _viewport;

public:
    GLuint GetColorTexture() const { return _colorTexture; };

    Framebuffer(Vector2 size);
    ~Framebuffer();
    
    void bind();
    void unbind();
};

#endif /* defined(__MAX__Framebuffer__) */
