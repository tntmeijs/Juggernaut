#ifndef JUGGERNAUT_VK_DEVICE_HPP
#define JUGGERNAUT_VK_DEVICE_HPP

#include "vulkan/vulkan.h"

namespace jnt
{
    // Juggernaut forward declarations
    class VulkanInstance;
    class VulkanQueueFamilies;

    /**
     * Wrapper class that makes it possible to interface with logical and physical
     * devices on a high and low level
     */
    class VulkanDevice
    {
    public:
        bool CreatePhysical(const VulkanInstance& instance);

        void FindQueueFamilies();

        void Destroy() const;

        /**
         * Retrieve the Vulkan physical device object
         * 
         * @return  Physical device object
         */
        const VkPhysicalDevice& GetPhysical() const;

    private:
        VkPhysicalDevice PhysicalDevice;

        VulkanQueueFamilies* QueueFamilies;
    };
}

#endif //! JUGGERNAUT_VK_DEVICE_HPP
