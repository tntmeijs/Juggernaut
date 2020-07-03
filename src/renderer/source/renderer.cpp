#include "renderer.hpp"

#include "vulkan/vulkan.h"
#include "glfw/glfw3.h"

#include <iostream>
#include <vector>

using namespace jnt;

VkInstance Instance;

Renderer::Renderer() :
    Window(nullptr)
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
{
    CreateInstance();
}

void Renderer::CreateInstance()
{
    VkApplicationInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    info.pApplicationName = "Juggernaut";
    info.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
    info.pEngineName = "Juggernaut";
    info.engineVersion = VK_MAKE_VERSION(0, 1, 0);
    info.apiVersion = VK_API_VERSION_1_2;

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    VkInstanceCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.pApplicationInfo = &info;
    create_info.enabledExtensionCount = glfwExtensionCount;
    create_info.ppEnabledExtensionNames = glfwExtensions;
    create_info.enabledLayerCount = 0;

    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    std::cout << "Extensions available on this system:" << std::endl;
    uint32_t foundRequiredExtensionCount = 0;
    for (const auto& extension : extensions)
    {
        bool found = false;

        for (uint32_t i = 0; i < glfwExtensionCount; ++i)
        {
            if (strcmp(glfwExtensions[i], extension.extensionName) == 0)
            {
                std::cout << "[REQUIRED]\t";

                found = true;
                ++foundRequiredExtensionCount;
                break;
            }
        }

        if (!found)
        {
            std::cout << "\t\t";
        }

        std::cout << extension.extensionName << std::endl;
    }

    if (foundRequiredExtensionCount != glfwExtensionCount)
    {
        throw std::runtime_error("Not all required extensions are present on this system.");
    }

    if (vkCreateInstance(&create_info, nullptr, &Instance) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create instance!");
    }
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
    vkDestroyInstance(Instance, nullptr);

    glfwDestroyWindow(Window);
    glfwTerminate();
}
