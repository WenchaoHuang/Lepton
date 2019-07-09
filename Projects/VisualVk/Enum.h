/*************************************************************************
**************************    VisualVk_Enum    ***************************
*************************************************************************/
#pragma once

#include <vulkan/vulkan_core.h>

namespace Vk
{
	/*********************************************************************
	*************************    SampleCount    **************************
	*********************************************************************/

	/**
	 *	@brief	Bitmask specifying sample counts supported for an image used for storage operations.
	 */
	enum class SampleCount : VkFlags
	{
		e1		= VK_SAMPLE_COUNT_1_BIT,
		e2		= VK_SAMPLE_COUNT_2_BIT,
		e4		= VK_SAMPLE_COUNT_4_BIT,
		e8		= VK_SAMPLE_COUNT_8_BIT,
		e16		= VK_SAMPLE_COUNT_16_BIT,
		e32		= VK_SAMPLE_COUNT_32_BIT,
		e64		= VK_SAMPLE_COUNT_64_BIT
	};

	/*********************************************************************
	**********************    PipelineBindPoint    ***********************
	*********************************************************************/

	/**
	 *	@brief	Specify the bind point of a pipeline object to a command buffer.
	 */
	enum class PipelineBindPoint
	{
		eCompute			= VK_PIPELINE_BIND_POINT_COMPUTE,
		eGraphics			= VK_PIPELINE_BIND_POINT_GRAPHICS,
		eRayTracingNV		= VK_PIPELINE_BIND_POINT_RAY_TRACING_NV
	};

	/*********************************************************************
	*************************    ShaderStage    **************************
	*********************************************************************/

	/**
	 *	@brief	Bitmask specifying a pipeline shader stage.
	 */
	enum class ShaderStage : VkFlags
	{
		eAll						= VK_SHADER_STAGE_ALL,
		eVertex						= VK_SHADER_STAGE_VERTEX_BIT,
		eCompute					= VK_SHADER_STAGE_COMPUTE_BIT,
		eGeometry					= VK_SHADER_STAGE_GEOMETRY_BIT,
		eFragment					= VK_SHADER_STAGE_FRAGMENT_BIT,
		eAllGraphics				= VK_SHADER_STAGE_ALL_GRAPHICS,
		eTessellationControl		= VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT,
		eTessellationEvaluation		= VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT,
		eIntersectionNV				= VK_SHADER_STAGE_INTERSECTION_BIT_NV,
		eClosestHitNV				= VK_SHADER_STAGE_CLOSEST_HIT_BIT_NV,
		eCallableNV					= VK_SHADER_STAGE_CALLABLE_BIT_NV,
		eRaygenNV					= VK_SHADER_STAGE_RAYGEN_BIT_NV,
		eAnyHitNV					= VK_SHADER_STAGE_ANY_HIT_BIT_NV,
		eMissNV						= VK_SHADER_STAGE_MISS_BIT_NV,
		eTaskNV						= VK_SHADER_STAGE_TASK_BIT_NV,
		eMeshNV						= VK_SHADER_STAGE_MESH_BIT_NV
	};

	/*********************************************************************
	************************    PipelineStage    *************************
	*********************************************************************/

