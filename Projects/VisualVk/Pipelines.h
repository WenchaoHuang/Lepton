/*************************************************************************
************************    VisualVk_Pipelines    ************************
*************************************************************************/
#pragma once

#include "Sampler.h"
#include "Framebuffer.h"
#include "ShaderModule.h"
#include "PipelineLayout.h"

namespace Vk
{
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
	 *	@brief	
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
		eTriangleStripWithAdjacency		= VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY,
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
	***************************    BlendOp    ****************************
	*********************************************************************/

	/**
	 *	@brief	Framebuffer blending operations.
	 */
	enum class BlendOp
	{
		eMin					= VK_BLEND_OP_MIN,
		eMax					= VK_BLEND_OP_MAX,
		eAdd					= VK_BLEND_OP_ADD,
		eSubtract				= VK_BLEND_OP_SUBTRACT,
		eReverseSubtract		= VK_BLEND_OP_REVERSE_SUBTRACT,
		eZeroEXT				= VK_BLEND_OP_ZERO_EXT,
		eSrcEXT					= VK_BLEND_OP_SRC_EXT,
		eDstEXT					= VK_BLEND_OP_DST_EXT,
		eSrcOverEXT				= VK_BLEND_OP_SRC_OVER_EXT,
		eDstOverEXT				= VK_BLEND_OP_DST_OVER_EXT,
		eSrcInEXT				= VK_BLEND_OP_SRC_IN_EXT,
		eDstInEXT				= VK_BLEND_OP_DST_IN_EXT,
		eSrcOutEXT				= VK_BLEND_OP_SRC_OUT_EXT,
		eDstOutEXT				= VK_BLEND_OP_DST_OUT_EXT,
		eSrcAtopEXT				= VK_BLEND_OP_SRC_ATOP_EXT,
		eDstAtopEXT				= VK_BLEND_OP_DST_ATOP_EXT,
		eXorEXT					= VK_BLEND_OP_XOR_EXT,
		eMultiplyEXT			= VK_BLEND_OP_MULTIPLY_EXT,
		eScreenEXT				= VK_BLEND_OP_SCREEN_EXT,
		eOverlayEXT				= VK_BLEND_OP_OVERLAY_EXT,
		eDarkenEXT				= VK_BLEND_OP_DARKEN_EXT,
		eLightenEXT				= VK_BLEND_OP_LIGHTEN_EXT,
		eColordodgeEXT			= VK_BLEND_OP_COLORDODGE_EXT,
		eColorburnEXT			= VK_BLEND_OP_COLORBURN_EXT,
		eHardlightEXT			= VK_BLEND_OP_HARDLIGHT_EXT,
		eSoftlightEXT			= VK_BLEND_OP_SOFTLIGHT_EXT,
		eDifferenceEXT			= VK_BLEND_OP_DIFFERENCE_EXT,
		eExclusionEXT			= VK_BLEND_OP_EXCLUSION_EXT,
		eInvertEXT				= VK_BLEND_OP_INVERT_EXT,
		eInvertRgbEXT			= VK_BLEND_OP_INVERT_RGB_EXT,
		eLineardodgeEXT			= VK_BLEND_OP_LINEARDODGE_EXT,
		eLinearburnEXT			= VK_BLEND_OP_LINEARBURN_EXT,
		eVividlightEXT			= VK_BLEND_OP_VIVIDLIGHT_EXT,
		eLinearlightEXT			= VK_BLEND_OP_LINEARLIGHT_EXT,
		ePinlightEXT			= VK_BLEND_OP_PINLIGHT_EXT,
		eHardmixEXT				= VK_BLEND_OP_HARDMIX_EXT,
		eHslHueEXT				= VK_BLEND_OP_HSL_HUE_EXT,
		eHslSaturationEXT		= VK_BLEND_OP_HSL_SATURATION_EXT,
		eHslColorEXT			= VK_BLEND_OP_HSL_COLOR_EXT,
		eHslLuminosityEXT		= VK_BLEND_OP_HSL_LUMINOSITY_EXT,
		ePlusEXT				= VK_BLEND_OP_PLUS_EXT,
		ePlusClampedEXT			= VK_BLEND_OP_PLUS_CLAMPED_EXT,
		ePlusClampedAlphaEXT	= VK_BLEND_OP_PLUS_CLAMPED_ALPHA_EXT,
		ePlusDarkerEXT			= VK_BLEND_OP_PLUS_DARKER_EXT,
		eMinusEXT				= VK_BLEND_OP_MINUS_EXT,
		eMinusClampedEXT		= VK_BLEND_OP_MINUS_CLAMPED_EXT,
		eContrastEXT			= VK_BLEND_OP_CONTRAST_EXT,
		eInvertOvgEXT			= VK_BLEND_OP_INVERT_OVG_EXT,
		eRedEXT					= VK_BLEND_OP_RED_EXT,
		eGreenEXT				= VK_BLEND_OP_GREEN_EXT,
		eBlueEXT				= VK_BLEND_OP_BLUE_EXT
	};

	/*********************************************************************
	***************************    LogicOp    ****************************
	*********************************************************************/
	
