#include "Cube.h"

Cube::Cube(std::wstring name) : GameObject(name), m_vs(nullptr), m_ps(nullptr), m_vb(nullptr), m_cb(nullptr), m_ib(nullptr) //m_samplerState(nullptr), m_texture(nullptr)
{

    this->init(GraphicsEngine::getInstance()->getD3DDevice());
    this->setScale(0.25f, 0.25f, 0.25f);
}

Cube::~Cube()
{
}

void Cube::init(ID3D11Device* device)
{
    // Load buffers
    GraphicsEngine* graphEngine = GraphicsEngine::getInstance();

    vertex vertex_list[] =
    {
        //X - Y - Z
        //FRONT FACE
        {Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,0,0),  Vector3D(0.2f,0,0) },
        {Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,1,0), Vector3D(0.2f,0.2f,0) },
        { Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,1,0),  Vector3D(0.2f,0.2f,0) },
        { Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,0,0), Vector3D(0.2f,0,0) },

        //BACK FACE
        { Vector3D(0.5f,-0.5f,0.5f),    Vector3D(0,1,0), Vector3D(0,0.2f,0) },
        { Vector3D(0.5f,0.5f,0.5f),    Vector3D(0,1,1), Vector3D(0,0.2f,0.2f) },
        { Vector3D(-0.5f,0.5f,0.5f),   Vector3D(0,1,1),  Vector3D(0,0.2f,0.2f) },
        { Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(0,1,0), Vector3D(0,0.2f,0) }

    };

    m_vb = graphEngine->createVertexBuffer();
    UINT size_list = ARRAYSIZE(vertex_list);

    unsigned int index_list[] =
    {
        //FRONT SIDE
        0,1,2,  //FIRST TRIANGLE
        2,3,0,  //SECOND TRIANGLE
        //BACK SIDE
        4,5,6,
        6,7,4,
        //TOP SIDE
        1,6,5,
        5,2,1,
        //BOTTOM SIDE
        7,0,3,
        3,4,7,
        //RIGHT SIDE
        3,2,5,
        5,4,3,
        //LEFT SIDE
        7,6,1,
        1,0,7
    };


    m_ib = graphEngine->createIndexBuffer();
    UINT size_index_list = ARRAYSIZE(index_list);

    m_ib->load(index_list, size_index_list);

    void* shaderByteCode = nullptr;
    size_t sizeShader = 0;


    graphEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
    this->m_vs = graphEngine->createVertexShader(shaderByteCode, sizeShader);
    m_vb->load(vertex_list, sizeof(vertex), ARRAYSIZE(vertex_list), shaderByteCode, sizeShader);
    graphEngine->releaseCompiledShader();

    // Compile and set pixel shader
    graphEngine->compilePixelShader(L"PixelShader.hlsl", "psmain", &shaderByteCode, &sizeShader);
    m_ps = graphEngine->createPixelShader(shaderByteCode, sizeShader);
    graphEngine->releaseCompiledShader();


    constant cc;
    cc.m_time = 0;

    m_cb = graphEngine->createConstantBuffer();
    m_cb->load(&cc, sizeof(constant));



}

void Cube::update(float deltaTime, RECT windowBounds)
{
    this->updateQuadPosition(deltaTime, windowBounds);
    this->draw(10, 10, m_vs, m_ps);
}

void Cube::draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader)
{
    GraphicsEngine* graphEngine = GraphicsEngine::getInstance();
    DeviceContext* deviceContext = graphEngine->getImmediateDeviceContext();

    if (m_cb != nullptr) {

        deviceContext->setConstantBuffer(m_vs, m_cb);
        deviceContext->setConstantBuffer(m_ps, m_cb);
    }

    // Set the vertex and pixel shaders
    deviceContext->setVertexShader(m_vs);
    deviceContext->setPixelShader(m_ps);

    // Set the vertex buffer and draw
    deviceContext->setVertexBuffer(m_vb);

    //Set indices of the triangle to draw
    deviceContext->setIndexBuffer(m_ib);

    deviceContext->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
}

void Cube::setAnimSpeed(float speed)
{
    this->m_speed = speed;
}

void Cube::updateQuadPosition(float m_delta_time, RECT windowBounds)
{

    GraphicsEngine* graphEngine = GraphicsEngine::getInstance();

    constant cc;
    cc.m_time = ::GetTickCount();

    m_delta_pos += m_speed * m_delta_time / 10.0f;
    if (m_delta_pos > 1.0f)
        m_delta_pos = 0;

    Matrix4x4 temp;

    m_delta_scale += m_speed * m_delta_time / 0.55f;

    cc.m_world.setScale(Vector3D(1, 1, 1));

    temp.setIdentity();
    temp.setRotationZ(m_delta_scale);
    cc.m_world *= temp;

    temp.setIdentity();
    temp.setRotationY(m_delta_scale);
    cc.m_world *= temp;

    temp.setIdentity();
    temp.setRotationX(m_delta_scale);
    cc.m_world *= temp;

    temp.setIdentity();
    temp.setScale(this->localScale);
    cc.m_world *= temp;

    cc.m_view.setIdentity();
    cc.m_proj.setOrthoLH
    (
        (windowBounds.right - windowBounds.left) / 300.0f,
        (windowBounds.bottom - windowBounds.top) / 300.0f,
        -4.0f,
        4.0f
    );


    m_cb->update(graphEngine->getImmediateDeviceContext(), &cc);
}

bool Cube::release()
{
    if (m_vb) m_vb->release();
    if (m_cb) m_cb->release();
    if (m_vs) m_vs->release();
    if (m_ps) m_ps->release();
    delete this;
    return true;
}



