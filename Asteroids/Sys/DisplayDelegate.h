//
//  DisplayDelegate.h
// Asteroids
//
//  Created by  Developer on 25.12.12.
//  Copyright (c) 2012 AntonKatekov. All rights reserved.
//

#ifndef __MAX__DisplayDelegate__
#define __MAX__DisplayDelegate__

class DisplayDelegate {
    
public:
    virtual void MoveVectorChanged(float x, float y) = 0;
    virtual void RotationVectorChanged(float x, float y) = 0;
    
};

#endif /* defined(__MAX__DisplayDelegate__) */
