#include "Viewport.h"

#include <exception>

#include "RenderSystem.h"
#include "DeviceContext.h"
#include "LogUtils.h"
#include "RasterizerState.h"

namespace gdeng03
{
	Viewport::Viewport(RenderSystem* system, FLOAT topLeftX, FLOAT topLeftY, FLOAT width, FLOAT height, FLOAT minDepth, FLOAT maxDepth) : m_system(system)
	{
		viewport = {};

		setPosition(topLeftX, topLeftY);
		setSize(width, height);
		setDepth(minDepth, maxDepth);

		LogUtils::log(this, "Initialized");
	}

	Viewport::~Viewport()
	{
	}

	void Viewport::setPosition(FLOAT topLeftX, FLOAT topLeftY)
	{
		viewport.TopLeftX = topLeftX;
		viewport.TopLeftY = topLeftY;
	}

	void Viewport::setSize(FLOAT width, FLOAT height)
	{
		viewport.Width = width;
		viewport.Height = height;
	}

	void Viewport::setDepth(FLOAT minDepth, FLOAT maxDepth)
	{
		viewport.MinDepth = minDepth;
		viewport.MaxDepth = maxDepth;
	}
}