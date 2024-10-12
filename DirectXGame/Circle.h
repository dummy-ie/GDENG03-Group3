
#pragma once
#include "GraphicsEngine.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "DeviceContext.h"
#include "Quad.h"
#include <cmath>
#include <vector>


class Circle
{
public:
    Circle(float posX, float posY, float posZ);
    ~Circle();

    void init(ID3D11Device* device);
    void render(float m_delta_time);
    bool release();
    void updateMovement(float deltaTime, RECT windowBounds);
    void randomizeVelocity();
    void setNewRandomDestination();


private:
    float position1[3];
    float radius;
    vec3 velocity;
    float m_speed = 0;
    UINT pointsU;
    constant cc;
    VertexBuffer* m_vb;
    ConstantBuffer* m_cb;
    VertexShader* m_vs;
    PixelShader* m_ps;
};

