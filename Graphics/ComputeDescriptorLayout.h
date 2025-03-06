#ifndef DRY_GRAPHICS_COMPUTE_DESCRIPTOR_LAYOUT_HPP
#define DRY_GRAPHICS_COMPUTE_DESCRIPTOR_LAYOUT_HPP

#include "LogicalDevice.h"
namespace Dry::Graphics
{

class ComputeDescriptorLayout
{
public:
	ComputeDescriptorLayout(LogicalDevice& device);
	~ComputeDescriptorLayout();

	LogicalDevice& r_LogicalDevice;
	VkDescriptorSetLayout computeDescriptorSetLayout;
};

}
#endif // !DRY_GRAPHICS_COMPUTE_DESCRIPTOR_LAYOUT_HPP