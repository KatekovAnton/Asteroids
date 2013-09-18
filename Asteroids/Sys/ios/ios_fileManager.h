//
//  ios_fileManager.h
//  Asterids
//
//  Created by Katekov Anton on 11/3/12.
//
//

#ifndef __Asterids__ios_fileManager__
#define __Asterids__ios_fileManager__

#include <iostream>

#include "FileManger.h"

class iosFileManager : public FileManager {
    
    
    
public:
    virtual string  GetFilePath(string filename);
    virtual string* GetContent(string filename);
    virtual GLubyte * CreateBitmapData(string filename, GLfloat *width, GLfloat *heigth);
    virtual GLubyte * CreateBitmapData(char* data, size_t size, GLfloat *width, GLfloat *heigth);
};

#endif /* defined(__Asterids__ios_fileManager__) */
