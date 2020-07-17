#include "vk/vk_window_surface.hpp"
#include "vk/vk_instance.hpp"

using namespace jnt;

/************************************************************************/
/* Windows platform support                                             */
/************************************************************************/
#if _WINDOWS
bool VulkanWindowSurface::Create(const VulkanInstance& instance, HWND windowHandle)
{
	VkWin32SurfaceCreateInfoKHR createInfo	= {};
	createInfo.hinstance					= GetModuleHandle(nullptr);
	createInfo.hwnd							= windowHandle;
	createInfo.sType						= VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;

	return (vkCreateWin32SurfaceKHR(instance.Get(), &createInfo, nullptr, &Surface) == VK_SUCCESS);
}
#endif

void VulkanWindowSurface::Destroy(const VulkanInstance& instance) const
{
	vkDestroySurfaceKHR(instance.Get(), Surface, nullptr);
}

const VkSurfaceKHR& VulkanWindowSurface::Get() const
{
	return Surface;
}
