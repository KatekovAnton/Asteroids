//
//  EngineMesh.cpp
//  Asteroids
//
//  Created by Katekov Anton on 11/3/12.
//
//

#include "EngineMesh.h"
#include "BinaryReader.h"

const int vertexSize = sizeof(vertexStruct);
const size_t vertexPositionOffset = offsetof(vertexStruct,position);
const size_t vertexNormalOffset = offsetof(vertexStruct,normal);
const size_t vertexTcoordOffset = offsetof(vertexStruct,tcoord);

GLfloat cubeVertexData[288] =
{
    // Data layout for each line below is:
    // positionX, positionY, positionZ,     normalX, normalY, normalZ,  tccordX, tcoordY
    0.5f, -0.5f, -0.5f,        1.0f, 0.0f, 0.0f,    1,0,
    0.5f, 0.5f, -0.5f,         1.0f, 0.0f, 0.0f,    1,1,
    0.5f, -0.5f, 0.5f,         1.0f, 0.0f, 0.0f,    0,0,
    0.5f, -0.5f, 0.5f,         1.0f, 0.0f, 0.0f,    0,0,
    0.5f, 0.5f, 0.5f,          1.0f, 0.0f, 0.0f,    0,1,
    0.5f, 0.5f, -0.5f,         1.0f, 0.0f, 0.0f,    1,1,
    
    0.5f, 0.5f, -0.5f,         0.0f, 1.0f, 0.0f,    1,0,
    -0.5f, 0.5f, -0.5f,        0.0f, 1.0f, 0.0f,    1,1,
    0.5f, 0.5f, 0.5f,          0.0f, 1.0f, 0.0f,    0,0,
    0.5f, 0.5f, 0.5f,          0.0f, 1.0f, 0.0f,    0,0,
    -0.5f, 0.5f, -0.5f,        0.0f, 1.0f, 0.0f,    1,1,
    -0.5f, 0.5f, 0.5f,         0.0f, 1.0f, 0.0f,    0,1,
    
    -0.5f, 0.5f, -0.5f,        -1.0f, 0.0f, 0.0f,   0,0,
    -0.5f, -0.5f, -0.5f,       -1.0f, 0.0f, 0.0f,   0,0,
    -0.5f, 0.5f, 0.5f,         -1.0f, 0.0f, 0.0f,   0,0,
    -0.5f, 0.5f, 0.5f,         -1.0f, 0.0f, 0.0f,   0,0,
    -0.5f, -0.5f, -0.5f,       -1.0f, 0.0f, 0.0f,   0,0,
    -0.5f, -0.5f, 0.5f,        -1.0f, 0.0f, 0.0f,   0,0,
    
    -0.5f, -0.5f, -0.5f,       0.0f, -1.0f, 0.0f,   0,0,
    0.5f, -0.5f, -0.5f,        0.0f, -1.0f, 0.0f,   0,0,
    -0.5f, -0.5f, 0.5f,        0.0f, -1.0f, 0.0f,   0,0,
    -0.5f, -0.5f, 0.5f,        0.0f, -1.0f, 0.0f,   0,0,
    0.5f, -0.5f, -0.5f,        0.0f, -1.0f, 0.0f,   0,0,
    0.5f, -0.5f, 0.5f,         0.0f, -1.0f, 0.0f,   0,0,
    
    0.5f, 0.5f, 0.5f,          0.0f, 0.0f, 1.0f,    0,1,
    -0.5f, 0.5f, 0.5f,         0.0f, 0.0f, 1.0f,    1,1,
    0.5f, -0.5f, 0.5f,         0.0f, 0.0f, 1.0f,    0,0,
    0.5f, -0.5f, 0.5f,         0.0f, 0.0f, 1.0f,    0,0,
    -0.5f, 0.5f, 0.5f,         0.0f, 0.0f, 1.0f,    1,1,
    -0.5f, -0.5f, 0.5f,        0.0f, 0.0f, 1.0f,    1,0,
    
    0.5f, -0.5f, -0.5f,        0.0f, 0.0f, -1.0f,   0,0,
    -0.5f, -0.5f, -0.5f,       0.0f, 0.0f, -1.0f,   0,0,
    0.5f, 0.5f, -0.5f,         0.0f, 0.0f, -1.0f,   0,0,
    0.5f, 0.5f, -0.5f,         0.0f, 0.0f, -1.0f,   0,0,
    -0.5f, -0.5f, -0.5f,       0.0f, 0.0f, -1.0f,   0,0,
    -0.5f, 0.5f, -0.5f,        0.0f, 0.0f, -1.0f,   0,0
};

