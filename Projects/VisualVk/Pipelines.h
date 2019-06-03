/*************************************************************************
************************    VisualVk_Pipelines    ************************
*************************************************************************/
#pragma once

#include "Framebuffer.h"
#include "ShaderModule.h"
#include "PipelineLayout.h"

namespace Vk
{
	/*********************************************************************
	*********************    GraphicsPipelineInfo    *********************
	*********************************************************************/

	/**
	 *	@brief	Creating information of Vulkan graphics pipeline.
	 */
	struct GraphicsPipelineInfo : private VkGraphicsPipelineCreateInfo
	{
		operator const VkGraphicsPipelineCreateInfo*();

		GraphicsPipelineInfo();

	private:

		/*****************************************************************
		*********************    DynamicStateInfo    *********************
		*****************************************************************/

		class DynamicStateInfo : public std::vector<VkDynamicState>
		{

		public:

			DynamicStateInfo();

			operator const VkPipelineDynamicStateCreateInfo*();

		private:

			VkPipelineDynamicStateCreateInfo	m_CreateInfo;
		};

		/*****************************************************************
		******************    InputAssemblyStateInfo    ******************
		*****************************************************************/

		class InputAssemblyStateInfo
		{

		public:

			InputAssemblyStateInfo();

			InputAssemblyStateInfo(VkPrimitiveTopology eTopology);

			operator VkPrimitiveTopology() const { return m_CreateInfo.topology; }

		private:

			VkPipelineInputAssemblyStateCreateInfo		m_CreateInfo;
		};

		/*****************************************************************
		******************    RasterizationStateInfo    ******************
		*****************************************************************/

		/**
		 *	@brief	Wrapper of VkPipelineRasterizationStateCreateInfo object.
		 */
		class RasterizationStateInfo
		{

		private:

			VkStructureType								sType						= VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
			const void *								pNext						= nullptr;
			VkPipelineRasterizationStateCreateFlags		flags						= 0;

		public:

			VkBool32									depthClampEnable			= VK_FALSE;
			VkBool32									rasterizerDiscardEnable		= VK_FALSE;
			VkPolygonMode								polygonMode					= VK_POLYGON_MODE_FILL;
			VkCullModeFlags								cullMode					= VK_CULL_MODE_NONE;
			VkFrontFace									frontFace					= VK_FRONT_FACE_COUNTER_CLOCKWISE;
			VkBool32									depthBiasEnable				= VK_FALSE;
			float										depthBiasConstantFactor		= 0.0f;
			float										depthBiasClamp				= 0.0f;
			float										depthBiasSlopeFactor		= 0.0f;
			float										lineWidth					= 1.0f;
		};

		static_assert(sizeof(RasterizationStateInfo) == sizeof(VkPipelineRasterizationStateCreateInfo), "struct and wrapper have different size!");

		/*****************************************************************
		******************    TessellationStateInfo    *******************
		*****************************************************************/

		class TessellationStateInfo
		{

		public:

			TessellationStateInfo();

			void SetPatchControlPoints(uint32_t PatchControlPoints);

		private:

			VkPipelineTessellationStateCreateInfo		m_CreateInfo;
		};

		/*****************************************************************
		******************    DepthStencilStateInfo    *******************
		*****************************************************************/

		/**
		 *	@brief	Wrapper of VkPipelineDepthStencilStateCreateInfo object.
		 */
		class DepthStencilStateInfo
		{

		private:

			VkStructureType								sType					= VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
			const void *								pNext					= nullptr;
			VkPipelineDepthStencilStateCreateFlags		flags					= 0;

		public:

			VkBool32									depthTestEnable			= VK_FALSE;
			VkBool32									depthWriteEnable		= VK_FALSE;
			VkCompareOp									depthCompareOp			= VK_COMPARE_OP_LESS_OR_EQUAL;
			VkBool32									depthBoundsTestEnable	= VK_FALSE;
			VkBool32									stencilTestEnable		= VK_FALSE;
			VkStencilOpState							front					= {};
			VkStencilOpState							back					= {};
			float										minDepthBounds			= 0.0f;
			float										maxDepthBounds			= 0.0f;
		};

		static_assert(sizeof(DepthStencilStateInfo) == sizeof(VkPipelineDepthStencilStateCreateInfo), "struct and wrapper have different size!");

