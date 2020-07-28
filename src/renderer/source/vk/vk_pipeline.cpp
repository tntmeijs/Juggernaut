#include "vk/vk_pipeline.hpp"

using namespace jnt;

VulkanPipeline::VulkanPipeline(PipelineType type) :
	Type(type)
{}

const PipelineType VulkanPipeline::GetType() const
{
	return Type;
}
