#ifndef JUGGERNAUT_VK_IMAGE_VIEW_HPP
#define JUGGERNAUT_VK_IMAGE_VIEW_HPP

#include "juggernaut_enums.hpp"

#include "vulkan/vulkan.h"

#include <cstdint>

namespace jnt
{
	// Juggernaut forward declarations
	class VulkanDevice;

	/**
	 * Helper structure to create a Vulkan image view object
	 */
	struct VulkanImageViewInfo
	{
		/** Type of image view */
		ImageViewType Type;
		
		/** Format of the image */
		VkFormat Format;

		/** What this image will be used for */
		ImageViewUsage Usage;

		/** Current mip-map level */
		std::uint32_t MipLevel;

		/** Total number of mip-map levels */
		std::uint32_t LevelCount;

		/** Current array layer index */
		std::uint32_t ArrayLayer;

		/** Total number of array layers */
		std::uint32_t LayerCount;
	};

	/**
	 * Vulkan image view wrapper
	 */
	class VulkanImageView
	{
	public:
		VulkanImageView();															// Constructor
		VulkanImageView(const VulkanImageView& other)					= default;	// Copy constructor
		VulkanImageView(VulkanImageView&& other) noexcept				= default;	// Move constructor
		VulkanImageView& operator=(const VulkanImageView& other)		= default;	// Copy assignment operator
		VulkanImageView& operator=(VulkanImageView&& other) noexcept	= default;	// Move assignment operator
		~VulkanImageView();															// Destructor

		/**
		 * Create a new Vulkan image view
		 * 
		 * @param	device	Vulkan device
		 * @param	image	Image to create the image view for
		 * @param	info	Data needed to create an image view
		 * @return	True when the image view was created successfully, false otherwise
		 */
		bool Create(const VulkanDevice& device, const VkImage& image, const VulkanImageViewInfo& info);

		/**
		 * Destroy the image view and free any used resources
		 * 
		 * @param	device	Vulkan device
		 */
		void Destroy(const VulkanDevice& device) const;

	private:
		VkImageView ImageView;
	};
}

#endif //! JUGGERNAUT_VK_IMAGE_VIEW_HPP
