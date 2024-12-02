#include "AppWindow.h"

#include "GameObjectManager.h"
#include "MeshManager.h"
#include <reactphysics3d/reactphysics3d.h>

#include "ActionHistory.h"
#include "BaseComponentSystem.h"
#include "EngineBackend.h"
#include "FileUtils.h"
#include "PhysicsSystem.h"
#include "Renderer3D.h"
#include "ShaderLibrary.h"
#include "ViewportScreen.h"

namespace gdeng03
{
	AppWindow* AppWindow::sharedInstance = nullptr;

	AppWindow* AppWindow::get()
	{
		if (!sharedInstance)
			sharedInstance = new AppWindow();

		return sharedInstance;
	}

	AppWindow::AppWindow()
		= default;

	AppWindow::~AppWindow()
	{
		Window::~Window();
		delete sharedInstance;
	}

	void AppWindow::onKeyDown(const int key)
	{
		// if (!CameraManager::get()->activeCamera)
		// 	return;

		switch (key)
		{
		case VK_ESCAPE:
		{
			LogUtils::log(this, "Exiting application");
			this->windowIsRunning = false;
			//exit(0);
			break;
		}
		default:
		{
			break;
		}
		}
	}

	void AppWindow::onKeyUp(const int key)
	{
		switch (key)
		{
			//case 'W':
			//{
			//	LogUtils::log(this, "Pressed W!");
			//	break;
			//}
		case VK_SPACE:
		{
			// float randsize = randrange_float(0.1f, 1.0f);
			// Vec2 size = { randsize, randsize };
			// Vector3D pos = { randrange_float(-0.8f, 0.8f), randrange_float(-0.8f, 0.8f), randrange_float(-0.8f, 0.8f) };
			//
			// std::cout << "position: " << pos << std::endl;
			// circleVector.emplace_back(size, pos);
			//circleVector.emplace_back();
			break;
		}
		default:
		{
			break;
		}
		}
	}

	void AppWindow::onCreate()
	{
		Window::onCreate();

		// initialize and get instance of 
		ShaderLibrary* shaderLib = ShaderLibrary::get();
		RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();

		UIManager::initialize(this->windowHandle);

		const RECT rc = this->getClientWindowRect();
		swapChain = GraphicsEngine::get()->getRenderSystem()->createSwapChain(this->windowHandle, rc.right - rc.left, rc.bottom - rc.top);

		InputSystem::get()->addListener(this);

		// camera moved to viewportscreen
		//CameraManager::get()->addSceneCamera(std::make_shared<SceneCamera>("Camera", false, rc));
		//CameraManager::get()->getActiveSceneCamera()->setLocalPosition({ 0.0f, 5.0f, -20.0f });

		this->solidState = renderSystem->createRasterizerState(D3D11_FILL_SOLID, D3D11_CULL_BACK);

		// mainMaterial = std::make_shared<Material>(L"PixelShader.hlsl");
		// //mainMaterial->samplerState = GraphicsEngine::get()->getRenderSystem()->createSamplerState();
		// UIManager::get()->mainMaterial = mainMaterial;


		// GameObjectPtr cube = std::make_shared<GameObject>("Cube");
		//
		// MeshPtr cubeMesh = GraphicsEngine::get()->getMeshManager()->createMeshFromPrimitiveType(PrimitiveType::CUBE);
		// cube->attachComponent(new Renderer3D(cube.get(), cubeMesh));
		// GameObjectManager::get()->addObject(cube);
		//
		// GameObjectPtr cube2 = std::make_shared<GameObject>("Cube2");
		//
		// cube2->attachComponent(new Renderer3D(cube2.get(), cubeMesh));
		// cube2->setLocalPosition({ 0, 2, 0 });
		//
		// GameObjectManager::get()->addObject(cube2);
		//
		// GameObjectPtr cube3 = std::make_shared<GameObject>("Cube3");
		//
		// cube3->attachComponent(new Renderer3D(cube3.get(), cubeMesh));
		// cube3->setLocalPosition({ 0, 4, 0 });
		//
		// GameObjectManager::get()->addObject(cube3);
		//
		// cube->attachChild(cube2);
		// cube2->attachChild(cube3);
	}

