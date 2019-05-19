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

		struct DynamicStateCreateInfo : private VkPipelineDynamicStateCreateInfo, public std::vector<VkDynamicState>
		{
			operator const VkPipelineDynamicStateCreateInfo*();

			DynamicStateCreateInfo();
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

		struct InputAssemblyStateCreateInfo : private VkPipelineInputAssemblyStateCreateInfo
		{
			operator const VkPipelineInputAssemblyStateCreateInfo*() { return this; }

			using VkPipelineInputAssemblyStateCreateInfo::topology;

			InputAssemblyStateCreateInfo();
		};

		/*****************************************************************
		***************    TessellationStateCreateInfo    ****************
		*****************************************************************/

		struct TessellationStateCreateInfo : private VkPipelineTessellationStateCreateInfo
		{
			operator const VkPipelineTessellationStateCreateInfo*() { return this; }

			using VkPipelineTessellationStateCreateInfo::patchControlPoints;

			TessellationStateCreateInfo();
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

		class VertexInputStateCreateInfo : private VkPipelineVertexInputStateCreateInfo
		{

		public:

			VertexInputStateCreateInfo();

			operator const VkPipelineVertexInputStateCreateInfo*();

			void SetAttribute(uint32_t Binding, uint32_t Location, VkFormat eFormat, uint32_t Offset);

			void SetBinding(uint32_t Binding, uint32_t Stride, VkVertexInputRate eInputRate = VK_VERTEX_INPUT_RATE_VERTEX);

		private:

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

		struct ViewportStateCreateInfo : private VkPipelineViewportStateCreateInfo
		{
			operator const VkPipelineViewportStateCreateInfo*();

			std::vector<VkViewport>		Viewports;
			std::vector<VkRect2D>		Scissors;

			ViewportStateCreateInfo();
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