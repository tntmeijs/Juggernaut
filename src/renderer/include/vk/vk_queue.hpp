#ifndef JUGGERNAUT_VK_QUEUE_HPP
#define JUGGERNAUT_VK_QUEUE_HPP

#include "vulkan/vulkan.h"

#include <cstdint>

namespace jnt
{
    /**
     * Helper class to construct new Vulkan device queues
     */
    class VulkanQueue
    {
    public:
        /**
         * Create a new device queue create information structure
         * 
         * @param   familyIndex     Queue family index to create the queue for
         * @param   count           Number of queues to create of this type
         * @param   priority        Command buffer execution scheduling priority
         * @return  Queue create information structure
         */
        static VkDeviceQueueCreateInfo Create(std::uint32_t familyIndex, std::uint32_t count = 1, float priority = 1.0f);

        /**
         * Save a queue handle
         */
        void Set(const VkQueue& queue);

        /**
         * Retrieve a queue handle
         */
        const VkQueue& Get() const;

    private:
        VkQueue Queue;
    };
}

#endif //! JUGGERNAUT_VK_QUEUE_HPP
