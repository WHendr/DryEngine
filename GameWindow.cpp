#include "GameWindow.h"

#include "Dry_SDL.h"

#define GLM_FORCE_RADIANS
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <chrono>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <limits>
#include <array>
#include <optional>
#include <set>
#include <random>

#include "GraphicsConstants.h"
#include <GameSettings.h>
#include "QueueFamilyMan.h"


float lastFrameTime = 0.0f;

double lastTime = 0.0f;


using namespace Dry::Graphics;

enum INIT_ERROR
{
	SDL_FAILED_TO_INIT,
	VULKAN_FAILED_TO_CREATE_INSTANCE,
	VULKAN_FAILED_TO_CREATE_SURFACE,
};

namespace Dry
{

	GameWindow::GameWindow()
	{
		SDL_Init(SDL_INIT_VIDEO);  // Initialize SDL video subsystem

		window = SDL_CreateWindow("SDL Vulkan Window",
			Dry::Graphics::WIDTH,
			Dry::Graphics::HEIGHT,
			SDL_WINDOW_VULKAN);

		if (!window)
		{
			SDL_Quit();
			throw INIT_ERROR::SDL_FAILED_TO_INIT;
		}
	}

	GameWindow::~GameWindow()
	{
		SDL_DestroyWindow(window);
		SDL_Quit();
	}
}
