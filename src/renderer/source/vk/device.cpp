#include "vk/device.hpp"
#include "vk/instance.hpp"
#include "utility/console_output.hpp"

#include <map>
#include <string>
#include <vector>

using namespace jnt;

bool VulkanDevice::CreatePhysical(const VulkanInstance& instance)
{
	/************************************************************************/
	/* Enumerate physical devices                                           */
	/************************************************************************/
	uint32_t physicalDeviceCount = 0;
	vkEnumeratePhysicalDevices(instance.Get(), &physicalDeviceCount, nullptr);

	if (physicalDeviceCount == 0)
	{
		ConsoleOutput::Error("No physical devices found.");
		return false;
	}

	std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
	vkEnumeratePhysicalDevices(instance.Get(), &physicalDeviceCount, physicalDevices.data());

	ConsoleOutput::Info("Found " + std::to_string(physicalDevices.size()) + " physical device(s):");

	/************************************************************************/
	/* Sort devices from best to worst                                      */
	/************************************************************************/
	std::multimap<uint64_t, VkPhysicalDevice> deviceScores;
	for (const auto& physicalDevice : physicalDevices)
	{
		uint64_t score = 0;
		VkPhysicalDeviceProperties deviceProperties		= {};
		VkPhysicalDeviceFeatures deviceFeatures			= {};
		VkPhysicalDeviceMemoryProperties deviceMemory	= {};

		vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);
		vkGetPhysicalDeviceFeatures(physicalDevice, &deviceFeatures);
		vkGetPhysicalDeviceMemoryProperties(physicalDevice, &deviceMemory);

		// Print generic device information to the console
		ConsoleOutput::Info("  - " + std::string(deviceProperties.deviceName));

		// Prefer a discrete GPU
		switch (deviceProperties.deviceType)
		{
			case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
				score += 10000;
				break;
			case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
				score += 5000;
				break;
			case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
				score += 2500;
				break;
			case VK_PHYSICAL_DEVICE_TYPE_CPU:
				score += 1000;
				break;
		}

		// Prefer high VRAM
		score += deviceMemory.memoryHeaps[0].size;

		// Save this score and the device that belongs to it
		deviceScores.insert(std::make_pair(score, physicalDevice));
	}

	/************************************************************************/
	/* Select the best physical device                                      */
	/************************************************************************/
	if (deviceScores.rbegin()->first > 0)
	{
		// Found a suitable physical device
		PhysicalDevice = deviceScores.rbegin()->second;
		return true;
	}

	// No suitable physical devices found
	return false;
}

void VulkanDevice::Destroy() const
{}
