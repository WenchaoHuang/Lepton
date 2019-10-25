/*************************************************************************
*********************    VisualVk_PipelineLayout    **********************
*************************************************************************/
#pragma once

#include "DescriptorSet.h"

namespace Vk
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


		Result Create(VkDevice hDevice,
					  ArrayProxy<const DescriptorSetLayout> pDescriptorSetLayouts = nullptr,
					  ArrayProxy<const PushConstantRange> pPushConstantRanges = nullptr);
		

	private:

		/**
		 *	@brief	Unique handle of pipeline layout.
		 */
		struct UniqueHandle
		{
			VK_NONCOPYABLE(UniqueHandle)

		public:

			//!	@brief	Constructor (all handles must be generated outside).
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