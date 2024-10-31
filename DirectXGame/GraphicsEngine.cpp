#include "GraphicsEngine.h"


GraphicsEngine* GraphicsEngine::sharedInstance = nullptr;

GraphicsEngine::GraphicsEngine()
{
	try { renderSystem = new RenderSystem(); }
	catch (...) { renderSystem = nullptr; }
}

GraphicsEngine::~GraphicsEngine()
{
	delete renderSystem;
	delete sharedInstance;
}

GraphicsEngine* GraphicsEngine::get()
{
	if (!sharedInstance)
		sharedInstance = new GraphicsEngine();

	return sharedInstance;
}

void GraphicsEngine::create()
{
}

void GraphicsEngine::release()
{
}

RenderSystem* GraphicsEngine::getRenderSystem() const
{
	return renderSystem;
}
