#ifndef DRY_GRAPHICS_SWAPCHAIN_HPP
#define DRY_GRAPHICS_SWAPCHAIN_HPP

#include "Surface.h"
#include "PhysicalDevice.h"
#include "LogicalDevice.h"

namespace Dry::Graphics
{

class SwapChain
{
public:
	SwapChain(PhysicalDevice& physicalDevice, Surface& surface, LogicalDevice& device, GameWindow& gameWindow);
	~SwapChain();
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	LogicalDevice& r_LogicDevice;
	GameWindow& r_GameWindow;
	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;
};

}
#endif // !DRY_GRAPHICS_SWAPCHAIN_HPP