#ifndef JUGGERNAUT_VK_WINDOW_SURFACE_HPP
#define JUGGERNAUT_VK_WINDOW_SURFACE_HPP

#if _WINDOWS
#define VK_USE_PLATFORM_WIN32_KHR
#include <Windows.h>
#endif

#include "vulkan/vulkan.h"

namespace jnt
{
    // Juggernaut forward declarations
    class VulkanInstance;

    /**
     * Vulkan window surface wrapper
     * Allows for surface creation on various platforms
     */
    class VulkanWindowSurface
    {
    public:
#if _WINDOWS
        /**
         * Create a new surface for the Windows platform
         * 
         * @param   instance        Vulkan instance wrapper object
         * @param   windowHandle    Windows native handle to the window
         * @return  True when surface creation was successful, false otherwise
         */
        bool Create(const VulkanInstance& instance, HWND windowHandle);
#endif

        /**
         * Destroy the Vulkan window surface object
         */
        void Destroy(const VulkanInstance& instance) const;

        /**
         * Get a handle to the underlaying Vulkan object that backs this wrapper
         */
        const VkSurfaceKHR& Get() const;

    private:
        VkSurfaceKHR Surface;
    };
}

#endif //! JUGGERNAUT_VK_WINDOW_SURFACE_HPP
