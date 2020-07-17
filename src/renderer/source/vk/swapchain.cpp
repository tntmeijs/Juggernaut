#include "vk/swapchain.hpp"
#include "vk/device.hpp"
#include "vk/queue_families.hpp"
#include "vk/window_surface.hpp"

#include <algorithm>

using namespace jnt;

VulkanSwapchain::VulkanSwapchain(std::uint32_t width, std::uint32_t height) :
	Width(width),
	Height(height),
	Swapchain(VK_NULL_HANDLE)
{}

bool VulkanSwapchain::SwapchainSupportOk(const VulkanSwapchainSupportDetails& details)
{
	return (!details.formats.empty() && !details.presentModes.empty());
}

VulkanSwapchainSupportDetails VulkanSwapchain::QuerySwapchainSupport(const VkPhysicalDevice& physicalDevice, const VkSurfaceKHR& surface)
{
	VulkanSwapchainSupportDetails details;

	/************************************************************************/
	/* Surface capabilities                                                 */
	/************************************************************************/
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &details.capabilities);

	/************************************************************************/
	/* Surface formats                                                      */
	/************************************************************************/
	std::uint32_t formatCount = 0;
	vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, nullptr);

	if (formatCount > 0)
	{
		details.formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, details.formats.data());
	}

	/************************************************************************/
	/* Surface present modes                                                */
	/************************************************************************/
	std::uint32_t presentModeCount = 0;
	vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, nullptr);

	if (presentModeCount > 0)
	{
		details.presentModes.resize(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, details.presentModes.data());
	}

	return details;
}

bool VulkanSwapchain::Create(const VulkanDevice& device, const VulkanWindowSurface& windowSurface)
{
	VulkanSwapchainSupportDetails supportDetails = QuerySwapchainSupport(device.GetGPU(), windowSurface.Get());

	SwapchainSurfaceFormat			= ChooseSwapchainSurfaceFormat(supportDetails);
	SwapchainExtent					= ChooseSwapchainExtent(supportDetails);
	VkPresentModeKHR presentMode	= ChooseSwapchainPresentMode(supportDetails);

	// Request enough images for the swapchain
	std::uint32_t swapchainImageCount = supportDetails.capabilities.minImageCount + 1;
	if (supportDetails.capabilities.maxImageCount > 0 && swapchainImageCount > supportDetails.capabilities.maxImageCount)
	{
		swapchainImageCount = supportDetails.capabilities.maxImageCount;
	}

	// Create info
	VkSwapchainCreateInfoKHR createInfo	= {};
	createInfo.sType					= VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.surface					= windowSurface.Get();

	// Create info swapchain images
	{
		createInfo.minImageCount	= swapchainImageCount;
		createInfo.imageFormat		= SwapchainSurfaceFormat.format;
		createInfo.imageColorSpace	= SwapchainSurfaceFormat.colorSpace;
		createInfo.imageExtent		= SwapchainExtent;
		createInfo.imageArrayLayers	= 1;
		createInfo.imageUsage		= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	}

	// Create info queue families
	{
		std::uint32_t graphicsIndex = device.GetQueueFamilies().GetGraphicsFamilyIndex();
		std::uint32_t presentIndex = device.GetQueueFamilies().GetPresentationFamilyIndex();

		std::uint32_t queueFamilyIndices[] = { graphicsIndex, presentIndex };

		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	
		// Graphics and present queue indices are different, overwrite image sharing mode
		if (graphicsIndex != presentIndex)
		{
			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = (sizeof(queueFamilyIndices) / sizeof(queueFamilyIndices[0]));
			createInfo.pQueueFamilyIndices = queueFamilyIndices;
		}
	}

	// Create info miscellaneous options
	{
		createInfo.preTransform = supportDetails.capabilities.currentTransform;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode = presentMode;
		createInfo.clipped = VK_TRUE;
		createInfo.oldSwapchain = VK_NULL_HANDLE;
	}

	// Create the swapchain object
	if (vkCreateSwapchainKHR(device.Get(), &createInfo, nullptr, &Swapchain) != VK_SUCCESS)
	{
		return false;
	}

	// Swapchain creation successful, retrieve the images that back the swapchain
	vkGetSwapchainImagesKHR(device.Get(), Swapchain, &swapchainImageCount, nullptr);
	SwapchainImages.resize(swapchainImageCount);
	vkGetSwapchainImagesKHR(device.Get(), Swapchain, &swapchainImageCount, SwapchainImages.data());

	return true;
}

void VulkanSwapchain::Destroy(const VulkanDevice& device) const
{
	vkDestroySwapchainKHR(device.Get(), Swapchain, nullptr);
}

VkSurfaceFormatKHR VulkanSwapchain::ChooseSwapchainSurfaceFormat(const VulkanSwapchainSupportDetails& details) const
{
	// Check if the most ideal color format (SRGB) is supported
	for (const auto& formatInfo : details.formats)
	{
		if (formatInfo.format == VK_FORMAT_B8G8R8A8_SRGB && formatInfo.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
		{
			return formatInfo;
		}
	}

	// SRGB not supported, use whatever format is at the front of the list
	return details.formats[0];
}

VkPresentModeKHR VulkanSwapchain::ChooseSwapchainPresentMode(const VulkanSwapchainSupportDetails& details) const
{
	for (const auto& presentMode : details.presentModes)
	{
		// Always prefer mailbox over the other modes
		if (presentMode == VK_PRESENT_MODE_MAILBOX_KHR)
		{
			return presentMode;
		}
	}

	// Guaranteed to be available
	return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D VulkanSwapchain::ChooseSwapchainExtent(const VulkanSwapchainSupportDetails& details) const
{
	if (details.capabilities.currentExtent.width != std::numeric_limits<std::uint32_t>::max())
	{
		// Allowed to use the current extent's resolution
		return details.capabilities.currentExtent;
	}
	
	// Calculate the best matching output resolution
	VkExtent2D actualExtent = { Width, Height };
	actualExtent.width = std::max(details.capabilities.minImageExtent.width, std::min(details.capabilities.maxImageExtent.width, actualExtent.width));
	actualExtent.height = std::max(details.capabilities.minImageExtent.height, std::min(details.capabilities.maxImageExtent.height, actualExtent.height));

	return actualExtent;
}
