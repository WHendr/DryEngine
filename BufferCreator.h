#ifndef DRY_GRAPHICS_BUFFER_CREATOR_H
#define DRY_GRAPHICS_BUFFER_CREATOR_H

#include "Dry_SDL.h"

#include "LogicalDevice.h"
#include "PhysicalDevice.h"
#include "CommandPool.h"

namespace Dry::Graphics
{

class BufferCreator
{
public:
	static void create(LogicalDevice& device, CommandPool& commandPool, PhysicalDevice& physicalDevice);
	static void destroy();

	static void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	static void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage,
		VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);

private:
	static uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

	static BufferCreator* getInstance();

	BufferCreator(LogicalDevice& device, CommandPool& commandPool, PhysicalDevice& physicalDevice);
	~BufferCreator();

	static BufferCreator* pos_Instance;
	LogicalDevice&  r_device;
	CommandPool&    r_commandPool;
	PhysicalDevice& r_physicalDevice;
};

}
#endif // !DRY_GRAPHICS_BUFFER_CREATOR_H