GLushort cubeIndexData[36] =
{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35};

GLfloat planeVertexData[48] =
{
    // Data layout for each line below is:
    // positionX, positionY, positionZ,     normalX, normalY, normalZ,   tccordX, tcoordY
    0.05f, 0.5f, 0.0f,          0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
    -0.05f, 0.5f, 0.0f,         0.0f, 0.0f, 1.0f,   0.0f, 1.0f,
    0.05f, -0.5f, 0.0f,         0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
    0.05f, -0.5f, 0.0f,         0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
    -0.05f, 0.5f, 0.0f,         0.0f, 0.0f, 1.0f,   0.0f, 1.0f,
    -0.05f, -0.5f, 0.0f,        0.0f, 0.0f, 1.0f,   0.0f, 0.0f
};

GLfloat squarePlaneVertexData[48] =
{
    // Data layout for each line below is:
    // positionX, positionY, positionZ,     normalX, normalY, normalZ,   tccordX, tcoordY
    0.5f, 0.5f, 0.0f,          0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f, 0.5f, 0.0f,         0.0f, 0.0f, 1.0f,   0.0f, 1.0f,
    0.5f, -0.5f, 0.0f,         0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
    0.5f, -0.5f, 0.0f,         0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
    -0.5f, 0.5f, 0.0f,         0.0f, 0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f, 0.0f,        0.0f, 0.0f, 1.0f,   0.0f, 0.0f
};

GLfloat screenQuadVertexData[48] =
{
    // Data layout for each line below is:
    // positionX, positionY, positionZ,     normalX, normalY, normalZ,   tccordX, tcoordY
    -1.0f, -1.0f, 0.0f,         0.0f, 0.0f, 1.0f,   0.0f, 1.0f,
    1.0f, 1.0f, 0.0f,         0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,         0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
    -1.0f, -1.0f, 0.0f,         0.0f, 0.0f, 1.0f,   0.0f, 1.0f,
    -1.0f, 1.0f, 0.0f,         0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
    1.0f, 1.0f, 0.0f,         0.0f, 0.0f, 1.0f,   1.0f, 0.0f
};

GLfloat squareVertexData[48] =
{
    // Data layout for each line below is:
    // positionX, positionY, positionZ,     normalX, normalY, normalZ,   tccordX, tcoordY
    -0.5f, -0.5f, 0.0f,         0.0f, 0.0f, 1.0f,   0.0f, 1.0f,
    0.5f, 0.5f, 0.0f,         0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
    0.5f, -0.5f, 0.0f,         0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f, -0.5f, 0.0f,         0.0f, 0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, 0.5f, 0.0f,         0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
    0.5f, 0.5f, 0.0f,         0.0f, 0.0f, 1.0f,   1.0f, 0.0f
};

GLfloat squareVertexData1[48] =
{
    // Data layout for each line below is:
    // positionX, positionY, positionZ,     normalX, normalY, normalZ,   tccordX, tcoordY
    -0.5f, -0.5f, 0.0f,         0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
    0.5f, 0.5f, 0.0f,         0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
    0.5f, -0.5f, 0.0f,         0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f,         0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
    -0.5f, 0.5f, 0.0f,         0.0f, 0.0f, 1.0f,   0.0f, 1.0f,
    0.5f, 0.5f, 0.0f,         0.0f, 0.0f, 1.0f,   1.0f, 1.0f
};

GLushort planeIndexData[6] =
{0,1,2,3,4,5};

EngineMesh::EngineMesh()
{
    _disposed = true;
    _vertexBuffer = 0;
    _indexBuffer = 0;
}

EngineMesh::EngineMesh(void * vertices, long vSize, void *indices, long iSize):_vSize(vSize), _iSize(iSize)
{ 
    Init(vertices, vSize, indices, iSize);
}

void EngineMesh::Init(void * vertices, long vSize, void *indices, long iSize)
{
    if (!_disposed) 
        Dispose();
    
    glEnable(GL_DEPTH_TEST);
    
    glGenBuffers(1, &_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vSize, vertices, GL_STATIC_DRAW);

    if (indices) {
        glGenBuffers(1, &_indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, iSize, indices, GL_STATIC_DRAW);
    }

    _primitivesCount = vSize/sizeof(vertexStruct);
    
    _disposed = false;
	Unbind();
}

