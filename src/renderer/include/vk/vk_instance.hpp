#ifndef JUGGERNAUT_VK_INSTANCE_HPP
#define JUGGERNAUT_VK_INSTANCE_HPP

#include "vulkan/vulkan.h"

#include <memory>
#include <string_view>
#include <vector>

namespace jnt
{
	// Juggernaut forward declarations
	class VulkanExtensions;
	class VulkanValidationLayers;
	class VulkanDebugMessenger;

	/**
	 * Vulkan instance wrapper
	 */
	class VulkanInstance
	{
	public:
		VulkanInstance();														// Constructor
		VulkanInstance(const VulkanInstance& other)					= default;	// Copy constructor
		VulkanInstance(VulkanInstance&& other) noexcept				= default;	// Move constructor
		VulkanInstance& operator=(const VulkanInstance& other)		= default;	// Copy assignment operator
		VulkanInstance& operator=(VulkanInstance&& other) noexcept	= default;	// Move assignment operator
		~VulkanInstance();														// Destructor

		/**
		 * Create a new Vulkan instance wrapper object
		 * 
		 * @param	applicationName	Name of the application
		 * @param	engineName		Name of the engine
		 */
		VulkanInstance(std::string_view applicationName, std::string_view engineName);

		/**
		 * Create a new Vulkan instance object
		 * 
		 * @param	extensions		Extensions to use
		 * @param	validationLayers	Validation layers to enable
		 * @retur	True when the instance creation was successful, false otherwise
		 */
		bool Create(const VulkanExtensions& extensions, const VulkanValidationLayers& validationLayers);

		/**
		 * Destroy the Vulkan instance object
		 */
		void Destroy() const;

		/**
		 * Retrieve a reference to the internal Vulkan object that backs this wrapper
		 */
		const VkInstance& Get() const;

	private:
		/**
		 * Helper function to construct a VkApplicationInfo structure
		 * 
		 * @return	Filled application info structure
		 */
		VkApplicationInfo ConstructApplicationInfo() const;

		/**
		 * Helper function to construct a VkInstanceCreateInfo structure
		 * 
		 * @param	extensions			Extensions to use
		 * @param	validationLayers	Validation layers to use
		 * @return	Filled instance create info structure
		 */
		VkInstanceCreateInfo ConstructInstanceCreateInfo(const std::vector<const char*>& extensions, const std::vector<const char*>& validationLayers) const;

	private:
		std::string ApplicationName;
		std::string EngineName;

		VkInstance Instance;

		std::unique_ptr<VulkanDebugMessenger> DebugMessenger;
	};
}

#endif //! JUGGERNAUT_VK_INSTANCE_HPP