	/**
	 *	@brief	Bitmask specifying pipeline stages.
	 */
	enum class PipelineStage : VkFlags
	{
		eHost								= VK_PIPELINE_STAGE_HOST_BIT,
		eTransfer							= VK_PIPELINE_STAGE_TRANSFER_BIT,
		eTopOfPipe							= VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
		eVertexInput						= VK_PIPELINE_STAGE_VERTEX_INPUT_BIT,
		eAllGraphics						= VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT,
		eAllCommands						= VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
		eBottomOfPipe						= VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
		eDrawIndirect						= VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT,
		eVertexShader						= VK_PIPELINE_STAGE_VERTEX_SHADER_BIT,
		eComputeShader						= VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
		eGeometryShader						= VK_PIPELINE_STAGE_GEOMETRY_SHADER_BIT,
		eFragmentShader						= VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
		eLateFragmentTests					= VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT,
		eEarlyFragmentTests					= VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT,
		eColorAttachmentOutput				= VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
		eTessellationControlShader			= VK_PIPELINE_STAGE_TESSELLATION_CONTROL_SHADER_BIT,
		eTessellationEvaluationShader		= VK_PIPELINE_STAGE_TESSELLATION_EVALUATION_SHADER_BIT,
		eAccelerationStructureBuildNV		= VK_PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_NV,
		eFragmentDensityProcessEXT			= VK_PIPELINE_STAGE_FRAGMENT_DENSITY_PROCESS_BIT_EXT,
		eConditionalRenderingEXT			= VK_PIPELINE_STAGE_CONDITIONAL_RENDERING_BIT_EXT,
		eTransformFeedbackEXT				= VK_PIPELINE_STAGE_TRANSFORM_FEEDBACK_BIT_EXT,
		eShadingRateImageNV					= VK_PIPELINE_STAGE_SHADING_RATE_IMAGE_BIT_NV,
		eRayTracingShaderNV					= VK_PIPELINE_STAGE_RAY_TRACING_SHADER_BIT_NV,
		eCommandProcessNVX					= VK_PIPELINE_STAGE_COMMAND_PROCESS_BIT_NVX,
		eTaskShaderNV						= VK_PIPELINE_STAGE_TASK_SHADER_BIT_NV,
		eMeshShaderNV						= VK_PIPELINE_STAGE_MESH_SHADER_BIT_NV
	};

	/*********************************************************************
	**************************    ImageUsage    **************************
	*********************************************************************/

	/**
	 *	@brief	Bitmask specifying intended usage of an image.
	 */
	enum class ImageUsage : VkFlags
	{
		eSampled					= VK_IMAGE_USAGE_SAMPLED_BIT,
		eStorage					= VK_IMAGE_USAGE_STORAGE_BIT,
		eTransferSrc				= VK_IMAGE_USAGE_TRANSFER_SRC_BIT,
		eTransferDst				= VK_IMAGE_USAGE_TRANSFER_DST_BIT,
		eColorAttachment			= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
		eInputAttachment			= VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT,
		eTransientAttachment		= VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT,
		eDepthStencilAttachment		= VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
		eFragmentDensityMapEXT		= VK_IMAGE_USAGE_FRAGMENT_DENSITY_MAP_BIT_EXT,
		eShadingRateImageNV			= VK_IMAGE_USAGE_SHADING_RATE_IMAGE_BIT_NV
	};

	/*********************************************************************
	*************************    ImageAspect    **************************
	*********************************************************************/

	/**
	 *	@brief	Bitmask specifying which aspects of an image are included in a view.
	 */
	enum class ImageAspect : VkFlags
	{
		eColor					= VK_IMAGE_ASPECT_COLOR_BIT,
		eDepth					= VK_IMAGE_ASPECT_DEPTH_BIT,
		eStencil				= VK_IMAGE_ASPECT_STENCIL_BIT,
		eMetadata				= VK_IMAGE_ASPECT_METADATA_BIT,
		ePlane0					= VK_IMAGE_ASPECT_PLANE_0_BIT,
		ePlane1					= VK_IMAGE_ASPECT_PLANE_1_BIT,
		ePlane2					= VK_IMAGE_ASPECT_PLANE_2_BIT,
		ePlane0KHR				= VK_IMAGE_ASPECT_PLANE_0_BIT_KHR,
		ePlane1KHR				= VK_IMAGE_ASPECT_PLANE_1_BIT_KHR,
		ePlane2KHR				= VK_IMAGE_ASPECT_PLANE_2_BIT_KHR,
		eMemoryPlane0EXT		= VK_IMAGE_ASPECT_MEMORY_PLANE_0_BIT_EXT,
		eMemoryPlane1EXT		= VK_IMAGE_ASPECT_MEMORY_PLANE_1_BIT_EXT,
		eMemoryPlane2EXT		= VK_IMAGE_ASPECT_MEMORY_PLANE_2_BIT_EXT,
		eMemoryPlane3EXT		= VK_IMAGE_ASPECT_MEMORY_PLANE_3_BIT_EXT
	};

