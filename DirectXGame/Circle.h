#pragma once
#include "GraphicsEngine.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "DeviceContext.h"
#include "Quad.h"
#include <string>
#include <cmath>

class Circle
{
public:
    Circle(float posX, float posY, float posZ);
    ~Circle();

    void init(ID3D11Device* device);
    void render(float m_delta_time);
    void release();

private:
    float position1[3];
    float m_angle = 0;
    VertexBuffer* m_vb;
    ConstantBuffer* m_cb;
    VertexShader* m_vs;
    PixelShader* m_ps;
    //ID3D11ShaderResourceView* m_texture;
    //ID3D11SamplerState* m_samplerState;

};


