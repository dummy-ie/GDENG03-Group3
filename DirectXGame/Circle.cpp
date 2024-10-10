#include "Circle.h"
#include "vector"
#include "list"
#define PI 3.14159265359;

Circle::Circle(float posX, float posY, float posZ) : m_vb(nullptr), m_cb(nullptr), m_vs(nullptr), m_ps(nullptr) //m_samplerState(nullptr), m_texture(nullptr)
{
	this->position1[0] = posX;
	this->position1[1] = posY;
	this->position1[2] = posZ;
}

Circle::~Circle()
{
}

void Circle::init(ID3D11Device* device)
{
    int numberofVertices = 100;
    std::list<vertex> vertices;
    float radius = 10.0f;
    
    for (int i = 0; i <= numberofVertices; i += 1)
    {
        float t = 3.14159265359 * 2 * i / 100;
        vertices.push_back({ radius * cos(t), radius * -sin(t), 0.0f });
        vertices[(int)i + 1].position1 = { radius * cos(t), radius * -sin(t), 0.0f };
        vertices[(int)i + 1].color = { 1.0, 1.0, 0.0f };
        vertices[(int)i + 1].color1 = { 1.0, 1.0, 0.0f };
     }


    // Load shaders
    GraphicsEngine* graphEngine = GraphicsEngine::getInstance();
    void* shader_byte_code = nullptr;
    size_t shader_size = 0;

    // Create vertex buffer for the quad
    m_vb = graphEngine->createVertexBuffer();

    // Compile and set vertex shader
    graphEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &shader_size);
    m_vs = graphEngine->createVertexShader(shader_byte_code, shader_size);
    m_vb->load(vertices, sizeof(vertex), ARRAYSIZE(vertices), shader_byte_code, shader_size);
    graphEngine->releaseCompiledShader();

    // Compile and set pixel shader
    graphEngine->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &shader_size);
    m_ps = graphEngine->createPixelShader(shader_byte_code, shader_size);
    graphEngine->releaseCompiledShader();

    constant cc;
    cc.m_angle = 0;

    m_cb = GraphicsEngine::getInstance()->createConstantBuffer();
    m_cb->load(&cc, sizeof(constant));
}

void Circle::render(float m_delta_time)
{
    GraphicsEngine* graphEngine = GraphicsEngine::getInstance();
    DeviceContext* deviceContext = graphEngine->getImmediateDeviceContext();

    m_angle += 1.57f * m_delta_time;
    constant cc;
    cc.m_angle = m_angle;

    m_cb->update(GraphicsEngine::getInstance()->getImmediateDeviceContext(), &cc);


    GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
    GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

    // Bind the sampler state
   //deviceContext->getContext()->PSSetSamplers(0, 1, &m_samplerState);

   /*
   // Check if m_texture is valid
   if (m_texture) {
       deviceContext->getContext()->PSSetShaderResources(0, 1, &m_texture);
   } else {
       // Handle error: Texture is not initialized
       return;
   }
   */
   // Set the vertex and pixel shaders
    deviceContext->setVertexShader(m_vs);
    deviceContext->setPixelShader(m_ps);

    // Set the vertex buffer and draw
    deviceContext->setVertexBuffer(m_vb);
    deviceContext->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
}

void Circle::release()
{
    if (m_vb) m_vb->release();
    if (m_cb) m_cb->release();
    if (m_vs) m_vs->release();
    if (m_ps) m_ps->release();
}
