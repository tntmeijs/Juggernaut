#include "vk/vk_debug_messenger.hpp"
#include "vk/vk_extensions.hpp"
#include "vk/vk_instance.hpp"
#include "vk/vk_validation_layers.hpp"
#include "utility/console_output.hpp"

using namespace jnt;

VulkanInstance::VulkanInstance(std::string_view applicationName, std::string_view engineName) :
	ApplicationName(applicationName),
	EngineName(engineName),
	Instance(nullptr),
	DebugMessenger(nullptr)
{
}

bool VulkanInstance::Create(const VulkanExtensions& extensions, const VulkanValidationLayers& validationLayers)
{
	if (!extensions.AllExtensionsAvailable())
	{
		ConsoleOutput::Error("Not all required extensions are available on this system.");
		return false;
	}

	if (!validationLayers.AllValidationLayersAvailable())
	{
		ConsoleOutput::Error("Not all required validation layers are available on this system.");
		return false;
	}

	std::vector<const char*> extensionNames			= extensions.GetExtensions();
	std::vector<const char*> validationLayerNames	= validationLayers.GetValidationLayers();

	VkApplicationInfo appInfo		= ConstructApplicationInfo();
	VkInstanceCreateInfo createInfo	= ConstructInstanceCreateInfo(extensionNames, validationLayerNames);

	createInfo.pApplicationInfo = &appInfo;

#if !NDEBUG
	/************************************************************************/
	/* Debug messenger initialization (ALWAYS BEFORE INSTANCE CREATION)     */
	/************************************************************************/
	DebugMessenger = new VulkanDebugMessenger();
	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = DebugMessenger->Initialize();
#endif

	// Create the instance
	bool instanceResult = (vkCreateInstance(&createInfo, nullptr, &Instance) == VK_SUCCESS);

#if !NDEBUG
	/************************************************************************/
	/* Debug messenger creation (ALWAYS AFTER INSTANCE CREATION             */
	/************************************************************************/
	if (DebugMessenger->Create(Instance, debugCreateInfo))
	{
		ConsoleOutput::Success("Debug messenger created successfully.");

		// Register to any instance creation errors
		createInfo.pNext = reinterpret_cast<VkDebugUtilsMessengerCreateInfoEXT*>(&debugCreateInfo);
	}
	else
	{
		ConsoleOutput::Error("Debug messenger creation unsuccessful.");
	}
#endif

	return instanceResult;
}

void VulkanInstance::Destroy() const
{
#if !NDEBUG
	if (DebugMessenger)
	{
		DebugMessenger->Destroy(Instance);
		delete DebugMessenger;
	}
#endif

	vkDestroyInstance(Instance, nullptr);
}

const VkInstance& VulkanInstance::Get() const
{
	return Instance;
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
