/*************************************************************************
*********************    VisualVk_PipelineLayout    **********************
*************************************************************************/
#pragma once

#include <map>
#include <memory>
#include "Resource.h"
#include "ShaderModule.h"

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
		eSampler					= VK_DESCRIPTOR_TYPE_SAMPLER,
		eSampledImage				= VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,
		eStorageImage				= VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,
		eUniformBuffer				= VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
		eStorageBuffer				= VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
		eInputAttachment			= VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT,
		eStorageTexelBuffer			= VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER,
		eUniformTexelBuffer			= VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER,
		eCombinedImageSampler		= VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
		eUniformBufferDynamic		= VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC,
		eStorageBufferDynamic		= VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC,
		eInlineUniformBlockEXT		= VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK_EXT,
		eAccelerationStructureNV	= VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV
	};

	/*********************************************************************
	*************************    ImageLayout    **************************
	*********************************************************************/

	/**
	 *	@brief	Layout of image and image subresources.
	 */
	enum class ImageLayout
	{
		eGeneral									= VK_IMAGE_LAYOUT_GENERAL,
		eUndefined									= VK_IMAGE_LAYOUT_UNDEFINED,
		ePreinitialized								= VK_IMAGE_LAYOUT_PREINITIALIZED,
		eTransferSrcOptimal							= VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
		eTransferDstOptimal							= VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
		eShaderReadOnlyOptimal						= VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
		eColorAttachmentOptimal						= VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
		eDepthStencilReadOnlyOptimal				= VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL,
		eDepthStencilAttachmentOptimal				= VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
		eDepthReadOnlyStencilAttachmentOptimal		= VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL,
		eDepthAttachmentStencilReadOnlyOptimal		= VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL,
		eDepthAttachmentStencilReadOnlyOptimalKHR	= VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL_KHR,
		eDepthReadOnlyStencilAttachmentOptimalKHR	= VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL_KHR,
		eFragmentDensityMapOptimalEXT				= VK_IMAGE_LAYOUT_FRAGMENT_DENSITY_MAP_OPTIMAL_EXT,
		eShadingRateOptimalNV						= VK_IMAGE_LAYOUT_SHADING_RATE_OPTIMAL_NV,
		eSharedPresentKHR							= VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR,
		ePresentSrcKHR								= VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
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
			constantRanges.push_back({ StageFlags, OffsetBytes, SizeBytes });
		}
		
		//!	@brief	Specify descriptor set layout binding.
		template<uint32_t Binding> void SetBinding(Flags<ShaderStage> StageFlags, DescriptorType eDescriptorType, uint32_t DescriptorCount)
		{
			layoutBindings[Binding] = { StageFlags, eDescriptorType, DescriptorCount };
		}

	private:

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

		//!	@brief	Update the contents of descriptor set.
		VkBool32 Write(uint32_t DstBinding, uint32_t DstArrayElement, VkBuffer hBuffer, VkDeviceSize OffsetBytes, VkDeviceSize SizeBytes);

		//!	@brief	Update the content of descriptor set.
		VkBool32 Write(uint32_t DstBinding, uint32_t DstArrayElement, VkSampler hSampler, VkImageView hImageView, ImageLayout eImageLayout);

	private:

		const VkDescriptorSet					m_hDescriptorSet;

		const VkDescriptorPool					m_hDescriptorPool;

		std::map<uint32_t, LayoutBinding>		m_LayoutBindings;
	};
}