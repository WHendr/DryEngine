#ifndef DRY_DEBUG_MESSENGER
#define DRY_DEBUG_MESSENGER
#include "Dry_SDL.h"
#include <Instance.h>


namespace Dry::Graphics
{

class DebugMessenger
{
public:
	DebugMessenger(Instance& instance);
	~DebugMessenger();


	static void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
private:
	VkDebugUtilsMessengerEXT debugMessenger;
};

}
#endif // !DRY_DEBUG_MESSENGER
