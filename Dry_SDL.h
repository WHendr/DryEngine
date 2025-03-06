#ifndef DRY_SDL_HPP
#define DRY_SDL_HPP

// Sdl error get ridder
#pragma warning(push)
#pragma warning(disable : 4820)
#pragma warning(disable : 4191)

#if defined(_MSC_VER)
#pragma warning (push)
//#pragma warning(disable : 4820)
#pragma warning(disable : 4514)

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_vulkan.h>

#pragma warning(pop)
#endif

// Vulkan Error get ridder
#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning(disable : 4820)
#pragma warning(disable : 4514)
#include "vulkan/vulkan.h"

#pragma warning(pop)
#endif
#include <iostream>
#include <vector>

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

#include <optional>
// Probably swap out the in lines for 

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

struct WindowObject
{
    WindowObject()
        : po_Window_(nullptr),
        instance(),
        surface(),
        po_Renderer(nullptr),
        m_WindowHeight(0),
        m_WindowWidth(0)
    {
    }

    SDL_Window*   po_Window_  = nullptr;
 
    VkInstance    instance;
    VkDebugUtilsMessengerEXT debug_messenger;// Vulkan debug output handle
    VkPhysicalDevice _chosenGPU;// GPU chosen as the default device
    VkSurfaceKHR  surface;
    SDL_Renderer* po_Renderer    = nullptr;
    uint32_t queue_count;
    VkQueueFamilyProperties* queue_props;
    uint32_t graphics_queue_node_index;
    int  m_WindowHeight = 0;
    int  m_WindowWidth  = 0;
};


enum SDL_ERROR : unsigned int
{
    COULDNT_INITIALIZE
};

#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */

inline SDL_AppResult SDL_AppInit(void** window, int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    WindowObject* winParam = (WindowObject*)*window;
    SDL_SetAppMetadata("Example Renderer Debug Texture", "1.0", "com.example.renderer-debug-text");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("examples/renderer/debug-text", 
        winParam->m_WindowWidth, winParam->m_WindowHeight, 0, 
        &winParam->po_Window_, &winParam->po_Renderer)) 
    {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

inline SDL_AppResult SDL_AppEvent(SDL_Event* event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}


inline SDL_AppResult SDL_AppIterate(void *window)
{
    WindowObject* windowParam = (WindowObject*)window;
    const int charsize = SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;

    /* as you can see from this, rendering draws over whatever was drawn before it. */
    SDL_SetRenderDrawColor(windowParam->po_Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);  /* black, full alpha */
    SDL_RenderClear(windowParam->po_Renderer);  /* start with a blank canvas. */

    SDL_SetRenderDrawColor(windowParam->po_Renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);  /* white, full alpha */
    SDL_RenderDebugText(windowParam->po_Renderer, 272, 100, "Hello world!");
    SDL_RenderDebugText(windowParam->po_Renderer, 224, 150, "This is some debug text.");

    SDL_SetRenderDrawColor(windowParam->po_Renderer, 51, 102, 255, SDL_ALPHA_OPAQUE);  /* light blue, full alpha */
    SDL_RenderDebugText(windowParam->po_Renderer, 184, 200, "You can do it in different colors.");
    SDL_SetRenderDrawColor(windowParam->po_Renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);  /* white, full alpha */

    SDL_SetRenderScale(windowParam->po_Renderer, 4.0f, 4.0f);
    SDL_RenderDebugText(windowParam->po_Renderer, 14, 65, "It can be scaled.");
    SDL_SetRenderScale(windowParam->po_Renderer, 1.0f, 1.0f);
    SDL_RenderDebugText(windowParam->po_Renderer, 64, 350, "This only does ASCII chars. So this laughing emoji won't draw: ??");

    SDL_RenderDebugTextFormat(windowParam->po_Renderer, (float)((windowParam->m_WindowWidth 
        - (charsize * 46)) / 2), 400, "(This program has been running for %" SDL_PRIu64 " seconds.)"
        , SDL_GetTicks() / 1000);

    SDL_RenderPresent(windowParam->po_Renderer);  /* put it all on the screen! */

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
inline SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    (void)appstate;
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

// Off vulkan tutorial
static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
    (void)messageSeverity;
    (void)messageType;
    (void)pCallbackData;
    (void)pUserData;
    
    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
    return VK_FALSE;
}

inline void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(instance, debugMessenger, pAllocator);
    }
}

inline VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr) {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    }
    else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

#pragma warning(pop)

#endif // !DRY_SDL_HPP
