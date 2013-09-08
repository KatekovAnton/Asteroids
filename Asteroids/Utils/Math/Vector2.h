#ifndef ___VECTOR_2_H
#define ___VECTOR_2_H

#include <stdbool.h>
#include <math.h>
#include "MathTypes.h"

#ifdef __cplusplus
extern "C" {
#endif
    
#pragma mark -
#pragma mark Prototypes
#pragma mark -

static inline Vector2 Vector2Make(float x, float y);
static inline Vector2 Vector2MakeWithArray(float values[2]);

static inline Vector2 Vector2Negate(Vector2 vector);

static inline Vector2 Vector2Add(Vector2 vectorLeft, Vector2 vectorRight);
static inline Vector2 Vector2Subtract(Vector2 vectorLeft, Vector2 vectorRight);
static inline Vector2 Vector2Multiply(Vector2 vectorLeft, Vector2 vectorRight);
static inline Vector2 Vector2Divide(Vector2 vectorLeft, Vector2 vectorRight);
        
static inline Vector2 Vector2AddScalar(Vector2 vector, float value);
static inline Vector2 Vector2SubtractScalar(Vector2 vector, float value);
static inline Vector2 Vector2MultiplyScalar(Vector2 vector, float value);
static inline Vector2 Vector2DivideScalar(Vector2 vector, float value);
        
static inline Vector2 Vector2Maximum(Vector2 vectorLeft, Vector2 vectorRight);
static inline Vector2 Vector2Minimum(Vector2 vectorLeft, Vector2 vectorRight);
    
static inline bool Vector2AllEqualToVector2(Vector2 vectorLeft, Vector2 vectorRight);
static inline bool Vector2AllEqualToScalar(Vector2 vector, float value);
static inline bool Vector2AllGreaterThanVector2(Vector2 vectorLeft, Vector2 vectorRight);
static inline bool Vector2AllGreaterThanScalar(Vector2 vector, float value);
static inline bool Vector2AllGreaterThanOrEqualToVector2(Vector2 vectorLeft, Vector2 vectorRight);
static inline bool Vector2AllGreaterThanOrEqualToScalar(Vector2 vector, float value);
    
static inline Vector2 Vector2Normalize(Vector2 vector);

static inline float Vector2DotProduct(Vector2 vectorLeft, Vector2 vectorRight);
static inline float Vector2Length(Vector2 vector);
static inline float Vector2Distance(Vector2 vectorStart, Vector2 vectorEnd);

#pragma mark -
#pragma mark Implementations
#pragma mark -
    
static inline Vector2 Vector2Make(float x, float y)
{
    Vector2 v = { x, y };
    return v;
}
    
static inline Vector2 Vector2MakeWithArray(float values[2])
{
    Vector2 v = { values[0], values[1] };
    return v;
}
    
static inline Vector2 Vector2Negate(Vector2 vector)
{
    Vector2 v = { -vector.v[0] , -vector.v[1] };
    return v;
}
 
static inline Vector2 Vector2Add(Vector2 vectorLeft, Vector2 vectorRight)
{
    Vector2 v = { vectorLeft.v[0] + vectorRight.v[0],
                     vectorLeft.v[1] + vectorRight.v[1] };
    return v;
}
  
static inline Vector2 Vector2Subtract(Vector2 vectorLeft, Vector2 vectorRight)
{
    Vector2 v = { vectorLeft.v[0] - vectorRight.v[0],
                     vectorLeft.v[1] - vectorRight.v[1] };
    return v;
}
    
static inline Vector2 Vector2Multiply(Vector2 vectorLeft, Vector2 vectorRight)
{
    Vector2 v = { vectorLeft.v[0] * vectorRight.v[0],
                     vectorLeft.v[1] * vectorRight.v[1] };
    return v;
}
    
static inline Vector2 Vector2Divide(Vector2 vectorLeft, Vector2 vectorRight)
{
    Vector2 v = { vectorLeft.v[0] / vectorRight.v[0],
                     vectorLeft.v[1] / vectorRight.v[1] };
    return v;
}

static inline Vector2 Vector2AddScalar(Vector2 vector, float value)
{
    Vector2 v = { vector.v[0] + value,
                     vector.v[1] + value };
    return v;
}
    
static inline Vector2 Vector2SubtractScalar(Vector2 vector, float value)
{   
    Vector2 v = { vector.v[0] - value,
                     vector.v[1] - value };
    return v;
}
    
static inline Vector2 Vector2MultiplyScalar(Vector2 vector, float value)
{
    Vector2 v = { vector.v[0] * value,
                     vector.v[1] * value };
    return v;
}
    
static inline Vector2 Vector2DivideScalar(Vector2 vector, float value)
{
    Vector2 v = { vector.v[0] / value,
                     vector.v[1] / value };
    return v;
}
    
static inline Vector2 Vector2Maximum(Vector2 vectorLeft, Vector2 vectorRight)
{
    Vector2 max = vectorLeft;
    if (vectorRight.v[0] > vectorLeft.v[0])
        max.v[0] = vectorRight.v[0];
    if (vectorRight.v[1] > vectorLeft.v[1])
        max.v[1] = vectorRight.v[1];
    return max;
}

static inline Vector2 Vector2Minimum(Vector2 vectorLeft, Vector2 vectorRight)
{
    Vector2 min = vectorLeft;
    if (vectorRight.v[0] < vectorLeft.v[0])
        min.v[0] = vectorRight.v[0];
    if (vectorRight.v[1] < vectorLeft.v[1])
        min.v[1] = vectorRight.v[1];
    return min;
}
   
static inline bool Vector2AllEqualToVector2(Vector2 vectorLeft, Vector2 vectorRight)
{
    bool compare = false;
    if (vectorLeft.v[0] == vectorRight.v[0] &&
        vectorLeft.v[1] == vectorRight.v[1])
        compare = true;
    return compare;
}

static inline bool Vector2AllEqualToScalar(Vector2 vector, float value)
{
    bool compare = false;
    if (vector.v[0] == value &&
        vector.v[1] == value)
        compare = true;
    return compare;
}

static inline bool Vector2AllGreaterThanVector2(Vector2 vectorLeft, Vector2 vectorRight)
{
    bool compare = false;
    if (vectorLeft.v[0] > vectorRight.v[0] &&
        vectorLeft.v[1] > vectorRight.v[1])
        compare = true;
    return compare;
}

static inline bool Vector2AllGreaterThanScalar(Vector2 vector, float value)
{
    bool compare = false;
    if (vector.v[0] > value &&
        vector.v[1] > value)
        compare = true;
    return compare;
}

static inline bool Vector2AllGreaterThanOrEqualToVector2(Vector2 vectorLeft, Vector2 vectorRight)
{
    bool compare = false;
    if (vectorLeft.v[0] >= vectorRight.v[0] &&
        vectorLeft.v[1] >= vectorRight.v[1])
        compare = true;
    return compare;
}

static inline bool Vector2AllGreaterThanOrEqualToScalar(Vector2 vector, float value)
{
    bool compare = false;
    if (vector.v[0] >= value &&
        vector.v[1] >= value)
        compare = true;
    return compare;
}
    
static inline Vector2 Vector2Normalize(Vector2 vector)
{
    float scale = 1.0f / Vector2Length(vector);
    Vector2 v = Vector2MultiplyScalar(vector, scale);
    return v;
}

static inline float Vector2DotProduct(Vector2 vectorLeft, Vector2 vectorRight)
{
    return vectorLeft.v[0] * vectorRight.v[0] + vectorLeft.v[1] * vectorRight.v[1];
}

static inline float Vector2Length(Vector2 vector)
{
    return sqrt(vector.v[0] * vector.v[0] + vector.v[1] * vector.v[1]);
}

static inline float Vector2Distance(Vector2 vectorStart, Vector2 vectorEnd)
{
    return Vector2Length(Vector2Subtract(vectorEnd, vectorStart));
}

#ifdef __cplusplus
}
#endif

#endif /* ___VECTOR_2_H */
