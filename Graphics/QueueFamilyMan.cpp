#include "QueueFamilyMan.h"

namespace Dry::Graphics
{
    QueueFamilyMan* QueueFamilyMan::pos_Instance = nullptr;

    void QueueFamilyMan::Create(Surface& surface)
    {
        pos_Instance = new QueueFamilyMan(surface);
    }

    QueueFamilyIndices QueueFamilyMan::findQueueFamilies(VkPhysicalDevice device)
    {
        QueueFamilyMan& instance = QueueFamilyMan::GetInstance();

        QueueFamilyIndices indices;
    
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
    
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
    
        int i = 0;
        for (const auto& queueFamily : queueFamilies) {
            if ((queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) && (queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT)) {
                indices.graphicsAndComputeFamily = i;
            }
    
            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, instance.p_Surface->surface, &presentSupport);
    
            if (presentSupport) {
                indices.presentFamily = i;
            }
    
            if (indices.isComplete()) {
                break;
            }
    
            i++;
        }
    
        return indices;
    }

    QueueFamilyMan::QueueFamilyMan(Surface& surface)
    {
        this->p_Surface = &surface;
    }

    // TODO - add some error handling
    QueueFamilyMan& QueueFamilyMan::GetInstance()
    {
        return *pos_Instance;
    }

}