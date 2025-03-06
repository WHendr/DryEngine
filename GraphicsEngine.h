#ifndef DRY_GRAPHICS_GRAPHICSENIGNE_H
#define DRY_GRAPHICS_GRAPHICSENIGNE_H

#include "GameWindow.h"
#include <Instance.h>
#include <DebugMessenger.h>
#include <Surface.h>
#include <PhysicalDevice.h>
#include <LogicalDevice.h>
#include <SwapChain.h>
#include <ImageViews.h>
#include <ComputeDescriptorLayout.h>
#include <RenderPass.h>
#include <RenderPipeline.h>
#include <FrameBuffers.h>
#include <ComputePipeline.h>
#include <CommandPool.h>
#include <DescriptorPool.h>
#include <UniformBuffers.h>
#include <ShaderStorageBuffers.h>
#include <ComputeDescriptorSets.h>
#include <CommandBuffers.h>
#include <SyncObjects.h>

namespace Dry::Graphics
{

class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();

	void init();
	void run();
private:
	void drawFrame();
	bool shouldKeepRunning();
	void cleanupSwapChain();

	void createRenderingWindow();
	void initVulkan();

	void recreateSwapChain();

	void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

	void recordComputeCommandBuffer(VkCommandBuffer commandBuffer);

	GameWindow* po_Window;
	Graphics::Instance* po_instance;
	Graphics::DebugMessenger* po_DebugMessenger;
	Graphics::Surface* po_Surface;
	Graphics::PhysicalDevice* po_PhysicalDevice;
	Graphics::LogicalDevice* po_LogicalDevice;
	Graphics::SwapChain* po_SwapChain;
	Graphics::ImageViews* po_ImageViews;
	Graphics::RenderPass* po_RenderPass;
	Graphics::ComputeDescriptorLayout* po_ComputeDescriporLayout;
	Graphics::RenderPipeline* po_RenderPipeline;
	Graphics::ComputePipeline* po_ComputePipeline;
	Graphics::FrameBuffers* po_FrameBuffer;
	Graphics::CommandPool* po_CommandPool;
	Graphics::ShaderStorageBuffers* po_ShaderStorageBuffers;
	Graphics::UniformBuffers* po_UniformBuffers;
	Graphics::DescriptorPool* po_DescriptorPools;
	Graphics::ComputeDescriptorSets* po_ComputeDescriptorSets;
	Graphics::CommandBuffers* po_CommandBuffers;
	Graphics::SyncObjects* po_SyncObjects;

	bool shouldRun;

};

}
#endif // !DRY_GRAPHICS_GRAPHICSENIGNE_H
