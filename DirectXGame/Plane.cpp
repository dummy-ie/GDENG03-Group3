#include "Plane.h"


Plane::Plane(std::wstring name, RECT windowBounds) : GameObject(name), m_vs(nullptr), m_ps(nullptr), m_vb(nullptr), m_cb(nullptr), m_ib(nullptr)
{
    this->init(GraphicsEngine::getInstance()->getD3DDevice());
    this->setScale(3.0f, 3.0f, 3.0f);
    this->setPosition(1, -1, 1);
    this->setRotation(-0.6f, 0.0f, 0.0f);
}

Plane::~Plane()
{}

void Plane::init(ID3D11Device* device)
{
    GraphicsEngine* graphEngine = GraphicsEngine::getInstance();

    //set to quad for vertex list
    vertex vertex_list[] =
    {
        { Vector3D(-1.5f, -1.5f, -1.5f), Vector3D(1,1,1),  Vector3D(0,1,0) },    // POS1
        { Vector3D(-1.5f, 1.5f, 1.5f),  Vector3D(1,1,1),  Vector3D(0,1,1) },   // POS2
        { Vector3D(1.5f, -1.5f,-1.5f),  Vector3D(1,1,1),  Vector3D(1,0,0) },  // POS3
        { Vector3D(1.5f, 1.5f, 1.5f),   Vector3D(1,1,1),  Vector3D(0,0,1) }  // POS4
    };

    m_vb = graphEngine->createVertexBuffer();
    UINT size_list = ARRAYSIZE(vertex_list);

    /*unsigned int index_list[] =
    {
            //FRONT SIDE
          0,1,2, 1,3,2,

          //BACK SIDE
          4,5,6, 6,5,7,

    };

    m_ib = graphEngine->createIndexBuffer();
    UINT size_index_list = ARRAYSIZE(index_list);*/

    //m_ib->load(index_list, size_index_list);

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

    CBData cc;
    cc.m_time = 0;

    m_cb = graphEngine->createConstantBuffer();
    m_cb->load(&cc, sizeof(CBData));
}

void Plane::update(float deltaTime, RECT windowBounds)
{
    this->draw(windowBounds.right - windowBounds.left, windowBounds.bottom - windowBounds.top, deltaTime, m_vs, m_ps);
}

void Plane::draw(int width, int height, float deltaTime, VertexShader* vertexShader, PixelShader* pixelShader)
{
    GraphicsEngine* graphEngine = GraphicsEngine::getInstance();
    DeviceContext* deviceContext = graphEngine->getImmediateDeviceContext();

    CBData cc = {};

    m_delta_pos += m_speed * deltaTime;
    if (m_delta_pos > 1.0f)
        m_delta_pos = 0;
    else
        this->m_delta_pos += deltaTime;

    Matrix4x4 temp;

    
   //this->localRotation.m_x += m_speed * deltaTime / 0.55f;
   //this->localRotation.m_y += m_speed * deltaTime / 0.55f;
   //this->localRotation.m_z += m_speed * deltaTime / 0.55f;
   

    Matrix4x4 allMatrix; allMatrix.setIdentity();
    Matrix4x4 translationMatrix; translationMatrix.setIdentity(); translationMatrix.setTranslation(this->getLocalPosition());
    Matrix4x4 scaleMatrix; scaleMatrix.setIdentity(); scaleMatrix.setScale(this->getLocalScale());
    Vector3D rotation = this->getLocalRotation();
    Matrix4x4 zMatrix; zMatrix.setIdentity(); zMatrix.setRotationZ(rotation.m_z);
    Matrix4x4 xMatrix; xMatrix.setIdentity(); xMatrix.setRotationX(rotation.m_x);
    Matrix4x4 yMatrix; yMatrix.setIdentity(); yMatrix.setRotationY(rotation.m_y);

    allMatrix *= scaleMatrix;
    allMatrix *= zMatrix;
    allMatrix *= yMatrix;
    allMatrix *= xMatrix;
    allMatrix *= translationMatrix;
    cc.m_world = allMatrix;

    /*
    Matrix4x4 rotMatrix; rotMatrix.setIdentity();
    yMatrix *= xMatrix;
    zMatrix *= yMatrix;
    rotMatrix *= zMatrix;
    scaleMatrix *= rotMatrix;
    allMatrix *= scaleMatrix;
    allMatrix *= translationMatrix;
    cc.m_world = allMatrix;*/

    Matrix4x4 cameraMatrix = SceneCameraHandler::getInstance()->getSceneCameraViewMatrix();
    cc.m_view = cameraMatrix;
    //cc.m_view.setIdentity();

    //cc.m_view.setIdentity();

    /*cc.m_proj.setOrthoLH
    (
        (width) / 300.0f,
        (height) / 300.0f,
        -4.0f,
        4.0f
    );*/

    //cc.m_world.setIdentity();
    float aspecRatio = (float)width / (float)height;
    cc.m_proj.setPerspectiveFovLH(1.57f, aspecRatio, 0.1f, 1000.0f);
    //cc.m_proj.setIdentity();

    m_cb->update(graphEngine->getImmediateDeviceContext(), &cc);

    deviceContext->setConstantBuffer(m_vs, m_cb);
    deviceContext->setConstantBuffer(m_ps, m_cb);


    // Set the vertex and pixel shaders
    deviceContext->setVertexShader(m_vs);
    deviceContext->setPixelShader(m_ps);

    // Set the vertex buffer and draw
    deviceContext->setVertexBuffer(m_vb);

    // use drawTriangleStrip instead, ignore index buffer
    deviceContext->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
}

void Plane::setAnimSpeed(float speed)
{
    this->m_speed = speed;
}

bool Plane::release()
{
    if (m_vb) m_vb->release();
    if (m_cb) m_cb->release();
    if (m_vs) m_vs->release();
    if (m_ps) m_ps->release();
    delete this;
    return true;
}


