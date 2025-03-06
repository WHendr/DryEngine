#include "ShaderModuleMan.h"

namespace Dry::Graphics
{
    ShaderModuleMan* ShaderModuleMan::pos_Instance = nullptr;

void ShaderModuleMan::create(LogicalDevice& logicalDevice)
{
    pos_Instance = new ShaderModuleMan(logicalDevice);
}

void ShaderModuleMan::destroy()
{
    delete pos_Instance;
}

VkShaderModule Dry::Graphics::ShaderModuleMan::createShaderModule(std::vector<char> code)
{
    ShaderModuleMan* instance = ShaderModuleMan::getInstance();

    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

    VkShaderModule shaderModule;
    if (vkCreateShaderModule(instance->r_logicalDevice.device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
        throw std::runtime_error("failed to create shader module!");
    }

    return shaderModule;
}

ShaderModuleMan* ShaderModuleMan::getInstance()
{
    return pos_Instance;
}

ShaderModuleMan::ShaderModuleMan(LogicalDevice& logicalDevice)
    : r_logicalDevice(logicalDevice)
{
}

ShaderModuleMan::~ShaderModuleMan()
{
}

}