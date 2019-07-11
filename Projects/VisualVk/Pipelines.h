/*************************************************************************
************************    VisualVk_Pipelines    ************************
*************************************************************************/
#pragma once

#include "Format.h"
#include "ShaderModule.h"
#include "PipelineLayout.h"

namespace Vk
{
	class RenderPass;

	/*********************************************************************
	************************    ColorComponent    ************************
	*********************************************************************/

	/**
	 *	@brief	Bitmask controlling which components are written to the framebuffer.
	 */
	enum class ColorComponent : VkFlags
	{
		eRed		= VK_COLOR_COMPONENT_R_BIT,
		eBlue		= VK_COLOR_COMPONENT_B_BIT,
		eGreen		= VK_COLOR_COMPONENT_G_BIT,
		eAlpha		= VK_COLOR_COMPONENT_A_BIT
	};

	/*********************************************************************
	***********************    VertexInputRate    ************************
	*********************************************************************/

	/**
	 *	@brief	Specify rate at which vertex attributes are pulled from buffers.
	 */
	enum class VertexInputRate
	{
		eVertex			= VK_VERTEX_INPUT_RATE_VERTEX,
		eInstance		= VK_VERTEX_INPUT_RATE_INSTANCE
	};

	/*********************************************************************
	**************************    FrontFace    ***************************
	*********************************************************************/

	/**
	 *	@brief	Interpret polygon front-facing orientation.
	 */
	enum class FrontFace
	{
		eClockwise				= VK_FRONT_FACE_CLOCKWISE,
		eCounterClockwise		= VK_FRONT_FACE_COUNTER_CLOCKWISE
	};

	/*********************************************************************
	***************************    CullMode    ***************************
	*********************************************************************/

	/**
	 *	@brief	Bitmask controlling triangle culling.
	 */
	enum class CullMode
	{
		eNone				= VK_CULL_MODE_NONE,
		eBack				= VK_CULL_MODE_BACK_BIT,
		eFront				= VK_CULL_MODE_FRONT_BIT,
		eFrontAndBack		= VK_CULL_MODE_FRONT_AND_BACK
	};

	/*********************************************************************
	*************************    PolygonMode    **************************
	*********************************************************************/

	/**
	 *	@brief	Control polygon rasterization mode.
	 */
	enum class PolygonMode
	{
		eFill					= VK_POLYGON_MODE_FILL,
		eLine					= VK_POLYGON_MODE_LINE,
		ePoint					= VK_POLYGON_MODE_POINT,
		eFillRectangleNV		= VK_POLYGON_MODE_FILL_RECTANGLE_NV
	};

	/*********************************************************************
	**********************    PrimitiveTopology    ***********************
	*********************************************************************/

	/**
	 *	@brief	Supported primitive topologies.
	 */
	enum class PrimitiveTopology
	{
		eLineList						= VK_PRIMITIVE_TOPOLOGY_LINE_LIST,
		ePointList						= VK_PRIMITIVE_TOPOLOGY_POINT_LIST,
		eLineStrip						= VK_PRIMITIVE_TOPOLOGY_LINE_STRIP,
		ePatchList						= VK_PRIMITIVE_TOPOLOGY_PATCH_LIST,
		eTriangleFan					= VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN,
		eTriangleList					= VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
		eTriangleStrip					= VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP,
		eLineListWithAdjacency			= VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY,
		eLineStripWithAdjacency			= VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY,
		eTriangleListWithAdjacency		= VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY,
		eTriangleStripWithAdjacency		= VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY
	};

	/*********************************************************************
	*************************    BlendFactor    **************************
	*********************************************************************/

