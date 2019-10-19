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
	****************************    Sampler   ****************************
	*********************************************************************/

	/**
	 *	@brief	Wrapper for Vulkan sampler object.
	 */
	class Sampler
	{

	public:

		//!	@brief	Invalidate this resource handle.
		void Destroy() { m_spHandle.reset(); }

		//!	@brief	Whether this resource handle is valid.
		bool IsValid() const { return m_spHandle != nullptr; }

		//!	@brief	Return constant reference to its parameter (must be valid).
		const SamplerParam & GetParam() const { return m_spHandle->m_Parameter; }

		//!	@brief	Create a new sampler object.
		Result Create(VkDevice hDevice, const SamplerParam & Param = SamplerParam());

		//!	@brief	Convert to VkSampler.
		operator VkSampler() const { return (m_spHandle != nullptr) ? m_spHandle->m_hSampler : VK_NULL_HANDLE; }

	private:

		/**
		 *	@brief	Unique handle of Vulkan resource.
		 */
		struct UniqueHandle
		{
			VK_NONCOPYABLE(UniqueHandle)

		public:

			//!	@brief	Constructor (all handles must be generated outside).
			UniqueHandle(VkDevice, VkSampler, const SamplerParam&);

			//!	@brief	Where resource will be released.
			~UniqueHandle() noexcept;

		public:

			const VkDevice					m_hDevice;
			const VkSampler					m_hSampler;
			const SamplerParam				m_Parameter;
		};

		std::shared_ptr<UniqueHandle>		m_spHandle;
	};
}