/*************************************************************************
**********************    Lepton_PipelineLayout    ***********************
*************************************************************************/
#pragma once

#include "DescriptorSet.h"

namespace Lepton
{
	/*********************************************************************
	************************    PipelineLayout    ************************
	*********************************************************************/

	/**
	 *	@brief	Wrapper for Vulkan pipeline layout object.
	 */
	class PipelineLayout
	{

	public:

		//!	@brief	Whether this resource handle is valid.
		bool IsValid() const { return m_spUniqueHandle != nullptr; }

		//!	@brief	Return VkDevice handle.
		VkDevice GetDeviceHandle() const { return (m_spUniqueHandle != nullptr) ? m_spUniqueHandle->m_hDevice : VK_NULL_HANDLE; }
		
		//!	@brief	Return array of descriptor set layouts.
		const std::vector<DescriptorSetLayout> & GetDescriptorSetLayouts() const { return m_spUniqueHandle->m_DescriptorSetLayouts; }

		//!	@brief	Create a new pipeline layout.
		Result Create(VkDevice hDevice, vk::ArrayProxy<DescriptorSetLayout> pDescriptorSetLayouts = nullptr, vk::ArrayProxy<vk::PushConstantRange> pPushConstantRanges = nullptr);

		//!	@brief	Convert to VkPipelineLayout.
		operator VkPipelineLayout() const { return m_spUniqueHandle != nullptr ? m_spUniqueHandle->m_hPipelineLayout : VK_NULL_HANDLE; }

	private:

		/**
		 *	@brief	Unique handle of pipeline layout.
		 */
		struct UniqueHandle
		{
			LAVA_NONCOPYABLE(UniqueHandle)

		public:

			//!	@brief	Constructor (handles must be initialized).
			UniqueHandle(VkDevice, VkPipelineLayout, const std::vector<DescriptorSetLayout>&, const std::vector<vk::PushConstantRange>&);

			//!	@brief	Where resource will be released.
			~UniqueHandle() noexcept;

		public:

			const VkDevice								m_hDevice;
			const VkPipelineLayout						m_hPipelineLayout;
			const std::vector<vk::PushConstantRange>	m_PushConstantRanges;
			const std::vector<DescriptorSetLayout>		m_DescriptorSetLayouts;
		};

		std::shared_ptr<UniqueHandle>					m_spUniqueHandle;
	};
}