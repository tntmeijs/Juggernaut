#include "renderer.hpp"
#include "vk/vk_renderer.hpp"
#include "utility/console_output.hpp"

using namespace jnt;

JuggernautRenderer::JuggernautRenderer() :
	OutputWidth(0),
	OutputHeight(0)
{}

void JuggernautRenderer::Initialize(std::uint32_t outputWidth, std::uint32_t outputHeight)
{
	OutputWidth = outputWidth;
	OutputHeight = outputHeight;

	PostInitialize();
}

std::unique_ptr<JuggernautRenderer> JuggernautRenderer::New(GraphicsAPI api)
{
	std::unique_ptr<JuggernautRenderer> renderer = nullptr;

	switch (api)
	{
		case jnt::GraphicsAPI::Vulkan:
			renderer = std::make_unique<VulkanRenderer>();
			break;
		default:
			ConsoleOutput::Error("Invalid graphics API specified during renderer creation.");
			break;
	}

	return renderer;
}
