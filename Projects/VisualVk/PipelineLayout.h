/*************************************************************************
*********************    VisualVk_PipelineLayout    **********************
*************************************************************************/
#pragma once

#include <map>
#include "Enum.h"
#include "Flags.h"
#include "Handle.h"
#include "Resource.h"

namespace Vk
{
	class DescriptorSet;

	/*********************************************************************
	************************    DescriptorType    ************************
	*********************************************************************/

	/**
	 *	@brief	Specifies the type of a descriptor in a descriptor set.
	 */
	enum class DescriptorType
	{
		eSampler						= VK_DESCRIPTOR_TYPE_SAMPLER,
		eSampledImage					= VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,
		eStorageImage					= VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,
		eUniformBuffer					= VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
		eStorageBuffer					= VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
		eInputAttachment				= VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT,
		eStorageTexelBuffer				= VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER,
		eUniformTexelBuffer				= VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER,
		eCombinedImageSampler			= VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
		eUniformBufferDynamic			= VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC,
		eStorageBufferDynamic			= VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC,
		eAccelerationStructureNV		= VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV,
		eInlineUniformBlockEXT			= VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK_EXT
	};

	/*********************************************************************
	******************    DescriptorSetLayoutBinding    ******************
	*********************************************************************/

	/**
	 *	@brief	Descriptor set layout binding object.
	 */
	struct LayoutBinding
	{
		Flags<ShaderStage>		stageFlags			= ShaderStage::eAllGraphics;
		DescriptorType			descriptorType		= DescriptorType::eSampler;
		uint32_t				descriptorCount		= 1;
	};

	/*********************************************************************
	**********************    PipelineLayoutInfo    **********************
	*********************************************************************/

	/**
	 *	@brief	Creating information of Vulkan pipeline layout object.
	 */
	class PipelineLayoutInfo
	{

	public:

		friend class PipelineLayout;

		//!	@brief	Specify push constant range.
		void PushConstantRange(Flags<ShaderStage> StageFlags, uint32_t OffsetBytes, uint32_t SizeBytes)
		{
			m_ConstantRanges.push_back({ StageFlags, OffsetBytes, SizeBytes });
		}
		
		//!	@brief	Specify descriptor set layout binding.
		template<uint32_t Binding> void SetBinding(Flags<ShaderStage> StageFlags, DescriptorType eDescriptorType, uint32_t DescriptorCount)
		{
			m_LayoutBindings[Binding] = { StageFlags, eDescriptorType, DescriptorCount };
		}

	private:

		std::vector<VkPushConstantRange>		m_ConstantRanges;

		std::map<uint32_t, LayoutBinding>		m_LayoutBindings;
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

		//!	@brief	Update the contents of descriptor set.
		VkBool32 WriteBuffer(uint32_t DstBinding, uint32_t DstArrayElement, VkBuffer hBuffer, VkDeviceSize OffsetBytes, VkDeviceSize SizeBytes);

		//!	@brief	Update the content of descriptor set.
		VkBool32 WriteSampler(uint32_t DstBinding, uint32_t DstArrayElement, VkSampler hSampler, VkImageView hImageView, ImageLayout eImageLayout);

	private:

		const VkDescriptorSet					m_hDescriptorSet;

		const VkDescriptorPool					m_hDescriptorPool;

		std::map<uint32_t, LayoutBinding>		m_LayoutBindings;
	};
}