/*************************************************************************
*************************    Lepton_Pipelines    *************************
*************************************************************************/
#pragma once

#include "Framebuffer.h"
#include "ShaderModule.h"
#include "PipelineLayout.h"

namespace Lepton
{
	typedef VkPipeline		VkGraphicsPipeline;

	/*********************************************************************
	********************    GraphicsPipelineParam    *********************
	*********************************************************************/

	/**
	 *	@brief	Vulkan graphics pipeline parameters.
	 */
	struct GraphicsPipelineParam
	{

	public:

		//!	@brief	Constructor.
		GraphicsPipelineParam();

	private:

		//!	@brief	Parameter of a newly created pipeline tessellation state.
		using TessellationStateInfo = uint32_t;

		//!	@brief	Parameter of a newly created pipeline input assembly state.
		using InputAssemblyStateInfo = vk::PrimitiveTopology;

		//!	@brief	Parameters of a newly created pipeline dynamic state.
		using DynamicStateInfo = std::vector<vk::DynamicState>;

		//!	@brief	Parameters of a newly created pipeline shader stages.
		using ShaderStagesInfo = std::vector<ShaderModule>;

		/*****************************************************************
		********************    ViewportStateInfo    *********************
		*****************************************************************/

		/**
		 *	@brief	Structure specifying parameters of a newly created pipeline viewport state.
		 */
		struct ViewportStateInfo
		{
			std::vector<VkRect2D>		scissors;
			std::vector<VkViewport>		viewports;
		};

		/*****************************************************************
		**********************    StencilOpState    **********************
		*****************************************************************/

		/**
		 *	@brief	Structure specifying stencil operation state.
		 */
		struct StencilOpState
		{
			vk::StencilOp		failOp			= vk::StencilOp::eKeep;
			vk::StencilOp		passOp			= vk::StencilOp::eKeep;
			vk::StencilOp		depthFailOp		= vk::StencilOp::eKeep;
			vk::CompareOp		compareOp		= vk::CompareOp::eNever;
			uint32_t			compareMask		= 0;
			uint32_t			writeMask		= 0;
			uint32_t			reference		= 0;
		};

		/*****************************************************************
		******************    DepthStencilStateInfo    *******************
		*****************************************************************/

		/**
		 *	@brief	Structure specifying parameters of a newly created pipeline depth stencil state.
		 */
		struct DepthStencilStateInfo
		{
			vk::Bool32			depthTestEnable				= false;
			vk::Bool32			depthWriteEnable			= false;
			vk::Bool32			depthBoundsTestEnable		= false;
			vk::Bool32			stencilTestEnable			= false;
			vk::CompareOp		depthCompareOp				= vk::CompareOp::eNever;
			StencilOpState		front						= {};
			StencilOpState		back						= {};
			float				minDepthBounds				= 0.0f;
			float				maxDepthBounds				= 0.0f;
		};

		/*****************************************************************
		******************    RasterizationStateInfo    ******************
		*****************************************************************/

		/**
		 *	@brief	Structure specifying parameters of a newly created pipeline rasterization state.
		 */
		struct RasterizationStateInfo
		{
			vk::CullModeFlagBits		cullMode					= vk::CullModeFlagBits::eNone;
			vk::FrontFace				frontFace					= vk::FrontFace::eCounterClockwise;
			vk::PolygonMode				polygonMode					= vk::PolygonMode::eFill;
			vk::Bool32					depthBiasEnable				= false;
			vk::Bool32					depthClampEnable			= false;
			vk::Bool32					rasterizerDiscardEnable		= false;
			float						depthBiasConstantFactor		= 0.0f;
			float						depthBiasSlopeFactor		= 0.0f;
			float						depthBiasClamp				= 0.0f;
			float						lineWidth					= 1.0f;
		};

		/*****************************************************************
		*******************    MultisampleStateInfo    *******************
		*****************************************************************/

		/**
		 *	@brief	Structure specifying parameters of a newly created pipeline multisample state.
		 */
		struct MultisampleStateInfo
		{
			vk::SampleCountFlagBits		rasterizationSamples		= vk::SampleCountFlagBits::e1;
			vk::Bool32					alphaToCoverageEnable		= false;
			vk::Bool32					sampleShadingEnable			= false;
			vk::Bool32					alphaToOneEnable			= false;
			float						minSampleShading			= 0.0f;
		};

