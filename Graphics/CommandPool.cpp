#include "CommandPool.h"
#include <QueueFamilyMan.h>

namespace Dry::Graphics
{
	CommandPool::CommandPool(PhysicalDevice& physicalDevice, LogicalDevice& logicalDevice)
		: r_LogicDevice(logicalDevice)
	{
		QueueFamilyIndices queueFamilyIndices = QueueFamilyMan::findQueueFamilies(physicalDevice.physicalDevice);

		VkCommandPoolCreateInfo poolInfo{};
		poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
		poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsAndComputeFamily.value();

		if (vkCreateCommandPool(logicalDevice.device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
			throw std::runtime_error("failed to create graphics command pool!");
		}
	}

	CommandPool::~CommandPool()
	{
		vkDestroyCommandPool(r_LogicDevice.device, commandPool, nullptr);
	}

}
