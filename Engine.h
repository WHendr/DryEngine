#ifndef DRY_ENGINE_HPP
#define DRY_ENGINE_HPP

#include "GameWindow.h"
#include <GraphicsEngine.h>

namespace Dry
{

class Engine
{
public:
	Engine(int WindowHeight, int WindowWidth);

	void run();
private:

	Graphics::GraphicsEngine* po_GraphicsEngine;
};

}

#endif // !DRY_ENGINE_HPP

