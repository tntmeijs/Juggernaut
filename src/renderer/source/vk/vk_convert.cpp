#include "vk/vk_convert.hpp"

VkImageViewType jnt::JuggernautToVulkan(ImageViewType type)
{
	switch (type)
	{
		case ImageViewType::Image1D:
			return VK_IMAGE_VIEW_TYPE_1D;
		case ImageViewType::Image2D:
			return VK_IMAGE_VIEW_TYPE_2D;
		case ImageViewType::Image3D:
			return VK_IMAGE_VIEW_TYPE_3D;
		case ImageViewType::ImageCube:
			return VK_IMAGE_VIEW_TYPE_CUBE;
		case ImageViewType::ImageArray1D:
			return VK_IMAGE_VIEW_TYPE_1D_ARRAY;
		case ImageViewType::ImageArray2D:
			return VK_IMAGE_VIEW_TYPE_2D_ARRAY;
		case ImageViewType::ImageArrayCube:
			return VK_IMAGE_VIEW_TYPE_CUBE_ARRAY;
		case ImageViewType::Invalid:
		default:
			return VK_IMAGE_VIEW_TYPE_MAX_ENUM;
	}
}

VkImageAspectFlags jnt::JuggernautToVulkan(ImageViewUsage usage)
{
    switch (usage)
    {
        case jnt::ImageViewUsage::Color:
            return VK_IMAGE_ASPECT_COLOR_BIT;
        case jnt::ImageViewUsage::Depth:
			return VK_IMAGE_ASPECT_DEPTH_BIT;
        case jnt::ImageViewUsage::Stencil:
            return VK_IMAGE_ASPECT_STENCIL_BIT;
        default:
            return VK_IMAGE_ASPECT_FLAG_BITS_MAX_ENUM;
    }
}

VkFormat jnt::JuggernautToVulkan(ImageFormat format)
{
	switch (format)
	{
        case ImageFormat::Unorm_R8:
            return VK_FORMAT_R8_UNORM;
        case ImageFormat::Uint_R8:
            return VK_FORMAT_R8_UINT;
        case ImageFormat::Srgb_R8:
            return VK_FORMAT_R8_SRGB;
        case ImageFormat::Unorm_R16:
            return VK_FORMAT_R16_UNORM;
        case ImageFormat::Uint_R16:
            return VK_FORMAT_R16_UINT;
        case ImageFormat::Sfloat_R16:
            return VK_FORMAT_R16_SFLOAT;
        case ImageFormat::Uint_R32:
            return VK_FORMAT_R32_UINT;
        case ImageFormat::Sfloat_R32:
            return VK_FORMAT_R32_SFLOAT;
        case ImageFormat::Uint_R64:
            return VK_FORMAT_R64_UINT;
        case ImageFormat::Sfloat_R64:
            return VK_FORMAT_R64_SFLOAT;
        case ImageFormat::Unorm_R8_G8:
            return VK_FORMAT_R8G8_UNORM;
        case ImageFormat::Uint_R8_G8:
            return VK_FORMAT_R8G8_UINT;
        case ImageFormat::Srgb_R8_G8:
            return VK_FORMAT_R8G8_SRGB;
        case ImageFormat::Unorm_R16_G16:
            return VK_FORMAT_R16G16_UNORM;
        case ImageFormat::Uint_R16_G16:
            return VK_FORMAT_R16G16_UINT;
        case ImageFormat::Sfloat_R16_G16:
            return VK_FORMAT_R16G16_SFLOAT;
        case ImageFormat::Uint_R32_G32:
            return VK_FORMAT_R32G32_UINT;
        case ImageFormat::Sfloat_R32_G32:
            return VK_FORMAT_R32G32_SFLOAT;
        case ImageFormat::Uint_R64_G64:
            return VK_FORMAT_R64G64_UINT;
        case ImageFormat::Sfloat_R64_G64:
            return VK_FORMAT_R64G64_SFLOAT;
        case ImageFormat::Unorm_R8_G8_B8:
            return VK_FORMAT_R8G8B8_UNORM;
        case ImageFormat::Uint_R8_G8_B8:
            return VK_FORMAT_R8G8B8_UINT;
        case ImageFormat::Srgb_R8_G8_B8:
            return VK_FORMAT_R8G8B8_SRGB;
        case ImageFormat::Unorm_B8_G8_R8:
            return VK_FORMAT_B8G8R8_UNORM;
        case ImageFormat::Uint_B8_G8_R8:
            return VK_FORMAT_B8G8R8_UINT;
        case ImageFormat::Srgb_B8_G8_R8:
            return VK_FORMAT_B8G8R8_SRGB;
        case ImageFormat::Unorm_R16_G16_B16:
            return VK_FORMAT_R16G16B16_UNORM;
        case ImageFormat::Uint_R16_G16_B16:
            return VK_FORMAT_R16G16B16_UINT;
        case ImageFormat::Sfloat_R16_G16_B16:
            return VK_FORMAT_R16G16B16_SFLOAT;
        case ImageFormat::Uint_R32_G32_B32:
            return VK_FORMAT_R32G32B32_UINT;
        case ImageFormat::Sfloat_R32_G32_B32:
            return VK_FORMAT_R32G32B32_SFLOAT;
        case ImageFormat::Uint_R64_G64_B64:
            return VK_FORMAT_R64G64B64_UINT;
        case ImageFormat::Sfloat_R64_G64_B64:
            return VK_FORMAT_R64G64B64_SFLOAT;
        case ImageFormat::Unorm_R8_G8_B8_A8:
            return VK_FORMAT_R8G8B8A8_UNORM;
        case ImageFormat::Uint_R8_G8_B8_A8:
            return VK_FORMAT_R8G8B8A8_UINT;
        case ImageFormat::Srgb_R8_G8_B8_A8:
            return VK_FORMAT_R8G8B8A8_SRGB;
        case ImageFormat::Unorm_B8_G8_R8_A8:
            return VK_FORMAT_B8G8R8A8_UNORM;
        case ImageFormat::Uint_B8_G8_R8_A8:
            return VK_FORMAT_B8G8R8A8_UINT;
        case ImageFormat::Srgb_B8_G8_R8_A8:
            return VK_FORMAT_B8G8R8A8_SRGB;
        case ImageFormat::Unorm_R16_G16_B16_A16:
            return VK_FORMAT_R16G16B16A16_UNORM;
        case ImageFormat::Uint_R16_G16_B16_A16:
            return VK_FORMAT_R16G16B16A16_UINT;
        case ImageFormat::Sfloat_R16_G16_B16_A16:
            return VK_FORMAT_R16G16B16A16_SFLOAT;
        case ImageFormat::Uint_R32_G32_B32_A32:
            return VK_FORMAT_R32G32B32A32_UINT;
        case ImageFormat::Sfloat_R32_G32_B32_A32:
            return VK_FORMAT_R32G32B32A32_SFLOAT;
        case ImageFormat::Uint_R64_G64_B64_A64:
            return VK_FORMAT_R64G64B64A64_UINT;
        case ImageFormat::Sfloat_R64_G64_B64_A64:
            return VK_FORMAT_R64G64B64A64_SFLOAT;
		case ImageFormat::Invalid:
		default:
            return VK_FORMAT_UNDEFINED;
	}
}
