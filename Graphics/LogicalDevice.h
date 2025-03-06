#ifndef DRY_GRAPHICS_LOGICAL_DEVICE_HPP
#define DRY_GRAPHICS_LOGICAL_DEVICE_HPP

#include "PhysicalDevice.h"

namespace Dry::Graphics
{

class LogicalDevice
{
public:
	LogicalDevice(PhysicalDevice& physicalDevice);
	~LogicalDevice();

	VkDevice device;

	VkQueue graphicsQueue;
	VkQueue computeQueue;
	VkQueue presentQueue;
};

}
#endif // !DRY_GRAPHICS_LOGICAL_DEVICE_HPP
