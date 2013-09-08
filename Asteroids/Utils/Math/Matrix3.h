//
//  Matrix3.h
//  it
//
//  Copyright (c) 2011, Apple Inc. All rights reserved.
//

#ifndef ___MATRIX_3_H
#define ___MATRIX_3_H

#include <stddef.h>
#include <stdbool.h>
#include <math.h>

#include "MathTypes.h"
#include "Vector3.h"

#ifdef __cplusplus
extern "C" {
#endif
    
#pragma mark -
#pragma mark Prototypes
#pragma mark -
    
extern const Matrix3 Matrix3Identity;

static inline Matrix3 Matrix3Make(float m00, float m01, float m02,
                                            float m10, float m11, float m12,
                                            float m20, float m21, float m22);

static inline Matrix3 Matrix3MakeAndTranspose(float m00, float m01, float m02,
                                                        float m10, float m11, float m12,
                                                        float m20, float m21, float m22);

static inline Matrix3 Matrix3MakeWithArray(float values[9]);

static inline Matrix3 Matrix3MakeWithArrayAndTranspose(float values[9]);

static inline Matrix3 Matrix3MakeWithRows(Vector3 row0,
                                                    Vector3 row1, 
                                                    Vector3 row2);

static inline Matrix3 Matrix3MakeWithColumns(Vector3 column0,
                                                       Vector3 column1, 
                                                       Vector3 column2);


static inline Matrix3 Matrix3MakeScale(float sx, float sy, float sz);	
static inline Matrix3 Matrix3MakeRotation(float radians, float x, float y, float z);

static inline Matrix3 Matrix3MakeXRotation(float radians);
static inline Matrix3 Matrix3MakeYRotation(float radians);
static inline Matrix3 Matrix3MakeZRotation(float radians);

/*
 Returns the upper left 2x2 portion of the 3x3 matrix.
 */
static inline Matrix2 Matrix3GetMatrix2(Matrix3 matrix);

static inline Vector3 Matrix3GetRow(Matrix3 matrix, int row);
static inline Vector3 Matrix3GetColumn(Matrix3 matrix, int column);

static inline Matrix3 Matrix3SetRow(Matrix3 matrix, int row, Vector3 vector);
static inline Matrix3 Matrix3SetColumn(Matrix3 matrix, int column, Vector3 vector);
    
static inline Matrix3 Matrix3Transpose(Matrix3 matrix);

Matrix3 Matrix3Invert(Matrix3 matrix, bool *isInvertible);
Matrix3 Matrix3InvertAndTranspose(Matrix3 matrix, bool *isInvertible);

static inline Matrix3 Matrix3Multiply(Matrix3 matrixLeft, Matrix3 matrixRight);

static inline Matrix3 Matrix3Add(Matrix3 matrixLeft, Matrix3 matrixRight);
static inline Matrix3 Matrix3Subtract(Matrix3 matrixLeft, Matrix3 matrixRight);
    
static inline Matrix3 Matrix3Scale(Matrix3 matrix, float sx, float sy, float sz);
static inline Matrix3 Matrix3ScaleWithVector3(Matrix3 matrix, Vector3 scaleVector);
/*
 The last component of the Vector4, scaleVector, is ignored.
 */
static inline Matrix3 Matrix3ScaleWithVector4(Matrix3 matrix, Vector4 scaleVector);

static inline Matrix3 Matrix3Rotate(Matrix3 matrix, float radians, float x, float y, float z);
static inline Matrix3 Matrix3RotateWithVector3(Matrix3 matrix, float radians, Vector3 axisVector);
/*
 The last component of the Vector4, axisVector, is ignored.
 */
static inline Matrix3 Matrix3RotateWithVector4(Matrix3 matrix, float radians, Vector4 axisVector);

static inline Matrix3 Matrix3RotateX(Matrix3 matrix, float radians);
static inline Matrix3 Matrix3RotateY(Matrix3 matrix, float radians);
static inline Matrix3 Matrix3RotateZ(Matrix3 matrix, float radians);

static inline Vector3 Matrix3MultiplyVector3(Matrix3 matrixLeft, Vector3 vectorRight);

static inline void Matrix3MultiplyVector3Array(Matrix3 matrix, Vector3 *vectors, size_t vectorCount);

#pragma mark -
#pragma mark Implementations
#pragma mark -

static inline Matrix3 Matrix3Make(float m00, float m01, float m02,
                                            float m10, float m11, float m12,
                                            float m20, float m21, float m22)
{
    Matrix3 m = { m00, m01, m02,
                     m10, m11, m12,
                     m20, m21, m22 };
    return m;
}

static inline Matrix3 Matrix3MakeAndTranspose(float m00, float m01, float m02,
                                                        float m10, float m11, float m12,
                                                        float m20, float m21, float m22)
{
    Matrix3 m = { m00, m10, m20,
                     m01, m11, m21,
                     m02, m12, m22};
    return m;
}

static inline Matrix3 Matrix3MakeWithArray(float values[9])
{
    Matrix3 m = { values[0], values[1], values[2],
                     values[3], values[4], values[5],
                     values[6], values[7], values[8] };
    return m;
}

static inline Matrix3 Matrix3MakeWithArrayAndTranspose(float values[9])
{
    Matrix3 m = { values[0], values[3], values[6],
                     values[1], values[4], values[7],
                     values[2], values[5], values[8] };
    return m;
}

static inline Matrix3 Matrix3MakeWithRows(Vector3 row0,
                                                    Vector3 row1, 
                                                    Vector3 row2)
{
    Matrix3 m = { row0.v[0], row1.v[0], row2.v[0],
                     row0.v[1], row1.v[1], row2.v[1],
                     row0.v[2], row1.v[2], row2.v[2] };
    return m;
}

static inline Matrix3 Matrix3MakeWithColumns(Vector3 column0,
                                                       Vector3 column1, 
                                                       Vector3 column2)
{
    Matrix3 m = { column0.v[0], column0.v[1], column0.v[2],
                     column1.v[0], column1.v[1], column1.v[2],
                     column2.v[0], column2.v[1], column2.v[2] };
    return m;
}



static inline Matrix3 Matrix3MakeScale(float sx, float sy, float sz)
{
    Matrix3 m = Matrix3Identity;
    m.m[0] = sx;
    m.m[4] = sy;
    m.m[8] = sz;
    return m;
}

static inline Matrix3 Matrix3MakeRotation(float radians, float x, float y, float z)
{
    Vector3 v = Vector3Normalize(Vector3Make(x, y, z));
    float cos = cosf(radians);
    float cosp = 1.0f - cos;
    float sin = sinf(radians);
    
    Matrix3 m = { cos + cosp * v.v[0] * v.v[0],
                     cosp * v.v[0] * v.v[1] + v.v[2] * sin,
                     cosp * v.v[0] * v.v[2] - v.v[1] * sin,

                     cosp * v.v[0] * v.v[1] - v.v[2] * sin,
                     cos + cosp * v.v[1] * v.v[1],
                     cosp * v.v[1] * v.v[2] + v.v[0] * sin,

                     cosp * v.v[0] * v.v[2] + v.v[1] * sin,
                     cosp * v.v[1] * v.v[2] - v.v[0] * sin,
                     cos + cosp * v.v[2] * v.v[2] };
    
    return m;
}

static inline Matrix3 Matrix3MakeXRotation(float radians)
{
    float cos = cosf(radians);
    float sin = sinf(radians);
    
    Matrix3 m = { 1.0f, 0.0f, 0.0f,
                     0.0f, cos, sin,
                     0.0f, -sin, cos };
    
    return m;
}

static inline Matrix3 Matrix3MakeYRotation(float radians)
{
    float cos = cosf(radians);
    float sin = sinf(radians);
    
    Matrix3 m = { cos, 0.0f, -sin,
                     0.0f, 1.0f, 0.0f,
                     sin, 0.0f, cos };
    
    return m;
}

static inline Matrix3 Matrix3MakeZRotation(float radians)
{
    float cos = cosf(radians);
    float sin = sinf(radians);
    
    Matrix3 m = { cos, sin, 0.0f,
                     -sin, cos, 0.0f,
                     0.0f, 0.0f, 1.0f };
    
    return m;
}

static inline Matrix2 Matrix3GetMatrix2(Matrix3 matrix)
{
    Matrix2 m = { matrix.m[0], matrix.m[1],
                     matrix.m[3], matrix.m[4] };
    return m;
}

static inline Vector3 Matrix3GetRow(Matrix3 matrix, int row)
{
    Vector3 v = { matrix.m[row], matrix.m[3 + row], matrix.m[6 + row] };
    return v;
}

static inline Vector3 Matrix3GetColumn(Matrix3 matrix, int column)
{
    Vector3 v = { matrix.m[column * 3 + 0], matrix.m[column * 3 + 1], matrix.m[column * 3 + 2] };
    return v;
}

static inline Matrix3 Matrix3SetRow(Matrix3 matrix, int row, Vector3 vector)
{
    matrix.m[row] = vector.v[0];
    matrix.m[row + 3] = vector.v[1];
    matrix.m[row + 6] = vector.v[2];
    
    return matrix;
}

static inline Matrix3 Matrix3SetColumn(Matrix3 matrix, int column, Vector3 vector)
{
    matrix.m[column * 3 + 0] = vector.v[0];
    matrix.m[column * 3 + 1] = vector.v[1];
    matrix.m[column * 3 + 2] = vector.v[2];
    
    return matrix;
}
    
static inline Matrix3 Matrix3Transpose(Matrix3 matrix)
{
    Matrix3 m = { matrix.m[0], matrix.m[3], matrix.m[6],
                     matrix.m[1], matrix.m[4], matrix.m[7],
                     matrix.m[2], matrix.m[5], matrix.m[8] };
    return m;
}
 
static inline Matrix3 Matrix3Multiply(Matrix3 matrixLeft, Matrix3 matrixRight)
{
    Matrix3 m;
    
    m.m[0] = matrixLeft.m[0] * matrixRight.m[0] + matrixLeft.m[3] * matrixRight.m[1] + matrixLeft.m[6] * matrixRight.m[2];
    m.m[3] = matrixLeft.m[0] * matrixRight.m[3] + matrixLeft.m[3] * matrixRight.m[4] + matrixLeft.m[6] * matrixRight.m[5];
    m.m[6] = matrixLeft.m[0] * matrixRight.m[6] + matrixLeft.m[3] * matrixRight.m[7] + matrixLeft.m[6] * matrixRight.m[8];
    
    m.m[1] = matrixLeft.m[1] * matrixRight.m[0] + matrixLeft.m[4] * matrixRight.m[1] + matrixLeft.m[7] * matrixRight.m[2];
    m.m[4] = matrixLeft.m[1] * matrixRight.m[3] + matrixLeft.m[4] * matrixRight.m[4] + matrixLeft.m[7] * matrixRight.m[5];
    m.m[7] = matrixLeft.m[1] * matrixRight.m[6] + matrixLeft.m[4] * matrixRight.m[7] + matrixLeft.m[7] * matrixRight.m[8];
    
    m.m[2] = matrixLeft.m[2] * matrixRight.m[0] + matrixLeft.m[5] * matrixRight.m[1] + matrixLeft.m[8] * matrixRight.m[2];
    m.m[5] = matrixLeft.m[2] * matrixRight.m[3] + matrixLeft.m[5] * matrixRight.m[4] + matrixLeft.m[8] * matrixRight.m[5];
    m.m[8] = matrixLeft.m[2] * matrixRight.m[6] + matrixLeft.m[5] * matrixRight.m[7] + matrixLeft.m[8] * matrixRight.m[8];
    
    return m;
}

static inline Matrix3 Matrix3Add(Matrix3 matrixLeft, Matrix3 matrixRight)
{
    Matrix3 m;
    
    m.m[0] = matrixLeft.m[0] + matrixRight.m[0];
    m.m[1] = matrixLeft.m[1] + matrixRight.m[1];
    m.m[2] = matrixLeft.m[2] + matrixRight.m[2];
    
    m.m[3] = matrixLeft.m[3] + matrixRight.m[3];
    m.m[4] = matrixLeft.m[4] + matrixRight.m[4];
    m.m[5] = matrixLeft.m[5] + matrixRight.m[5];
    
    m.m[6] = matrixLeft.m[6] + matrixRight.m[6];
    m.m[7] = matrixLeft.m[7] + matrixRight.m[7];
    m.m[8] = matrixLeft.m[8] + matrixRight.m[8];
    
    return m;
}

static inline Matrix3 Matrix3Subtract(Matrix3 matrixLeft, Matrix3 matrixRight)
{
    Matrix3 m;
    
    m.m[0] = matrixLeft.m[0] - matrixRight.m[0];
    m.m[1] = matrixLeft.m[1] - matrixRight.m[1];
    m.m[2] = matrixLeft.m[2] - matrixRight.m[2];
    
    m.m[3] = matrixLeft.m[3] - matrixRight.m[3];
    m.m[4] = matrixLeft.m[4] - matrixRight.m[4];
    m.m[5] = matrixLeft.m[5] - matrixRight.m[5];
    
    m.m[6] = matrixLeft.m[6] - matrixRight.m[6];
    m.m[7] = matrixLeft.m[7] - matrixRight.m[7];
    m.m[8] = matrixLeft.m[8] - matrixRight.m[8];
    
    return m;
}
    
static inline Matrix3 Matrix3Scale(Matrix3 matrix, float sx, float sy, float sz)
{
    Matrix3 m = { matrix.m[0] * sx, matrix.m[1] * sx, matrix.m[2] * sx,
                     matrix.m[3] * sy, matrix.m[4] * sy, matrix.m[5] * sy,
                     matrix.m[6] * sz, matrix.m[7] * sz, matrix.m[8] * sz };
    return m;
}

static inline Matrix3 Matrix3ScaleWithVector3(Matrix3 matrix, Vector3 scaleVector)
{
    Matrix3 m = { matrix.m[0] * scaleVector.v[0], matrix.m[1] * scaleVector.v[0], matrix.m[2] * scaleVector.v[0],
                     matrix.m[3] * scaleVector.v[1], matrix.m[4] * scaleVector.v[1], matrix.m[5] * scaleVector.v[1],
                     matrix.m[6] * scaleVector.v[2], matrix.m[7] * scaleVector.v[2], matrix.m[8] * scaleVector.v[2] };
    return m;
}

static inline Matrix3 Matrix3ScaleWithVector4(Matrix3 matrix, Vector4 scaleVector)
{
    Matrix3 m = { matrix.m[0] * scaleVector.v[0], matrix.m[1] * scaleVector.v[0], matrix.m[2] * scaleVector.v[0],
                     matrix.m[3] * scaleVector.v[1], matrix.m[4] * scaleVector.v[1], matrix.m[5] * scaleVector.v[1],
                     matrix.m[6] * scaleVector.v[2], matrix.m[7] * scaleVector.v[2], matrix.m[8] * scaleVector.v[2] };
    return m;
}

static inline Matrix3 Matrix3Rotate(Matrix3 matrix, float radians, float x, float y, float z)
{
    Matrix3 rm = Matrix3MakeRotation(radians, x, y, z);
    return Matrix3Multiply(matrix, rm);
}

static inline Matrix3 Matrix3RotateWithVector3(Matrix3 matrix, float radians, Vector3 axisVector)
{
    Matrix3 rm = Matrix3MakeRotation(radians, axisVector.v[0], axisVector.v[1], axisVector.v[2]);
    return Matrix3Multiply(matrix, rm);
}

static inline Matrix3 Matrix3RotateWithVector4(Matrix3 matrix, float radians, Vector4 axisVector)
{
    Matrix3 rm = Matrix3MakeRotation(radians, axisVector.v[0], axisVector.v[1], axisVector.v[2]);
    return Matrix3Multiply(matrix, rm);
}

static inline Matrix3 Matrix3RotateX(Matrix3 matrix, float radians)
{
    Matrix3 rm = Matrix3MakeXRotation(radians);
    return Matrix3Multiply(matrix, rm);
}

static inline Matrix3 Matrix3RotateY(Matrix3 matrix, float radians)
{
    Matrix3 rm = Matrix3MakeYRotation(radians);
    return Matrix3Multiply(matrix, rm);
}

static inline Matrix3 Matrix3RotateZ(Matrix3 matrix, float radians)
{
    Matrix3 rm = Matrix3MakeZRotation(radians);
    return Matrix3Multiply(matrix, rm);
}

static inline Vector3 Matrix3MultiplyVector3(Matrix3 matrixLeft, Vector3 vectorRight)
{
    Vector3 v = { matrixLeft.m[0] * vectorRight.v[0] + matrixLeft.m[3] * vectorRight.v[1] + matrixLeft.m[6] * vectorRight.v[2],
                     matrixLeft.m[1] * vectorRight.v[0] + matrixLeft.m[4] * vectorRight.v[1] + matrixLeft.m[7] * vectorRight.v[2],
                     matrixLeft.m[2] * vectorRight.v[0] + matrixLeft.m[5] * vectorRight.v[1] + matrixLeft.m[8] * vectorRight.v[2] };
    return v;
}

static inline void Matrix3MultiplyVector3Array(Matrix3 matrix, Vector3 *vectors, size_t vectorCount)
{
    int i;
    for (i=0; i < vectorCount; i++)
        vectors[i] = Matrix3MultiplyVector3(matrix, vectors[i]);
}
    
#ifdef __cplusplus
}
#endif

#endif /* ___MATRIX_3_H */
