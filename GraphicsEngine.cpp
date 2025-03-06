#include "GraphicsEngine.h"
#include <cassert>
#include "Dry_SDL.h"
#include "QueueFamilyMan.h"
#include "GraphicsConstants.h"
#include "GameSettings.h"

#include "ShaderModuleMan.h"
#include "BufferCreator.h"

uint32_t currentFrame = 0;
bool framebufferResized = false;


namespace Dry::Graphics
{
    GraphicsEngine::GraphicsEngine()
        :shouldRun(true)
    {
        createRenderingWindow();
        initVulkan();
    }

    GraphicsEngine::~GraphicsEngine()
    {
        cleanupSwapChain();

        delete this->po_RenderPipeline;
        // render pipeline

        // compute pipeline
        delete this->po_ComputePipeline;

        // render pass
        delete this->po_RenderPass;

        // Uniform buffers
        delete this->po_UniformBuffers;

        // Descriptor Pool
        delete this->po_DescriptorPools;

        // Compute Descriptor
        delete this->po_ComputeDescriptorSets;
        delete this->po_ComputeDescriporLayout;

        // ShaderStorageBuffers
        delete this->po_ShaderStorageBuffers;

        // Sync Objects
        delete this->po_SyncObjects;

        // Command Pool
        delete this->po_CommandPool;

        // Logical Device
        delete this->po_LogicalDevice;

        // Surface
        delete this->po_Surface;
    }

    //void GraphicsEngine::init()
    //{
    //}

    void GraphicsEngine::run()
    {
        SDL_Event event;
        while (shouldKeepRunning())
        {
            while (SDL_PollEvent(&event))
            {
                if (SDL_AppEvent(&event) != SDL_APP_CONTINUE)
                {
                    shouldRun = false;
                }

                //this->acquireNextFrame();
                this->drawFrame();
                //this->present();
            }
        }
        SDL_Quit();
    }

    bool GraphicsEngine::shouldKeepRunning()
    {
        return shouldRun && SDL_AppIterate(this->po_Window->window)
            == SDL_AppResult::SDL_APP_CONTINUE;
    }

    void GraphicsEngine::cleanupSwapChain()
    {
        delete this->po_FrameBuffer;
        delete this->po_ImageViews;
        delete this->po_SwapChain;
    }

    void GraphicsEngine::createRenderingWindow()
    {
        this->po_Window = new GameWindow();
        assert(this->po_Window);
    }

