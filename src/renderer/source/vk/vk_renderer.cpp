#include "vk/vk_renderer.hpp"
#include "vk/vk_extensions.hpp"
#include "vk/vk_instance.hpp"
#include "vk/vk_validation_layers.hpp"
#include "vk/vk_device.hpp"
#include "vk/vk_window_surface.hpp"
#include "vk/vk_swapchain.hpp"
#include "utility/console_output.hpp"

#if _WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#endif
#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

#include <iostream>
#include <stdexcept>

using namespace jnt;

VulkanRenderer::VulkanRenderer() :
    Window(nullptr),
    Instance(nullptr),
    Device(nullptr),
    WindowSurface(nullptr),
    Swapchain(nullptr)
{}

bool VulkanRenderer::Create()
{
	InitWindow();
	InitVulkan();

    //#TODO: get rid of the two function above and actually return something here
    return true;
}

void VulkanRenderer::Destroy()
{
    Cleanup();
}

bool VulkanRenderer::IsActive()
{
    //#TODO: make window creation optional, move it to a new library
    //       the renderer should not rely on a window at all as it should be
    //       able to perform off-screen rendering too
    bool isActive = !glfwWindowShouldClose(Window);
    glfwPollEvents();

    return isActive;
}

void VulkanRenderer::PostInitialize()
{
	Window = nullptr;
	Instance = nullptr;
	Device = nullptr;
	WindowSurface = nullptr;
	Swapchain = nullptr;
}

void VulkanRenderer::InitWindow()
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    Window = glfwCreateWindow(OutputWidth, OutputHeight, "Juggernaut", nullptr, nullptr);
}

void VulkanRenderer::InitVulkan()
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
	Device->AddExtension(VK_KHR_SWAPCHAIN_EXTENSION_NAME);

	if (Device->CreatePhysical(*Instance, *WindowSurface))
    {
        ConsoleOutput::Success("Suitable physical device found.");
    }
    else
    {
		ConsoleOutput::Error("No suitable physical devices found on this system.");
    }

    if (Device->FindQueueFamilies(*WindowSurface))
    {
		ConsoleOutput::Success("Found all required queue families.");
    }
    else
    {
		ConsoleOutput::Error("Unable to find all required queue families.");
    }

    if (Device->CreateLogical(validationLayers))
    {
        ConsoleOutput::Success("Logical device created successfully.");
    }
    else
    {
        ConsoleOutput::Error("Unable to create logical device.");
    }

    Device->ConfigureQueueHandles();

    /************************************************************************/
    /* Swapchain creation                                                   */
    /************************************************************************/
    Swapchain = new VulkanSwapchain(OutputWidth, OutputHeight);
    if (Swapchain->Create(*Device, *WindowSurface))
    {
        ConsoleOutput::Success("Swapchain created successfully.");
    }
    else
    {
        ConsoleOutput::Error("Unable to create swapchain.");
    }
}

void VulkanRenderer::Cleanup()
{
    if (Swapchain)
    {
        Swapchain->Destroy(*Device);
        delete Swapchain;
        ConsoleOutput::Success("Swapchain deleted.");
    }

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
    ConsoleOutput::Flush();
}
