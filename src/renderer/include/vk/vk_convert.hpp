#ifndef JUGGERNAUT_VK_CONVERT_HPP
#define JUGGERNAUT_VK_CONVERT_HPP

#include "juggernaut_enums.hpp"

#include "vulkan/vulkan.h"

namespace jnt
{
    /**
     * Convert a Juggernaut image view type to a Vulkan image view type
     * 
     * @param   type    Image view type to convert
     * @return  Vulkan image view type equivalent
     */
    VkImageViewType JuggernautToVulkan(ImageViewType type);

    /**
     * Convert a Juggernaut image view usage to a Vulkan image aspect flag
     * 
     * @param   usage   Image view usage
     * @return  Vulkan image aspect flag
     */
    VkImageAspectFlags JuggernautToVulkan(ImageViewUsage usage);

    /**
     * Convert a Juggernaut image format to a Vulkan format
     * 
     * @param   format  Format to convert
     * @return  Vulkan format type equivalent
     */
    VkFormat JuggernautToVulkan(ImageFormat format);
}

#endif
