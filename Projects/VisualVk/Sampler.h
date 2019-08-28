/*************************************************************************
*************************    VisualVk_Sampler    *************************
*************************************************************************/
#pragma once

#include "Enums.h"
#include "Handle.h"
#include "Context.h"

namespace Vk
{
	/*********************************************************************
	****************************    Filter    ****************************
	*********************************************************************/

	/**
	 *	@brief	Specify filters used for texture lookups.
	 */
	enum class Filter
	{
		eLinear			= VK_FILTER_LINEAR,
		eNearest		= VK_FILTER_NEAREST,
	};

	/*********************************************************************
	**************************    MipmapMode    **************************
	*********************************************************************/

	/**
	 *	@brief	Specify mipmap mode used for texture lookups.
	 */
	enum class MipmapMode
	{
		eLinear			= VK_SAMPLER_MIPMAP_MODE_LINEAR,
		eNearest		= VK_SAMPLER_MIPMAP_MODE_NEAREST
	};

	/*********************************************************************
	*************************    AddressMode    **************************
	*********************************************************************/

	/**
	 *	@brief	Specify behavior of sampling with texture coordinates outside an image.
	 */
	enum class AddressMode
	{
		eRepeat					= VK_SAMPLER_ADDRESS_MODE_REPEAT,
		eClampToEdge			= VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
		eClampToBorder			= VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER,
		eMirroredRepeat			= VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT,
		eMirrorClampToEdge		= VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE
	};

	/*********************************************************************
	*************************    BorderColor    **************************
	*********************************************************************/

	/**
	 *	@brief	Specify border color used for texture lookups.
	 */
	enum class BorderColor
	{
		eIntOpaqueWhite				= VK_BORDER_COLOR_INT_OPAQUE_WHITE,
		eIntOpaqueBlack				= VK_BORDER_COLOR_INT_OPAQUE_BLACK,
		eFloatOpaqueWhite			= VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE,
		eFloatOpaqueBlack			= VK_BORDER_COLOR_FLOAT_OPAQUE_BLACK,
		eIntTransparentBlack		= VK_BORDER_COLOR_INT_TRANSPARENT_BLACK,
		eFloatTransparentBlack		= VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK
	};

	/*********************************************************************
	*************************    SamplerParam    *************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan sampler parameters.
	 */
	struct SamplerParam
	{
		Filter				magFilter					= Filter::eNearest;
		Filter				minFilter					= Filter::eNearest;
		CompareOp			compareOp					= CompareOp::eNever;
		MipmapMode			mipmapMode					= MipmapMode::eNearest;
		AddressMode			addressModeU				= AddressMode::eRepeat;
		AddressMode			addressModeV				= AddressMode::eRepeat;
		AddressMode			addressModeW				= AddressMode::eRepeat;
		BorderColor			borderColor					= BorderColor::eFloatTransparentBlack;
		Bool32				unnormalizedCoordinates		= eFalse;
		Bool32				anisotropyEnable			= eFalse;
		Bool32				compareEnable				= eFalse;
		float				maxAnisotropy				= 1.0f;
		float				mipLodBias					= 0.0f;
		float				minLod						= 0.0f;
		float				maxLod						= 0.0f;
	};

	/*********************************************************************
	***************************    Sampler    ****************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan sampler object.
	 */
	class Sampler : public SamplerH
	{

	public:

		//!	@brief	Create a sampler object.
		VkResult Create(const SamplerParam & Param = SamplerParam());

		//!	@brief	Return sampler parameters.
		const SamplerParam & GetParam() const { return m_Param; }

	private:

		SamplerParam			m_Param;
	};
}