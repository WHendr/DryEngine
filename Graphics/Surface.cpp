#include "Surface.h"

namespace Dry::Graphics
{
    Surface::Surface(GameWindow& window, Instance& instance)
        : r_Instance(instance)
    {
        this->createSurface(window.window, instance.instance);
    }

    Surface::~Surface()
    {
        vkDestroySurfaceKHR(r_Instance.instance, surface, nullptr);
    }

    void Surface::createSurface(SDL_Window* window, VkInstance& instance) {


    if (!SDL_Vulkan_CreateSurface(window, instance, nullptr, &surface)) {
        vkDestroyInstance(instance, nullptr);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
}

}