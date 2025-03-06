#ifndef DRY_GRAPHICS_COMPUTEPIPELINE_HPP
#define DRY_GRAPHICS_COMPUTEPIPELINE_HPP

#include "Dry_SDL.h"
#include "ComputeDescriptorLayout.h"

namespace Dry::Graphics
{

class ComputePipeline
{
public:
	ComputePipeline(LogicalDevice& logicDevice, ComputeDescriptorLayout& compDescLayout);
	~ComputePipeline();

	LogicalDevice& logicalDevice;
	VkPipelineLayout computePipelineLayout;
	VkPipeline computePipeline;
};

}

#endif // !DRY_GRAPHICS_COMPUTEPIPELINE_HPP