	void AppWindow::draw(int width, int height, EFillMode fillMode)
	{
		const DeviceContextPtr context = GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext();

		//CBEditor cbData;
		switch (fillMode)
		{
		default:
			context->setRasterizerState(solidState);
			//cbData.wireframe = false;
			break;
			// case WIREFRAME:
			// 	context->setRasterizerState(wireframeState);
			// 	cbData.wireframe = true;
			// 	break;
			// case SOLID_WIREFRAME:
			// 	context->setRasterizerState(solidState);
			// 	this->draw(width, height, SOLID);
			// 	context->setRasterizerState(wireframeState);
			// 	cbData.wireframe = true;
			// 	break;
		}

		//context->setConstantBuffer(constantBuffer, 2);
		//this->constantBuffer->update(context, &cbData);

		GameObjectManager::get()->drawAll(width, height);
	}

	void AppWindow::onUpdate()
	{
		//LogUtils::log(this, "Updating window");
		Window::onUpdate();
		//LogUtils::log(this, "Updating input system");
		InputSystem::get()->update();

		ticks += EngineTime::getDeltaTime() * 1.0f;

		//LogUtils::log(this, "Setting shaders");
		// GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(vertexShader);
		// GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setGeometryShader(geometryShader);
		// GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(pixelShader);

		//LogUtils::log(this, "Clear render target");
		GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->clearRenderTargetColor(
			this->swapChain,
			0.3f,
			0.3f,
			0.3f,
			1.f);

		const auto& [left, top, right, bottom] = this->getClientWindowRect();
		GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setViewportSize(right - left, bottom - top);

		EngineBackend* backend = EngineBackend::get();
		if (backend->getMode() == EngineBackend::EditorMode::PLAY)
		{
			//GameObjectManager::get()->setPhysics(true);
			GameObjectManager::get()->updateAll(EngineTime::getDeltaTime());
			BaseComponentSystem::get()->getPhysicsSystem()->updateAllComponents();
		}
		else if (backend->getMode() == EngineBackend::EditorMode::EDITOR)
		{
			//GameObjectManager::get()->setPhysics(false);
			GameObjectManager::get()->updateAll(EngineTime::getDeltaTime());
			BaseComponentSystem::get()->getPhysicsSystem()->updateAllComponentsWithoutWorld();
		}
		else if (backend->getMode() == EngineBackend::EditorMode::PAUSED)
		{
			if (backend->insideFrameStep())
			{
				GameObjectManager::get()->updateAll(EngineTime::getDeltaTime());
				BaseComponentSystem::get()->getPhysicsSystem()->updateAllComponents();
				backend->endFrameStep();
			}
		}

		UIManager::get()->draw();

		if (UIManager::resizeWidth != 0 && UIManager::resizeHeight != 0)
		{
			swapChain->cleanRenderTarget();
			swapChain->resizeBuffers(0, UIManager::resizeWidth, UIManager::resizeHeight);
			UIManager::resizeWidth = UIManager::resizeHeight = 0;
			swapChain->createRenderTarget();
		}

		swapChain->present(true);
	}

	void AppWindow::onFocus()
	{
		Window::onFocus();
		InputSystem::get()->setEnabled(true);
	}

	void AppWindow::onKillFocus()
	{
		Window::onKillFocus();
		InputSystem::get()->setEnabled(false);
	}

	void AppWindow::onDestroy()
	{
		Window::onDestroy();

		//vertexBuffer->release();
		// swapChain->release();
		// vertexShader->release();
		// pixelShader->release();


		//GraphicsEngine::get()->getRenderSystem()->release();
	}

	SwapChain* AppWindow::getSwapChain() const
	{
		return swapChain.get();
	}
}
