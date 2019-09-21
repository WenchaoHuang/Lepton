/*************************************************************************
*************************    VisualVk_Sampler    *************************
*************************************************************************/
#pragma once

#include "Vulkan.h"

namespace Vk
{
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
	 *	@brief	Wrapper for Vulkan sampler object.
	 */
	class Sampler
	{
		VK_UNIQUE_RESOURCE(Sampler)

	public:

		//!	@brief	Create sampler object.
		Sampler();

		//!	@brief	Create and initialize immediately.
		explicit Sampler(VkDevice hDevice, const SamplerParam & Param = SamplerParam());

		//!	@brief	Destroy sampler object.
		~Sampler();

	public:

		//!	@brief	Return sampler parameters.
		const SamplerParam & GetParam() const { return m_Parameter; }

		//!	@brief	Create a new sampler object.
		Result Create(VkDevice hDevice, const SamplerParam & Param = SamplerParam());

		//!	@brief	Destroy the sampler.
		void Destroy();

	private:

		SamplerParam		m_Parameter;
	};
}