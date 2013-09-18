//
//  RenderObject.h
//  Asteroids
//
//  Created by Katekov Anton on 11/1/12.
//
//

#ifndef __Asteroids__RenderObject__
#define __Asteroids__RenderObject__

#include <iostream>

class RenderObject {
public:

    
    RenderObject();
    virtual ~RenderObject();
    
    virtual void Render() = 0;
};



#endif /* defined(__Asteroids__RenderObject__) */