    void GraphicsEngine::initVulkan()
    {
        this->po_instance = new Instance();
        assert(this->po_instance);
    
        this->po_DebugMessenger = new DebugMessenger(*this->po_instance);
        assert(this->po_DebugMessenger);
    
        this->po_Surface = new Surface(*this->po_Window, *this->po_instance);
        assert(this->po_Surface);
    
        QueueFamilyMan::Create(*this->po_Surface);
    
        this->po_PhysicalDevice = new PhysicalDevice(*this->po_instance, *this->po_Surface);
        assert(this->po_PhysicalDevice);
    
        this->po_LogicalDevice = new LogicalDevice(*this->po_PhysicalDevice);
        assert(this->po_LogicalDevice);

        ShaderModuleMan::create(*this->po_LogicalDevice);
    
        this->po_SwapChain = new SwapChain(*this->po_PhysicalDevice, *this->po_Surface, *this->po_LogicalDevice, *this->po_Window);
        assert(this->po_SwapChain);
    
        this->po_ImageViews = new ImageViews(*this->po_SwapChain, *this->po_LogicalDevice);
        assert(this->po_ImageViews);
    
        this->po_RenderPass = new RenderPass(*this->po_SwapChain, *this->po_LogicalDevice);
        assert(this->po_RenderPass);
    
        this->po_ComputeDescriporLayout = new ComputeDescriptorLayout(*this->po_LogicalDevice);
        assert(this->po_ComputeDescriporLayout);
    
        this->po_RenderPipeline = new RenderPipeline(*this->po_LogicalDevice, *this->po_RenderPass);
        assert(this->po_RenderPipeline);
    
        this->po_ComputePipeline = new ComputePipeline(*this->po_LogicalDevice, *this->po_ComputeDescriporLayout);
        assert(this->po_ComputePipeline);
    
        this->po_FrameBuffer = new FrameBuffers(*this->po_LogicalDevice, *this->po_ImageViews,
            *this->po_RenderPass, *this->po_SwapChain);
        assert(this->po_FrameBuffer);
    
        this->po_CommandPool = new CommandPool(*this->po_PhysicalDevice, *this->po_LogicalDevice);
        assert(this->po_CommandPool);

        BufferCreator::create(*this->po_LogicalDevice, *this->po_CommandPool, *this->po_PhysicalDevice);
    
        this->po_ShaderStorageBuffers = new ShaderStorageBuffers(*this->po_LogicalDevice);
        assert(this->po_ShaderStorageBuffers);
    
        this->po_UniformBuffers = new UniformBuffers(*this->po_LogicalDevice);
        assert(this->po_UniformBuffers);
    
        this->po_DescriptorPools = new DescriptorPool(*this->po_LogicalDevice);
        assert(this->po_DescriptorPools);
    
        this->po_ComputeDescriptorSets = new ComputeDescriptorSets(*this->po_LogicalDevice,
            *this->po_ComputeDescriporLayout, *this->po_DescriptorPools,
            *this->po_UniformBuffers, *this->po_ShaderStorageBuffers);
        assert(this->po_ComputeDescriptorSets);
    
        this->po_CommandBuffers = new CommandBuffers(*this->po_LogicalDevice, *this->po_CommandPool);
        assert(this->po_CommandBuffers);
    
        this->po_SyncObjects = new SyncObjects(*this->po_LogicalDevice);
        assert(this->po_SyncObjects);
    }


    void GraphicsEngine::recreateSwapChain() {
        int width = 0, height = 0;
        SDL_GetWindowSize(this->po_Window->window, &width, &height);
        while (width == 0 || height == 0) {
            SDL_GetWindowSize(this->po_Window->window, &width, &height);
            SDL_Event event;
            SDL_WaitEvent(&event);
        }

        vkDeviceWaitIdle(this->po_LogicalDevice->device);

        cleanupSwapChain();

        this->po_SwapChain = new SwapChain(*this->po_PhysicalDevice, *this->po_Surface, *this->po_LogicalDevice, *this->po_Window);
        assert(this->po_SwapChain);

        this->po_ImageViews = new ImageViews(*this->po_SwapChain, *this->po_LogicalDevice);
        assert(this->po_ImageViews);

        this->po_FrameBuffer = new FrameBuffers(*this->po_LogicalDevice, *this->po_ImageViews,
            *this->po_RenderPass, *this->po_SwapChain);
        assert(this->po_FrameBuffer);
    }

