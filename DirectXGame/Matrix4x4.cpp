#include "Matrix4x4.h"

Matrix4x4::Matrix4x4()
{
    this->setIdentity();
}

void Matrix4x4::setIdentity()
{

    // Clear all values to 0
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            m[i][j] = 0;

    // Set diagonal to 1
    m[0][0] = 1;
    m[1][1] = 1;
    m[2][2] = 1;
    m[3][3] = 1;
}

void Matrix4x4::setTranslation(float x, float y, float z)
{
    this->setIdentity(); // Start with an identity matrix

    m[3][0] = x;
    m[3][1] = y;
    m[3][2] = z;
}

Matrix4x4 Matrix4x4::multiply(Matrix4x4 multiplicant)
{
    Matrix4x4 result;

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            result.m[i][j] = this->m[i][0] * multiplicant.m[0][j] +
                this->m[i][1] * multiplicant.m[1][j] +
                this->m[i][2] * multiplicant.m[2][j] +
                this->m[i][3] * multiplicant.m[3][j];
        }
    }

    return result;
}

void Matrix4x4::setScale(float scaleX, float scaleY, float scaleZ)
{
    setIdentity(); // Start with an identity matrix

    m[0][0] = scaleX;
    m[1][1] = scaleY;
    m[2][2] = scaleZ;
}

void Matrix4x4::setRotationZ(float angle)
{
    setIdentity(); // Start with an identity matrix

    float cosAngle = cosf(angle);
    float sinAngle = sinf(angle);

    m[0][0] = cosAngle;
    m[0][1] = -sinAngle;
    m[1][0] = sinAngle;
    m[1][1] = cosAngle;
}
