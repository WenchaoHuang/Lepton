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
}