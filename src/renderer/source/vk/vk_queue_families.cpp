#include "vk/vk_queue_families.hpp"
#include "utility/console_output.hpp"

#include <vector>

using namespace jnt;

void VulkanQueueFamilies::Find(const VkPhysicalDevice& physicalDevice, const VkSurfaceKHR& surface)
{
	std::uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

	if (queueFamilyCount == 0)
	{
		ConsoleOutput::Error("No queue families found.");
	}

	std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilyProperties.data());

	// Find queue indices for all queues
	std::uint32_t index = 0;
	for (const auto& queueFamily : queueFamilyProperties)
	{
		VkBool32 presentationSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, index, surface, &presentationSupport);

		if (presentationSupport)
		{
			// Found a presentation queue
			PresentationFamilyIndex = index;
		}

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
	return (GraphicsFamilyIndex.has_value() && PresentationFamilyIndex.has_value());
}

const std::uint32_t VulkanQueueFamilies::GetGraphicsFamilyIndex() const
{
	// The queue should always have a value by the time this function is used
	return *GraphicsFamilyIndex;
}

const std::uint32_t VulkanQueueFamilies::GetPresentationFamilyIndex() const
{
	// The queue should always have a value by the time this function is used
	return *PresentationFamilyIndex;
}
