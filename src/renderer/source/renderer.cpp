#include "renderer.hpp"
#include "vk/extensions.hpp"
#include "vk/instance.hpp"
#include "vk/validation_layers.hpp"
#include "vk/device.hpp"
#include "utility/console_output.hpp"

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
    /************************************************************************/
    /* Instance creation                                                    */
    /************************************************************************/
    VulkanExtensions extensions;
    VulkanValidationLayers validationLayers;

#if !NDEBUG
    extensions.AddExtension(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    validationLayers.AddValidationLayer("VK_LAYER_KHRONOS_validation");
#endif

    Instance = new VulkanInstance("Juggernaut", "Juggernaut");
    if (Instance->Create(extensions, validationLayers))
    {
		ConsoleOutput::Success("Vulkan instance created successfully.");
    }
    else
    {
        ConsoleOutput::Error("Vulkan instance creation unsuccessful.");
    }

    /************************************************************************/
    /* Device creation                                                      */
    /************************************************************************/
    Device = new VulkanDevice();
    if (Device->CreatePhysical(*Instance))
    {
        ConsoleOutput::Success("Suitable physical device found.");
    }
    else
    {
		ConsoleOutput::Error("No suitable physical devices found on this system.");
    }

    Device->FindQueueFamilies();
    
    if (Device->CreateLogical(validationLayers))
    {
        ConsoleOutput::Success("Logical device created successfully.");
    }
    else
    {
        ConsoleOutput::Error("Unable to create logical device.");
    }

    Device->ConfigureQueueHandles();
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
    Device->Destroy();
    delete Device;

    Instance->Destroy();
	delete Instance;

    glfwDestroyWindow(Window);
    glfwTerminate();

    // Make sure the text color is set to the default console color again
    ConsoleOutput::Reset();
}
