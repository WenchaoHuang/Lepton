/*************************************************************************
*********************    VisualVk_PipelineLayout    **********************
*************************************************************************/
#pragma once

#include <map>
#include <memory>
#include "Resource.h"

namespace Vk
{
	class DescriptorSet;

	/*********************************************************************
	******************    DescriptorSetLayoutBinding    ******************
	*********************************************************************/

	/**
	 *	@brief	Descriptor set layout binding object.
	 */
	struct LayoutBinding
	{
		VkShaderStageFlags		stageFlags			= VK_SHADER_STAGE_ALL_GRAPHICS;
		VkDescriptorType		descriptorType		= VK_DESCRIPTOR_TYPE_SAMPLER;
		uint32_t				descriptorCount		= 1;
	};

	/*********************************************************************
	**********************    PipelineLayoutInfo    **********************
	*********************************************************************/

	/**
	 *	@brief	Creating information of Vulkan pipeline layout object.
	 */
	struct PipelineLayoutInfo
	{

	public:

		//!	@brief	Specify push constant range.
		void PushConstantRange(VkShaderStageFlags eStageFlags, uint32_t OffsetBytes, uint32_t SizeBytes);

		//!	@brief	Specify descriptor set layout binding.
		void SetBinding(uint32_t Binding, VkShaderStageFlags eStageFlags, VkDescriptorType eDescriptorType, uint32_t DescriptorCount);

	public:

		std::vector<VkPushConstantRange>		constantRanges;

		std::map<uint32_t, LayoutBinding>		layoutBindings;
	};

	/*********************************************************************
	************************    PipelineLayout    ************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan pipeline layout object.
	 */
	class PipelineLayout : private Resource
	{

	public:

		//!	@brief	Create pipeline layout object.
		PipelineLayout(VkPipelineLayout hPipelineLayout = VK_NULL_HANDLE,
					   VkDescriptorSetLayout hDescriptorSetLayout = VK_NULL_HANDLE,
					   const PipelineLayoutInfo & LayoutInfo = PipelineLayoutInfo());

		//!	@brief	Destroy pipeline layout object.
		~PipelineLayout() noexcept;

	public:

		//!	@brief	Create a new descriptor set object.
		std::shared_ptr<DescriptorSet> CreateDescriptorSet();

		//!	@brief	Create a new pipeline layout object.
		static std::shared_ptr<PipelineLayout> Create(const PipelineLayoutInfo & CreateInfo = PipelineLayoutInfo());

		//!	@brief	If pipeline layout handle is valid.
		VkBool32 IsValid() const { return m_hPipelineLayout != VK_NULL_HANDLE; }

		//!	@brief	Return the VkPipelineLayout handle.
		VkPipelineLayout GetHandle() const { return m_hPipelineLayout; }

	private:

		const VkPipelineLayout					m_hPipelineLayout;

		const PipelineLayoutInfo				m_PipelineLayoutInfo;

		const VkDescriptorSetLayout				m_hDescriptorSetLayout;

		std::vector<VkDescriptorPoolSize>		m_DescriptorPoolSizes;
	};

	/*********************************************************************
	************************    DescriptorSet    *************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan Descriptor set object.
	 */
	class DescriptorSet : private Resource
	{

	public:

		friend class PipelineLayout;

		//!	@brief	Create descriptor set object.
		DescriptorSet(VkDescriptorSet hDescriptorSet = VK_NULL_HANDLE,
					  VkDescriptorPool hDescriptorPool = VK_NULL_HANDLE);

		//!	@brief	Destroy descriptor set object.
		~DescriptorSet() noexcept;

	public:

		//!	@brief	Return the VkDescriptorSet handle.
		VkDescriptorSet GetHandle() const { return m_hDescriptorSet; }

		//!	@brief	Update the content of descriptor set.
		VkBool32 Write(uint32_t DstBinding, uint32_t EstArrayElement, const VkDescriptorImageInfo & ImageInfo);

		//!	@brief	Update the contents of descriptor set.
		VkBool32 Write(uint32_t DstBinding, uint32_t EstArrayElement, const VkDescriptorBufferInfo & BufferInfo);

	private:

		const VkDescriptorSet					m_hDescriptorSet;

		const VkDescriptorPool					m_hDescriptorPool;

		std::map<uint32_t, LayoutBinding>		m_LayoutBindings;
	};
}