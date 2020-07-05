#ifndef JUGGERNAUT_VK_QUEUE_FAMILIES_HPP
#define JUGGERNAUT_VK_QUEUE_FAMILIES_HPP

#include "vulkan/vulkan.h"

#include <optional>

namespace jnt
{
    /**
     * Wrapper that makes it easier to find the relevant queue family indices
     */
    class VulkanQueueFamilies
    {
    public:
        /**
         * Find the best queue family indices for this application
         * 
         * @param   physicalDevice  Physical device to look for queues on
         */
        void Find(const VkPhysicalDevice& physicalDevice);

        /**
         * Check if all queue families have been found
         * 
         * @return  True when all queue families have a value, false otherwise
         */
        bool IsComplete() const;

        /**
         * Retrieve the graphics family queue index
         * 
         * @return  Graphics queue family index
         */
        const uint32_t GetGraphicsFamilyIndex() const;

    private:
		std::optional<uint32_t> GraphicsFamilyIndex;
    };
}

#endif //! JUGGERNAUT_VK_QUEUE_FAMILIES_HPP
