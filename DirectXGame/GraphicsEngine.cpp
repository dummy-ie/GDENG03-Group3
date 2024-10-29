#include "GraphicsEngine.h"

#include <d3dcompiler.h>

#include "LogUtils.h"

GraphicsEngine* GraphicsEngine::sharedInstance = nullptr;


GraphicsEngine::GraphicsEngine()
= default;

GraphicsEngine::~GraphicsEngine()
= default;

GraphicsEngine::GraphicsEngine(GraphicsEngine const&)
{}

bool GraphicsEngine::init()
{
	renderSystem = new RenderSystem();
	renderSystem->init();
	return true;
}

bool GraphicsEngine::release() const
{
	renderSystem->release();
	delete renderSystem;

	return true;
}

GraphicsEngine* GraphicsEngine::get()
{
	// if (!sharedInstance)
	// sharedInstance = new GraphicsEngine();
	return sharedInstance;
}

void GraphicsEngine::initialize()
{
	sharedInstance = new GraphicsEngine();
	sharedInstance->init();
}

void GraphicsEngine::destroy()
{
	if (sharedInstance != nullptr)
		sharedInstance->release();

	delete sharedInstance;
}

RenderSystem* GraphicsEngine::getRenderSystem() const
{
	return renderSystem;
}
