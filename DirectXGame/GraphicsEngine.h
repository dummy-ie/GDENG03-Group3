#pragma once

#include <d3d11.h>
#include "Prerequisites.h"
#include "RenderSystem.h"

class GraphicsEngine
{
public:
	static GraphicsEngine* get();
	static void initialize();
	static void destroy();

	RenderSystem* getRenderSystem() const;

private:
	GraphicsEngine();
	~GraphicsEngine();
	GraphicsEngine(GraphicsEngine const&);
	GraphicsEngine& operator=(GraphicsEngine const&) {}
	static GraphicsEngine* sharedInstance;

	bool init();
	bool release() const;

	RenderSystem* renderSystem = nullptr;
};

