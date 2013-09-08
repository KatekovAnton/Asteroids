#ifndef ___VECTOR_4_H
#define ___VECTOR_4_H

#include <stdbool.h>
#include <math.h>


#include "MathTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

#pragma mark -
#pragma mark Prototypes
#pragma mark -
    
static  Vector4 Vector4Make(float x, float y, float z, float w);
static  Vector4 Vector4MakeWithArray(float values[4]);
static  Vector4 Vector4MakeWithVector3(Vector3 vector, float w);

static  Vector4 Vector4Negate(Vector4 vector);

static  Vector4 Vector4Add(Vector4 vectorLeft, Vector4 vectorRight);
static  Vector4 Vector4Subtract(Vector4 vectorLeft, Vector4 vectorRight);
static  Vector4 Vector4Multiply(Vector4 vectorLeft, Vector4 vectorRight);
static  Vector4 Vector4Divide(Vector4 vectorLeft, Vector4 vectorRight);
        
static  Vector4 Vector4AddScalar(Vector4 vector, float value);
static  Vector4 Vector4SubtractScalar(Vector4 vector, float value);
static  Vector4 Vector4MultiplyScalar(Vector4 vector, float value);
static  Vector4 Vector4DivideScalar(Vector4 vector, float value);
    
static  Vector4 Vector4Normalize(Vector4 vector);

static  float Vector4DotProduct(Vector4 vectorLeft, Vector4 vectorRight);
static  float Vector4Length(Vector4 vector);
static  float Vector4Distance(Vector4 vectorStart, Vector4 vectorEnd);

static  Vector4 Vector4Lerp(Vector4 vectorStart, Vector4 vectorEnd, float t);

/*
 Performs a 3D cross product. The last component of the resulting cross product will be zeroed out.
 */
static  Vector4 Vector4CrossProduct(Vector4 vectorLeft, Vector4 vectorRight);
	
/*
 Project the vector, vectorToProject, onto the vector, projectionVector.
 */
static  Vector4 Vector4Project(Vector4 vectorToProject, Vector4 projectionVector);

#pragma mark -
#pragma mark Implementations
#pragma mark -
    
static  Vector4 Vector4Make(float x, float y, float z, float w)
{
    Vector4 v = { x, y, z, w };
    return v;
}

static  Vector4 Vector4MakeWithArray(float values[4])
{
    Vector4 v = { values[0], values[1], values[2], values[3] };
    return v;
}
    
static  Vector4 Vector4MakeWithVector3(Vector3 vector, float w)
{
    Vector4 v = { vector.v[0], vector.v[1], vector.v[2], w };
    return v;
}
    
static  Vector4 Vector4Negate(Vector4 vector)
{
    Vector4 v = { -vector.v[0], -vector.v[1], -vector.v[2], -vector.v[3] };
    return v;
}

static  Vector4 Vector4Add(Vector4 vectorLeft, Vector4 vectorRight)
{
    Vector4 v = { vectorLeft.v[0] + vectorRight.v[0],
                     vectorLeft.v[1] + vectorRight.v[1],
                     vectorLeft.v[2] + vectorRight.v[2],
                     vectorLeft.v[3] + vectorRight.v[3] };
    return v;
}

static  Vector4 Vector4Subtract(Vector4 vectorLeft, Vector4 vectorRight)
{
    Vector4 v = { vectorLeft.v[0] - vectorRight.v[0],
                     vectorLeft.v[1] - vectorRight.v[1],
                     vectorLeft.v[2] - vectorRight.v[2],
                     vectorLeft.v[3] - vectorRight.v[3] };
    return v;
}

static  Vector4 Vector4Multiply(Vector4 vectorLeft, Vector4 vectorRight)
{
    Vector4 v = { vectorLeft.v[0] * vectorRight.v[0],
                     vectorLeft.v[1] * vectorRight.v[1],
                     vectorLeft.v[2] * vectorRight.v[2],
                     vectorLeft.v[3] * vectorRight.v[3] };
    return v;
}

