#ifndef MATH_H
#define MATH_H

typedef struct Vec2 Vec2;
typedef struct Vec3 Vec3;
typedef struct Vec4 Vec4;

// Data types
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef signed long long s64;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef float f32;
typedef double f64;

// Matrix definition
typedef float Mtx[3][4];
typedef float (*MtxPtr)[4];

// bool lingo
#define true 1
#define false 0

struct Vec2
{
    float X;
    float Y;
};

struct Vec3
{
    float X;
    float Y;
    float Z;
};

struct Vec4
{
    float X;
    float Y;
    float Z;
    float W;
};

typedef struct Matrix
{
    float M00;
    float M01;
    float M02;
    float M03;
    float M10;
    float M11;
    float M12;
    float M13;
    float M20;
    float M21;
    float M22;
    float M23;
} Matrix;


// inline functions

float Vec3_Length(Vec3 v)
{
    return sqrtf(v.X*v.X + v.Y*v.Y + v.Z*v.Z);
};

Vec3 Vec3_Add(Vec3 a, Vec3 b)
{
    Vec3 r =
    { 
        a.X + b.X, 
        a.Y + b.Y, 
        a.Z + b.Z 
    };
    return r;
}

Vec3 Vec3_Sub(Vec3 a, Vec3 b)
{
    Vec3 r =
    { 
        a.X - b.X, 
        a.Y - b.Y, 
        a.Z - b.Z 
    };
    return r;
}

Vec3 Vec3_Divide(Vec3 a, float v)
{
    Vec3 r =
    { 
        a.X / v, 
        a.Y / v, 
        a.Z / v 
    };
    return r;
}

Vec3 Vec3_Mult(Vec3 a, float v)
{
    Vec3 r =
    { 
        a.X * v, 
        a.Y * v, 
        a.Z * v 
    };
    return r;
}

float Vec3_Distance(Vec3 a, Vec3 b)
{
    return Vec3_Length(Vec3_Sub(a, b));
}


// game functions
void PSMTXCopy(Mtx *src, Mtx *dest);
void MTXLookAt(Mtx *dest, Vec3 *eye, Vec3 *up, Vec3 *target);
void HSD_MtxGetRotation(Mtx *m, Vec3 *dest);

#endif