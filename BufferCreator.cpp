#include "BufferCreator.h"

namespace Dry::Graphics
{
    BufferCreator* BufferCreator::pos_Instance = nullptr;

    void BufferCreator::create(LogicalDevice& device, CommandPool& commandPool, PhysicalDevice& physicalDevice)
    {
        pos_Instance = new BufferCreator(device, commandPool, physicalDevice);
    }

    void BufferCreator::destroy()
    {
        delete pos_Instance;
    }


    void BufferCreator::copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size)
    {
        BufferCreator* instance = BufferCreator::getInstance();

        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = instance->r_commandPool.commandPool;
        allocInfo.commandBufferCount = 1;
    
        VkCommandBuffer commandBuffer;
        vkAllocateCommandBuffers(instance->r_device.device, &allocInfo, &commandBuffer);
    
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    
        vkBeginCommandBuffer(commandBuffer, &beginInfo);
    
        VkBufferCopy copyRegion{};
        copyRegion.size = size;
        vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);
    
        vkEndCommandBuffer(commandBuffer);
    
        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffer;
    
        vkQueueSubmit(instance->r_device.graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
        vkQueueWaitIdle(instance->r_device.graphicsQueue);
    
        vkFreeCommandBuffers(instance->r_device.device, instance->r_commandPool.commandPool, 1, &commandBuffer);
    }
    
    void BufferCreator::createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory)
    {
        BufferCreator* instance = BufferCreator::getInstance();

        VkBufferCreateInfo bufferInfo{};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = size;
        bufferInfo.usage = usage;
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    
        if (vkCreateBuffer(instance->r_device.device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
            throw std::runtime_error("failed to create buffer!");
        }
    
        VkMemoryRequirements memRequirements;
        vkGetBufferMemoryRequirements(instance->r_device.device, buffer, &memRequirements);
    
        VkMemoryAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;
        allocInfo.memoryTypeIndex = BufferCreator::findMemoryType(memRequirements.memoryTypeBits, properties);
    
        if (vkAllocateMemory(instance->r_device.device, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate buffer memory!");
        }
    
        vkBindBufferMemory(instance->r_device.device, buffer, bufferMemory, 0);
    }
    
    uint32_t BufferCreator::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties)
    {
        BufferCreator* instance = BufferCreator::getInstance();

        VkPhysicalDeviceMemoryProperties memProperties;
        vkGetPhysicalDeviceMemoryProperties(instance->r_physicalDevice.physicalDevice, &memProperties);
    
        for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
            if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
                return i;
            }
        }
    
        throw std::runtime_error("failed to find suitable memory type!");
    }

    BufferCreator* BufferCreator::getInstance()
    {
        return pos_Instance;
    }

    BufferCreator::BufferCreator(LogicalDevice& device, CommandPool& commandPool, PhysicalDevice& physicalDevice)
        :r_device(device),
         r_commandPool(commandPool),
         r_physicalDevice(physicalDevice)
    {
    }

    BufferCreator::~BufferCreator()
    {
    }
    
    

}