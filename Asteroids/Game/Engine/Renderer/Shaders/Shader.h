//
//  Shader.h
//  Asteroids
//
//  Created by Katekov Anton on 11/3/12.
//
//

#ifndef __Asteroids__Shader__
#define __Asteroids__Shader__

#include <iostream>
#include "Math.h"
#include "GlobalConstants.h"

using namespace std;

class Shader {
    GLuint      _program;
    GLuint      _shaderUniforms[MAX_UNIFORMS];
    
    bool LoadShader(const string& vertexName, const string& fragmentName);
	bool LoadShaderWin(string vertexName, string fragmentName);

	GLchar* LoadShaderSource(const char *filename);

    bool CompileShader(GLuint *shader, GLenum type, string file);
    bool LinkProgram(GLuint program, const string& vname, const string& fname);
    bool ValidateProgram(GLuint program);
    
public:
    
    Shader(const string& vertexName, const string& fragmentName);
    void SetMatrixValue(int uniformCode, float *value);
    void SetFloatValue(int uniformCode, float value);
    void SetVector4Value(int uniformCode, float* value);
    
    GLuint  GetProgram();
    
    GLuint * GetShaderUniforms();
};

#endif /* defined(__Asteroids__Shader__) */
