//
//  FileManger.h
//  Asteroids
//
//  Created by Katekov Anton on 11/3/12.
//
//

#ifndef __Asteroids__FileManger__
#define __Asteroids__FileManger__

#include <iostream>
#include "GlobalConstants.h"

using namespace std;

class FileManager {
    
protected:

    
public:
    
    static FileManager *CreateManager();
    
    virtual string  GetFilePath(string filename);
    virtual string * GetContent(string filename);
    virtual GLubyte * CreateBitmapData(string filename, GLfloat *width, GLfloat *heigth);
    virtual GLubyte * CreateBitmapData(char* data, size_t size, GLfloat *width, GLfloat *heigth);
};

#endif /* defined(__Asteroids__FileManger__) */
