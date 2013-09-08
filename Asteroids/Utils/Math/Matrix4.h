#ifndef ___MATRIX_4_H
#define ___MATRIX_4_H

#include <stddef.h>
#include <stdbool.h>


#include <math.h>

#include "MathTypes.h"
#include "Matrix3.h"
#include "Vector3.h"
#include "Vector4.h"

#ifdef __cplusplus
extern "C" {
#endif
    
const Matrix4 Matrix4Identity =  {1, 0, 0, 0,
                                        0, 1, 0, 0,
                                        0, 0, 1, 0,
                                        0, 0, 0, 1};
      


static inline Matrix4 Matrix4Make(float m00, float m01, float m02, float m03,
                                            float m10, float m11, float m12, float m13,
                                            float m20, float m21, float m22, float m23,
                                            float m30, float m31, float m32, float m33);
static inline Matrix4 Matrix4MakeAndTranspose(float m00, float m01, float m02, float m03,
                                                            float m10, float m11, float m12, float m13,
                                                            float m20, float m21, float m22, float m23,
                                                            float m30, float m31, float m32, float m33);
static inline Matrix4 Matrix4MakeWithArrayAndTranspose(float values[16]);
    
	
static inline Matrix4 Matrix4MakeTranslation(float tx, float ty, float tz);
static inline Matrix4 Matrix4MakeScale(float sx, float sy, float sz);	
static inline Matrix4 Matrix4MakeRotation(float radians, float x, float y, float z);

static inline Matrix4 Matrix4MakeXRotation(float radians);
static inline Matrix4 Matrix4MakeYRotation(float radians);
static inline Matrix4 Matrix4MakeZRotation(float radians);


static inline Matrix4 Matrix4MakePerspective(float fovyRadians, float aspect, float nearZ, float farZ);
static inline Matrix4 Matrix4MakeOrtho(float left, float right,
                                                 float bottom, float top,
                                                 float nearZ, float farZ);
static inline Matrix4 Matrix4MakeLookAt(float eyeX, float eyeY, float eyeZ,
                                                  float centerX, float centerY, float centerZ,
                                                  float upX, float upY, float upZ);
    
    
static inline Matrix3 Matrix4GetMatrix3(Matrix4 matrix);
static inline Matrix4 Matrix4Transpose(Matrix4 matrix);
static inline Matrix4 Matrix4Invert(Matrix4 matrix, bool *isInvertible);

static inline Matrix4 Matrix4Multiply(Matrix4 matrixLeft, Matrix4 matrixRight);

static inline Matrix4 Matrix4Add(Matrix4 matrixLeft, Matrix4 matrixRight);
static inline Matrix4 Matrix4Subtract(Matrix4 matrixLeft, Matrix4 matrixRight);
    
static inline Matrix4 Matrix4Translate(Matrix4 matrix, float tx, float ty, float tz);
static inline Matrix4 Matrix4Scale(Matrix4 matrix, float sx, float sy, float sz);
static inline Matrix4 Matrix4Rotate(Matrix4 matrix, float radians, float x, float y, float z);
        
static inline Matrix4 Matrix4RotateX(Matrix4 matrix, float radians);
static inline Matrix4 Matrix4RotateY(Matrix4 matrix, float radians);
static inline Matrix4 Matrix4RotateZ(Matrix4 matrix, float radians);



#pragma mark -
#pragma mark Implementations
#pragma mark -
    
static inline Matrix4 Matrix4Make(float m00, float m01, float m02, float m03,
                                            float m10, float m11, float m12, float m13,
                                            float m20, float m21, float m22, float m23,
                                            float m30, float m31, float m32, float m33)
{
    Matrix4 m = { m00, m01, m02, m03,
                     m10, m11, m12, m13,
                     m20, m21, m22, m23,
                     m30, m31, m32, m33 };
    return m;
}
    
    
static inline Matrix4 Matrix4MakeAndTranspose(float m00, float m01, float m02, float m03,
                                                        float m10, float m11, float m12, float m13,
                                                        float m20, float m21, float m22, float m23,
                                                        float m30, float m31, float m32, float m33)
{
    Matrix4 m = { m00, m10, m20, m30,
        m01, m11, m21, m31,
        m02, m12, m22, m32,
        m03, m13, m23, m33 };
    return m;
}
    
static inline Matrix4 Matrix4MakeWithArrayAndTranspose(float values[16])
{
    Matrix4 m = { values[0], values[4], values[8], values[12],
            values[1], values[5], values[9], values[13],
            values[2], values[6], values[10], values[14],
            values[3], values[7], values[11], values[15] };
    return m;
}
    
static inline Matrix4 Matrix4MakeTranslation(float tx, float ty, float tz)
{
    Matrix4 m = Matrix4Identity;
    m.m[12] = tx;
    m.m[13] = ty;
    m.m[14] = tz;
    return m;
}

static inline Matrix4 Matrix4MakeScale(float sx, float sy, float sz)
{
    Matrix4 m = Matrix4Identity;
    m.m[0] = sx;
    m.m[5] = sy;
    m.m[10] = sz;
    return m;
}

static inline Matrix4 Matrix4MakeRotation(float radians, float x, float y, float z)
{
    Vector3 v = Vector3Normalize(Vector3Make(x, y, z));
    float cos = cosf(radians);
    float cosp = 1.0f - cos;
    float sin = sinf(radians);
    
    Matrix4 m = { cos + cosp * v.v[0] * v.v[0],
                     cosp * v.v[0] * v.v[1] + v.v[2] * sin,
                     cosp * v.v[0] * v.v[2] - v.v[1] * sin,
                     0.0f,
                     cosp * v.v[0] * v.v[1] - v.v[2] * sin,
                     cos + cosp * v.v[1] * v.v[1],
                     cosp * v.v[1] * v.v[2] + v.v[0] * sin,
                     0.0f,
                     cosp * v.v[0] * v.v[2] + v.v[1] * sin,
                     cosp * v.v[1] * v.v[2] - v.v[0] * sin,
                     cos + cosp * v.v[2] * v.v[2],
                     0.0f,
                     0.0f,
                     0.0f,
                     0.0f,
                     1.0f };

    return m;
}
   
static inline Matrix4 Matrix4MakeXRotation(float radians)
{
    float cos = cosf(radians);
    float sin = sinf(radians);
    
    Matrix4 m = { 1.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, cos, sin, 0.0f,
                     0.0f, -sin, cos, 0.0f,
                     0.0f, 0.0f, 0.0f, 1.0f };
    
    return m;
}

static inline Matrix4 Matrix4MakeYRotation(float radians)
{
    float cos = cosf(radians);
    float sin = sinf(radians);
    
    Matrix4 m = { cos, 0.0f, -sin, 0.0f,
                     0.0f, 1.0f, 0.0f, 0.0f,
                     sin, 0.0f, cos, 0.0f,
                     0.0f, 0.0f, 0.0f, 1.0f };
    
    return m;
}

static inline Matrix4 Matrix4MakeZRotation(float radians)
{
    float cos = cosf(radians);
    float sin = sinf(radians);
    
    Matrix4 m = { cos, sin, 0.0f, 0.0f,
                     -sin, cos, 0.0f, 0.0f,
                     0.0f, 0.0f, 1.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 1.0f };
    
    return m;
}
    
static inline Matrix4 Matrix4Transpose(Matrix4 matrix)
{
    Matrix4 m = { matrix.m[0], matrix.m[4], matrix.m[8], matrix.m[12],
            matrix.m[1], matrix.m[5], matrix.m[9], matrix.m[13],
            matrix.m[2], matrix.m[6], matrix.m[10], matrix.m[14],
            matrix.m[3], matrix.m[7], matrix.m[11], matrix.m[15] };
    return m;
}

static inline Matrix3 Matrix4GetMatrix3(Matrix4 matrix)
{
    Matrix3 m = { matrix.m[0], matrix.m[1], matrix.m[2],
            matrix.m[4], matrix.m[5], matrix.m[6],
            matrix.m[8], matrix.m[9], matrix.m[10] };
    return m;
}
    
static inline Matrix4 Matrix4Invert(Matrix4 matrix, bool *isInvertible)
{
    return Matrix4Identity;
}
    
static inline Matrix4 Matrix4Multiply(Matrix4 matrixLeft, Matrix4 matrixRight)
{
    Matrix4 m;
    
    m.m[0]  = matrixLeft.m[0] * matrixRight.m[0]  + matrixLeft.m[4] * matrixRight.m[1]  + matrixLeft.m[8] * matrixRight.m[2]   + matrixLeft.m[12] * matrixRight.m[3];
    m.m[4]  = matrixLeft.m[0] * matrixRight.m[4]  + matrixLeft.m[4] * matrixRight.m[5]  + matrixLeft.m[8] * matrixRight.m[6]   + matrixLeft.m[12] * matrixRight.m[7];
    m.m[8]  = matrixLeft.m[0] * matrixRight.m[8]  + matrixLeft.m[4] * matrixRight.m[9]  + matrixLeft.m[8] * matrixRight.m[10]  + matrixLeft.m[12] * matrixRight.m[11];
    m.m[12] = matrixLeft.m[0] * matrixRight.m[12] + matrixLeft.m[4] * matrixRight.m[13] + matrixLeft.m[8] * matrixRight.m[14]  + matrixLeft.m[12] * matrixRight.m[15];
    
    m.m[1]  = matrixLeft.m[1] * matrixRight.m[0]  + matrixLeft.m[5] * matrixRight.m[1]  + matrixLeft.m[9] * matrixRight.m[2]   + matrixLeft.m[13] * matrixRight.m[3];
    m.m[5]  = matrixLeft.m[1] * matrixRight.m[4]  + matrixLeft.m[5] * matrixRight.m[5]  + matrixLeft.m[9] * matrixRight.m[6]   + matrixLeft.m[13] * matrixRight.m[7];
    m.m[9]  = matrixLeft.m[1] * matrixRight.m[8]  + matrixLeft.m[5] * matrixRight.m[9]  + matrixLeft.m[9] * matrixRight.m[10]  + matrixLeft.m[13] * matrixRight.m[11];
    m.m[13] = matrixLeft.m[1] * matrixRight.m[12] + matrixLeft.m[5] * matrixRight.m[13] + matrixLeft.m[9] * matrixRight.m[14]  + matrixLeft.m[13] * matrixRight.m[15];
    
    m.m[2]  = matrixLeft.m[2] * matrixRight.m[0]  + matrixLeft.m[6] * matrixRight.m[1]  + matrixLeft.m[10] * matrixRight.m[2]  + matrixLeft.m[14] * matrixRight.m[3];
    m.m[6]  = matrixLeft.m[2] * matrixRight.m[4]  + matrixLeft.m[6] * matrixRight.m[5]  + matrixLeft.m[10] * matrixRight.m[6]  + matrixLeft.m[14] * matrixRight.m[7];
    m.m[10] = matrixLeft.m[2] * matrixRight.m[8]  + matrixLeft.m[6] * matrixRight.m[9]  + matrixLeft.m[10] * matrixRight.m[10] + matrixLeft.m[14] * matrixRight.m[11];
    m.m[14] = matrixLeft.m[2] * matrixRight.m[12] + matrixLeft.m[6] * matrixRight.m[13] + matrixLeft.m[10] * matrixRight.m[14] + matrixLeft.m[14] * matrixRight.m[15];
    
    m.m[3]  = matrixLeft.m[3] * matrixRight.m[0]  + matrixLeft.m[7] * matrixRight.m[1]  + matrixLeft.m[11] * matrixRight.m[2]  + matrixLeft.m[15] * matrixRight.m[3];
    m.m[7]  = matrixLeft.m[3] * matrixRight.m[4]  + matrixLeft.m[7] * matrixRight.m[5]  + matrixLeft.m[11] * matrixRight.m[6]  + matrixLeft.m[15] * matrixRight.m[7];
    m.m[11] = matrixLeft.m[3] * matrixRight.m[8]  + matrixLeft.m[7] * matrixRight.m[9]  + matrixLeft.m[11] * matrixRight.m[10] + matrixLeft.m[15] * matrixRight.m[11];
    m.m[15] = matrixLeft.m[3] * matrixRight.m[12] + matrixLeft.m[7] * matrixRight.m[13] + matrixLeft.m[11] * matrixRight.m[14] + matrixLeft.m[15] * matrixRight.m[15];
    
    return m;
}
 
static inline Matrix4 Matrix4Add(Matrix4 matrixLeft, Matrix4 matrixRight)
{
    Matrix4 m;
    
    m.m[0] = matrixLeft.m[0] + matrixRight.m[0];
    m.m[1] = matrixLeft.m[1] + matrixRight.m[1];
    m.m[2] = matrixLeft.m[2] + matrixRight.m[2];
    m.m[3] = matrixLeft.m[3] + matrixRight.m[3];
    
    m.m[4] = matrixLeft.m[4] + matrixRight.m[4];
    m.m[5] = matrixLeft.m[5] + matrixRight.m[5];
    m.m[6] = matrixLeft.m[6] + matrixRight.m[6];
    m.m[7] = matrixLeft.m[7] + matrixRight.m[7];
    
    m.m[8] = matrixLeft.m[8] + matrixRight.m[8];
    m.m[9] = matrixLeft.m[9] + matrixRight.m[9];
    m.m[10] = matrixLeft.m[10] + matrixRight.m[10];
    m.m[11] = matrixLeft.m[11] + matrixRight.m[11];
    
    m.m[12] = matrixLeft.m[12] + matrixRight.m[12];
    m.m[13] = matrixLeft.m[13] + matrixRight.m[13];
    m.m[14] = matrixLeft.m[14] + matrixRight.m[14];
    m.m[15] = matrixLeft.m[15] + matrixRight.m[15];
    
    return m;
}

static inline Matrix4 Matrix4Subtract(Matrix4 matrixLeft, Matrix4 matrixRight)
{
    Matrix4 m;
    
    m.m[0] = matrixLeft.m[0] - matrixRight.m[0];
    m.m[1] = matrixLeft.m[1] - matrixRight.m[1];
    m.m[2] = matrixLeft.m[2] - matrixRight.m[2];
    m.m[3] = matrixLeft.m[3] - matrixRight.m[3];
    
    m.m[4] = matrixLeft.m[4] - matrixRight.m[4];
    m.m[5] = matrixLeft.m[5] - matrixRight.m[5];
    m.m[6] = matrixLeft.m[6] - matrixRight.m[6];
    m.m[7] = matrixLeft.m[7] - matrixRight.m[7];
    
    m.m[8] = matrixLeft.m[8] - matrixRight.m[8];
    m.m[9] = matrixLeft.m[9] - matrixRight.m[9];
    m.m[10] = matrixLeft.m[10] - matrixRight.m[10];
    m.m[11] = matrixLeft.m[11] - matrixRight.m[11];
    
    m.m[12] = matrixLeft.m[12] - matrixRight.m[12];
    m.m[13] = matrixLeft.m[13] - matrixRight.m[13];
    m.m[14] = matrixLeft.m[14] - matrixRight.m[14];
    m.m[15] = matrixLeft.m[15] - matrixRight.m[15];
    
    return m;
}
    
static inline Matrix4 Matrix4Translate(Matrix4 matrix, float tx, float ty, float tz)
{
    Matrix4 m = { matrix.m[0], matrix.m[1], matrix.m[2], matrix.m[3],
                     matrix.m[4], matrix.m[5], matrix.m[6], matrix.m[7],
                     matrix.m[8], matrix.m[9], matrix.m[10], matrix.m[11],
                     matrix.m[0] * tx + matrix.m[4] * ty + matrix.m[8] * tz + matrix.m[12],
                     matrix.m[1] * tx + matrix.m[5] * ty + matrix.m[9] * tz + matrix.m[13],
                     matrix.m[2] * tx + matrix.m[6] * ty + matrix.m[10] * tz + matrix.m[14],
                     matrix.m[15] };
    return m;
}
    
static inline Matrix4 Matrix4Scale(Matrix4 matrix, float sx, float sy, float sz)
{
    Matrix4 m = { matrix.m[0] * sx, matrix.m[1] * sx, matrix.m[2] * sx, matrix.m[3] * sx,
                     matrix.m[4] * sy, matrix.m[5] * sy, matrix.m[6] * sy, matrix.m[7] * sy,
                     matrix.m[8] * sz, matrix.m[9] * sz, matrix.m[10] * sz, matrix.m[11] * sz,
                     matrix.m[12], matrix.m[13], matrix.m[14], matrix.m[15] };
    return m;
}

static inline Matrix4 Matrix4Rotate(Matrix4 matrix, float radians, float x, float y, float z)
{
    Matrix4 rm = Matrix4MakeRotation(radians, x, y, z);
    return Matrix4Multiply(matrix, rm);
}
    
static inline Matrix4 Matrix4RotateX(Matrix4 matrix, float radians)
{
    Matrix4 rm = Matrix4MakeXRotation(radians);
    return Matrix4Multiply(matrix, rm);
}

static inline Matrix4 Matrix4RotateY(Matrix4 matrix, float radians)
{
    Matrix4 rm = Matrix4MakeYRotation(radians);
    return Matrix4Multiply(matrix, rm);
}

static inline Matrix4 Matrix4RotateZ(Matrix4 matrix, float radians)
{
    Matrix4 rm = Matrix4MakeZRotation(radians);
    return Matrix4Multiply(matrix, rm);
}

static inline Vector4 Matrix4MultiplyVector4(Matrix4 matrixLeft, Vector4 vectorRight)
{
    Vector4 v = { matrixLeft.m[0] * vectorRight.v[0] + matrixLeft.m[4] * vectorRight.v[1] + matrixLeft.m[8] * vectorRight.v[2] + matrixLeft.m[12] * vectorRight.v[3],
                     matrixLeft.m[1] * vectorRight.v[0] + matrixLeft.m[5] * vectorRight.v[1] + matrixLeft.m[9] * vectorRight.v[2] + matrixLeft.m[13] * vectorRight.v[3],
                     matrixLeft.m[2] * vectorRight.v[0] + matrixLeft.m[6] * vectorRight.v[1] + matrixLeft.m[10] * vectorRight.v[2] + matrixLeft.m[14] * vectorRight.v[3],
                     matrixLeft.m[3] * vectorRight.v[0] + matrixLeft.m[7] * vectorRight.v[1] + matrixLeft.m[11] * vectorRight.v[2] + matrixLeft.m[15] * vectorRight.v[3] };
    return v;
}
    
static inline Matrix4 Matrix4MakeBillboardEasy(Matrix4 view, Vector3 objectPositon)
{
    Matrix4 result = Matrix4Transpose(view);
    
    result.m[12] = objectPositon.v[0];
    result.m[13] = objectPositon.v[1];
    result.m[14] = objectPositon.v[2];
    
    return  result;
}


static inline Matrix4 Matrix4MakeBillboard(Matrix4 view, Vector3 objectPositon, float scalex, float scaley)
{
    Matrix4 result = view;
    result.m00 = view.m00*scalex;
    result.m01 = view.m10*scalex;
    result.m02 = view.m20*scalex;
    result.m10 = view.m01*scaley;
    result.m11 = view.m11*scaley;
    result.m12 = view.m21*scaley;
    result.m20 = view.m02;
    result.m21 = view.m12;
    result.m22 = view.m22;
    
    
    
    result.m30 = objectPositon.x;
    result.m31 = objectPositon.y;
    result.m32 = objectPositon.z;
    return  result;
}


static inline Vector3 Matrix4GetTranslation(Matrix4 matrix)
{
    Vector3 v;
    v.x = matrix.m30;
    v.y = matrix.m31;
    v.z = matrix.m32;
    return v;
}

static inline Matrix4 Matrix4MakeCylBB(Matrix4 baseTransformMatrix, Matrix4 cameraView, Vector3 objectConstrAxis)
{
    Matrix4 result = Matrix4Identity;
    Vector3 translation = Vector3Make(baseTransformMatrix.m30, baseTransformMatrix.m31, baseTransformMatrix.m32);
    
    result.m30 = translation.x;
    result.m31 = translation.y;
    result.m32 = translation.z;
    
    
    Vector3 v0 = Vector3Make(cameraView.m02,cameraView.m12,cameraView.m22);
    v0 = Vector3Normalize(v0);
    result.m20 = v0.x;
    result.m21 = v0.y;
    result.m22 = v0.z;
    
    
    Vector3 v2 = Matrix3MultiplyVector3(Matrix4GetMatrix3(baseTransformMatrix), objectConstrAxis);
    v2 = Vector3Normalize(v2);
    result.m10 = v2.x;
    result.m11 = v2.y;
    result.m12 = v2.z;
    
    
    Vector3 v1 = Vector3CrossProduct(v2, v0);
    v1 = Vector3Normalize(v1);
    result.m00 = v1.x;
    result.m01 = v1.y;
    result.m02 = v1.z;
    
    
    return result;
}

static inline Matrix4 Matrix4MakeTranslationV(Vector3 position)
{
    return Matrix4MakeTranslation(position.x, position.y, position.z);
}

static inline float Vector3LengthSquired(Vector3 vector)
{
    return vector.x * vector.x + vector.y * vector.y + vector.z * vector.z;
}


static inline Vector3 UnprojectPointWIdent(Vector3 screenSpace, Matrix4 projection, Matrix4 view, float minDepth, float maxDepth, Size screenSize)
{
    //First, convert raw screen coords to unprojectable ones
    Vector3 position;
    position.x = (((screenSpace.x/* - (float)viewport.x*/) / (screenSize.width)) * 2.0) - 1.0;
    position.y = -((((screenSpace.y/* - (float)viewport.y*/) / (screenSize.height)) * 2.0) - 1.0);
    position.z = (screenSpace.y - minDepth) / (maxDepth - minDepth);
    
    //Unproject by transforming the 4d vector by the inverse of the projecttion matrix, followed by the inverse of the view matrix.  
    Vector4 us4 = Vector4MakeWithVector3(position, 1.0);
    
    bool l;
    Matrix4 m = Matrix4Invert(Matrix4Multiply(view, projection), &l);
    
    Vector4 up4 = Matrix4MultiplyVector4(m, us4); 
    Vector3 up3 = Vector3Make(up4.x/up4.w, up4.y/up4.w, up4.z/up4.w); //better to do this here to reduce precision loss..   
    return up3;
} 

    
#ifdef __cplusplus
}
#endif

#endif /* ___MATRIX_4_H */