static  Vector4 Vector4Divide(Vector4 vectorLeft, Vector4 vectorRight)
{
    Vector4 v = { vectorLeft.v[0] / vectorRight.v[0],
                     vectorLeft.v[1] / vectorRight.v[1],
                     vectorLeft.v[2] / vectorRight.v[2],
                     vectorLeft.v[3] / vectorRight.v[3] };
    return v;
}

static  Vector4 Vector4AddScalar(Vector4 vector, float value)
{
    Vector4 v = { vector.v[0] + value,
                     vector.v[1] + value,
                     vector.v[2] + value,
                     vector.v[3] + value };
    return v;
}

static  Vector4 Vector4SubtractScalar(Vector4 vector, float value)
{
    Vector4 v = { vector.v[0] - value,
                     vector.v[1] - value,
                     vector.v[2] - value,
                     vector.v[3] - value };
    return v;
}

static  Vector4 Vector4MultiplyScalar(Vector4 vector, float value)
{
    Vector4 v = { vector.v[0] * value,
                     vector.v[1] * value,
                     vector.v[2] * value,
                     vector.v[3] * value };
    return v; 
}

static  Vector4 Vector4DivideScalar(Vector4 vector, float value)
{
    Vector4 v = { vector.v[0] / value,
                     vector.v[1] / value,
                     vector.v[2] / value,
                     vector.v[3] / value };
    return v;
}
        
static  Vector4 Vector4Normalize(Vector4 vector)
{
    float scale = 1.0f / Vector4Length(vector);
    Vector4 v = Vector4MultiplyScalar(vector, scale);
    return v;
}

static  float Vector4DotProduct(Vector4 vectorLeft, Vector4 vectorRight)
{
    return vectorLeft.v[0] * vectorRight.v[0] +
           vectorLeft.v[1] * vectorRight.v[1] +
           vectorLeft.v[2] * vectorRight.v[2] +
           vectorLeft.v[3] * vectorRight.v[3];
}

static  float Vector4Length(Vector4 vector)
{
    return sqrt(vector.v[0] * vector.v[0] +
                vector.v[1] * vector.v[1] +
                vector.v[2] * vector.v[2] +
                vector.v[3] * vector.v[3]);
}

static  float Vector4Distance(Vector4 vectorStart, Vector4 vectorEnd)
{
    return Vector4Length(Vector4Subtract(vectorEnd, vectorStart));
}

static  Vector4 Vector4Lerp(Vector4 vectorStart, Vector4 vectorEnd, float t)
{
    Vector4 v = { vectorStart.v[0] + ((vectorEnd.v[0] - vectorStart.v[0]) * t),
                     vectorStart.v[1] + ((vectorEnd.v[1] - vectorStart.v[1]) * t),
                     vectorStart.v[2] + ((vectorEnd.v[2] - vectorStart.v[2]) * t),
                     vectorStart.v[3] + ((vectorEnd.v[3] - vectorStart.v[3]) * t) };
    return v;
}
    
static  Vector4 Vector4CrossProduct(Vector4 vectorLeft, Vector4 vectorRight)
{
    Vector4 v = { vectorLeft.v[1] * vectorRight.v[2] - vectorLeft.v[2] * vectorRight.v[1],
                     vectorLeft.v[2] * vectorRight.v[0] - vectorLeft.v[0] * vectorRight.v[2],
                     vectorLeft.v[0] * vectorRight.v[1] - vectorLeft.v[1] * vectorRight.v[0],
                     0.0f };
    return v;
}
    
static  Vector4 Vector4Project(Vector4 vectorToProject, Vector4 projectionVector)
{
    float scale = Vector4DotProduct(projectionVector, vectorToProject) / Vector4DotProduct(projectionVector, projectionVector);
    Vector4 v = Vector4MultiplyScalar(projectionVector, scale);
    return v;
}
    
#ifdef __cplusplus
}
#endif

#endif /* ___VECTOR_4_H */
