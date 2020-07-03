#ifndef JUGGERNAUT_RENDERER_HPP
#define JUGGERNAUT_RENDERER_HPP

// GLFW forward declarations
struct GLFWwindow;

namespace jnt
{
    class Renderer
    {
    public:
        Renderer();

        void Run();

    private:
        void InitWindow();

        void InitVulkan();

        void CreateInstance();

        void MainLoop();

        void Cleanup();

    private:
        GLFWwindow* Window;
    };
}

#endif //! JUGGERNAUT_RENDERER_HPP