    void GraphicsEngine::recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex) {
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
            throw std::runtime_error("failed to begin recording command buffer!");
        }

        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = this->po_RenderPass->renderPass;
        renderPassInfo.framebuffer = this->po_FrameBuffer->swapChainFramebuffers[imageIndex];
        renderPassInfo.renderArea.offset = { 0, 0 };
        renderPassInfo.renderArea.extent = this->po_SwapChain->swapChainExtent;

        VkClearValue clearColor = { {{0.0f, 0.0f, 0.0f, 1.0f}} };
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;

        vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
            this->po_RenderPipeline->graphicsPipeline);

        VkViewport viewport{};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = (float)this->po_SwapChain->swapChainExtent.width;
        viewport.height = (float)this->po_SwapChain->swapChainExtent.height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;
        vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

        VkRect2D scissor{};
        scissor.offset = { 0, 0 };
        scissor.extent = this->po_SwapChain->swapChainExtent;
        vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

        VkDeviceSize offsets[] = { 0 };
        vkCmdBindVertexBuffers(commandBuffer, 0, 1,
            &this->po_ShaderStorageBuffers->shaderStorageBuffers[currentFrame], offsets);

        vkCmdDraw(commandBuffer, PARTICLE_COUNT, 1, 0, 0);

        vkCmdEndRenderPass(commandBuffer);

        if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
            throw std::runtime_error("failed to record command buffer!");
        }
    }

    void GraphicsEngine::recordComputeCommandBuffer(VkCommandBuffer commandBuffer) {
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
            throw std::runtime_error("failed to begin recording compute command buffer!");
        }

        vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE,
            this->po_ComputePipeline->computePipeline);

        vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE,
            this->po_ComputePipeline->computePipelineLayout, 0, 1,
            &this->po_ComputeDescriptorSets->computeDescriptorSets[currentFrame], 0, nullptr);

        vkCmdDispatch(commandBuffer, PARTICLE_COUNT / 256, 1, 1);

        if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
            throw std::runtime_error("failed to record compute command buffer!");
        }

    }

    void GraphicsEngine::drawFrame() {
        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

        // Compute submission        
        vkWaitForFences(this->po_LogicalDevice->device, 1,
            &this->po_SyncObjects->computeInFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

        this->po_UniformBuffers->update(currentFrame);

        vkResetFences(this->po_LogicalDevice->device, 1,
            &this->po_SyncObjects->computeInFlightFences[currentFrame]);

        vkResetCommandBuffer(this->po_CommandBuffers->computeCommandBuffers[currentFrame],
            /*VkCommandBufferResetFlagBits*/ 0);
        recordComputeCommandBuffer(this->po_CommandBuffers->computeCommandBuffers[currentFrame]);

        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &this->po_CommandBuffers->computeCommandBuffers[currentFrame];
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = &this->po_SyncObjects->computeFinishedSemaphores[currentFrame];

        if (vkQueueSubmit(this->po_LogicalDevice->computeQueue, 1, &submitInfo,
            this->po_SyncObjects->computeInFlightFences[currentFrame]) != VK_SUCCESS) {
            throw std::runtime_error("failed to submit compute command buffer!");
        };

        // Graphics submission
        vkWaitForFences(this->po_LogicalDevice->device, 1,
            &this->po_SyncObjects->inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

        uint32_t imageIndex;
        VkResult result = vkAcquireNextImageKHR(this->po_LogicalDevice->device,
            this->po_SwapChain->swapChain, UINT64_MAX,
            this->po_SyncObjects->imageAvailableSemaphores[currentFrame],
            VK_NULL_HANDLE, &imageIndex);

        if (result == VK_ERROR_OUT_OF_DATE_KHR) {
            recreateSwapChain();
            return;
        }
        else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
            throw std::runtime_error("failed to acquire swap chain image!");
        }

        vkResetFences(this->po_LogicalDevice->device, 1,
            &this->po_SyncObjects->inFlightFences[currentFrame]);

        vkResetCommandBuffer(this->po_CommandBuffers->commandBuffers[currentFrame],
            /*VkCommandBufferResetFlagBits*/ 0);
        recordCommandBuffer(this->po_CommandBuffers->commandBuffers[currentFrame],
            imageIndex);

        VkSemaphore waitSemaphores[] = { this->po_SyncObjects->computeFinishedSemaphores[currentFrame],
            this->po_SyncObjects->imageAvailableSemaphores[currentFrame] };
        VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_VERTEX_INPUT_BIT, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
        submitInfo = {};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

        submitInfo.waitSemaphoreCount = 2;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &this->po_CommandBuffers->commandBuffers[currentFrame];
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = &this->po_SyncObjects->renderFinishedSemaphores[currentFrame];

        if (vkQueueSubmit(this->po_LogicalDevice->graphicsQueue, 1, &submitInfo,
            this->po_SyncObjects->inFlightFences[currentFrame]) != VK_SUCCESS) {
            throw std::runtime_error("failed to submit draw command buffer!");
        }

        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = &this->po_SyncObjects->renderFinishedSemaphores[currentFrame];

        VkSwapchainKHR swapChains[] = { this->po_SwapChain->swapChain };
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;

        presentInfo.pImageIndices = &imageIndex;

        result = vkQueuePresentKHR(this->po_LogicalDevice->presentQueue, &presentInfo);

        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || framebufferResized) {
            framebufferResized = false;
            recreateSwapChain();
        }
        else if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to present swap chain image!");
        }

        currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
    }
}