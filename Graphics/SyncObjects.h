#ifndef DRY_GRAPHICS_SYNC_OBJECTS_HPP
#define DRY_GRAPHICS_SYNC_OBJECTS_HPP

#include <vector>
#include "Dry_SDL.h"
#include <LogicalDevice.h>


namespace Dry::Graphics
{

class SyncObjects
{
public:
	SyncObjects(LogicalDevice& logicalDevice);
	~SyncObjects();

	LogicalDevice& r_LogicDevice;
	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkSemaphore> computeFinishedSemaphores;
	std::vector<VkFence> inFlightFences;
	std::vector<VkFence> computeInFlightFences;
};

}
#endif // !DRY_GRAPHICS_SYNC_OBJECTS_HPP
