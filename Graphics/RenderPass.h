#ifndef DRY_GRAPHICS_RENDERPASS_HPP
#define DRY_GRAPHICS_RENDERPASS_HPP

#include "Dry_SDL.h"
#include <SwapChain.h>
#include "LogicalDevice.h"

namespace Dry::Graphics
{

class RenderPass
{
public:
	RenderPass(SwapChain& swapChain, LogicalDevice& logicalDevice);
	~RenderPass();

	LogicalDevice& r_LogicalDevice;
	VkRenderPass renderPass;
};

}
#endif // !DRY_GRAPHICS_RENDERPASS_HPP