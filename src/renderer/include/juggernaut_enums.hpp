#ifndef JUGGERNAUT_ENUMS_HPP
#define JUGGERNAUT_ENUMS_HPP

namespace jnt
{
    /**
     * All supported graphics APIs
     */
    enum class GraphicsAPI
    {
        Vulkan
    };

    /**
     * All image view types
     */
    enum class ImageViewType
    {
        Invalid = -1,
        Image1D,
        Image2D,
        Image3D,
        ImageCube,
        ImageArray1D,
        ImageArray2D,
        ImageArrayCube
    };

	/**
	 * All possible image view use cases
	 */
	enum class ImageViewUsage
	{
		Color,
		Depth,
		Stencil
	};

    /**
     * All image formats
     */
    enum class ImageFormat
    {
        Invalid = -1,

        /************************************************************************/
        /* One component                                                        */
        /************************************************************************/
        // Red 8 bit
        Unorm_R8,
        Uint_R8,
        Srgb_R8,

		// Red - 16
		Unorm_R16,
		Uint_R16,
		Sfloat_R16,

		// Red - 32
		Uint_R32,
		Sfloat_R32,

		// Red - 64
		Uint_R64,
		Sfloat_R64,

        /************************************************************************/
        /* Two components                                                       */
        /************************************************************************/
		// Red-green 8 bit
        Unorm_R8_G8,
		Uint_R8_G8,
		Srgb_R8_G8,

		// Red-green - 16 bit
		Unorm_R16_G16,
		Uint_R16_G16,
		Sfloat_R16_G16,

		// Red-green 32 bit
		Uint_R32_G32,
		Sfloat_R32_G32,

		// Red-green 64 bit
		Uint_R64_G64,
		Sfloat_R64_G64,

        /************************************************************************/
        /* Three components                                                     */
        /************************************************************************/
        // Red-green-blue 8 bit
		Unorm_R8_G8_B8,
		Uint_R8_G8_B8,
		Srgb_R8_G8_B8,

        // Blue-green-red 8 bit
		Unorm_B8_G8_R8,
		Uint_B8_G8_R8,
		Srgb_B8_G8_R8,

		// Red-green-blue 16 bit
		Unorm_R16_G16_B16,
		Uint_R16_G16_B16,
		Sfloat_R16_G16_B16,

		// Red-green-blue 32 bit
		Uint_R32_G32_B32,
		Sfloat_R32_G32_B32,

		// Red-green-blue 64 bit
		Uint_R64_G64_B64,
		Sfloat_R64_G64_B64,

        /************************************************************************/
        /* Four components                                                      */
        /************************************************************************/
        // Red-green-blue-alpha 8 bit
		Unorm_R8_G8_B8_A8,
		Uint_R8_G8_B8_A8,
		Srgb_R8_G8_B8_A8,

		// Blue-green-red-alpha 8 bit
		Unorm_B8_G8_R8_A8,
		Uint_B8_G8_R8_A8,
		Srgb_B8_G8_R8_A8,

		// Red-green-blue-alpha 16 bit
		Unorm_R16_G16_B16_A16,
		Uint_R16_G16_B16_A16,
		Sfloat_R16_G16_B16_A16,

		// Red-green-blue-alpha 32 bit
		Uint_R32_G32_B32_A32,
		Sfloat_R32_G32_B32_A32,

		// Red-green-blue-alpha 64 bit
		Uint_R64_G64_B64_A64,
		Sfloat_R64_G64_B64_A64
    };
}

#endif //! JUGGERNAUT_ENUMS_HPP
