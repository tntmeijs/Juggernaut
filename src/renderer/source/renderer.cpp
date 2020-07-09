#include "renderer.hpp"
#include "vk/extensions.hpp"
#include "vk/instance.hpp"
#include "vk/validation_layers.hpp"
#include "vk/device.hpp"
#include "vk/window_surface.hpp"
#include "utility/console_output.hpp"

#if _WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#endif
#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

#include <iostream>
#include <stdexcept>

using namespace jnt;

Renderer::Renderer() :
    Window(nullptr),
    Instance(nullptr),
    Device(nullptr)
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
    /* Window surface creation                                              */
    /************************************************************************/
#if _WINDOWS
    WindowSurface = new VulkanWindowSurface();
    if (WindowSurface->Create(*Instance, glfwGetWin32Window(Window)))
    {
        ConsoleOutput::Success("Vulkan window surface created successfully.");
    }
    else
    {
		ConsoleOutput::Error("Vulkan window surface creation unsuccessful.");
    }
#else
    ConsoleOutput::Error("THIS PLATFORM DOES NOT SUPPORT WINDOW CREATION YET");
#endif

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

    Device->FindQueueFamilies(*WindowSurface);
    
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
    if (Device)
    {
        Device->Destroy();
        delete Device;
		ConsoleOutput::Success("Device deleted.");
	}

    if (WindowSurface)
    {
        WindowSurface->Destroy(*Instance);
        delete WindowSurface;
		ConsoleOutput::Success("Window surface deleted.");
    }

    if (Instance)
    {
        Instance->Destroy();
        delete Instance;
		ConsoleOutput::Success("Instance deleted.");
	}

    glfwDestroyWindow(Window);
    glfwTerminate();

    // Make sure the text color is set to the default console color again
    ConsoleOutput::Reset();
}
