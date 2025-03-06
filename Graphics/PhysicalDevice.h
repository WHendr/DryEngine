#ifndef DRY_GRAPHICS_PHYSICAL_DEVICE_HPP
#define DRY_GRAPHICS_PHYSICAL_DEVICE_HPP

#include "Dry_SDL.h"
#include "Instance.h"
#include "Surface.h"

namespace Dry::Graphics
{

class PhysicalDevice
{
public:
	PhysicalDevice(Instance& instance, Surface& surface);
	~PhysicalDevice();

	void pickPhysicalDevice(VkInstance& instance);
	bool isDeviceSuitable(VkPhysicalDevice device);
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

	Surface& r_Surface;
};

}
#endif // !DRY_GRAPHICS_PHYSICAL_DEVICE_HPP
