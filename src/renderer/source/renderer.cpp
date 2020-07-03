#include "renderer.hpp"

#include "vulkan/vulkan.h"
#include "glfw/glfw3.h"

#include <iostream>

using namespace jnt;

Renderer::Renderer()
{
    std::cout << "Juggernaut renderer" << std::endl;
}

void Renderer::Run()
{
    InitWindow();
    InitVulkan();
    MainLoop();
    Cleanup();
}

void Renderer::InitWindow()
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    Window = glfwCreateWindow(800, 600, "Juggernaut", nullptr, nullptr);
}

void Renderer::InitVulkan()
{}

void Renderer::MainLoop()
{
    while (!glfwWindowShouldClose(Window))
    {
        glfwPollEvents();
    }
}

void Renderer::Cleanup()
{
    glfwDestroyWindow(Window);
    glfwTerminate();
}
