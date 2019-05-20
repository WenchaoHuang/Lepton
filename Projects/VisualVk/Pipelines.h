/*************************************************************************
************************    VisualVk_Pipelines    ************************
*************************************************************************/
#pragma once

#include "Descriptor.h"
#include "Framebuffer.h"
#include "ShaderModule.h"

namespace Vk
{
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
		PipelineLayout(VkPipelineLayout hPipelineLayout = VK_NULL_HANDLE);

		//!	@brief	Destroy pipeline layout object.
		~PipelineLayout() noexcept;

	public:

		//!	@brief	Return Vulkan handle.
		VkPipelineLayout GetHandle() const { return m_hPipelineLayout; }

		//!	@brief	If pipeline layout handle is valid.
		VkBool32 IsValid() const { return m_hPipelineLayout != VK_NULL_HANDLE; }

		//!	@brief	Create a new pipeline layout object.
		static std::shared_ptr<PipelineLayout> Create(const std::vector<VkDescriptorSetLayout> & DescriptorSetLayouts = std::vector<VkDescriptorSetLayout>(),
													  const std::vector<VkPushConstantRange> & PushConstantRanges = std::vector<VkPushConstantRange>());

	private:

		const VkPipelineLayout					m_hPipelineLayout;

		std::vector<VkPushConstantRange>		m_PushConstantRanges;

