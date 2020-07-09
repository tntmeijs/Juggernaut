#ifndef JUGGERNAUT_RENDERER_HPP
#define JUGGERNAUT_RENDERER_HPP

// GLFW forward declarations
struct GLFWwindow;

namespace jnt
{
	// Juggernaut forward declarations
	class VulkanInstance;
    class VulkanDevice;
    class VulkanWindowSurface;

    class Renderer
    {
    public:
        Renderer();

        void Run();

    private:
        void InitWindow();

        void InitVulkan();

        void MainLoop();

        void Cleanup();

    private:
        GLFWwindow* Window;

        VulkanInstance* Instance;
        VulkanDevice* Device;
        VulkanWindowSurface* WindowSurface;
    };
}

#endif //! JUGGERNAUT_RENDERER_HPP
