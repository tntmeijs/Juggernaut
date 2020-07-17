#include "vk/vk_debug_messenger.hpp"
#include "vk/vk_instance.hpp"
#include "utility/console_output.hpp"

using namespace jnt;

VkDebugUtilsMessengerCreateInfoEXT VulkanDebugMessenger::Initialize() const
{
	VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
	createInfo.messageSeverity	= VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createInfo.messageType		= VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	createInfo.pfnUserCallback	= ValidationLayerDebugCallback;
	createInfo.sType			= VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

	return createInfo;
}

bool VulkanDebugMessenger::Create(const VkInstance& instance, const VkDebugUtilsMessengerCreateInfoEXT& createInfo)
{
	// Attempt to load the creation extension function manually
	auto vkCreateDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"));
	if (!vkCreateDebugUtilsMessengerEXT)
	{
		ConsoleOutput::Error("Unable to load extension function: vkCreateDebugUtilsMessengerEXT.");
		return false;
	}

	return (vkCreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &DebugMessenger) == VK_SUCCESS);
}

void VulkanDebugMessenger::Destroy(const VkInstance& instance) const
{
	// Attempt to load the creation extension function manually
	auto vkDestroyDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT"));
	if (!vkDestroyDebugUtilsMessengerEXT)
	{
		ConsoleOutput::Error("Unable to load extension function: vkDestroyDebugUtilsMessengerEXT.");
		return;
	}

	vkDestroyDebugUtilsMessengerEXT(instance, DebugMessenger, nullptr);
}

VKAPI_ATTR VkBool32 VKAPI_CALL VulkanDebugMessenger::ValidationLayerDebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT severity, VkDebugUtilsMessageTypeFlagsEXT type, const VkDebugUtilsMessengerCallbackDataEXT* data, void* userData)
{
	// Suppress "unreferenced formal parameter"
	userData;
	type;

	// Handle all messages except those with a severity of "verbose" or "info"
	if (severity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
	{
		ConsoleOutput::Warning(data->pMessage);
	}
	else if (severity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
	{
		ConsoleOutput::Error(data->pMessage);
	}

	return VK_FALSE;
}
