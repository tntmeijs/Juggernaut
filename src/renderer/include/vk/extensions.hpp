#ifndef JUGGERNAUT_VK_EXTENSIONS_HPP
#define JUGGERNAUT_VK_EXTENSIONS_HPP

#include <string_view>
#include <string>
#include <vector>

namespace jnt
{
    /**
     * Vulkan extension list wrapper
     */
    class VulkanExtensions
    {
    public:
        /**
         * Add a new extension to the list of extensions
         * @param   extensionName     Name of the extension to add
         */
        void AddExtension(std::string_view extensionName);

        /**
         * Check if all extensions in the list of extensions are available on
         * this system
         * @return  True when all extensions are available, false otherwise
         */
        bool AllExtensionsAvailable() const;

        /**
         * Get a list of all extensions to enable, automatically adds all
         * extensions required by GLFW to the list
         * @return  List of extension names
         */
        const std::vector<const char*> GetExtensions() const;

    private:
        /**
         * Retrieve a list of extensions required by GLFW
         * @return  List of required extensions
         */
        std::vector<const char*> GetGLFWRequiredExtensions() const;

    private:
		std::vector<const char*> Extensions;
    };
}

#endif //! JUGGERNAUT_VK_EXTENSIONS_HPP
