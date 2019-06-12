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
	struct GraphicsPipelineInfo
	{

	public:

		//!	@brief	Construction.
		GraphicsPipelineInfo();

	private:

		//!	@brief	Tessellation state information.
		using TessellationStateInfo = uint32_t;

		//!	@brief	Input assembly state information. 
		using InputAssemblyStateInfo = VkPrimitiveTopology;

		//!	@brief	Dynamic states information.
		using DynamicStateInfo = std::vector<VkDynamicState>;

		/*****************************************************************
		********************    ViewportStateInfo    *********************
		*****************************************************************/

		/**
		 *	@brief	Viewport stage information.
		 */
		struct ViewportStateInfo
		{
			std::vector<VkRect2D>				scissors;
			std::vector<VkViewport>				viewports;
		};

		/*****************************************************************
		*********************    ShaderStagesInfo    *********************
		*****************************************************************/

		/**
		 *	@brief	Shader stages information.
		 */
		struct ShaderStagesInfo
		{
			std::shared_ptr<ShaderModule>		spVertexShader;
			std::shared_ptr<ShaderModule>		spGeometryShader;
			std::shared_ptr<ShaderModule>		spFragmentShader;
			std::shared_ptr<ShaderModule>		spTessControlShader;
			std::shared_ptr<ShaderModule>		spTessEvalutionShader;
		};

		/*****************************************************************
		******************    RasterizationStateInfo    ******************
		*****************************************************************/

		/**
		 *	@brief	Rasterization state information.
		 */
		struct RasterizationStateInfo
		{
			VkBool32			depthClampEnable			= VK_FALSE;
			VkBool32			rasterizerDiscardEnable		= VK_FALSE;
			VkPolygonMode		polygonMode					= VK_POLYGON_MODE_FILL;
			VkCullModeFlags		cullMode					= VK_CULL_MODE_NONE;
			VkFrontFace			frontFace					= VK_FRONT_FACE_COUNTER_CLOCKWISE;
			VkBool32			depthBiasEnable				= VK_FALSE;
			float				depthBiasConstantFactor		= 0.0f;
			float				depthBiasClamp				= 0.0f;
			float				depthBiasSlopeFactor		= 0.0f;
			float				lineWidth					= 1.0f;
		};

		/*****************************************************************
		******************    DepthStencilStateInfo    *******************
		*****************************************************************/

		/**
		 *	@brief	DepthStencil state information
		 */
		struct DepthStencilStateInfo
		{
			VkBool32				depthTestEnable				= VK_FALSE;
			VkBool32				depthWriteEnable			= VK_FALSE;
			VkCompareOp				depthCompareOp				= VK_COMPARE_OP_LESS_OR_EQUAL;
			VkBool32				depthBoundsTestEnable		= VK_FALSE;
			VkBool32				stencilTestEnable			= VK_FALSE;
			VkStencilOpState		front						= {};
			VkStencilOpState		back						= {};
			float					minDepthBounds				= 0.0f;
			float					maxDepthBounds				= 0.0f;
		};

		/*****************************************************************
		*******************    MultisampleStateInfo    *******************
		*****************************************************************/

		/**
		 *	@brief	Multisample state information.
		 */
		struct MultisampleStateInfo
		{
			VkSampleCountFlagBits		rasterizationSamples		= VK_SAMPLE_COUNT_1_BIT;
			VkBool32					sampleShadingEnable			= VK_FALSE;
			float						minSampleShading			= 0.0f;
			const VkSampleMask *		pSampleMask					= nullptr;
			VkBool32					alphaToCoverageEnable		= VK_FALSE;
			VkBool32					alphaToOneEnable			= VK_FALSE;
		};

		/*****************************************************************
		*******************    VertexInputStateInfo    *******************
		*****************************************************************/

		/**
		 *	@brief	VertexInput state information.
		 */
		struct VertexInputStateInfo
		{

		public:

			//!	@brief	Specify vertex attribute location.
			void SetLocation(uint32_t Location, uint32_t Binding, VkFormat eFormat, uint32_t Offset);

			//!	@brief	Specify vertex input binding.
			void SetBinding(uint32_t Binding, uint32_t Stride, VkVertexInputRate eInputRate = VK_VERTEX_INPUT_RATE_VERTEX);

		public:

			std::vector<VkVertexInputBindingDescription>		bindingDescriptions;
			std::vector<VkVertexInputAttributeDescription>		attributeDescriptions;
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

		struct ColorBlendStateInfo
		{
			VkBool32									logicOpEnable			= VK_FALSE;
			VkLogicOp									logicOp					= VK_LOGIC_OP_NO_OP;
			float										blendConstants[4]		= { 1.0f, 1.0f, 1.0f, 1.0f };
			std::vector<ColorBlendAttachmentState>		attachments;
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

		VkResult Create(const GraphicsPipelineInfo & CreateInfo);

		void Release() noexcept;

	private:

		VkPipeline					m_hPipeline;

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