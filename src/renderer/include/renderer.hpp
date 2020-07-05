#ifndef JUGGERNAUT_RENDERER_HPP
#define JUGGERNAUT_RENDERER_HPP

// GLFW forward declarations
struct GLFWwindow;

namespace jnt
{
	// Juggernaut forward declarations
	class VulkanInstance;

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
    };
}

#endif //! JUGGERNAUT_RENDERER_HPP
