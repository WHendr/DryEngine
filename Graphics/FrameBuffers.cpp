#include "FrameBuffers.h"

namespace Dry::Graphics
{
    FrameBuffers::FrameBuffers(LogicalDevice& logicDevice, ImageViews& imageViews,
        RenderPass & renderPass, SwapChain& swapChain)
        :r_LogicDevice(logicDevice)
    {
        swapChainFramebuffers.resize(imageViews.swapChainImageViews.size());
    
        size_t size = imageViews.swapChainImageViews.size();
        for (size_t i = 0; i < size; i++) {
            VkImageView attachments[] = {
                imageViews.swapChainImageViews[i]
            };
    
            VkFramebufferCreateInfo framebufferInfo{};
            framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            framebufferInfo.renderPass = renderPass.renderPass;
            framebufferInfo.attachmentCount = 1;
            framebufferInfo.pAttachments = attachments;
            framebufferInfo.width = swapChain.swapChainExtent.width;
            framebufferInfo.height = swapChain.swapChainExtent.height;
            framebufferInfo.layers = 1;
    
            if (vkCreateFramebuffer(logicDevice.device, &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create framebuffer!");
            }
        }
    }
    
    FrameBuffers::~FrameBuffers()
    {
        for (auto framebuffer : swapChainFramebuffers) {
            vkDestroyFramebuffer(r_LogicDevice.device, framebuffer, nullptr);
        }

    }
}