#include "UniformBuffers.h"
#include "Dry_SDL.h"

#include "GraphicsConstants.h"
#include "BufferCreator.h"

namespace Dry::Graphics
{

    float lastFrameTime = 0.0f;

UniformBuffers::UniformBuffers(LogicalDevice& logicalDevice)
    : r_LogicalDevice(logicalDevice)
{
    VkDeviceSize bufferSize = sizeof(UniformBufferObject);

    uniformBuffers.resize(MAX_FRAMES_IN_FLIGHT);
    uniformBuffersMemory.resize(MAX_FRAMES_IN_FLIGHT);
    uniformBuffersMapped.resize(MAX_FRAMES_IN_FLIGHT);

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        BufferCreator::createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffers[i], uniformBuffersMemory[i]);

        vkMapMemory(logicalDevice.device, uniformBuffersMemory[i], 0, bufferSize, 0, &uniformBuffersMapped[i]);
    }
}

UniformBuffers::~UniformBuffers()
{
    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        vkDestroyBuffer(r_LogicalDevice.device, uniformBuffers[i], nullptr);
        vkFreeMemory(r_LogicalDevice.device, uniformBuffersMemory[i], nullptr);
    }
}

void UniformBuffers::update(uint32_t currentImage)
{
    UniformBufferObject ubo{};
    ubo.deltaTime = lastFrameTime * 2.0f;

    memcpy(uniformBuffersMapped[currentImage], &ubo, sizeof(ubo));
}

}