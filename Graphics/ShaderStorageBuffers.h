#ifndef DRY_GRAPHICS_SHADERSTORAGEBUFFERS_HPP
#define DRY_GRAPHICS_SHADERSTORAGEBUFFERS_HPP

#include "Dry_SDL.h"
#include <LogicalDevice.h>

namespace Dry::Graphics
{

class ShaderStorageBuffers
{
public:
	ShaderStorageBuffers(LogicalDevice& device);
	~ShaderStorageBuffers();

	LogicalDevice& r_LogicalDevice;
	std::vector<VkBuffer> shaderStorageBuffers;
	std::vector<VkDeviceMemory> shaderStorageBuffersMemory;
};

}
#endif // !DRY_GRAPHICS_SHADERSTORAGEBUFFERS_HPP
