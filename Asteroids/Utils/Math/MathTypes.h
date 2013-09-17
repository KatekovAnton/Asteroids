#ifndef Asteroids_MathTypes_h
#define Asteroids_MathTypes_h

#ifdef  TARGET_OS_IPHONE
#define GLES2    <OpenGLES/ES2/gl.h>
#define Glext    <OpenGLES/ES2/glext.h>
#include GLES2
#include Glext
#endif
#ifdef TARGET_OS_WIN
#include <windows.h>
#include "glew.h"
#include "glext.h"
#include "wchar.h"
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#define PI 3.14159265
#define PIOVER2 1.57079

// Pre-calculated value of PI / 180.
#define kPI180   0.017453

// Pre-calculated value of 180 / PI.
#define k180PI  57.295780

// Converts degrees to radians.
#define degreesToRadians(x) (x * kPI180)

// Converts radians to degrees.
#define radiansToDegrees(x) (x * k180PI)


#ifdef __cplusplus
extern "C" {
#endif
    
#define ____min(a, b) ((a)<(b)?(a):(b))
#define ____max(a, b) ((a)>(b)?(a):(b))
    
    
    ///////////////////////Matrix2//////////////////////////////////////////////
#if defined(__STRICT_ANSI__)
    struct _Matrix2
    {
        float m[4];
    };
    typedef struct _Matrix2 Matrix2;
#else
    union _Matrix2
    {
        struct
        {
            float m00, m01;
            float m10, m11;
        };
        float m2[2][2];
        float m[4];
    };
    typedef union _Matrix2 Matrix2;
#endif
    ///////////////////////Matrix3//////////////////////////////////////////////
#if defined(__STRICT_ANSI__)
    struct _Matrix3
    {
        float m[9];
    };
    typedef struct _Matrix3 Matrix3;
#else
    union _Matrix3
    {
        struct
        {
            float m00, m01, m02;
            float m10, m11, m12;
            float m20, m21, m22;
        };
        float m[9];
    };
    typedef union _Matrix3 Matrix3;
#endif
    ///////////////////////
    ///////////////////////Matrix4//////////////////////////////////////////////
    ///////////////////////
#if defined(__STRICT_ANSI__)
    struct _Matrix4
    {
        float m[16];
    } __attribute__((aligned(16)));
    typedef struct _Matrix4 Matrix4;
#else
    union _Matrix4
    {
        struct
        {
            float m00, m01, m02, m03;
            float m10, m11, m12, m13;
            float m20, m21, m22, m23;
            float m30, m31, m32, m33;
        };
        float m[16];
    }
#endif
#ifdef TARGET_OS_IPHONE
    __attribute__((aligned(16)));
    typedef union _Matrix4 Matrix4;
#endif
#ifdef TARGET_OS_WIN
    ;
    typedef union _Matrix4 Matrix4;
#endif
    ///////////////////////
    ///////////////////////Vector2//////////////////////////////////////////////
    ///////////////////////
#if defined(__STRICT_ANSI__)
    struct _Vector2
    {
        float v[2];
    };
    typedef struct _Vector2 Vector2;
#else
    union _Vector2
    {
        struct { float x, y; };
        struct { float s, t; };
        float v[2];
    };
    typedef union _Vector2 Vector2;
#endif
    ///////////////////////
    ///////////////////////Vector3//////////////////////////////////////////////
    ///////////////////////
#if defined(__STRICT_ANSI__)
    struct _Vector3
    {
        float v[3];
    };
    typedef struct _Vector3 Vector3;
#else
    union _Vector3
    {
        struct { float x, y, z; };
        struct { float r, g, b; };
        struct { float s, t, p; };
        float v[3];
    };
    typedef union _Vector3 Vector3;
#endif
    ///////////////////////
    ///////////////////////Vector4//////////////////////////////////////////////
    ///////////////////////
#if defined(__STRICT_ANSI__)
    struct _Vector4
    {
        float v[4];
    } __attribute__((aligned(16)));
    typedef struct _Vector4 Vector4;
#else
    union _Vector4
    {
        struct { float x, y, z, w; };
        struct { float r, g, b, a; };
        struct { float s, t, p, q; };
        float v[4];
    }
#endif
#ifdef TARGET_OS_IPHONE
    __attribute__((aligned(16)));
    typedef union _Vector4 Vector4;
#endif
#ifdef TARGET_OS_WIN
    ;
    typedef union _Vector4 Vector4;
#endif  
    
#include "Vector2.h"
    
    struct __Size {
        GLfloat height;
        GLfloat width;
    };
    
    typedef struct __Size MSize;
    
    static inline MSize SizeMake(float height, float width) {
        MSize result;
        result.height = height;
        result.width = width;
        return result;
    }
    
    struct __Rect {
        Vector2   origin;
        MSize      size;
    };
    
    typedef struct __Rect MRect;
    
    
    
    static inline MRect RectMake(GLfloat x, GLfloat y, GLfloat width, GLfloat height) {
        MRect rect;
        rect.origin.x = x;
        rect.origin.y = y;
        rect.size.width = width;
        rect.size.height = height;
        return rect;
    };
    
    
    struct __BoundingBox {
        Vector2 min;
        Vector2 max;
        
        Vector2 GetCenter() const {return Vector2Make((min.x + max.x)/2.0, (min.y + max.y)/2.0); }
        Vector2 GetSize() const {return Vector2Make(- (min.x - max.x), -(min.y - max.y)); }
        
        void AddBoundingBox(__BoundingBox bb)
        {
            min.x = ____min(min.x, bb.min.x);
            min.y = ____min(min.y, bb.min.y);
            max.x = ____max(max.x, bb.max.x);
            max.y = ____max(max.y, bb.max.y);
        }
        
    };
    typedef struct __BoundingBox BoundingBox;
    
    static inline BoundingBox BoundingBoxMake(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) {
        BoundingBox rect;
        rect.min.x = x1;
        rect.min.y = y1;
        rect.max.x = x2;
        rect.max.y = y2;
        return rect;
    };
    
    static inline BoundingBox BoundingBoxMake(Vector2 min, Vector2 max) {
        BoundingBox rect;
        rect.min = min;
        rect.max = max;
        return rect;
    };
    
    enum __ContainmentType
    {
        ContainmentType_Disjoint,
        ContainmentType_Contains,
        ContainmentType_Intersects
    };
    
    typedef enum __ContainmentType ContainmentType;
    
    
    static inline ContainmentType GetContainmentType(BoundingBox first, BoundingBox second)
    {
        if (first.max.x < second.min.x || first.max.y < second.min.y ||
            first.min.x > second.max.x || first.min.y > second.max.y) {
            return ContainmentType_Disjoint;
        }
        
        if (second.min.x > first.min.x && second.min.y > first.min.y &&
            second.max.x < first.max.x && second.max.y < first.max.y) {
            return ContainmentType_Contains;
        }
        
        return ContainmentType_Intersects;
    }
    
    
    
#ifdef __cplusplus
}
#endif

#endif
