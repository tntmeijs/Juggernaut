#include "vk/extensions.hpp"
#include "vk/instance.hpp"
#include "vk/validation_layers.hpp"

#include <iostream>

using namespace jnt;

VulkanInstance::VulkanInstance(std::string_view applicationName, std::string_view engineName) :
	ApplicationName(applicationName),
	EngineName(engineName),
	Instance(nullptr)
{
}

bool VulkanInstance::Create(const VulkanExtensions& extensions, const VulkanValidationLayers& validationLayers)
{
	if (!extensions.AllExtensionsAvailable())
	{
		std::cerr << "Not all required extensions are available on this system." << std::endl;
		return false;
	}

	if (!validationLayers.AllValidationLayersAvailable())
	{
		std::cerr << "Not all required validation layers are available on this system." << std::endl;
		return false;
	}

	std::vector<const char*> extensionNames			= extensions.GetExtensions();
	std::vector<const char*> validationLayerNames	= validationLayers.GetValidationLayers();

	VkApplicationInfo appInfo		= ConstructApplicationInfo();
	VkInstanceCreateInfo createInfo	= ConstructInstanceCreateInfo(extensionNames, validationLayerNames);

	createInfo.pApplicationInfo = &appInfo;

	return (vkCreateInstance(&createInfo, nullptr, &Instance) == VK_SUCCESS);
}

void VulkanInstance::Destroy() const
{
	vkDestroyInstance(Instance, nullptr);
}

VkApplicationInfo VulkanInstance::ConstructApplicationInfo() const
{
	VkApplicationInfo appInfo	= {};
	appInfo.apiVersion			= VK_API_VERSION_1_2;
	appInfo.applicationVersion	= VK_MAKE_VERSION(0, 1, 0);
	appInfo.engineVersion		= VK_MAKE_VERSION(0, 1, 0);
	appInfo.pApplicationName	= ApplicationName.c_str();
	appInfo.pEngineName			= EngineName.c_str();
	appInfo.sType				= VK_STRUCTURE_TYPE_APPLICATION_INFO;

	return appInfo;
}

VkInstanceCreateInfo VulkanInstance::ConstructInstanceCreateInfo(const std::vector<const char*>& extensions, const std::vector<const char*>& validationLayers) const
{
	VkInstanceCreateInfo createInfo		= {};
	createInfo.enabledExtensionCount	= static_cast<uint32_t>(extensions.size());
	createInfo.enabledLayerCount		= static_cast<uint32_t>(validationLayers.size());
	createInfo.ppEnabledExtensionNames	= extensions.data();
	createInfo.ppEnabledLayerNames		= validationLayers.data();
	createInfo.sType					= VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

	return createInfo;
}
