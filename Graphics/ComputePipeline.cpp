#include "ComputePipeline.h"
#include "File.h"
#include "ShaderModuleMan.h"

namespace Dry::Graphics
{
	ComputePipeline::ComputePipeline(LogicalDevice& logicDevice, ComputeDescriptorLayout& compDescLayout)
        : logicalDevice(logicalDevice)
	{
        auto computeShaderCode = Dry::File::File::readFile("shaders/comp.spv");

        VkShaderModule computeShaderModule = ShaderModuleMan::createShaderModule(computeShaderCode);

        VkPipelineShaderStageCreateInfo computeShaderStageInfo{};
        computeShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        computeShaderStageInfo.stage = VK_SHADER_STAGE_COMPUTE_BIT;
        computeShaderStageInfo.module = computeShaderModule;
        computeShaderStageInfo.pName = "main";

        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = 1;
        pipelineLayoutInfo.pSetLayouts = &compDescLayout.computeDescriptorSetLayout;

        if (vkCreatePipelineLayout(logicDevice.device, &pipelineLayoutInfo, nullptr, &computePipelineLayout) != VK_SUCCESS) {
            throw std::runtime_error("failed to create compute pipeline layout!");
        }

        VkComputePipelineCreateInfo pipelineInfo{};
        pipelineInfo.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
        pipelineInfo.layout = computePipelineLayout;
        pipelineInfo.stage = computeShaderStageInfo;

        if (vkCreateComputePipelines(logicDevice.device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &computePipeline) != VK_SUCCESS) {
            throw std::runtime_error("failed to create compute pipeline!");
        }

        vkDestroyShaderModule(logicDevice.device, computeShaderModule, nullptr);
	}

	ComputePipeline::~ComputePipeline()
	{
        vkDestroyPipeline(logicalDevice.device, computePipeline, nullptr);
        vkDestroyPipelineLayout(logicalDevice.device, computePipelineLayout, nullptr);
	}
}