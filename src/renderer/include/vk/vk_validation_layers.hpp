#ifndef JUGGERNAUT_VK_VALIDATION_LAYERS_HPP
#define JUGGERNAUT_VK_VALIDATION_LAYERS_HPP

#include <string_view>
#include <vector>

namespace jnt
{
    /**
     * Vulkan validation layer list wrapper
     */
    class VulkanValidationLayers
    {
    public:
        /**
         * Add a new validation layer to the list of validation layers
         * Will not add the layer name to the internal list in release configurations
         * @param validationLayerName   Name of the validation layer to add
         */
        void AddValidationLayer(std::string_view validationLayerName);

        /**
         * Check if all specified validation layers are available on this system
         * @return  True when all validation layers are present, false otherwise
         */
        bool AllValidationLayersAvailable() const;

        /**
         * Retrieve a list of all validation layers to enable
         * Will be empty when compiling in a release configuration
         * @return  List of validation layer names
         */
        const std::vector<const char*>& GetValidationLayers() const;

    private:
        std::vector<const char*> ValidationLayerNames;
    };
}

#endif //! JUGGERNAUT_VK_VALIDATION_LAYERS_HPP
