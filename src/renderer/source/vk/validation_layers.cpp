#include "vk/validation_layers.hpp"
#include "utility/console_output.hpp"

#include "vulkan/vulkan.h"

#include <algorithm>
#include <string>

using namespace jnt;

void VulkanValidationLayers::AddValidationLayer(std::string_view validationLayerName)
{
	// Do not add any validation layers to the list of validation layers when
	// not in a debug configuration
#if NDEBUG
	validationLayerName;	// Suppress "unreferenced formal parameter"
#else
	auto result = std::find(ValidationLayerNames.begin(), ValidationLayerNames.end(), validationLayerName);
	if (result == ValidationLayerNames.end())
	{
		ValidationLayerNames.push_back(validationLayerName.data());
		ConsoleOutput::Info("Validation layer " + std::string(validationLayerName) + " has been added to the list.");
	}
	else
	{
		ConsoleOutput::Warning("Validation layer " + std::string(validationLayerName) + " has already been added to the list.");
	}
#endif
}

bool jnt::VulkanValidationLayers::AllValidationLayersAvailable() const
{
	// Release mode does not have any validation layers
#if NDEBUG
	return true;
#endif

	// Debug mode does use validation layers
	uint32_t layerCount = 0;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
	std::vector<VkLayerProperties> layerProperties(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, layerProperties.data());

	uint32_t layersFound = 0;
	for (const auto& layerName : ValidationLayerNames)
	{
		bool found = false;
		for (const auto& layerProperty : layerProperties)
		{
			if (strcmp(layerName, layerProperty.layerName) == 0)
			{
				found = true;
				++layersFound;
				break;
			}
		}

		if (found)
		{
			std::string message = "Found required validation layer: " + std::string(layerName);
			ConsoleOutput::Info(message);
		}
		else
		{
			std::string message = "Missing required validation layer: " + std::string(layerName);
			ConsoleOutput::Error(message);
		}
	}

	return (layersFound == ValidationLayerNames.size());
}

const std::vector<const char*>& jnt::VulkanValidationLayers::GetValidationLayers() const
{
	return ValidationLayerNames;
}
