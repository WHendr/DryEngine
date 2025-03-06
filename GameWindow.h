#ifndef DRY_GAME_WINDOW_HPP
#define DRY_GAME_WINDOW_HPP

#include "Dry_SDL.h"
#include <string>
#include <optional>

//
//struct SwapChainSupportDetails {
//	VkSurfaceCapabilitiesKHR capabilities;
//	std::vector<VkSurfaceFormatKHR> formats;
//	std::vector<VkPresentModeKHR> presentModes;
//};

namespace Dry
{
	// Game Window
	///
class GameWindow
{
public:
	GameWindow();
	~GameWindow();

	SDL_Window* window = nullptr;

private:
	void acquireNextFrame();
	void present();
	bool shouldKeepRunning();

	// Eventually replace voids with error codes
	void createRenderingWindow();
	void cleanup();

	std::string name;
	//WindowObject* windowParam;
	char padding[7];
};

}
#endif // !DRY_GAME_WINDOW_HPP