	/**
	 *	@brief	Framebuffer blending factors.
	 */
	enum class BlendFactor
	{
		eOne						= VK_BLEND_FACTOR_ONE,
		eZero						= VK_BLEND_FACTOR_ZERO,
		eSrcColor					= VK_BLEND_FACTOR_SRC_COLOR,
		eDstColor					= VK_BLEND_FACTOR_DST_COLOR,
		eSrcAlpha					= VK_BLEND_FACTOR_SRC_ALPHA,
		eDstAlpha					= VK_BLEND_FACTOR_DST_ALPHA,
		eSrc1Color					= VK_BLEND_FACTOR_SRC1_COLOR,
		eSrc1Alpha					= VK_BLEND_FACTOR_SRC1_ALPHA,
		eConstantColor				= VK_BLEND_FACTOR_CONSTANT_COLOR,
		eConstantAlpha				= VK_BLEND_FACTOR_CONSTANT_ALPHA,
		eSrcAlphaSaturate			= VK_BLEND_FACTOR_SRC_ALPHA_SATURATE,
		eOneMinusSrcColor			= VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR,
		eOneMinusDstColor			= VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR,
		eOneMinusSrcAlpha			= VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
		eOneMinusDstAlpha			= VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA,
		eOneMinusSrc1Color			= VK_BLEND_FACTOR_ONE_MINUS_SRC1_COLOR,
		eOneMinusSrc1Alpha			= VK_BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA,
		eOneMinusConstantColor		= VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR,
		eOneMinusConstantAlpha		= VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA
	};

	/*********************************************************************
	*************************    DynamicState    *************************
	*********************************************************************/

	/**
	 *	@brief	Indicate which dynamic state is taken from dynamic state commands.
	 */
	enum class DynamicState
	{
		eScissor							= VK_DYNAMIC_STATE_SCISSOR,
		eViewport							= VK_DYNAMIC_STATE_VIEWPORT,
		eLineWidth							= VK_DYNAMIC_STATE_LINE_WIDTH,
		eDepthBias							= VK_DYNAMIC_STATE_DEPTH_BIAS,
		eDepthBounds						= VK_DYNAMIC_STATE_DEPTH_BOUNDS,
		eBlendConstants						= VK_DYNAMIC_STATE_BLEND_CONSTANTS,
		eStencilWriteMask					= VK_DYNAMIC_STATE_STENCIL_WRITE_MASK,
		eStencilReference					= VK_DYNAMIC_STATE_STENCIL_REFERENCE,
		eStencilCompareMask					= VK_DYNAMIC_STATE_STENCIL_COMPARE_MASK,
		eViewportShadingRatePaletteNV		= VK_DYNAMIC_STATE_VIEWPORT_SHADING_RATE_PALETTE_NV,
		eViewportCoarseSampleOrderNV		= VK_DYNAMIC_STATE_VIEWPORT_COARSE_SAMPLE_ORDER_NV,
		eDiscardRectangleEXT				= VK_DYNAMIC_STATE_DISCARD_RECTANGLE_EXT,
		eSampleLocationsEXT					= VK_DYNAMIC_STATE_SAMPLE_LOCATIONS_EXT,
		eViewportWScalingNV					= VK_DYNAMIC_STATE_VIEWPORT_W_SCALING_NV,
		eExclusiveScissorNV					= VK_DYNAMIC_STATE_EXCLUSIVE_SCISSOR_NV
	};

	/*********************************************************************
	*********************    GraphicsPipelineInfo    *********************
	*********************************************************************/

	/**
	 *	@brief	Creating information of Vulkan graphics pipeline.
	 */
	struct GraphicsPipelineInfo
	{

	public:

		//!	@brief	Constructor.
		GraphicsPipelineInfo();

	private:

		//!	@brief	Parameter of a newly created pipeline tessellation state.
		using TessellationStateInfo = uint32_t;

		//!	@brief	Parameter of a newly created pipeline input assembly state.
		using InputAssemblyStateInfo = PrimitiveTopology;

		//!	@brief	Parameters of a newly created pipeline dynamic state.
		using DynamicStateInfo = std::vector<DynamicState>;

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
		*********************    ShaderStagesInfo    *********************
		*****************************************************************/

		/**
		 *	@brief	Structure specifying parameters of a newly created pipeline shader stages.
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
		 *	@brief	Structure specifying parameters of a newly created pipeline rasterization state.
		 */
		struct RasterizationStateInfo
		{
			CullMode		cullMode					= CullMode::eNone;
			FrontFace		frontFace					= FrontFace::eCounterClockwise;
			PolygonMode		polygonMode					= PolygonMode::eFill;
			VkBool32		depthClampEnable			= VK_FALSE;
			VkBool32		rasterizerDiscardEnable		= VK_FALSE;
			VkBool32		depthBiasEnable				= VK_FALSE;
			float			depthBiasConstantFactor		= 0.0f;
			float			depthBiasClamp				= 0.0f;
			float			depthBiasSlopeFactor		= 0.0f;
			float			lineWidth					= 1.0f;
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
			VkBool32			depthTestEnable				= VK_FALSE;
			VkBool32			depthWriteEnable			= VK_FALSE;
			VkBool32			depthBoundsTestEnable		= VK_FALSE;
			VkBool32			stencilTestEnable			= VK_FALSE;
			CompareOp			depthCompareOp				= CompareOp::eLessOrEqual;
			StencilOpState		front						= {};
			StencilOpState		back						= {};
			float				minDepthBounds				= 0.0f;
			float				maxDepthBounds				= 0.0f;
		};

