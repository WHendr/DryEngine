#include "Engine.h"

namespace Dry
{
	Engine::Engine(int WindowHeight, int WindowWidth)
		: po_GraphicsEngine(new Graphics::GraphicsEngine())
	{
	}

	void Engine::run()
	{
		po_GraphicsEngine->run();
	}
}