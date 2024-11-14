#include "GraphicsEngine.h"


GraphicsEngine* GraphicsEngine::sharedInstance = nullptr;

GraphicsEngine::GraphicsEngine()
{
	try { renderSystem = new RenderSystem(); }
	catch (...) { renderSystem = nullptr; }

	try { textureManager = new TextureManager(); }
	catch (...) { textureManager = nullptr; }
}

GraphicsEngine::~GraphicsEngine()
{
	delete renderSystem;
	delete textureManager;
	delete sharedInstance;
}

GraphicsEngine* GraphicsEngine::get()
{
	if (!sharedInstance)
		sharedInstance = new GraphicsEngine();

	return sharedInstance;
}

RenderSystem* GraphicsEngine::getRenderSystem() const
{
	return renderSystem;
}

TextureManager* GraphicsEngine::getTextureManager() const
{
	return textureManager;
}
