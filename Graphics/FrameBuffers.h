#ifndef DRY_GRAPHICS_FRAME_BUFFERS
#define DRY_GRAPHICS_FRAME_BUFFERS

#include "LogicalDevice.h"
#include "ImageViews.h"
#include "RenderPass.h"
#include "SwapChain.h"

namespace Dry::Graphics
{

class FrameBuffers
{
public:
	FrameBuffers(LogicalDevice& logicDevice, ImageViews& imageViews, RenderPass& renderPass, SwapChain& swapChain);
	~FrameBuffers();

	LogicalDevice& r_LogicDevice;
	std::vector<VkFramebuffer> swapChainFramebuffers;
};

}

#endif // !DRY_GRAPHICS_FRAME_BUFFERS