#ifndef JUGGERNAUT_VK_DEVICE_HPP
#define JUGGERNAUT_VK_DEVICE_HPP

#include "vulkan/vulkan.h"

namespace jnt
{
    // Juggernaut forward declarations
    class VulkanInstance;
    class VulkanQueueFamilies;
    class VulkanValidationLayers;
    class VulkanQueue;

    /**
     * Wrapper class that makes it possible to interface with logical and physical
     * devices on a high and low level
     */
    class VulkanDevice
    {
    public:
        /**
         * Create a new physical device using the best possible GPU available
         * 
         * @param   instance    Vulkan instance
         * @return  True when the physical device was created successfully, false otherwise
         */
        bool CreatePhysical(const VulkanInstance& instance);

        /**
         * Find all relevant queue family indices
         */
        void FindQueueFamilies();

        /**
         * Create a new logical device
         * 
         * @param   validationLayers    Validation layers to use
         * @return  True when the logical device was created successfully, false otherwise
         */
        bool CreateLogical(const VulkanValidationLayers& validationLayers);

        /**
         * Cache the device queue handles
         */
        void ConfigureQueueHandles();

        /**
         * Destroy the device and all relevant objects
         */
        void Destroy() const;

        /**
         * Retrieve the Vulkan physical device object
         * 
         * @return  Physical device object
         */
        const VkPhysicalDevice& GetGPU() const;

        /**
         * Retrieve the Vulkan logical device object
         * 
         * @return  Logical device object
         */
        const VkDevice& Get() const;

    private:
        VkPhysicalDevice PhysicalDevice;
        VkDevice LogicalDevice;

        VulkanQueueFamilies* QueueFamilies;
        VulkanQueue* GraphicsQueue;
    };
}

#endif //! JUGGERNAUT_VK_DEVICE_HPP
