/*************************************************************************
*************************    VisualVk_Sampler    *************************
*************************************************************************/
#pragma once

#include "Enum.h"
#include "Handle.h"
#include "Resource.h"

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
	*************************    SamplerInfo    **************************
	*********************************************************************/

	/**
	 *	@brief	Sampler information.
	 */
	struct SamplerInfo
	{
		Filter				magFilter					= Filter::eLinear;
		Filter				minFilter					= Filter::eLinear;
		CompareOp			compareOp					= CompareOp::eAlways;
		MipmapMode			mipmapMode					= MipmapMode::eNearest;
		AddressMode			addressModeU				= AddressMode::eRepeat;
		AddressMode			addressModeV				= AddressMode::eRepeat;
		AddressMode			addressModeW				= AddressMode::eRepeat;
		BorderColor			borderColor					= BorderColor::eFloatTransparentBlack;
		VkBool32			unnormalizedCoordinates		= VK_FALSE;
		VkBool32			anisotropyEnable			= VK_FALSE;
		VkBool32			compareEnable				= VK_FALSE;
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
	class Sampler : private Resource, public SamplerH
	{

	public:

		//!	@brief	Create sampler object.
		Sampler();

		//!	@brief	Destroy sampler object.
		~Sampler();

	public:

		VkResult Create(const SamplerInfo & CreateInfo = SamplerInfo());

	private:

		SamplerInfo			m_CreateInfo;
	};
}