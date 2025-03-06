#ifndef DRY_GRAPHICS_COMMANDBUFFERS_HPP
#define DRY_GRAPHICS_COMMANDBUFFERS_HPP

#include <vector>
#include "Dry_SDL.h"
#include "LogicalDevice.h"
#include "CommandPool.h"

namespace Dry::Graphics
{

class CommandBuffers
{
public:
	CommandBuffers(LogicalDevice& logicDevice, CommandPool& commandPool);

	std::vector<VkCommandBuffer> commandBuffers;
	std::vector<VkCommandBuffer> computeCommandBuffers;
};

}

#endif // !DRY_GRAPHICS_COMMANDBUFFERS_HPP