/*************************************************************************
************************    VisualVk_Pipelines    ************************
*************************************************************************/
#pragma once

#include "Framebuffer.h"
#include "ShaderModule.h"
#include "PipelineLayout.h"

namespace Vk
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
		using InputAssemblyStateInfo = PrimitiveTopology;

		//!	@brief	Parameters of a newly created pipeline dynamic state.
		using DynamicStateInfo = std::vector<DynamicState>;

		/*****************************************************************
		*********************    ShaderStagesInfo    *********************
		*****************************************************************/

		/**
		 *	@brief	Structure specifying parameters of a newly created pipeline shader stages.
		 */
		struct ShaderStagesInfo
		{
			ShaderModule		VertexShader;
			ShaderModule		GeometryShader;
			ShaderModule		FragmentShader;
			ShaderModule		TessControlShader;
			ShaderModule		TessEvalutionShader;
		};

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
			StencilOp		failOp			= StencilOp::eKeep;
			StencilOp		passOp			= StencilOp::eKeep;
			StencilOp		depthFailOp		= StencilOp::eKeep;
			CompareOp		compareOp		= CompareOp::eNever;
			uint32_t		compareMask		= 0;
			uint32_t		writeMask		= 0;
			uint32_t		reference		= 0;
		};

		/*****************************************************************
		******************    DepthStencilStateInfo    *******************
		*****************************************************************/

		/**
		 *	@brief	Structure specifying parameters of a newly created pipeline depth stencil state.
		 */
		struct DepthStencilStateInfo
		{
			Bool32				depthTestEnable				= eFalse;
			Bool32				depthWriteEnable			= eFalse;
			Bool32				depthBoundsTestEnable		= eFalse;
			Bool32				stencilTestEnable			= eFalse;
			CompareOp			depthCompareOp				= CompareOp::eNever;
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
			CullMode		cullMode					= CullMode::eNone;
			FrontFace		frontFace					= FrontFace::eCounterClockwise;
			PolygonMode		polygonMode					= PolygonMode::eFill;
			Bool32			depthBiasEnable				= eFalse;
			Bool32			depthClampEnable			= eFalse;
			Bool32			rasterizerDiscardEnable		= eFalse;
			float			depthBiasConstantFactor		= 0.0f;
			float			depthBiasSlopeFactor		= 0.0f;
			float			depthBiasClamp				= 0.0f;
			float			lineWidth					= 1.0f;
		};

		/*****************************************************************
		*******************    MultisampleStateInfo    *******************
		*****************************************************************/

		/**
		 *	@brief	Structure specifying parameters of a newly created pipeline multisample state.
		 */
		struct MultisampleStateInfo
		{
			SampleCount		rasterizationSamples		= SampleCount::x1;
			Bool32			alphaToCoverageEnable		= eFalse;
			Bool32			sampleShadingEnable			= eFalse;
			Bool32			alphaToOneEnable			= eFalse;
			float			minSampleShading			= 0.0f;
		};

		/*****************************************************************
		****************    ColorBlendAttachmentState    *****************
		*****************************************************************/

		/**
		 *	@brief	Structure specifying a pipeline color blend attachment state.
		 */
		struct ColorBlendAttachmentState
		{
			Bool32						blendEnable				= eTrue;
			BlendFactor					srcColorBlendFactor		= BlendFactor::eSrcAlpha;
			BlendFactor					dstColorBlendFactor		= BlendFactor::eOneMinusSrcAlpha;
			BlendOp						colorBlendOp			= BlendOp::eAdd;
			BlendFactor					srcAlphaBlendFactor		= BlendFactor::eZero;
			BlendFactor					dstAlphaBlendFactor		= BlendFactor::eZero;
			BlendOp						alphaBlendOp			= BlendOp::eAdd;
			Flags<ColorComponent>		colorWriteMask			= ColorComponent::eRed | ColorComponent::eGreen | ColorComponent::eBlue | ColorComponent::eAlpha;
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
			Bool32										logicOpEnable			= eFalse;
			LogicOp										logicOp					= LogicOp::eClear;
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
			void SetLocation(uint32_t location, uint32_t binding, Format eFormat, uint32_t offset);

			//!	@brief	Specify vertex input binding.
			void SetBinding(uint32_t binding, uint32_t stride, VertexInputRate eInputRate = VertexInputRate::eVertex);

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
		VK_UNIQUE_RESOURCE(GraphicsPipeline)

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