		/*****************************************************************
		*******************    MultisampleStateInfo    *******************
		*****************************************************************/

		/**
		 *	@brief	Wrapper of VkPipelineMultisampleStateCreateInfo object.
		 */
		class MultisampleStateInfo
		{

		private:

			VkStructureType								sType					= VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
			const void *								pNext					= nullptr;
			VkPipelineMultisampleStateCreateFlags		flags					= 0;

		public:

			VkSampleCountFlagBits						rasterizationSamples	= VK_SAMPLE_COUNT_1_BIT;
			VkBool32									sampleShadingEnable		= VK_FALSE;
			float										minSampleShading		= 0.0f;
			const VkSampleMask *						pSampleMask				= nullptr;
			VkBool32									alphaToCoverageEnable	= VK_FALSE;
			VkBool32									alphaToOneEnable		= VK_FALSE;
		};

		static_assert(sizeof(MultisampleStateInfo) == sizeof(VkPipelineMultisampleStateCreateInfo), "struct and wrapper have different size!");

		/*****************************************************************
		*******************    VertexInputStateInfo    *******************
		*****************************************************************/

		class VertexInputStateInfo
		{

		public:

			VertexInputStateInfo();

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

		/**
		 *	@brief	Wrapper of VkPipelineColorBlendAttachmentState object.
		 */
		struct ColorBlendAttachmentState
		{
			VkBool32					blendEnable				= VK_FALSE;
			VkBlendFactor				srcColorBlendFactor		= VK_BLEND_FACTOR_ZERO;
			VkBlendFactor				dstColorBlendFactor		= VK_BLEND_FACTOR_ZERO;
			VkBlendOp					colorBlendOp			= VK_BLEND_OP_ADD;
			VkBlendFactor				srcAlphaBlendFactor		= VK_BLEND_FACTOR_ZERO;
			VkBlendFactor				dstAlphaBlendFactor		= VK_BLEND_FACTOR_ZERO;
			VkBlendOp					alphaBlendOp			= VK_BLEND_OP_ADD;
			VkColorComponentFlags		colorWriteMask			= VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		};

		static_assert(sizeof(ColorBlendAttachmentState) == sizeof(VkPipelineColorBlendAttachmentState), "struct and wrapper have different size!");

		/*****************************************************************
		*******************    ColorBlendStateInfo    ********************
		*****************************************************************/

		struct ColorBlendStateInfo : private VkPipelineColorBlendStateCreateInfo
		{
			operator const VkPipelineColorBlendStateCreateInfo*();

			using VkPipelineColorBlendStateCreateInfo::blendConstants;
			using VkPipelineColorBlendStateCreateInfo::logicOpEnable;
			using VkPipelineColorBlendStateCreateInfo::logicOp;

			std::vector<ColorBlendAttachmentState>		attachments;

			ColorBlendStateInfo();
		};

		/*****************************************************************
		********************    ViewportStateInfo    *********************
		*****************************************************************/

		class ViewportStateInfo
		{

		public:

			ViewportStateInfo();

			operator const VkPipelineViewportStateCreateInfo*();

		public:

			std::vector<VkRect2D>					Scissors;
			std::vector<VkViewport>					Viewports;

		private:

			VkPipelineViewportStateCreateInfo		m_CreateInfo;
		};

	public:

		ShaderStagesInfo						ShaderStages;
		DynamicStateInfo						DynamicStates;
		ViewportStateInfo						ViewportState;
		ColorBlendStateInfo						ColorBlendState;
		VertexInputStateInfo					VertexInputState;
		MultisampleStateInfo					MultisampleState;
		DepthStencilStateInfo					DepthStencilState;
		TessellationStateInfo					TessellationState;
		InputAssemblyStateInfo					InputAssemblyState;
		RasterizationStateInfo					RasterizationState;
		std::shared_ptr<PipelineLayout>			spPipelineLayout;
		std::shared_ptr<RenderPass>				spRenderPass;
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

		//!	@brief	Convert to VkPipeline handle.
		operator VkPipeline() const { return m_hPipeline; }

		VkResult Create(GraphicsPipelineInfo & CreateInfo);

		void Release() noexcept;

	private:

		VkPipeline						m_hPipeline;

		GraphicsPipelineInfo		m_CreateInfo;
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