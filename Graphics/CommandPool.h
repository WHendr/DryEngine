#ifndef DRY_GRAPHICS_COMMANDPOOLS_HPP
#define DRY_GRAPHICS_COMMANDPOOLS_HPP

#include "Dry_SDL.h"
#include "PhysicalDevice.h"
#include <LogicalDevice.h>

namespace Dry::Graphics
{

class CommandPool
{
public:
	CommandPool(PhysicalDevice& physicalDevice, LogicalDevice& logicalDevice);
	~CommandPool();

	LogicalDevice& r_LogicDevice;
	VkCommandPool commandPool;
};

}

#endif // !DRY_GRAPHICS_COMMANDPOOLS_HPP
