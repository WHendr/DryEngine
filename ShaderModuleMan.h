#ifndef DRY_GRAPHICS_SHADER_MODULE_MAN_H
#define DRY_GRAPHICS_SHADER_MODULE_MAN_H

#include <vector>
#include "Dry_SDL.h"
#include "LogicalDevice.h"

namespace Dry::Graphics
{

class ShaderModuleMan
{
public:
	static void create(LogicalDevice& logicDevice);
	void destroy();

	static VkShaderModule createShaderModule(std::vector<char> shaderCode);
private:
	static ShaderModuleMan* getInstance();
	ShaderModuleMan(LogicalDevice& logicalDevice);
	~ShaderModuleMan();

	static ShaderModuleMan* pos_Instance;
	LogicalDevice& r_logicalDevice;

};

}

#endif // !DRY_GRAPHICS_SHADER_MODULE_MAN_H