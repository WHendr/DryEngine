#ifndef DRY_GRAPHICS_DESCRIPTORPOOL_HPP
#define DRY_GRAPHICS_DESCRIPTORPOOL_HPP

#include "LogicalDevice.h"

namespace Dry::Graphics
{

class DescriptorPool
{
public:
	DescriptorPool(LogicalDevice& logicDevice);
	~DescriptorPool();

	LogicalDevice& r_LogicalDevice;
	VkDescriptorPool descriptorPool;
};

}

#endif // !DRY_GRAPHICS_DESCRIPTORPOOL_HPP