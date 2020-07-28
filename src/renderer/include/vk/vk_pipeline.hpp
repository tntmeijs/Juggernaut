#ifndef JUGGERNAUT_VK_PIPELINE_HPP
#define JUGGERNAUT_VK_PIPELINE_HPP

#include "juggernaut_enums.hpp"

namespace jnt
{
	class VulkanPipeline
	{
	public:
		/**
		 * Constructor, set the default values for the members
		 * 
		 * @param	type	Pipeline type to create
		 */
		VulkanPipeline(PipelineType type);

		/**
		 * Return what kind of pipeline this is
		 * 
		 * @return	Pipeline type
		 */
		const PipelineType GetType() const;

	private:
		PipelineType Type;
	};
}

#endif //! JUGGERNAUT_VK_PIPELINE_HPP
