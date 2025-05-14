/*************************************************************************
**************************    Lepton_Sampler    **************************
*************************************************************************/
#pragma once

#include "Vulkan.h"

namespace Lepton
{
	/*********************************************************************
	*************************    SamplerParam    *************************
	*********************************************************************/

	/**
	 *	@brief	Structure specifying parameters of a sampler.
	 */
	struct SamplerParam
	{
		vk::Filter					magFilter					= vk::Filter::eNearest;
		vk::Filter					minFilter					= vk::Filter::eNearest;
		vk::CompareOp				compareOp					= vk::CompareOp::eNever;
		vk::SamplerMipmapMode		mipmapMode					= vk::SamplerMipmapMode::eNearest;
		vk::SamplerAddressMode		addressModeU				= vk::SamplerAddressMode::eRepeat;
		vk::SamplerAddressMode		addressModeV				= vk::SamplerAddressMode::eRepeat;
		vk::SamplerAddressMode		addressModeW				= vk::SamplerAddressMode::eRepeat;
		vk::BorderColor				borderColor					= vk::BorderColor::eFloatTransparentBlack;
		vk::Bool32					unnormalizedCoordinates		= false;
		vk::Bool32					anisotropyEnable			= false;
		vk::Bool32					compareEnable				= false;
		float						maxAnisotropy				= 1.0f;
		float						mipLodBias					= 0.0f;
		float						minLod						= 0.0f;
		float						maxLod						= 0.0f;
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

		//!	@brief	Return constant pointer to its parameter (must be valid).
		const SamplerParam * operator->() const { return &m_spUniqueHandle->m_Parameter; }

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