void EngineMesh::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glEnableVertexAttribArray(ATTRIB_VERTEX);
    glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT, GL_FALSE, vertexSize, (void*)vertexPositionOffset);
    glEnableVertexAttribArray(ATTRIB_NORMAL);
    glVertexAttribPointer(ATTRIB_NORMAL, 3, GL_FLOAT, GL_FALSE, vertexSize, (void*)vertexNormalOffset);
    glEnableVertexAttribArray(ATTRIB_TCOORD);
    glVertexAttribPointer(ATTRIB_TCOORD, 2, GL_FLOAT, GL_FALSE, vertexSize, (void*)vertexTcoordOffset);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
}

void EngineMesh::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EngineMesh::Dispose()
{
    if(_disposed)
        return;

    glDeleteBuffers(1, &_vertexBuffer);
    if (_indexBuffer)
        glDeleteBuffers(1, &_indexBuffer);
    
    _vertexBuffer = 0;
    _indexBuffer = 0;
    _disposed = true;
}

EngineMesh::~EngineMesh()
{
    Dispose();
}

void EngineMesh::Render() const {
    glDrawElements(GL_TRIANGLES, _primitivesCount, GL_UNSIGNED_SHORT, (void*)0);
  //  glDrawArrays(GL_TRIANGLES, 0, 4);
}

shared_ptr<EngineMesh> EngineMesh::CreateCube() {
    return shared_ptr<EngineMesh>(new  EngineMesh(cubeVertexData, sizeof(cubeVertexData), cubeIndexData, sizeof(cubeIndexData)));
}

shared_ptr<EngineMesh> EngineMesh::CreateFullscreenQuad() {
    return shared_ptr<EngineMesh>(new EngineMesh(screenQuadVertexData, sizeof(screenQuadVertexData), planeIndexData, sizeof(planeIndexData)));
}

shared_ptr<EngineMesh> EngineMesh::CreateUnitQuad() {
    return shared_ptr<EngineMesh>(new EngineMesh(squareVertexData1, sizeof(squareVertexData1), planeIndexData, sizeof(planeIndexData)));
}

shared_ptr<EngineMesh> EngineMesh::CreateScaledQuad(float sidex, float sidey)
{
    GLfloat* scaledVertexData = new GLfloat[48];
    memcpy(scaledVertexData, &squareVertexData, sizeof(squareVertexData));
    for (int i = 0; i < 6; i++) {
        scaledVertexData[i * 8] *= sidex;
        scaledVertexData[i * 8 + 1] *= sidey;
    }
    shared_ptr<EngineMesh> result = shared_ptr<EngineMesh>(new EngineMesh(scaledVertexData, 48 * sizeof(GLfloat), planeIndexData, sizeof(planeIndexData)));
    delete [] scaledVertexData;
    return result;
}

void EngineMesh::LoadFromBuffer(char *buffer, unsigned int bufferLength)
{
    BinaryReader br(buffer, bufferLength);
    
    int verticesCount = br.ReadInt();
    int indicesCount = br.ReadInt();
    
    GLsizeiptr vSize = vertexSize * verticesCount;
    GLsizeiptr iSize = sizeof(GLushort) * indicesCount;
    
    GLfloat* vertices = (GLfloat*)malloc(vSize);
    for(int i = 0;i < verticesCount; i++)
    {
        int baseStride = vertexSize * i/ sizeof(GLfloat);
        vertices[baseStride] = br.ReadSingle();
        vertices[baseStride + 1] = br.ReadSingle();
        vertices[baseStride + 2] = br.ReadSingle();
        
        
        vertices[baseStride + 3] = br.ReadSingle();
        vertices[baseStride + 4] = br.ReadSingle();
        vertices[baseStride + 5] = br.ReadSingle();
        
        
        vertices[baseStride + 6] = br.ReadSingle();
        vertices[baseStride + 7] = br.ReadSingle();
        
        
        int f = br.ReadInt();
        for (int j = 0; j < f; j++)
            br.ReadString();
        
        f = br.ReadInt();
        for (int j = 0; j < f; j++)
            br.ReadSingle();
    }
    
    GLushort* indices = (GLushort*)malloc(iSize);
    for(int i = 0;i < indicesCount; i++)
        indices[i] = (GLushort)br.ReadInt();
    
    
    
    glEnable(GL_DEPTH_TEST);
    
    glGenBuffers(1, &_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vSize, vertices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &_indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, iSize, indices, GL_STATIC_DRAW);
    
    _primitivesCount = iSize/sizeof(GLushort);
    _disposed = false;
    
    free(vertices);
    free(indices);
}

