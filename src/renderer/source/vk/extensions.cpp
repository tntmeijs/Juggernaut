#include "vk/extensions.hpp"
#include "utility/console_output.hpp"

#include "vulkan/vulkan.h"
#include "GLFW/glfw3.h"

#include <algorithm>
#include <string>

using namespace jnt;

void VulkanExtensions::AddExtension(std::string_view extensionName)
{
	auto result = std::find(Extensions.begin(), Extensions.end(), extensionName);
	if (result == Extensions.end())
	{
		Extensions.push_back(extensionName.data());
	}
}

bool VulkanExtensions::AllExtensionsAvailable() const
{
	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
	std::vector<VkExtensionProperties> extensionProperties(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensionProperties.data());

	std::vector<const char*> requiredExtensions = GetExtensions();

	uint32_t extensionsFound = 0;
	for (const auto& extensionName : requiredExtensions)
	{
		bool found = false;
		for (const auto& extensionProperty : extensionProperties)
		{
			if (strcmp(extensionProperty.extensionName, extensionName) == 0)
			{
				found = true;
				++extensionsFound;
				break;
			}
		}

		if (!found)
		{
			std::string message = "Missing required extension: " + std::string(extensionName);
			ConsoleOutput::Error(message);
		}
	}
	
	return (extensionsFound == requiredExtensions.size());
}

const std::vector<const char*> VulkanExtensions::GetExtensions() const
{
	// Get all required extensions from GLFW
	std::vector<const char*> glfwExtensions = GetGLFWRequiredExtensions();

	// Reserve memory
	std::vector<const char*> merged;
	merged.reserve(Extensions.size() + glfwExtensions.size());

	// Merge the GLFW extensions and the explicitly added extensions into one list
	merged.insert(merged.end(), glfwExtensions.begin(), glfwExtensions.end());
	merged.insert(merged.end(), Extensions.begin(), Extensions.end());

	return merged;
}

std::vector<const char*> VulkanExtensions::GetGLFWRequiredExtensions() const
{
	// Get all required extensions from GLFW
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	return std::vector<const char*>(glfwExtensions, glfwExtensions + glfwExtensionCount);
}