		/*****************************************************************
		*******************    MultisampleStateInfo    *******************
		*****************************************************************/

		/**
		 *	@brief	Structure specifying parameters of a newly created pipeline multisample state.
		 */
		struct MultisampleStateInfo
		{
			SampleCount		rasterizationSamples		= SampleCount::e1;
			VkBool32		alphaToCoverageEnable		= VK_FALSE;
			VkBool32		sampleShadingEnable			= VK_FALSE;
			VkBool32		alphaToOneEnable			= VK_FALSE;
			float			minSampleShading			= 0.0f;
		};

		/*****************************************************************
		*******************    VertexInputStateInfo    *******************
		*****************************************************************/

		/**
		 *	@brief	Structure specifying parameters of a newly created pipeline vertex input state.
		 */
		class VertexInputStateInfo
		{

		public:

			friend class GraphicsPipeline;

			//!	@brief	Specify vertex attribute location.
			void SetLocation(uint32_t Location, uint32_t Binding, Format eFormat, uint32_t Offset);

			//!	@brief	Specify vertex input binding.
			void SetBinding(uint32_t Binding, uint32_t Stride, VertexInputRate eInputRate = VertexInputRate::eVertex);

		private:

			std::vector<VkVertexInputBindingDescription>		bindingDescriptions;
			std::vector<VkVertexInputAttributeDescription>		attributeDescriptions;
		};

		/*****************************************************************
		****************    ColorBlendAttachmentState    *****************
		*****************************************************************/

		/**
		 *	@brief	Structure specifying a pipeline color blend attachment state.
		 */
		struct ColorBlendAttachmentState
		{
			VkBool32					blendEnable				= VK_FALSE;
			BlendFactor					srcColorBlendFactor		= BlendFactor::eZero;
			BlendFactor					dstColorBlendFactor		= BlendFactor::eZero;
			BlendOp						colorBlendOp			= BlendOp::eAdd;
			BlendFactor					srcAlphaBlendFactor		= BlendFactor::eZero;
			BlendFactor					stAlphaBlendFactor		= BlendFactor::eZero;
			BlendOp						alphaBlendOp			= BlendOp::eAdd;
			Flags<ColorComponent>		colorWriteMask			= ColorComponent::eRed | ColorComponent::eGreen | ColorComponent::eBlue | ColorComponent::eAlpha;
		};
		
		static_assert(sizeof(ColorBlendAttachmentState) == sizeof(VkPipelineColorBlendAttachmentState), "struct and wrapper have different size!");

		/*****************************************************************
		*******************    ColorBlendStateInfo    ********************
		*****************************************************************/

		/**
		 *	@brief	Structure specifying parameters of a newly created pipeline color blend state.
		 */
		struct ColorBlendStateInfo
		{
			VkBool32									logicOpEnable			= VK_FALSE;
			LogicOp										logicOp					= LogicOp::eNoOp;
			float										blendConstants[4]		= { 1.0f, 1.0f, 1.0f, 1.0f };
			std::vector<ColorBlendAttachmentState>		attachments;
		};

	public:

		RenderPassH								hRenderPass;
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

		//!	@brief	Create a new graphics pipeline.
		VkResult Create(const GraphicsPipelineInfo & CreateInfo);

		std::shared_ptr<PipelineLayout> GetLayout() { return m_CreateInfo.spPipelineLayout; }

		//!	@brief	Destroy graphics pipeline.
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

		//!	@brief	Convert to VkPipeline handle.
		operator VkPipeline() const { return m_hPipeline; }

	private:

		VkPipeline			m_hPipeline;
	};
}