	/**
	 *	@brief	Framebuffer logical operations.
	 */
	enum class LogicOp
	{
		eOr					= VK_LOGIC_OP_OR,
		eNor				= VK_LOGIC_OP_NOR,
		eXor				= VK_LOGIC_OP_XOR,
		eSet				= VK_LOGIC_OP_SET,
		eAnd				= VK_LOGIC_OP_AND,
		eNand				= VK_LOGIC_OP_NAND,
		eCopy				= VK_LOGIC_OP_COPY,
		eNoOp				= VK_LOGIC_OP_NO_OP,
		eClear				= VK_LOGIC_OP_CLEAR,
		eInvert				= VK_LOGIC_OP_INVERT,
		eOrReverse			= VK_LOGIC_OP_OR_REVERSE,
		eEquivalent			= VK_LOGIC_OP_EQUIVALENT,
		eOrInverted			= VK_LOGIC_OP_OR_INVERTED,
		eAndReverse			= VK_LOGIC_OP_AND_REVERSE,
		eAndInverted		= VK_LOGIC_OP_AND_INVERTED,
		eCopyInverted		= VK_LOGIC_OP_COPY_INVERTED
	};

	/*********************************************************************
	*************************    DynamicState    *************************
	*********************************************************************/

	/**
	 *	@brief	
	 */
	enum class DynamicState
	{
		eScissor						= VK_DYNAMIC_STATE_SCISSOR,
		eViewport						= VK_DYNAMIC_STATE_VIEWPORT,
		eLineWidth						= VK_DYNAMIC_STATE_LINE_WIDTH,
		eDepthBias						= VK_DYNAMIC_STATE_DEPTH_BIAS,
		eDepthBounds					= VK_DYNAMIC_STATE_DEPTH_BOUNDS,
		eBlendConstants					= VK_DYNAMIC_STATE_BLEND_CONSTANTS,
		eStencilWriteMask				= VK_DYNAMIC_STATE_STENCIL_WRITE_MASK,
		eStencilReference				= VK_DYNAMIC_STATE_STENCIL_REFERENCE,
		eStencilCompareMask				= VK_DYNAMIC_STATE_STENCIL_COMPARE_MASK,
		eViewportWScalingNV				= VK_DYNAMIC_STATE_VIEWPORT_W_SCALING_NV,
		eSampleLocationsEXT				= VK_DYNAMIC_STATE_SAMPLE_LOCATIONS_EXT,
		eDiscardRectangleEXT			= VK_DYNAMIC_STATE_DISCARD_RECTANGLE_EXT,
		eExclusiveScissorNV				= VK_DYNAMIC_STATE_EXCLUSIVE_SCISSOR_NV,
		eViewportCoarseSampleOrderNV	= VK_DYNAMIC_STATE_VIEWPORT_COARSE_SAMPLE_ORDER_NV,
		eViewportShadingRatePaletteNV	= VK_DYNAMIC_STATE_VIEWPORT_SHADING_RATE_PALETTE_NV
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

		//!	@brief	Construction.
		GraphicsPipelineInfo();

	private:

		//!	@brief	Tessellation state information.
		using TessellationStateInfo = uint32_t;

		//!	@brief	Input assembly state information. 
		using InputAssemblyStateInfo = PrimitiveTopology;

		//!	@brief	Dynamic states information.
		using DynamicStateInfo = std::vector<DynamicState>;

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
		******************    DepthStencilStateInfo    *******************
		*****************************************************************/

		/**
		 *	@brief	DepthStencil state information
		 */
		struct DepthStencilStateInfo
		{
			VkBool32				depthTestEnable				= VK_FALSE;
			VkBool32				depthWriteEnable			= VK_FALSE;
			VkBool32				depthBoundsTestEnable		= VK_FALSE;
			VkBool32				stencilTestEnable			= VK_FALSE;
			CompareOp				depthCompareOp				= CompareOp::eLessOrEqual;
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
			VkBool32					alphaToCoverageEnable		= VK_FALSE;
			VkBool32					sampleShadingEnable			= VK_FALSE;
			VkBool32					alphaToOneEnable			= VK_FALSE;
			float						minSampleShading			= 0.0f;
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
			BlendFactor					srcColorBlendFactor		= BlendFactor::eZero;
			BlendFactor					dstColorBlendFactor		= BlendFactor::eZero;
			BlendOp						colorBlendOp			= BlendOp::eAdd;
			BlendFactor					srcAlphaBlendFactor		= BlendFactor::eZero;
			BlendFactor					stAlphaBlendFactor		= BlendFactor::eZero;
			BlendOp						alphaBlendOp			= BlendOp::eAdd;
			VkColorComponentFlags		colorWriteMask			= VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		};
		
		static_assert(sizeof(ColorBlendAttachmentState) == sizeof(VkPipelineColorBlendAttachmentState), "struct and wrapper have different size!");

		/*****************************************************************
		*******************    ColorBlendStateInfo    ********************
		*****************************************************************/

		struct ColorBlendStateInfo
		{
			VkBool32									logicOpEnable			= VK_FALSE;
			LogicOp										logicOp					= LogicOp::eNoOp;
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