#include "renderer.hpp"
#include "vk/vk_renderer.hpp"

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

JuggernautRenderer* JuggernautRenderer::New(GraphicsAPI api)
{
	JuggernautRenderer* renderer;

	switch (api)
	{
		case jnt::GraphicsAPI::Vulkan:
			renderer = new VulkanRenderer();
			break;
		default:
			renderer = nullptr;
			break;
	}

	return renderer;
}
