/*************************************************************************
***************************    Lava_Sampler    ***************************
*************************************************************************/
#pragma once

#include "Vulkan.h"

namespace Lava
{
	/*********************************************************************
	*************************    SamplerParam    *************************
	*********************************************************************/

	/**
	 *	@brief	Structure specifying parameters of a sampler.
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
	****************************    Sampler   ****************************
	*********************************************************************/

	/**
	 *	@brief	Wrapper for Vulkan sampler object.
	 */
	class Sampler
	{

	public:

		//!	@brief	Invalidate this resource handle.
		void Destroy() { m_spUniqueHandle.reset(); }

		//!	@brief	Whether this resource handle is valid.
		bool IsValid() const { return m_spUniqueHandle != nullptr; }

		//!	@brief	Create a new sampler object.
		Result Create(VkDevice hDevice, const SamplerParam & Param = SamplerParam());

		//!	@brief	Return constant reference to its parameter (must be valid).
		const SamplerParam & GetParam() const { return m_spUniqueHandle->m_Parameter; }

		//!	@brief	Convert to VkSampler.
		operator VkSampler() const { return (m_spUniqueHandle != nullptr) ? m_spUniqueHandle->m_hSampler : VK_NULL_HANDLE; }

	private:

		/**
		 *	@brief	Unique handle of sampler.
		 */
		struct UniqueHandle
		{
			LAVA_NONCOPYABLE(UniqueHandle)

		public:

			//!	@brief	Constructor (handles must be initialized).
			UniqueHandle(VkDevice, VkSampler, const SamplerParam&);

			//!	@brief	Where resource will be released.
			~UniqueHandle() noexcept;

		public:

			const VkDevice					m_hDevice;
			const VkSampler					m_hSampler;
			const SamplerParam				m_Parameter;
		};

		std::shared_ptr<UniqueHandle>		m_spUniqueHandle;
	};
}