	/*********************************************************************
	*************************    ImageLayout    **************************
	*********************************************************************/

	/**
	 *	@brief	Layout of image and image subresources.
	 */
	enum class ImageLayout
	{
		eGeneral										= VK_IMAGE_LAYOUT_GENERAL,
		eUndefined										= VK_IMAGE_LAYOUT_UNDEFINED,
		ePreinitialized									= VK_IMAGE_LAYOUT_PREINITIALIZED,
		eTransferSrcOptimal								= VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
		eTransferDstOptimal								= VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
		eShaderReadOnlyOptimal							= VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
		eColorAttachmentOptimal							= VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
		eDepthStencilReadOnlyOptimal					= VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL,
		eDepthStencilAttachmentOptimal					= VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
		eDepthReadOnlyStencilAttachmentOptimal			= VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL,
		eDepthAttachmentStencilReadOnlyOptimal			= VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL,
		eDepthAttachmentStencilReadOnlyOptimalKHR		= VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL_KHR,
		eDepthReadOnlyStencilAttachmentOptimalKHR		= VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL_KHR,
		eFragmentDensityMapOptimalEXT					= VK_IMAGE_LAYOUT_FRAGMENT_DENSITY_MAP_OPTIMAL_EXT,
		eShadingRateOptimalNV							= VK_IMAGE_LAYOUT_SHADING_RATE_OPTIMAL_NV,
		eSharedPresentKHR								= VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR,
		ePresentSrcKHR									= VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
	};

	/*********************************************************************
	**************************    CompareOp    ***************************
	*********************************************************************/

	/**
	 *	@brief	Stencil comparison function.
	 */
	enum class CompareOp
	{
		eLess				= VK_COMPARE_OP_LESS,
		eEqual				= VK_COMPARE_OP_EQUAL,
		eNever				= VK_COMPARE_OP_NEVER,
		eAlways				= VK_COMPARE_OP_ALWAYS,
		eGreater			= VK_COMPARE_OP_GREATER,
		eNotEqual			= VK_COMPARE_OP_NOT_EQUAL,
		eLessOrEqual		= VK_COMPARE_OP_LESS_OR_EQUAL,
		eGreaterOrEqual		= VK_COMPARE_OP_GREATER_OR_EQUAL
	};


	/*********************************************************************
	**************************    StencilOp    ***************************
	*********************************************************************/

	/**
	 *	@brief	Stencil comparison function.
	 */
	enum class StencilOp
	{
		eKeep					= VK_STENCIL_OP_KEEP,
		eZero					= VK_STENCIL_OP_ZERO,
		eInvert					= VK_STENCIL_OP_INVERT,
		eReplace				= VK_STENCIL_OP_REPLACE,
		eIncrementAndWrap		= VK_STENCIL_OP_INCREMENT_AND_WRAP,
		eDecrementAndWrap		= VK_STENCIL_OP_DECREMENT_AND_WRAP,
		eIncrementAndClamp		= VK_STENCIL_OP_INCREMENT_AND_CLAMP,
		eDecrementAndClamp		= VK_STENCIL_OP_DECREMENT_AND_CLAMP
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
	***************************    BlendOp    ****************************
	*********************************************************************/

