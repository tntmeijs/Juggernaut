#ifndef JUGGERNAUT_RENDERER_HPP
#define JUGGERNAUT_RENDERER_HPP

#include <cstdint>

// GLFW forward declarations
struct GLFWwindow;

namespace jnt
{
	// Juggernaut forward declarations
	class VulkanInstance;
    class VulkanDevice;
    class VulkanWindowSurface;
    class VulkanSwapchain;

    class Renderer
    {
    public:
        /**
         * Create a new renderer
         * 
         * @param   width   Horizontal output resolution
         * @param   height  Vertical output resolution
         */
        Renderer(std::uint32_t width, std::uint32_t height);

        void Run();

    private:
        void InitWindow();

        void InitVulkan();

        void MainLoop();

        void Cleanup();

    private:
		std::uint32_t Width;
		std::uint32_t Height;

        GLFWwindow* Window;

        VulkanInstance* Instance;
        VulkanDevice* Device;
        VulkanWindowSurface* WindowSurface;
        VulkanSwapchain* Swapchain;
    };
}

#endif //! JUGGERNAUT_RENDERER_HPP
