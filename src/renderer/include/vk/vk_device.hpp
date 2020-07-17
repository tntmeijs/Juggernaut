#ifndef JUGGERNAUT_VK_DEVICE_HPP
#define JUGGERNAUT_VK_DEVICE_HPP

#include "vulkan/vulkan.h"

#include <memory>
#include <string_view>
#include <vector>

namespace jnt
{
    // Juggernaut forward declarations
    class VulkanInstance;
    class VulkanQueueFamilies;
    class VulkanValidationLayers;
    class VulkanQueue;
    class VulkanWindowSurface;

    /**
     * Wrapper class that makes it possible to interface with logical and physical
     * devices on a high and low level
     */
    class VulkanDevice
    {
    public:
        /**
         * Assign default values to members
         */
        VulkanDevice();

        /**
         * Create a new physical device using the best possible GPU available
         * 
         * @param   instance        Vulkan instance
         * @param   windowSurface   Vulkan window surface
         * @return  True when the physical device was created successfully, false otherwise
         */
        bool CreatePhysical(const VulkanInstance& instance, const VulkanWindowSurface& windowSurface);

        /**
         * Find all relevant queue family indices
         * 
         * @param   windowSurface   Window surface wrapper object
         * @return  True when all queue family indices have been found, false otherwise
         */
        bool FindQueueFamilies(const VulkanWindowSurface& windowSurface);

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
         * Register a new device extension
         * 
         * @param   extensionName   Name of the device extension to use
         */
        void AddExtension(std::string_view extensionName);

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

        /**
         * Retrieve the Vulkan queue families wrapper object
         * 
         * @return  Queue families wrapper object
         */
        const VulkanQueueFamilies& GetQueueFamilies() const;

    private:
        VkPhysicalDevice PhysicalDevice;
        VkDevice LogicalDevice;

        std::shared_ptr<VulkanQueueFamilies> QueueFamilies;
        std::shared_ptr<VulkanQueue> GraphicsQueue;
        std::shared_ptr<VulkanQueue> PresentationQueue;

        std::vector<const char*> DeviceExtensions;
    };
}

#endif //! JUGGERNAUT_VK_DEVICE_HPP