		std::vector<VkDescriptorSetLayout>		m_DescriptorSetLayouts;
	};

	/*********************************************************************
	******************    GraphicsPipelineCreateInfo    ******************
	*********************************************************************/

	/**
	 *	@brief	Creating information of Vulkan graphics pipeline.
	 */
	struct GraphicsPipelineCreateInfo : private VkGraphicsPipelineCreateInfo
	{
		operator const VkGraphicsPipelineCreateInfo*();

		GraphicsPipelineCreateInfo();

	private:

		/*****************************************************************
		******************    DynamicStateCreateInfo    ******************
		*****************************************************************/

		class DynamicStateCreateInfo : public std::vector<VkDynamicState>
		{

		public:

			DynamicStateCreateInfo();

			operator const VkPipelineDynamicStateCreateInfo*();

		private:

			VkPipelineDynamicStateCreateInfo	m_CreateInfo;
		};

		/*****************************************************************
		***************    RasterizationStateCreateInfo    ***************
		*****************************************************************/

		struct RasterizationStateCreateInfo : private VkPipelineRasterizationStateCreateInfo
		{
			operator const VkPipelineRasterizationStateCreateInfo*() { return this; }

			using VkPipelineRasterizationStateCreateInfo::rasterizerDiscardEnable;
			using VkPipelineRasterizationStateCreateInfo::depthBiasConstantFactor;
			using VkPipelineRasterizationStateCreateInfo::depthBiasSlopeFactor;
			using VkPipelineRasterizationStateCreateInfo::depthClampEnable;
			using VkPipelineRasterizationStateCreateInfo::depthBiasEnable;
			using VkPipelineRasterizationStateCreateInfo::depthBiasClamp;
			using VkPipelineRasterizationStateCreateInfo::polygonMode;
			using VkPipelineRasterizationStateCreateInfo::frontFace;
			using VkPipelineRasterizationStateCreateInfo::lineWidth;
			using VkPipelineRasterizationStateCreateInfo::cullMode;

			RasterizationStateCreateInfo();
		};

		/*****************************************************************
		***************    InputAssemblyStateCreateInfo    ***************
		*****************************************************************/

		class InputAssemblyStateCreateInfo
		{

		public:

			InputAssemblyStateCreateInfo();

			void operator=(VkPrimitiveTopology eTopology);

			operator const VkPipelineInputAssemblyStateCreateInfo*();

			operator VkPrimitiveTopology() const { return m_CreateInfo.topology; }

		private:

			VkPipelineInputAssemblyStateCreateInfo		m_CreateInfo;
		};

		/*****************************************************************
		***************    TessellationStateCreateInfo    ****************
		*****************************************************************/

		class TessellationStateCreateInfo
		{

		public:

			TessellationStateCreateInfo();

			operator const VkPipelineTessellationStateCreateInfo*();

			void SetPatchControlPoints(uint32_t PatchControlPoints);

		private:

			VkPipelineTessellationStateCreateInfo		m_CreateInfo;
		};

		/*****************************************************************
		***************    DepthStencilStateCreateInfo    ****************
		*****************************************************************/

		struct DepthStencilStateCreateInfo : private VkPipelineDepthStencilStateCreateInfo
		{
			operator const VkPipelineDepthStencilStateCreateInfo*() { return this; }

			using VkPipelineDepthStencilStateCreateInfo::depthBoundsTestEnable;
			using VkPipelineDepthStencilStateCreateInfo::stencilTestEnable;
			using VkPipelineDepthStencilStateCreateInfo::depthWriteEnable;
			using VkPipelineDepthStencilStateCreateInfo::depthTestEnable;
			using VkPipelineDepthStencilStateCreateInfo::depthCompareOp;
			using VkPipelineDepthStencilStateCreateInfo::minDepthBounds;
			using VkPipelineDepthStencilStateCreateInfo::maxDepthBounds;
			using VkPipelineDepthStencilStateCreateInfo::front;
			using VkPipelineDepthStencilStateCreateInfo::back;

			DepthStencilStateCreateInfo();
		};

		/*****************************************************************
		****************    MultisampleStateCreateInfo    ****************
		*****************************************************************/

		struct MultisampleStateCreateInfo : private VkPipelineMultisampleStateCreateInfo
		{
			operator const VkPipelineMultisampleStateCreateInfo*() { return this; }

			using VkPipelineMultisampleStateCreateInfo::alphaToCoverageEnable;
			using VkPipelineMultisampleStateCreateInfo::rasterizationSamples;
			using VkPipelineMultisampleStateCreateInfo::sampleShadingEnable;
			using VkPipelineMultisampleStateCreateInfo::minSampleShading;
			using VkPipelineMultisampleStateCreateInfo::alphaToOneEnable;

			MultisampleStateCreateInfo();
		};

		/*****************************************************************
		****************    VertexInputStateCreateInfo    ****************
		*****************************************************************/

		class VertexInputStateCreateInfo
		{

		public:

			VertexInputStateCreateInfo();

			operator const VkPipelineVertexInputStateCreateInfo*();

			void SetAttribute(uint32_t Binding, uint32_t Location, VkFormat eFormat, uint32_t Offset);

			void SetBinding(uint32_t Binding, uint32_t Stride, VkVertexInputRate eInputRate = VK_VERTEX_INPUT_RATE_VERTEX);

		private:

			VkPipelineVertexInputStateCreateInfo				m_CreateInfo;
			std::vector<VkVertexInputBindingDescription>		m_BindingDescriptions;
			std::vector<VkVertexInputAttributeDescription>		m_AttributeDescriptions;
		};

		/*****************************************************************
		****************    ColorBlendAttachmentState    *****************
		*****************************************************************/

		struct ColorBlendAttachmentState : public VkPipelineColorBlendAttachmentState
		{
			ColorBlendAttachmentState();
		};

		struct ColorBlendStateCreateInfo : private VkPipelineColorBlendStateCreateInfo
		{
			operator const VkPipelineColorBlendStateCreateInfo*();

			using VkPipelineColorBlendStateCreateInfo::blendConstants;
			using VkPipelineColorBlendStateCreateInfo::logicOpEnable;
			using VkPipelineColorBlendStateCreateInfo::logicOp;

			std::vector<ColorBlendAttachmentState>		attachments;

			ColorBlendStateCreateInfo();
		};

		/*****************************************************************
		*****************    ViewportStateCreateInfo    ******************
		*****************************************************************/

		class ViewportStateCreateInfo
		{

		public:

			ViewportStateCreateInfo();

			operator const VkPipelineViewportStateCreateInfo*();

		public:

			std::vector<VkRect2D>					Scissors;
			std::vector<VkViewport>					Viewports;

		private:

			VkPipelineViewportStateCreateInfo		m_CreateInfo;
		};

	public:

		PipelineShaderStages				ShaderStages;
		DynamicStateCreateInfo				DynamicStates;
		ViewportStateCreateInfo				ViewportState;
		ColorBlendStateCreateInfo			ColorBlendState;
		VertexInputStateCreateInfo			VertexInputState;
		MultisampleStateCreateInfo			MultisampleState;
		DepthStencilStateCreateInfo			DepthStencilState;
		TessellationStateCreateInfo			TessellationState;
		InputAssemblyStateCreateInfo		InputAssemblyState;
		RasterizationStateCreateInfo		RasterizationState;
		std::shared_ptr<PipelineLayout>		spPipelineLayout;
		std::shared_ptr<RenderPass>			spRenderPass;
	};

	/*********************************************************************
	***********************    GraphicsPipeline    ***********************
	*********************************************************************/

	/**
	 *	@brief	Vulkan graphics pipeline object.
	 */
	class GraphicsPipeline : private Resource
	{

	public:

		//!	@brief	Create graphics pipeline object.
		GraphicsPipeline();

		//!	@brief	Destroy graphics pipeline object.
		~GraphicsPipeline();

	public:

		operator VkPipeline() const { return m_hPipeline; }

		VkResult Create(GraphicsPipelineCreateInfo & CreateInfo);

		void Release() noexcept;

	private:

		VkPipeline						m_hPipeline;

		GraphicsPipelineCreateInfo		m_CreateInfo;
	};

	/*********************************************************************
	***********************    ComputePipeline    ************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan compute pipeline object.
	 */
	class ComputePipeline : private Resource
	{

	public:

		//!	@brief	Create compute pipeline object.
		ComputePipeline() {}

		//!	@brief	Destroy compute pipeline object.
		~ComputePipeline() {}
		
	public:



	private:

		VkPipeline			m_hPipeline;
	};
}