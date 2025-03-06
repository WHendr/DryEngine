#pragma once

#include "Dry_SDL.h"
#include "LogicalDevice.h"

namespace Dry::Graphics
{

class UniformBuffers
{
public:
	struct UniformBufferObject {
		float deltaTime = 1.0f;
	};
	
	UniformBuffers(LogicalDevice& logicalDevice);
	~UniformBuffers();

	void update(uint32_t currentImage);

	LogicalDevice& r_LogicalDevice;
	std::vector<VkBuffer> uniformBuffers;
	std::vector<VkDeviceMemory> uniformBuffersMemory;
	std::vector<void*> uniformBuffersMapped;
};

}