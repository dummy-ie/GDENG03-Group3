#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include "Prerequisites.h"
#include "RenderSystem.h"

class GraphicsEngine
{
public:
	static GraphicsEngine* get();
	// void initialize();
	// void destroy();

	static void create();
	static void release();

	RenderSystem* getRenderSystem() const;

	GraphicsEngine(GraphicsEngine const&) = delete;
	GraphicsEngine& operator=(GraphicsEngine const&) = delete;
	GraphicsEngine(GraphicsEngine&& other) noexcept = delete;
	GraphicsEngine& operator=(GraphicsEngine&& other) noexcept = delete;

private:
	GraphicsEngine();
	~GraphicsEngine();

	static GraphicsEngine* sharedInstance;
	RenderSystem* renderSystem = nullptr;
};

