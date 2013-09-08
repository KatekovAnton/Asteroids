#ifndef ___VECTOR_3_H
#define ___VECTOR_3_H

#include <stdbool.h>
#include <math.h>

#include "MathTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

#pragma mark -
#pragma mark Prototypes
#pragma mark -
    
static inline Vector3 Vector3Make(float x, float y, float z);
static inline Vector3 Vector3MakeWithArray(float values[3]);

static inline Vector3 Vector3Negate(Vector3 vector);

static inline Vector3 Vector3Add(Vector3 vectorLeft, Vector3 vectorRight);
static inline Vector3 Vector3Subtract(Vector3 vectorLeft, Vector3 vectorRight);
static inline Vector3 Vector3Multiply(Vector3 vectorLeft, Vector3 vectorRight);
static inline Vector3 Vector3Divide(Vector3 vectorLeft, Vector3 vectorRight);
        
static inline Vector3 Vector3AddScalar(Vector3 vector, float value);
static inline Vector3 Vector3SubtractScalar(Vector3 vector, float value);
static inline Vector3 Vector3MultiplyScalar(Vector3 vector, float value);
static inline Vector3 Vector3DivideScalar(Vector3 vector, float value);
	

    
static inline Vector3 Vector3Normalize(Vector3 vector);

static inline float Vector3DotProduct(Vector3 vectorLeft, Vector3 vectorRight);
static inline float Vector3Length(Vector3 vector);
static inline float Vector3Distance(Vector3 vectorStart, Vector3 vectorEnd);

static inline Vector3 Vector3Lerp(Vector3 vectorStart, Vector3 vectorEnd, float t);

static inline Vector3 Vector3CrossProduct(Vector3 vectorLeft, Vector3 vectorRight);
    
/*
 Project the vector, vectorToProject, onto the vector, projectionVector.
 */
static inline Vector3 Vector3Project(Vector3 vectorToProject, Vector3 projectionVector);

#pragma mark -
#pragma mark Implementations
#pragma mark -
    
static inline Vector3 Vector3Make(float x, float y, float z)
{
    Vector3 v = { x, y, z };
    return v;
}

static inline Vector3 Vector3MakeWithArray(float values[3])
{
    Vector3 v = { values[0], values[1], values[2] };
    return v;
}
   
static inline Vector3 Vector3Negate(Vector3 vector)
{
    Vector3 v = { -vector.v[0], -vector.v[1], -vector.v[2] };
    return v;
}
    
static inline Vector3 Vector3Add(Vector3 vectorLeft, Vector3 vectorRight)
{
    Vector3 v = { vectorLeft.v[0] + vectorRight.v[0],
                     vectorLeft.v[1] + vectorRight.v[1],
                     vectorLeft.v[2] + vectorRight.v[2] };
    return v;
}

static inline Vector3 Vector3Subtract(Vector3 vectorLeft, Vector3 vectorRight)
{
    Vector3 v = { vectorLeft.v[0] - vectorRight.v[0],
                     vectorLeft.v[1] - vectorRight.v[1],
                     vectorLeft.v[2] - vectorRight.v[2] };
    return v;
}

static inline Vector3 Vector3Multiply(Vector3 vectorLeft, Vector3 vectorRight)
{
    Vector3 v = { vectorLeft.v[0] * vectorRight.v[0],
                     vectorLeft.v[1] * vectorRight.v[1],
                     vectorLeft.v[2] * vectorRight.v[2] };
    return v;
}

static inline Vector3 Vector3Divide(Vector3 vectorLeft, Vector3 vectorRight)
{
    Vector3 v = { vectorLeft.v[0] / vectorRight.v[0],
                     vectorLeft.v[1] / vectorRight.v[1],
                     vectorLeft.v[2] / vectorRight.v[2] };
    return v;
}

static inline Vector3 Vector3AddScalar(Vector3 vector, float value)
{
    Vector3 v = { vector.v[0] + value,
                     vector.v[1] + value,
                     vector.v[2] + value };
    return v;
}

static inline Vector3 Vector3SubtractScalar(Vector3 vector, float value)
{
    Vector3 v = { vector.v[0] - value,
                     vector.v[1] - value,
                     vector.v[2] - value };
    return v;    
}

static inline Vector3 Vector3MultiplyScalar(Vector3 vector, float value)
{
    Vector3 v = { vector.v[0] * value,
                     vector.v[1] * value,
                     vector.v[2] * value };
    return v;   
}

static inline Vector3 Vector3DivideScalar(Vector3 vector, float value)
{
    Vector3 v = { vector.v[0] / value,
                     vector.v[1] / value,
                     vector.v[2] / value };
    return v;
}
      
static inline Vector3 Vector3Normalize(Vector3 vector)
{
    float scale = 1.0f / Vector3Length(vector);
    Vector3 v = { vector.v[0] * scale, vector.v[1] * scale, vector.v[2] * scale };
    return v;
}
    
static inline float Vector3DotProduct(Vector3 vectorLeft, Vector3 vectorRight)
{
    return vectorLeft.v[0] * vectorRight.v[0] + vectorLeft.v[1] * vectorRight.v[1] + vectorLeft.v[2] * vectorRight.v[2];
}

static inline float Vector3Length(Vector3 vector)
{
    return sqrt(vector.v[0] * vector.v[0] + vector.v[1] * vector.v[1] + vector.v[2] * vector.v[2]);
}

static inline float Vector3Distance(Vector3 vectorStart, Vector3 vectorEnd)
{
    return Vector3Length(Vector3Subtract(vectorEnd, vectorStart));
}
    
static inline Vector3 Vector3Lerp(Vector3 vectorStart, Vector3 vectorEnd, float t)
{
    Vector3 v = { vectorStart.v[0] + ((vectorEnd.v[0] - vectorStart.v[0]) * t),
                     vectorStart.v[1] + ((vectorEnd.v[1] - vectorStart.v[1]) * t),
                     vectorStart.v[2] + ((vectorEnd.v[2] - vectorStart.v[2]) * t) };
    return v;
}
 
static inline Vector3 Vector3CrossProduct(Vector3 vectorLeft, Vector3 vectorRight)
{
    Vector3 v = { vectorLeft.v[1] * vectorRight.v[2] - vectorLeft.v[2] * vectorRight.v[1],
                     vectorLeft.v[2] * vectorRight.v[0] - vectorLeft.v[0] * vectorRight.v[2],
                     vectorLeft.v[0] * vectorRight.v[1] - vectorLeft.v[1] * vectorRight.v[0] };
    return v;
}
        
static inline Vector3 Vector3Project(Vector3 vectorToProject, Vector3 projectionVector)
{
    float scale = Vector3DotProduct(projectionVector, vectorToProject) / Vector3DotProduct(projectionVector, projectionVector);
    Vector3 v = Vector3MultiplyScalar(projectionVector, scale);
    return v;
}
    
#ifdef __cplusplus
}
#endif

#endif /* ___VECTOR_3_H */
