#include "Cube.h"

Cube::Cube(float x, float y, float z, float r_x, float r_y, float r_z, float s_x, float s_y, float s_z, std::wstring name, RECT windowBounds) : GameObject(name), m_vs(nullptr), m_ps(nullptr), m_vb(nullptr), m_cb(nullptr), m_ib(nullptr) //m_samplerState(nullptr), m_texture(nullptr)
{
    this->init(GraphicsEngine::getInstance()->getD3DDevice());
    this->setScale(s_x ,s_y, s_z);
    // Randomize position within screen bounds
    //float randomX = (float)(rand() % 1000)/1000.0f * (windowBounds.right - windowBounds.left) / 300.0f;
    //float randomY = (float)(rand() % 1000)/1000.0f * (windowBounds.bottom - windowBounds.top) / 300.0f; 
    //   
    //float randomX = (float)(rand() % 1000) / 1000.0f * 10.0f - 5.0f; // X in range [-2, 2]
    //float randomY = (float)(rand() % 1000) / 1000.0f * 10.0f - 5.0f; // Y in range [-2, 2]
    //float randomZ = (float)(rand() % 1000) / 1000.0f * 10.0f - 5.0f; // Z in range [-2, 2]


    this->setPosition(x, y, z);
    this->setRotation(r_x, r_y, r_z);
    
    this->m_speed = 1.0f;
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
        {Vector3D(-1.0f,-1.0f,-1.0f), Vector3D(1,0,1),    Vector3D(0.2f,0,0) },
        {Vector3D(-1.0f,1.0f,-1.0f),  Vector3D(1,0,1),    Vector3D(0.2f,0.2f,0) },
        { Vector3D(1.0f,1.0f,-1.0f),  Vector3D(1,1,1),    Vector3D(0.2f,0.2f,0) },
        { Vector3D(1.0f,-1.0f,-1.0f), Vector3D(1,1,1),    Vector3D(0.2f,0,0) },

        //BACK FACE
        { Vector3D(1.0f,-1.0f,1.0f),   Vector3D(1,0,1), Vector3D(0,0.2f,0) },
        { Vector3D(1.0f,1.0f,1.0f),    Vector3D(1,0,1),   Vector3D(0,0.2f,0.2f) },
        { Vector3D(-1.0f,1.0f,1.0f),   Vector3D(1,1,1),  Vector3D(0,0.2f,0.2f) },
        { Vector3D(-1.0f,-1.0f,1.0f),  Vector3D(1,1,1), Vector3D(0,0.2f,0) },

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


    CBData cc;
    cc.m_time = 0;

    m_cb = graphEngine->createConstantBuffer();
    m_cb->load(&cc, sizeof(CBData));



}

void Cube::update(float deltaTime, RECT windowBounds)
{
    this->draw(windowBounds.right - windowBounds.left, windowBounds.bottom - windowBounds.top, deltaTime, m_vs, m_ps);
}

void Cube::draw(int width, int height, float deltaTime, VertexShader* vertexShader, PixelShader* pixelShader)
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
    
   //this->localRotation.m_x += m_speed * deltaTime;
   //this->localRotation.m_y += m_speed * deltaTime;
   //this->localRotation.m_z += m_speed * deltaTime;
   
    
   if (this->localScale.m_x < 2.5f && this->localScale.m_z < 2.5f) {
       //this->localScale.m_x += m_speed * deltaTime;
       //this->localScale.m_y -= m_speed * deltaTime;
       //this->localScale.m_z += m_speed * deltaTime;
   }

   if (this->localScale.m_y >= 0.0f) {
       this->localScale.m_y -= m_speed * deltaTime;
   }

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

    //Set indices of the triangle to draw
    deviceContext->setIndexBuffer(m_ib);

    deviceContext->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
}

void Cube::setAnimSpeed(float speed)
{
    this->m_speed = speed;
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


