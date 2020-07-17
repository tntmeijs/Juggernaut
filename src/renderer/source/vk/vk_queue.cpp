#include "vk/vk_queue.hpp"

using namespace jnt;

VkDeviceQueueCreateInfo VulkanQueue::Create(std::uint32_t familyIndex, std::uint32_t count, float priority)
{
	VkDeviceQueueCreateInfo createInfo	= {};
	createInfo.pQueuePriorities			= &priority;
	createInfo.queueCount				= count;
	createInfo.queueFamilyIndex			= familyIndex;
	createInfo.sType					= VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;

	return createInfo;
}

void VulkanQueue::Set(const VkQueue& queue)
{
	Queue = queue;
}

const VkQueue& VulkanQueue::Get() const
{
	return Queue;
}