		/*****************************************************************
		****************    ColorBlendAttachmentState    *****************
		*****************************************************************/

		/**
		 *	@brief	Structure specifying a pipeline color blend attachment state.
		 */
		struct ColorBlendAttachmentState
		{
			vk::Bool32						blendEnable				= true;
			vk::BlendFactor					srcColorBlendFactor		= vk::BlendFactor::eSrcAlpha;
			vk::BlendFactor					dstColorBlendFactor		= vk::BlendFactor::eOneMinusSrcAlpha;
			vk::BlendOp						colorBlendOp			= vk::BlendOp::eAdd;
			vk::BlendFactor					srcAlphaBlendFactor		= vk::BlendFactor::eZero;
			vk::BlendFactor					dstAlphaBlendFactor		= vk::BlendFactor::eZero;
			vk::BlendOp						alphaBlendOp			= vk::BlendOp::eAdd;
			vk::ColorComponentFlags			colorWriteMask			= vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG | vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA;
		};
		
		static_assert(sizeof(ColorBlendAttachmentState) == sizeof(VkPipelineColorBlendAttachmentState), "Struct and wrapper have different size!");

		/*****************************************************************
		*******************    ColorBlendStateInfo    ********************
		*****************************************************************/

		/**
		 *	@brief	Structure specifying parameters of a newly created pipeline color blend state.
		 */
		struct ColorBlendStateInfo
		{
			vk::Bool32									logicOpEnable			= false;
			vk::LogicOp									logicOp					= vk::LogicOp::eClear;
			float										blendConstants[4]		= { 1.0f, 1.0f, 1.0f, 1.0f };
			std::vector<ColorBlendAttachmentState>		attachments;
		};

		/*****************************************************************
		*******************    VertexInputStateInfo    *******************
		*****************************************************************/

		/**
		 *	@brief	Structure specifying parameters of a newly created pipeline vertex input state.
		 */
		class VertexInputStateInfo
		{
			friend class GraphicsPipeline;

		public:

			//!	@brief	Specify vertex attribute location.
			void SetLocation(uint32_t location, uint32_t binding, vk::Format eFormat, uint32_t offset);

			//!	@brief	Specify vertex input binding.
			void SetBinding(uint32_t binding, uint32_t stride, vk::VertexInputRate eInputRate = vk::VertexInputRate::eVertex);

		private:

			std::vector<VkVertexInputBindingDescription>		bindingDescriptions;
			std::vector<VkVertexInputAttributeDescription>		attributeDescriptions;
		};

	public:

		RenderPass							renderPass;
		PipelineLayout						pipelineLayout;

		ShaderStagesInfo					shaderStages;
		DynamicStateInfo					dynamicStates;
		ViewportStateInfo					viewportState;
		ColorBlendStateInfo					colorBlendState;
		VertexInputStateInfo				vertexInputState;
		MultisampleStateInfo				multisampleState;
		DepthStencilStateInfo				depthStencilState;
		TessellationStateInfo				tessellationState;
		InputAssemblyStateInfo				inputAssemblyState;
		RasterizationStateInfo				rasterizationState;
	};

	/*********************************************************************
	***********************    GraphicsPipeline    ***********************
	*********************************************************************/

	/**
	 *	@brief	Wrapper for Vulkan graphics pipeline object.
	 */
	class GraphicsPipeline
	{
		LAVA_UNIQUE_RESOURCE(GraphicsPipeline)

	public:

		//!	@brief	Create graphics pipeline object.
		GraphicsPipeline();

		//!	@brief	Create and initialize immediately.
		explicit GraphicsPipeline(const GraphicsPipelineParam & Param);

		//!	@brief	Destroy graphics pipeline object.
		~GraphicsPipeline();

	public:

		//!	@brief	Create a new graphics pipeline.
		Result Create(const GraphicsPipelineParam & Param);

		//!	@brief	Return pipeline parameters.
		const GraphicsPipelineParam & GetParam() const { return m_Parameter; }

		//!	@brief	Destroy the graphics pipeline.
		void Destroy();

	private:

		GraphicsPipelineParam		m_Parameter;
	};
}