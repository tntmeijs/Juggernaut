#ifndef JUGGERNAUT_VK_DEBUG_MESSENGER_HPP
#define JUGGERNAUT_VK_DEBUG_MESSENGER_HPP

#include "vulkan/vulkan.h"

namespace jnt
{
    // Juggernaut forward declarations
    class VulkanInstance;

    /**
     * Vulkan validation layer debug messenger wrapper
     */
    class VulkanDebugMessenger
    {
    public:
        VkDebugUtilsMessengerCreateInfoEXT Initialize() const;

        bool Create(const VkInstance& instance, const VkDebugUtilsMessengerCreateInfoEXT& createInfo);

        void Destroy(const VkInstance& instance) const;

        /**
         * Validation layer message callback
         * @param   severity    Message severity
         * @param   type        Message type
         * @param   data        Message content
         * @param   userData    User-defined data
         */
        static VKAPI_ATTR VkBool32 VKAPI_CALL ValidationLayerDebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT severity, VkDebugUtilsMessageTypeFlagsEXT type, const VkDebugUtilsMessengerCallbackDataEXT* data, void* userData);
    
    private:
        VkDebugUtilsMessengerEXT DebugMessenger;
    };
}

#endif //! JUGGERNAUT_VK_DEBUG_MESSENGER_HPP
