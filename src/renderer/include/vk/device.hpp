#ifndef JUGGERNAUT_VK_DEVICE_HPP
#define JUGGERNAUT_VK_DEVICE_HPP

#include "vulkan/vulkan.h"

namespace jnt
{
    // Juggernaut forward declarations
    class VulkanInstance;

    /**
     * Wrapper class that makes it possible to interface with logical and physical
     * devices on a high and low level
     */
    class VulkanDevice
    {
    public:
        bool CreatePhysical(const VulkanInstance& instance);

        void Destroy() const;

    private:
        VkPhysicalDevice PhysicalDevice;
    };
}

#endif //! JUGGERNAUT_VK_DEVICE_HPP
