#pragma once
#include "ViewportScreen.h"
#include "UIManager.h"
#include <vector>

namespace mrlol
{
	class ViewportManager
	{
		typedef std::shared_ptr<ViewportScreen> ViewportScreenPtr;
		typedef std::vector<ViewportScreenPtr> ViewportList;

	private:
		ViewportManager();
		~ViewportManager();
		ViewportManager(const ViewportManager&);
		ViewportManager& operator=(const ViewportManager&);

	private:
		ViewportList viewportList;

	public:
		static ViewportManager* get();
		static void initialize();
		static void destroy();
		void update() const;

		void createViewport();
		void deleteViewport(const ViewportScreenPtr& viewport);
		void deleteViewport(const ViewportScreen* viewport);
		void deleteAllViewports();
		void addViewport(UIScreen* viewport);
		void setNumViewports(int count);
		ViewportList getViewports();

	private:
		static ViewportManager* sharedInstance;

	};
}