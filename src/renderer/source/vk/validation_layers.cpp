#include "vk/validation_layers.hpp"

#include "vulkan/vulkan.h"

#include <algorithm>
#include <iostream>

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
	}
#endif
}

bool jnt::VulkanValidationLayers::AllValidationLayersAvailable() const
{
	// Release mode does not have any validation layers
#if NDEBUG
	std::cout << "[INFO] No validation layers will be used in release mode." << std::endl;
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

		std::cout << (found ? "[SUCCESS] Found" : "[FATAL] Missing") << " required validation layer: " << layerName << std::endl;
	}

	return (layersFound == ValidationLayerNames.size());
}

const std::vector<const char*>& jnt::VulkanValidationLayers::GetValidationLayers() const
{
	return ValidationLayerNames;
}
