#include "vk/vk_image_view.hpp"
#include "vk/vk_device.hpp"
#include "vk/vk_convert.hpp"

using namespace jnt;

VulkanImageView::VulkanImageView() :
	ImageView(VK_NULL_HANDLE)
{}

VulkanImageView::~VulkanImageView()
{}

bool VulkanImageView::Create(const VulkanDevice& device, const VkImage& image, const VulkanImageViewInfo& info)
{
	VkImageViewCreateInfo createInfo = {};
	createInfo.components = {
		VK_COMPONENT_SWIZZLE_IDENTITY,	// Red
		VK_COMPONENT_SWIZZLE_IDENTITY,	// Green
		VK_COMPONENT_SWIZZLE_IDENTITY,	// Blue
		VK_COMPONENT_SWIZZLE_IDENTITY	// Alpha
	};
	createInfo.format							= info.Format;
	createInfo.image							= image;
	createInfo.sType							= VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	createInfo.subresourceRange.aspectMask		= JuggernautToVulkan(info.Usage);
	createInfo.subresourceRange.baseArrayLayer	= info.ArrayLayer;
	createInfo.subresourceRange.baseMipLevel	= info.MipLevel;
	createInfo.subresourceRange.layerCount		= info.LayerCount;
	createInfo.subresourceRange.levelCount		= info.LevelCount;
	createInfo.viewType							= JuggernautToVulkan(info.Type);

	return (vkCreateImageView(device.Get(), &createInfo, nullptr, &ImageView) == VK_SUCCESS);
}

void VulkanImageView::Destroy(const VulkanDevice& device) const
{
	vkDestroyImageView(device.Get(), ImageView, nullptr);
}
