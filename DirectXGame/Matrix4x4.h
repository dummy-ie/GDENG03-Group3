#pragma once

#include <cmath>

struct vec3
{
    float x, y, z;

    vec3() : x(0), y(0), z(0) {}
    vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};

class Matrix4x4
{
public:
    float m[4][4];

    Matrix4x4();

    // Set this matrix as an identity matrix
    void setIdentity();

    // Set this matrix as a translation matrix
    void setTranslation(float x, float y, float z);

    // Multiply this matrix by another matrix (matrix multiplication)
    Matrix4x4 multiply(Matrix4x4 multiplicant);


    // Set this matrix as a scaling matrix
    void setScale(float scaleX, float scaleY, float scaleZ);


    // Set this matrix as a rotation matrix around the Z-axis
    void setRotationZ(float angle);
};