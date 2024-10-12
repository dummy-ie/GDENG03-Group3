#include "Circle.h"




Circle::Circle(float posX, float posY, float posZ) : m_vb(nullptr), m_cb(nullptr), m_vs(nullptr), m_ps(nullptr) //m_samplerState(nullptr), m_texture(nullptr)
{
    // Randomly assign initial position within the screen bounds
    this->position1[0] = static_cast<float>(rand()) / RAND_MAX;  // X range [0, 1]
    this->position1[1] = static_cast<float>(rand()) / RAND_MAX;  // Y range [0, 1]
    this->position1[2] = 0.0f;
    this->radius = 0.15f;
    randomizeVelocity();
   
}

// Assign a random velocity for the screensaver effect


void Circle::randomizeVelocity()
{
    // Random velocity between -0.005 and 0.005 in both X and Y directions
    this->velocity.x = (static_cast<float>(rand()) / RAND_MAX + 1.0f) * 0.5f;
    this->velocity.y = (static_cast<float>(rand()) / RAND_MAX + 1.0f) * 0.5f;
    this->velocity.z = 0.0f;  // No movement in Z-axis
}


Circle::~Circle()
{
}

void Circle::init(ID3D11Device* device)
{

    const int numberofVertices = 36;  // Adjusted to 36 to form a circle
    vertex vertices[numberofVertices];

    // Center vertex
    vertices[0].position = { 0.0f, 0.0f, 0.0f };
    vertices[0].position1 = { 0.0f + this->position1[0], 0.0f + this->position1[1], 0.0f };
    vertices[0].color = { 1.0f, 1.0f, 0.0f };  // Center color
    vertices[0].color1 = { 1.0f, 1.0f, 0.0f };  // Center color

    // Generate circle vertices
    for (int i = 1; i < numberofVertices; i++)
    {
        float t = 2 * 3.14159265359 * (i - 1) / (numberofVertices - 2);  // Adjust the angle for each segment
        vertices[i].position = { radius * cos(t), this->radius * sin(t), 0.0f };
        vertices[i].position1 = { radius * cos(t) + this->position1[0], radius * sin(t) + this->position1[1], 0.0f };
        vertices[i].color = { 1.0f, 1.0f, 0.0f };  // Same color for simplicity
        vertices[i].color1 = { 1.0f, 1.0f, 0.0f };  // Same color for simplicity
    }

    // Load shaders
    GraphicsEngine* graphEngine = GraphicsEngine::getInstance();
    void* shader_byte_code = nullptr;
    size_t shader_size = 0;

    // Create vertex buffer for the circle
    m_vb = graphEngine->createVertexBuffer();

    // Compile and set vertex shader
    if (!graphEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &shader_size)) {
        return; // Handle shader compilation failure
    }
    m_vs = graphEngine->createVertexShader(shader_byte_code, shader_size);
    m_vb->load(vertices, sizeof(vertex), numberofVertices, shader_byte_code, shader_size);
    graphEngine->releaseCompiledShader();

    // Compile and set pixel shader
    if (!graphEngine->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &shader_size)) {
        return; // Handle shader compilation failure
    }
    m_ps = graphEngine->createPixelShader(shader_byte_code, shader_size);
    graphEngine->releaseCompiledShader();

    this->cc.m_angle = 0;
    this->cc.new_position = { this->velocity.x, this->velocity.y, 0.0f };

    m_cb = GraphicsEngine::getInstance()->createConstantBuffer();
    m_cb->load(&cc, sizeof(constant));
}

void Circle::updateMovement(float deltaTime, RECT windowBounds)
{
    // Update position based on velocity
    position1[0] += velocity.x * deltaTime;
    position1[1] += velocity.y * deltaTime;

    // Check for boundary collisions
    if (position1[0] - radius <= windowBounds.left || position1[0] + radius >= windowBounds.right)
    {
        // Reverse X velocity (bounce horizontally)
        this->velocity.x = -this->velocity.x;
        setNewRandomDestination();
    }

    if (position1[1] - radius <= windowBounds.top || position1[1] + radius >= windowBounds.bottom)
    {
        // Reverse Y velocity (bounce vertically)
        this->velocity.y = -this->velocity.y;
        setNewRandomDestination();
    }
}

void Circle::setNewRandomDestination()
{
    // Set a new random velocity with a limit to avoid going out of bounds quickly
    this->velocity.x = (rand() % 100 - 50) / 100.0f; // Keep values smaller to slow movement
    this->velocity.y = (rand() % 100 - 50) / 100.0f;

    cc.new_position = { this->velocity.x, this->velocity.y, 0.0f };

    this->position1[0] += this->velocity.x;
    this->position1[1] += this->velocity.y;

    vertex vertices[36];

    // Center vertex
    vertices[0].position = { 0.0f, 0.0f, 0.0f };
    vertices[0].position1 = { 0.0f + this->position1[0], 0.0f + this->position1[1], 0.0f };
    vertices[0].color = { 1.0f, 1.0f, 0.0f };  // Center color
    vertices[0].color1 = { 1.0f, 1.0f, 0.0f };  // Center color

    // Generate circle vertices
    for (int i = 1; i < 36; i++)
    {
        float t = 2 * 3.14159265359 * (i - 1) / (36 - 2);  // Adjust the angle for each segment
        vertices[i].position = { radius * cos(t), this->radius * sin(t), 0.0f };
        vertices[i].position1 = { radius * cos(t) + this->position1[0], radius * sin(t) + this->position1[1], 0.0f };
        vertices[i].color = { 1.0f, 1.0f, 0.0f };  // Same color for simplicity
        vertices[i].color1 = { 1.0f, 1.0f, 0.0f };  // Same color for simplicity
    }


    GraphicsEngine* graphEngine = GraphicsEngine::getInstance();
    void* shader_byte_code = nullptr;
    size_t shader_size = 0;

    // Create vertex buffer for the circle
    m_vb = graphEngine->createVertexBuffer();

    // Compile and set vertex shader
    if (!graphEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &shader_size)) {
        return; // Handle shader compilation failure
    }
    m_vs = graphEngine->createVertexShader(shader_byte_code, shader_size);
    m_vb->load(vertices, sizeof(vertex), 36, shader_byte_code, shader_size);
    graphEngine->releaseCompiledShader();


}



void Circle::render(float m_delta_time)
{

    GraphicsEngine* graphEngine = GraphicsEngine::getInstance();
    DeviceContext* deviceContext = graphEngine->getImmediateDeviceContext();

    m_speed += 2.0f * m_delta_time;
    cc.m_angle = m_speed;
    cc.new_position.x += this->velocity.x;
    cc.new_position.y += this->velocity.y;

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

bool Circle::release()
{
    if (m_vb) m_vb->release();
    if (m_cb) m_cb->release();
    if (m_vs) m_vs->release();
    if (m_ps) m_ps->release();
    delete this;
    return true;
}