#pragma once

#include "Dry_SDL.h"
#include <LogicalDevice.h>
#include "PhysicalDevice.h"

namespace Dry::Graphics
{

class GraphicsBufferAllocator
{

    GraphicsBufferAllocator(LogicalDevice& logicDevice, PhysicalDevice& physicalDevice);

    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage,
        VkMemoryPropertyFlags properties, VkBuffer& buffer, 
        VkDeviceMemory& bufferMemory);

    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);


private:
    VkDevice& device;
    VkPhysicalDevice& physicalDevice;
};

}
