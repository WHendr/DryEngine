#ifndef DRY_GRAPHICS_QUEUE_FAMILY_INDICES
#define DRY_GRAPHICS_QUEUE_FAMILY_INDICES

#include "Dry_SDL.h"

namespace Dry::Graphics
{

struct QueueFamilyIndices
{
    bool isComplete();
    
    std::optional<uint32_t> graphicsAndComputeFamily;
    std::optional<uint32_t> presentFamily;
};

}

#endif // !DRY_GRAPHICS_QUEUE_FAMILY_INDICES