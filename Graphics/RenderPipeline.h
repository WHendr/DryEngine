#ifndef DRY_GRAPHICS_RENDERPIPELINE_HPP
#define DRY_GRAPHICS_RENDERPIPELINE_HPP

#include "Dry_SDL.h"
#include "LogicalDevice.h"
#include "RenderPass.h"


namespace Dry::Graphics
{

class RenderPipeline
{
public:
	RenderPipeline(LogicalDevice& logicalDevice, RenderPass& renderPass);
	~RenderPipeline();

	VkShaderModule createShaderModule(const std::vector<char>& code);
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;
	LogicalDevice& logicalDevice;

};

}

#endif // !DRY_GRAPHICS_RENDERPIPELINE_HPP