	/**
	 *	@brief	Framebuffer blending operations.
	 */
	enum class BlendOp
	{
		eMin						= VK_BLEND_OP_MIN,
		eMax						= VK_BLEND_OP_MAX,
		eAdd						= VK_BLEND_OP_ADD,
		eSubtract					= VK_BLEND_OP_SUBTRACT,
		eReverseSubtract			= VK_BLEND_OP_REVERSE_SUBTRACT,
		ePlusClampedAlphaEXT		= VK_BLEND_OP_PLUS_CLAMPED_ALPHA_EXT,
		eHslLuminosityEXT			= VK_BLEND_OP_HSL_LUMINOSITY_EXT,
		eHslSaturationEXT			= VK_BLEND_OP_HSL_SATURATION_EXT,
		eMinusClampedEXT			= VK_BLEND_OP_MINUS_CLAMPED_EXT,
		ePlusClampedEXT				= VK_BLEND_OP_PLUS_CLAMPED_EXT,
		eLinearlightEXT				= VK_BLEND_OP_LINEARLIGHT_EXT,
		eLineardodgeEXT				= VK_BLEND_OP_LINEARDODGE_EXT,
		ePlusDarkerEXT				= VK_BLEND_OP_PLUS_DARKER_EXT,
		eVividlightEXT				= VK_BLEND_OP_VIVIDLIGHT_EXT,
		eLinearburnEXT				= VK_BLEND_OP_LINEARBURN_EXT,
		eColordodgeEXT				= VK_BLEND_OP_COLORDODGE_EXT,
		eDifferenceEXT				= VK_BLEND_OP_DIFFERENCE_EXT,
		eInvertRgbEXT				= VK_BLEND_OP_INVERT_RGB_EXT,
		eInvertOvgEXT				= VK_BLEND_OP_INVERT_OVG_EXT,
		eExclusionEXT				= VK_BLEND_OP_EXCLUSION_EXT,
		eSoftlightEXT				= VK_BLEND_OP_SOFTLIGHT_EXT,
		eHardlightEXT				= VK_BLEND_OP_HARDLIGHT_EXT,
		eColorburnEXT				= VK_BLEND_OP_COLORBURN_EXT,
		eHslColorEXT				= VK_BLEND_OP_HSL_COLOR_EXT,
		eContrastEXT				= VK_BLEND_OP_CONTRAST_EXT,
		ePinlightEXT				= VK_BLEND_OP_PINLIGHT_EXT,
		eMultiplyEXT				= VK_BLEND_OP_MULTIPLY_EXT,
		eDstAtopEXT					= VK_BLEND_OP_DST_ATOP_EXT,
		eSrcAtopEXT					= VK_BLEND_OP_SRC_ATOP_EXT,
		eSrcOverEXT					= VK_BLEND_OP_SRC_OVER_EXT,
		eDstOverEXT					= VK_BLEND_OP_DST_OVER_EXT,
		eOverlayEXT					= VK_BLEND_OP_OVERLAY_EXT,
		eLightenEXT					= VK_BLEND_OP_LIGHTEN_EXT,
		eHardmixEXT					= VK_BLEND_OP_HARDMIX_EXT,
		eHslHueEXT					= VK_BLEND_OP_HSL_HUE_EXT,
		eDstOutEXT					= VK_BLEND_OP_DST_OUT_EXT,
		eSrcOutEXT					= VK_BLEND_OP_SRC_OUT_EXT,
		eDarkenEXT					= VK_BLEND_OP_DARKEN_EXT,
		eScreenEXT					= VK_BLEND_OP_SCREEN_EXT,
		eInvertEXT					= VK_BLEND_OP_INVERT_EXT,
		eDstInEXT					= VK_BLEND_OP_DST_IN_EXT,
		eSrcInEXT					= VK_BLEND_OP_SRC_IN_EXT,
		eMinusEXT					= VK_BLEND_OP_MINUS_EXT,
		eGreenEXT					= VK_BLEND_OP_GREEN_EXT,
		eBlueEXT					= VK_BLEND_OP_BLUE_EXT,
		ePlusEXT					= VK_BLEND_OP_PLUS_EXT,
		eZeroEXT					= VK_BLEND_OP_ZERO_EXT,
		eSrcEXT						= VK_BLEND_OP_SRC_EXT,
		eDstEXT						= VK_BLEND_OP_DST_EXT,
		eXorEXT						= VK_BLEND_OP_XOR_EXT,
		eRedEXT						= VK_BLEND_OP_RED_EXT
	};
}