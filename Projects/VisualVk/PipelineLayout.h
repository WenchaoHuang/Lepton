/*************************************************************************
*********************    VisualVk_PipelineLayout    **********************
*************************************************************************/
#pragma once

#include <set>
#include <map>
#include "Vulkan.h"

namespace Vk
{
	/*********************************************************************
	*********************    DescriptorSetLayout    **********************
	*********************************************************************/

	/**
	 *	@brief	Structure specifying a descriptor.
	 */
	struct Descriptor
	{
		Flags<ShaderStage>		stageFlags				= ShaderStage::eAllGraphics;
		DescriptorType			descriptorType			= DescriptorType::eSampler;
		uint32_t				descriptorCount			= 1;
	};

	typedef std::map<uint32_t, Descriptor>		DescriptorSetLayout;

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
		VK_UNIQUE_RESOURCE(PipelineLayout)

	public:

		//!	@brief	Create and initialize immediately.
		explicit PipelineLayout(VkDevice hDevice,
								ArrayProxy<const DescriptorSetLayout> descriptorSetLayouts = nullptr,
								ArrayProxy<const PushConstantRange> pushConstantRanges = nullptr);

		//!	@brief	Destroy pipeline layout object.
		~PipelineLayout();

	public:

		//!	@brief	Destroy the descriptor set object.
		Result DestroyDescriptorSet(DescriptorSet * pDescriptorSet);

		//!	@brief	Create a new descriptor set object.
		DescriptorSet * CreateDescriptorSet();

	private:

		std::set<DescriptorSet*>				m_pDescriptorSets;

		std::vector<PushConstantRange>			m_PushConstantRanges;

		std::vector<DescriptorSetLayout>		m_DescriptorSetLayouts;

		std::vector<VkDescriptorSetLayout>		m_hDescriptorSetLayouts;
	};

	/*********************************************************************
	************************    DescriptorSet    *************************
	*********************************************************************/

	/**
	 *	@brief	Wrapper for Vulkan descriptor set object.
	 */
	class DescriptorSet
	{
		friend class PipelineLayout;

	private:

		//!	@brief	Create descriptor set object.
		DescriptorSet(VkDevice hDevice, VkDescriptorPool hDescriptorPool, VkDescriptorSet hDescriptorSet);

		//!	@brief	Destroy descriptor set object.
		~DescriptorSet() noexcept;

	public:

		//!	@brief	Return Vulkan type of this object.
		VkDescriptorSet GetHandle() const { return m_hDescriptorSet; }

	private:

		const VkDevice				m_hDevice;

		const VkDescriptorSet		m_hDescriptorSet;

		const VkDescriptorPool		m_hDescriptorPool;
	};
}