#include "renderer.hpp"
#include "vk/extensions.hpp"
#include "vk/instance.hpp"
#include "vk/validation_layers.hpp"

#include "GLFW/glfw3.h"

#include <iostream>
#include <stdexcept>

using namespace jnt;

Renderer::Renderer() :
    Window(nullptr),
    Instance(nullptr)
{}

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

    Window = glfwCreateWindow(1280, 720, "Juggernaut", nullptr, nullptr);
}

void Renderer::InitVulkan()
{
    VulkanExtensions extensions;
    VulkanValidationLayers validationLayers;

    validationLayers.AddValidationLayer("VK_LAYER_KHRONOS_validation");

    Instance = new VulkanInstance("Juggernaut", "Juggernaut");
    if (!Instance->Create(extensions, validationLayers))
    {
        throw std::runtime_error("Failed to create a Vulkan instance.");
    }

    std::cout << "[INFO] Vulkan instance created successfully." << std::endl;
}

void Renderer::MainLoop()
{
    while (!glfwWindowShouldClose(Window))
    {
        glfwPollEvents();
    }
}

void Renderer::Cleanup()
{
    Instance->Destroy();

    glfwDestroyWindow(Window);
    glfwTerminate();
}
