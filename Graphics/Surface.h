#ifndef DRY_GRAPHICS_SURFACE_HPP
#define DRY_GRAPHICS_SURFACE_HPP

#include "Instance.h"
#include "GameWindow.h"

namespace Dry::Graphics
{

class Surface
{
public:
	Surface(GameWindow& window, Instance& instance);
	~Surface();

	void createSurface(SDL_Window* window, VkInstance& instance);

	//void createSurface(SDL_Window* window, VkInstance instance);

	Instance& r_Instance;
	VkSurfaceKHR surface;
};

}
#endif // !DRY_GRAPHICS_SURFACE_HPP