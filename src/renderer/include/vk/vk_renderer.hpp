#ifndef JUGGERNAUT_VULKAN_RENDERER_HPP
#define JUGGERNAUT_VULKAN_RENDERER_HPP

#include "renderer.hpp"

#include <memory>

// GLFW forward declarations
struct GLFWwindow;

namespace jnt
{
	// Juggernaut forward declarations
	class VulkanInstance;
    class VulkanDevice;
    class VulkanWindowSurface;
    class VulkanSwapchain;

    class VulkanRenderer : public JuggernautRenderer
    {
    public:
        /**
         * Assign default values to members
         */
        VulkanRenderer();

        /**
         * Create a new Vulkan renderer
         * 
         * @return	True when the renderer was created successfully, false otherwise
         */
        virtual bool Create() override;

        /**
         * Destroy the Vulkan renderer
         */
        virtual void Destroy() override;

        /**
         * Returns true as long as the renderer is still busy
         *
         * @return	True while busy, false when done
         */
        virtual bool IsActive() override;

    protected:
        /**
         * Ensure all members are ready to be used
         */
        virtual void PostInitialize() override;

    private:
        void InitWindow();

        void InitVulkan();

        void Cleanup();

    private:
        GLFWwindow* Window;

        std::unique_ptr<VulkanInstance> Instance;
        std::unique_ptr<VulkanDevice> Device;
        std::unique_ptr<VulkanWindowSurface> WindowSurface;
        std::unique_ptr<VulkanSwapchain> Swapchain;
    };
}

#endif //! JUGGERNAUT_RENDERER_HPP
