#ifndef DRY_GRAPHICS_INSTANCE
#define DRY_GRAPHICS_INSTANCE

#include "Dry_SDL.h"
namespace Dry::Graphics
{
	class Instance
	{
	public:
		Instance();
		~Instance();

		bool checkValidationLayerSupport();
		void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
		std::vector<const char*> getRequiredExtensions();

		int count_extensions;
		const char** SDL_extensions;
		VkInstance instance;
		VkDebugUtilsMessengerEXT debugMessenger;
	};
}


#endif // !DRY_GRAPHICS_INSTANCE