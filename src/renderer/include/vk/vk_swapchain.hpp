#ifndef JUGGERNAUT_VK_SWAPCHAIN_HPP
#define JUGGERNAUT_VK_SWAPCHAIN_HPP

#include "vulkan/vulkan.h"

#include <cstdint>
#include <vector>

namespace jnt
{
    // Juggernaut forward declarations
    class VulkanDevice;
    class VulkanWindowSurface;

    /**
     * Helper structure to save swapchain support details
     */
    struct VulkanSwapchainSupportDetails
    {
        VkSurfaceCapabilitiesKHR        capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR>   presentModes;
    };

    /**
     * Wrapper class for Vulkan swapchain objects
     */
    class VulkanSwapchain
    {
    public:
        /**
         * Initialize the Vulkan swapchain wrapper
         * 
		 * @param   width   Desired render output width
		 * @param   height  Desired render output height
         */
        VulkanSwapchain(std::uint32_t width, std::uint32_t height);

        /**
         * Helper function to determine if the swapchain support is adequate
         * 
         * @param   details     Vulkan swapchain support details structure
         * @return  True when support is adequate, false otherwise
         */
        static bool SwapchainSupportOk(const VulkanSwapchainSupportDetails& details);

        /**
         * Helper function to query swapchain support details
         * 
         * @param   physicalDevice      Physical device used to present to the screen
         * @return  Structure containing the information necessary to check what kind of swapchain is supported
         */
        static VulkanSwapchainSupportDetails QuerySwapchainSupport(const VkPhysicalDevice& physicalDevice, const VkSurfaceKHR& surface);
    
    public:
        /**
         * Create a new Vulkan swapchain object
         *
         * @param   device          Device to create the swapchain with
         * @param   windowSurface   Window surface to create the swapchain for
         * @return  True when swapchain creation was successful, false otherwise
         */
        bool Create(const VulkanDevice& device, const VulkanWindowSurface& windowSurface);

        /**
         * Deallocate Vulkan resources
         * 
         * @param   device      Device which was used to create the swapchain with
         */
        void Destroy(const VulkanDevice& device) const;

    private:
        /**
         * Helper function to choose the best swapchain surface format
         * 
         * @param   details     Swapchain support details structure
         * @return  Best surface format
         */
        VkSurfaceFormatKHR ChooseSwapchainSurfaceFormat(const VulkanSwapchainSupportDetails& details) const;

        /**
         * Helper function to choose the best swapchain present mode
         * 
         * @param   details     Swapchain support details structure
         * @return  Best present mode
         */
        VkPresentModeKHR ChooseSwapchainPresentMode(const VulkanSwapchainSupportDetails& details) const;

        /**
         * Helper function to choose the best swap extent
         * 
         * @param   details     Swapchain support details structure
         * @return  Best swap extent
         */
        VkExtent2D ChooseSwapchainExtent(const VulkanSwapchainSupportDetails& details) const;

    private:
        std::uint32_t Width;
        std::uint32_t Height;

        VkSurfaceFormatKHR SwapchainSurfaceFormat;
        VkExtent2D SwapchainExtent;
        VkSwapchainKHR Swapchain;

        std::vector<VkImage> SwapchainImages;
    };
}

#endif //! JUGGERNAUT_VK_SWAPCHAIN_HPP
