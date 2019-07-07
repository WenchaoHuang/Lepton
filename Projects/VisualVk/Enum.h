/*************************************************************************
**************************    VisualVk_Enum    ***************************
*************************************************************************/
#pragma once

#include <vulkan/vulkan_core.h>

namespace Vk
{
	/*********************************************************************
	****************************    Bool32    ****************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan boolean type.
	 */
	enum Bool32 : VkBool32
	{
		eTrue		= VK_TRUE,
		eFalse		= VK_FALSE
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
	*************************    ShaderStage    **************************
	*********************************************************************/

	/**
	 *	@brief	Bitmask specifying a pipeline stage.
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
	*************************    ImageLayout    **************************
	*********************************************************************/

	/**
	 *	@brief	Layout of image and image subresources.
	 */
	enum class ImageLayout
	{
		eGeneral									= VK_IMAGE_LAYOUT_GENERAL,
		eUndefined									= VK_IMAGE_LAYOUT_UNDEFINED,
		ePreinitialized								= VK_IMAGE_LAYOUT_PREINITIALIZED,
		eTransferSrcOptimal							= VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
		eTransferDstOptimal							= VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
		eShaderReadOnlyOptimal						= VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
		eColorAttachmentOptimal						= VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
		eDepthStencilReadOnlyOptimal				= VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL,
		eDepthStencilAttachmentOptimal				= VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
		eDepthReadOnlyStencilAttachmentOptimal		= VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL,
		eDepthAttachmentStencilReadOnlyOptimal		= VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL,
		eDepthAttachmentStencilReadOnlyOptimalKHR	= VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL_KHR,
		eDepthReadOnlyStencilAttachmentOptimalKHR	= VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL_KHR,
		eFragmentDensityMapOptimalEXT				= VK_IMAGE_LAYOUT_FRAGMENT_DENSITY_MAP_OPTIMAL_EXT,
		eShadingRateOptimalNV						= VK_IMAGE_LAYOUT_SHADING_RATE_OPTIMAL_NV,
		eSharedPresentKHR							= VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR,
		ePresentSrcKHR								= VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
	};
}