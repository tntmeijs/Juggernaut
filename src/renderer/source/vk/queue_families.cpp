#include "vk/queue_families.hpp"
#include "utility/console_output.hpp"

#include <vector>

using namespace jnt;

void VulkanQueueFamilies::Find(const VkPhysicalDevice& physicalDevice)
{
	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

	if (queueFamilyCount == 0)
	{
		ConsoleOutput::Error("No queue families found.");
	}

	std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilyProperties.data());

	// Find queue indices for all queues
	uint32_t index = 0;
	for (const auto& queueFamily : queueFamilyProperties)
	{
		if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			// Found a graphics queue
			GraphicsFamilyIndex = index;
		}

		// All queue indices have been found
		if (IsComplete())
		{
			break;
		}

		++index;
	}
}

bool VulkanQueueFamilies::IsComplete() const
{
	return GraphicsFamilyIndex.has_value();
}
