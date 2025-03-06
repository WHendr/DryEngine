#ifndef DRY_GRAPHICS_IMAGEVIEWS_HPP
#define DRY_GRAPHICS_IMAGEVIEWS_HPP

#include "Dry_SDL.h"
#include "SwapChain.h"
#include "LogicalDevice.h"

namespace Dry::Graphics
{

class ImageViews
{
public:
	ImageViews(SwapChain& swapChain, LogicalDevice& logicalDevice);
	~ImageViews();

	LogicalDevice& r_LogicDevice;
	std::vector<VkImageView> swapChainImageViews;
};

}
#endif // !DRY_GRAPHICS_IMAGEVIEWS_HPP