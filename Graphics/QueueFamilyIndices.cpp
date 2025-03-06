#include "QueueFamilyIndices.h"


namespace Dry::Graphics
{
    bool QueueFamilyIndices::isComplete()
    {
        return graphicsAndComputeFamily.has_value() && presentFamily.has_value();
    }
}