//
//  ACamera.h
//  MAX
//
//  Created by  Developer on 25.12.12.
//  Copyright (c) 2012 AntonKatekov. All rights reserved.
//

#ifndef __MAX__ACamera__
#define __MAX__ACamera__

#include <iostream>
#include "Math.h"

class ACamera {
    void RecalculateViewMatrix();
    //how many cells can be displayed on scrren by width
    GLfloat _scalex;
    //how many cells can be displayed on scrren by height
    GLfloat _scaley;
    Rect _bounds;
    float maxScale;
public:
    //allways 1
    GLfloat _displayScale;
    bool minZoom;
    bool changed;
    //100
    GLfloat             maxDepth;
    //0.1
    GLfloat             minDepth;
    GLfloat             _far;
    GLfloat             _aspectRatio;
    Size             screenSize;
    
    Matrix4          projection;
    Matrix4          view;
    
    int mapH;
    int mapW;
    
    //current game camera scale
    GLfloat             scale;
    //current game camera position
    Vector3          position;
    
    ACamera(Rect bounds, float displayScale);
    
    //set map bounds
    void SetMapSize(int w, int h);
    
    void SetPosition(const Vector3 &position);
    //scale camera, on touches
    void Scale(float deltaScale);
    //move camera
    void Move(float deltax, float deltay);
    //update camra, recalculates values
    void Update();

};

#endif /* defined(__MAX__ACamera__) */
