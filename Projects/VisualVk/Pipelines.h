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

	class PipelineLayout : private Resource
	{

	public:

		PipelineLayout();

		~PipelineLayout() noexcept;

	public:

		operator VkPipelineLayout() { return m_hPipelineLayout; }

		VkBool32 IsValid() const { return m_hPipelineLayout != VK_NULL_HANDLE; }

		VkResult Create(const std::vector<VkDescriptorSetLayout> & DescriptorSetLayouts = std::vector<VkDescriptorSetLayout>(),
						const std::vector<VkPushConstantRange> & PushConstantRanges = std::vector<VkPushConstantRange>());

		void Release() noexcept;

	private:

		VkPipelineLayout						m_hPipelineLayout;

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

			using VkPipelineInputAssemblyStateCreateInfo::primitiveRestartEnable;
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

		struct VertexInputStateCreateInfo : private VkPipelineVertexInputStateCreateInfo
		{
			operator const VkPipelineVertexInputStateCreateInfo*();

			std::vector<VkVertexInputAttributeDescription>		attributeDescriptions;
			std::vector<VkVertexInputBindingDescription>		bindingDescriptions;

			VertexInputStateCreateInfo();
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

	//	PipelineShaderStages				ShaderStages;
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

		GraphicsPipeline();

		~GraphicsPipeline();

	public:

		VkResult Create(GraphicsPipelineCreateInfo & CreateInfo, std::shared_ptr<RenderPass> spRenderPass);

		void Release() noexcept;
		
	private:

		VkPipeline						m_hPipeline;

		GraphicsPipelineCreateInfo		m_CreateInfo;
	};
}