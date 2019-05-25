/*************************************************************************
*************************    VisualVk_Sampler    *************************
*************************************************************************/
#pragma once

#include "Resource.h"

namespace Vk
{
	/*********************************************************************
	**********************    SamplerCreateInfo    ***********************
	*********************************************************************/

	/**
	 *	@brief	Wrapper of VkSamplerCreateInfo object.
	 */
	class SamplerCreateInfo
	{

	private:

		VkStructureType				sType						= VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
		const void *				pNext						= nullptr;
		VkSamplerCreateFlags		flags						= 0;

	public:

		VkFilter					magFilter					= VK_FILTER_LINEAR;
		VkFilter					minFilter					= VK_FILTER_LINEAR;
		VkSamplerMipmapMode			mipmapMode					= VK_SAMPLER_MIPMAP_MODE_NEAREST;
		VkSamplerAddressMode		addressModeU				= VK_SAMPLER_ADDRESS_MODE_REPEAT;
		VkSamplerAddressMode		addressModeV				= VK_SAMPLER_ADDRESS_MODE_REPEAT;
		VkSamplerAddressMode		addressModeW				= VK_SAMPLER_ADDRESS_MODE_REPEAT;
		float						mipLodBias					= 0.0f;
		VkBool32					anisotropyEnable			= VK_FALSE;
		float						maxAnisotropy				= 1.0f;
		VkBool32					compareEnable				= VK_FALSE;
		VkCompareOp					compareOp					= VK_COMPARE_OP_ALWAYS;
		float						minLod						= 0.0f;
		float						maxLod						= 0.0f;
		VkBorderColor				borderColor					= VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK;
		VkBool32					unnormalizedCoordinates		= VK_FALSE;
	};

	static_assert(sizeof(SamplerCreateInfo) == sizeof(VkSamplerCreateInfo), "struct and wrapper have different size!");

	/*********************************************************************
	***************************    Sampler    ****************************
	*********************************************************************/

	class Sampler : private Resource
	{

	public:

		Sampler();

		~Sampler();

	public:

		operator VkSampler() const { return m_hSampler; }

		VkResult Create(const SamplerCreateInfo & CreateInfo);

		VkBool32 IsValid() const { return m_hSampler != VK_NULL_HANDLE; }

		void Release() noexcept;

	private:

		VkSampler				m_hSampler;

		SamplerCreateInfo		m_CreateInfo;
	};
}