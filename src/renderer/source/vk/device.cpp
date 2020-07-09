#include "vk/device.hpp"
#include "vk/instance.hpp"
#include "vk/queue_families.hpp"
#include "vk/queue.hpp"
#include "vk/validation_layers.hpp"
#include "vk/window_surface.hpp"
#include "utility/console_output.hpp"

#include <map>
#include <set>
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

void VulkanDevice::FindQueueFamilies(const VulkanWindowSurface& windowSurface)
{
	if (!QueueFamilies)
	{
		QueueFamilies = new VulkanQueueFamilies();
		QueueFamilies->Find(PhysicalDevice, windowSurface.Get());

		if (QueueFamilies->IsComplete())
		{
			ConsoleOutput::Success("Found all required queue families.");
		}
		else
		{
			ConsoleOutput::Error("Unable to find all required queue families.");
		}
	}
	else
	{
		ConsoleOutput::Error("Cannot create new queue families object, one already exists.");
	}
}

bool VulkanDevice::CreateLogical(const VulkanValidationLayers& validationLayers)
{
	/************************************************************************/
	/* Create queues                                                        */
	/************************************************************************/
	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	std::set<uint32_t> uniqueQueueIndices = { QueueFamilies->GetGraphicsFamilyIndex(), QueueFamilies->GetPresentationFamilyIndex() };

	for (const uint32_t queueFamilyIndex : uniqueQueueIndices)
	{
		VkDeviceQueueCreateInfo createInfo = VulkanQueue::Create(queueFamilyIndex);
		queueCreateInfos.push_back(createInfo);
	}

	/************************************************************************/
	/* Specify used device features                                         */
	/************************************************************************/
	VkPhysicalDeviceFeatures physicalDeviceFeatures = {};

	/************************************************************************/
	/* Create a logical device                                              */
	/************************************************************************/
	std::vector<const char*> validationLayerList = validationLayers.GetValidationLayers();

	VkDeviceCreateInfo createInfo	= {};
	createInfo.enabledLayerCount	= static_cast<uint32_t>(validationLayerList.size());
	createInfo.pEnabledFeatures		= &physicalDeviceFeatures;
	createInfo.ppEnabledLayerNames	= validationLayerList.data();
	createInfo.pQueueCreateInfos	= queueCreateInfos.data();
	createInfo.queueCreateInfoCount	= static_cast<uint32_t>(queueCreateInfos.size());
	createInfo.sType				= VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

	return (vkCreateDevice(PhysicalDevice, &createInfo, nullptr, &LogicalDevice) == VK_SUCCESS);
}

void VulkanDevice::ConfigureQueueHandles()
{
	if (!GraphicsQueue)
	{
		VkQueue queue = VK_NULL_HANDLE;
		vkGetDeviceQueue(LogicalDevice, QueueFamilies->GetGraphicsFamilyIndex(), 0, &queue);

		GraphicsQueue = new VulkanQueue();
		GraphicsQueue->Set(queue);
	}
	else
	{
		ConsoleOutput::Error("Cannot create a new graphics queue object, one already exists.");
	}

	if (!PresentationQueue)
	{
		VkQueue queue = VK_NULL_HANDLE;
		vkGetDeviceQueue(LogicalDevice, QueueFamilies->GetPresentationFamilyIndex(), 0, &queue);

		PresentationQueue = new VulkanQueue();
		PresentationQueue->Set(queue);
	}
	else
	{
		ConsoleOutput::Error("Cannot create a new presentation queue object, one already exists.");
	}
}

void VulkanDevice::Destroy() const
{
	vkDestroyDevice(LogicalDevice, nullptr);

	if (QueueFamilies)
	{
		delete QueueFamilies;
	}

	if (GraphicsQueue)
	{
		delete GraphicsQueue;
	}
}

const VkPhysicalDevice& VulkanDevice::GetGPU() const
{
	return PhysicalDevice;
}

const VkDevice& VulkanDevice::Get() const
{
	return LogicalDevice;
}
