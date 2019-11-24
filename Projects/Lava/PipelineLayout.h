/*************************************************************************
***********************    Lava_PipelineLayout    ************************
*************************************************************************/
#pragma once

#include "DescriptorSet.h"

namespace Lava
{
	/*********************************************************************
	**********************    PushConstantRange    ***********************
	*********************************************************************/

	/**
	 *	@brief	Structure specifying a push constant range.
	 */
	struct PushConstantRange
	{
		Flags<ShaderStage>		stageFlags		= ShaderStage::eAllGraphics;
		uint32_t				offset			= 0;
		uint32_t				size			= 0;
	};

	static_assert(sizeof(PushConstantRange) == sizeof(VkPushConstantRange), "Struct and wrapper have different size!");

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
		Result Create(VkDevice hDevice, ArrayProxy<const DescriptorSetLayout> pDescriptorSetLayouts = nullptr, ArrayProxy<const PushConstantRange> pPushConstantRanges = nullptr);

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
			UniqueHandle(VkDevice, VkPipelineLayout, const std::vector<DescriptorSetLayout>&, const std::vector<PushConstantRange>&);

			//!	@brief	Where resource will be released.
			~UniqueHandle() noexcept;

		public:

			const VkDevice								m_hDevice;
			const VkPipelineLayout						m_hPipelineLayout;
			const std::vector<PushConstantRange>		m_PushConstantRanges;
			const std::vector<DescriptorSetLayout>		m_DescriptorSetLayouts;
		};

		std::shared_ptr<UniqueHandle>					m_spUniqueHandle;
	};
}