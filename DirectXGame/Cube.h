#pragma once
#include "GraphicsEngine.h"
#include "GameObject.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "IndexBuffer.h"
#include "DeviceContext.h"
#include "Matrix4x4.h"
#include "WICTextureLoader.h"
#include <string>

struct vertex
{
    Vector3D position;
    Vector3D color;
    Vector3D color1;
};


__declspec(align(16))
struct constant
{
    Matrix4x4 m_world;
    Matrix4x4 m_view;
    Matrix4x4 m_proj;
    unsigned int m_time;
};

class Cube : GameObject
{
public:
    Cube(std::wstring name);
    ~Cube();

    void init(ID3D11Device* device);
    void update(float deltaTime, RECT windowBounds) override;
    void draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader) override;
    void setAnimSpeed(float speed);
    void updateQuadPosition(float m_delta_time, RECT windowBounds);
    bool release();

private:
    float ticks = 0.0f;
    float m_delta_pos = 0.0f;
    float m_delta_scale = 0.0f;
    float m_delta_rot = 0.0f;
    float m_speed = 1.0f;
    VertexBuffer* m_vb;
    ConstantBuffer* m_cb;
    IndexBuffer* m_ib;
    VertexShader* m_vs;
    PixelShader* m_ps;
    //ID3D11ShaderResourceView* m_texture;
    //ID3D11SamplerState* m_samplerState;

};


