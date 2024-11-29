#include "ViewportManager.h"

namespace mrlol
{
	ViewportManager* ViewportManager::sharedInstance = nullptr;

	ViewportManager::ViewportManager()
	{
		LogUtils::log(this, "Initialized");
	}

	ViewportManager::~ViewportManager()
	{
		LogUtils::log(this, "Destroyed");
		delete sharedInstance;
	}

	ViewportManager::ViewportManager(const ViewportManager&) {}

	ViewportManager* ViewportManager::get()
	{
		if (!sharedInstance)
			sharedInstance = new ViewportManager();

		return sharedInstance;
	}

	void ViewportManager::update() const
	{
		for (const auto viewport : viewportList)
		{
			viewport->draw();
		}
	}

	void ViewportManager::createViewport()
	{
		const ViewportScreenPtr viewport = std::make_shared<ViewportScreen>(viewportList.size());
		viewportList.push_back(viewport);
		//UIManager::get()->addViewport(viewport);
	}

	void ViewportManager::deleteViewport(const ViewportScreenPtr& viewport)
	{
		int index = 0;
		for (int i = 0; i < viewportList.size(); i++)
		{
			if (viewportList[i] == viewport)
			{
				viewportList.erase(viewportList.begin() + index);
			}

			index++;
		}
		delete viewport;
	}

	void ViewportManager::deleteAllViewports()
	{
		viewportList.clear();
	}

	void ViewportManager::addViewport(UIScreen* viewport)
	{
		// const ViewportScreenPtr c_viewport = std::make_shared<ViewportScreen>(viewport);
		// viewportList.push_back(c_viewport);

	}

	void ViewportManager::setNumViewports(const int count)
	{
		while (viewportList.size() > count)
		{
			this->deleteViewport(viewportList.back());
		}

		while (viewportList.size() < count)
		{
			this->createViewport();
		}
	}

	ViewportManager::ViewportList ViewportManager::getViewports()
	{
		return viewportList;
	}
}
