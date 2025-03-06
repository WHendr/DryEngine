#ifndef COMPUTE_DESCRIPTOR_SETS_HPP
#define COMPUTE_DESCRIPTOR_SETS_HPP

#include "Dry_SDL.h"
#include "DescriptorPool.h"
#include "UniformBuffers.h"
#include "ShaderStorageBuffers.h"
#include "ComputeDescriptorLayout.h"

namespace Dry::Graphics
{

class ComputeDescriptorSets
{
public:
	ComputeDescriptorSets(LogicalDevice& logicDevice,
		ComputeDescriptorLayout& computeDescriptorSetLayout, DescriptorPool& descPool,
		UniformBuffers& uniformBuffer, ShaderStorageBuffers& shaderStorageBuffers);
	~ComputeDescriptorSets();

	LogicalDevice& r_LogicDevice;
	std::vector<VkDescriptorSet> computeDescriptorSets;
};

}

#endif // !COMPUTE_DESCRIPTOR_SETS_HPP