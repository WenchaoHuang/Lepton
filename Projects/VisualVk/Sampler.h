/*************************************************************************
*************************    VisualVk_Sampler    *************************
*************************************************************************/
#pragma once

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
	**************************    CompareOp    ***************************
	*********************************************************************/

	/**
	 *	@brief	Stencil comparison function.
	 */
	enum class CompareOp
	{
		eLess				= VK_COMPARE_OP_LESS,
		eEqual				= VK_COMPARE_OP_EQUAL,
		eNever				= VK_COMPARE_OP_NEVER,
		eAlways				= VK_COMPARE_OP_ALWAYS,
		eGreater			= VK_COMPARE_OP_GREATER,
		eNotEqual			= VK_COMPARE_OP_NOT_EQUAL,
		eLessOrEqual		= VK_COMPARE_OP_LESS_OR_EQUAL,
		eGreaterOrEqual		= VK_COMPARE_OP_GREATER_OR_EQUAL
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
	class Sampler : private Resource
	{

	public:

		Sampler();

		~Sampler();

	public:

		operator VkSampler() const { return m_hSampler; }

		VkResult Create(const SamplerInfo & CreateInfo);

		VkBool32 IsValid() const { return m_hSampler != VK_NULL_HANDLE; }

		void Release() noexcept;

	private:

		VkSampler			m_hSampler;

		SamplerInfo			m_CreateInfo;
	};



}