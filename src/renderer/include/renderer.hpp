#ifndef JUGGERNAUT_RENDERER_HPP
#define JUGGERNAUT_RENDERER_HPP

#include "enums.hpp"

#include <cstdint>

namespace jnt
{
	/**
	 * Base class for renderers
	 */
	class JuggernautRenderer
	{
	public:
		/**
		 * Assign default values to members
		 */
		JuggernautRenderer();

		/**
		 * Initialize a new renderer
		 * 
		 * @param	outputWidth		Horizontal output resolution
		 * @param	outputHeight	Vertical output resolution
		 */
		void Initialize(std::uint32_t outputWidth, std::uint32_t outputHeight);

		/**
		 * Create a new renderer
		 * 
		 * @return	True when the renderer was created successfully, false otherwise
		 */
		virtual bool Create() = 0;

		/**
		 * Destroy the renderer
		 */
		virtual void Destroy() = 0;

		/**
		 * Returns true as long as the renderer is still busy
		 * 
		 * @return	True while busy, false when done
		 */
		virtual bool IsActive() = 0;

	public:
		/**
		 * Factory to create a new renderer using the specified graphics API
		 * 
		 * @param	api		Graphics API to create a renderer for
		 * @return	New renderer
		 */
		static JuggernautRenderer* New(GraphicsAPI api);

	protected:
		/**
		 * Called after initializing the base renderer
		 * Useful for setting default values and ensuring all variables have
		 * valid values
		 */
		virtual void PostInitialize() = 0;

	protected:
		std::uint32_t OutputWidth;
		std::uint32_t OutputHeight;
	};
}

#endif //! JUGGERNAUT_RENDERER_HPP
