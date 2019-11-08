/*************************************************************************
****************************    Lava_Enums    ****************************
*************************************************************************/
#pragma once

#include <vulkan/vulkan.h>

namespace Lava
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
		eFalse		= VK_FALSE,
	};

	/*********************************************************************
	*************************    SampleCount    **************************
	*********************************************************************/

	/**
	 *	@brief	Bitmask specifying sample counts supported for an image used for storage operations.
	 */
	enum class SampleCount : VkFlags
	{
		x1		= VK_SAMPLE_COUNT_1_BIT,
		x2		= VK_SAMPLE_COUNT_2_BIT,
		x4		= VK_SAMPLE_COUNT_4_BIT,
		x8		= VK_SAMPLE_COUNT_8_BIT,
		x16		= VK_SAMPLE_COUNT_16_BIT,
		x32		= VK_SAMPLE_COUNT_32_BIT,
		x64		= VK_SAMPLE_COUNT_64_BIT,
	};

	/*********************************************************************
	***********************    QueueCapability    ************************
	*********************************************************************/

	/**
	 *	@brief	Bitmask specifying capabilities of queues in a queue family.
	 */
	enum class QueueCapability : VkFlags
	{
		eCompute			= VK_QUEUE_COMPUTE_BIT,
		eGraphics			= VK_QUEUE_GRAPHICS_BIT,
		eTransfer			= VK_QUEUE_TRANSFER_BIT,
		eProtected			= VK_QUEUE_PROTECTED_BIT,
		eSparseBinding		= VK_QUEUE_SPARSE_BINDING_BIT,
	};

	/*********************************************************************
	*******************    CommandPoolUsageBehavior    *******************
	*********************************************************************/

	/**
	 *	@brief	Bitmask specifying usage behavior for a command pool.
	 */
	enum class CommandPoolUsageBehavior : VkFlags
	{
		eTransient				= VK_COMMAND_POOL_CREATE_TRANSIENT_BIT,
		eProtected				= VK_COMMAND_POOL_CREATE_PROTECTED_BIT,
		eResetCommandBuffer		= VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
	};

	/*********************************************************************
	**********************    CommandBufferUsage    **********************
	*********************************************************************/

	/**
	 *	@brief	Bitmask specifying usage behavior for command buffer.
	 */
	enum CommandBufferUsage
	{
		eOneTimeSubmit			= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
		eSimultaneousUse		= VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT,
		eRenderPassContinue		= VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT,
	};

	/*********************************************************************
	**************************    ColorSpace    **************************
	*********************************************************************/

	/**
	 *	@brief	 Supported color space of the presentation engine.
	 */
	enum class ColorSpace
	{
		eSrgbNonlinear					= VK_COLOR_SPACE_SRGB_NONLINEAR_KHR,
		eExtendedSrgbNonlinearEXT		= VK_COLOR_SPACE_EXTENDED_SRGB_NONLINEAR_EXT,
		eDisplayP3NonlinearEXT			= VK_COLOR_SPACE_DISPLAY_P3_NONLINEAR_EXT,
		eExtendedSrgbLinearEXT			= VK_COLOR_SPACE_EXTENDED_SRGB_LINEAR_EXT,
		eAdobergbNonlinearEXT			= VK_COLOR_SPACE_ADOBERGB_NONLINEAR_EXT,
		eDciP3NonlinearEXT				= VK_COLOR_SPACE_DCI_P3_NONLINEAR_EXT,
		eBt709NonlinearEXT				= VK_COLOR_SPACE_BT709_NONLINEAR_EXT,
		eAdobergbLinearEXT				= VK_COLOR_SPACE_ADOBERGB_LINEAR_EXT,
		eBt2020LinearEXT				= VK_COLOR_SPACE_BT2020_LINEAR_EXT,
		eDciP3LinearEXT					= VK_COLOR_SPACE_DCI_P3_LINEAR_EXT,
		eBt709LinearEXT					= VK_COLOR_SPACE_BT709_LINEAR_EXT,
		eHdr10St2084EXT					= VK_COLOR_SPACE_HDR10_ST2084_EXT,
		eDolbyvisionEXT					= VK_COLOR_SPACE_DOLBYVISION_EXT,
		ePassThroughEXT					= VK_COLOR_SPACE_PASS_THROUGH_EXT,
		eHdr10HlgEXT					= VK_COLOR_SPACE_HDR10_HLG_EXT,
	};

	/**********************************************************************
	**********************    SurfaceTransform    ***********************
	*********************************************************************/

	/**
	 *	@brief	Presentation transforms supported on a device.
	 */
	enum class SurfaceTransform : VkFlags
	{
		eInherit						= VK_SURFACE_TRANSFORM_INHERIT_BIT_KHR,
		eIdentity						= VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
		eRotate90						= VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR,
		eRotate180						= VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR,
		eRotate270						= VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR,
		eHorizontalMirror				= VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_BIT_KHR,
		eHorizontalMirrorRotate90		= VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_90_BIT_KHR,
		eHorizontalMirrorRotate180		= VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_180_BIT_KHR,
		eHorizontalMirrorRotate270		= VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_270_BIT_KHR,
	};

	/*********************************************************************
	********************    AlphaCompositingMmode    *********************
	*********************************************************************/

	/**
	 *	@brief	Alpha compositing modes supported on a device.
	 */
	enum class AlphaCompositingMmode : VkFlags
	{
		eOpaque				= VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
		eInherit			= VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR,
		ePreMultiplied		= VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR,
		ePostMultiplied		= VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR,
	};

	/*********************************************************************
	************************    MemoryProperty    ************************
	*********************************************************************/

	/**
	 *	@brief	Bitmask specifying properties for a memory type.
	 */
	enum class MemoryProperty
	{
		eHostCached				= VK_MEMORY_PROPERTY_HOST_CACHED_BIT,
		eHostVisible			= VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
		eDeviceLocal			= VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
		eHostCoherent			= VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		eLazilyAllocated		= VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT,
	};

	/*********************************************************************
	*************************    PresentMode    **************************
	*********************************************************************/

	/**
	 *	@brief	Presentation mode supported for a surface.
	 */
	enum class PresentMode
	{
		eFIFO							= VK_PRESENT_MODE_FIFO_KHR,
		eMailbox						= VK_PRESENT_MODE_MAILBOX_KHR,
		eImmediate						= VK_PRESENT_MODE_IMMEDIATE_KHR,
		eFIFORelaxed					= VK_PRESENT_MODE_FIFO_RELAXED_KHR,
		eSharedDemandRefresh			= VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR,
		eSharedContinuousRefresh		= VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR,
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
		eRayTracingNV		= VK_PIPELINE_BIND_POINT_RAY_TRACING_NV,
	};

	/*********************************************************************
	***********************    MemoryDependency    ***********************
	*********************************************************************/

	/**
	 *	@brief	Bitmask specifying how execution and memory dependencies are formed.
	 */
	enum class MemoryDependency : VkFlags
	{
		eByRegion			= VK_DEPENDENCY_BY_REGION_BIT,
		eViewLocal			= VK_DEPENDENCY_VIEW_LOCAL_BIT,
		eDeviceGroup		= VK_DEPENDENCY_DEVICE_GROUP_BIT,
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
		eMeshNV						= VK_SHADER_STAGE_MESH_BIT_NV,
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
		eMeshShaderNV						= VK_PIPELINE_STAGE_MESH_SHADER_BIT_NV,
	};

	/*********************************************************************
	************************    DescriptorType    ************************
	*********************************************************************/

	/**
	 *	@brief	Specifies the type of a descriptor in a descriptor set.
	 */
	enum class DescriptorType
	{
		eSampler						= VK_DESCRIPTOR_TYPE_SAMPLER,
		eSampledImage					= VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,
		eStorageImage					= VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,
		eUniformBuffer					= VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
		eStorageBuffer					= VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
		eInputAttachment				= VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT,
		eStorageTexelBuffer				= VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER,
		eUniformTexelBuffer				= VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER,
		eCombinedImageSampler			= VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
		eUniformBufferDynamic			= VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC,
		eStorageBufferDynamic			= VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC,
		eInlineUniformBlockEXT			= VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK_EXT,
		eAccelerationStructureNV		= VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV,
	};

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
		eAlpha		= VK_COLOR_COMPONENT_A_BIT,
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
		eInstance		= VK_VERTEX_INPUT_RATE_INSTANCE,
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
		eCounterClockwise		= VK_FRONT_FACE_COUNTER_CLOCKWISE,
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
		eFrontAndBack		= VK_CULL_MODE_FRONT_AND_BACK,
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
		eFillRectangleNV		= VK_POLYGON_MODE_FILL_RECTANGLE_NV,
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
		eOneMinusConstantAlpha		= VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA,
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
		eSampleLocationsEXT					= VK_DYNAMIC_STATE_SAMPLE_LOCATIONS_EXT,
		eViewportWScalingNV					= VK_DYNAMIC_STATE_VIEWPORT_W_SCALING_NV,
		eExclusiveScissorNV					= VK_DYNAMIC_STATE_EXCLUSIVE_SCISSOR_NV,
		eDiscardRectangleEXT				= VK_DYNAMIC_STATE_DISCARD_RECTANGLE_EXT,
		eViewportCoarseSampleOrderNV		= VK_DYNAMIC_STATE_VIEWPORT_COARSE_SAMPLE_ORDER_NV,
		eViewportShadingRatePaletteNV		= VK_DYNAMIC_STATE_VIEWPORT_SHADING_RATE_PALETTE_NV,
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
		eShadingRateImageNV			= VK_IMAGE_USAGE_SHADING_RATE_IMAGE_BIT_NV,
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
		ePlane0					= VK_IMAGE_ASPECT_PLANE_0_BIT,
		ePlane1					= VK_IMAGE_ASPECT_PLANE_1_BIT,
		ePlane2					= VK_IMAGE_ASPECT_PLANE_2_BIT,
		eMetadata				= VK_IMAGE_ASPECT_METADATA_BIT,
		eMemoryPlane0EXT		= VK_IMAGE_ASPECT_MEMORY_PLANE_0_BIT_EXT,
		eMemoryPlane1EXT		= VK_IMAGE_ASPECT_MEMORY_PLANE_1_BIT_EXT,
		eMemoryPlane2EXT		= VK_IMAGE_ASPECT_MEMORY_PLANE_2_BIT_EXT,
		eMemoryPlane3EXT		= VK_IMAGE_ASPECT_MEMORY_PLANE_3_BIT_EXT,
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
		ePresentSrcKHR									= VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
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
		eGreaterOrEqual		= VK_COMPARE_OP_GREATER_OR_EQUAL,
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
		eDecrementAndClamp		= VK_STENCIL_OP_DECREMENT_AND_CLAMP,
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
		eCopyInverted		= VK_LOGIC_OP_COPY_INVERTED,
	};

	/*********************************************************************
	****************************    Filter    ****************************
	*********************************************************************/

	/**
	 *	@brief	Specify filters used for texture lookups.
	 */
	enum class Filter
	{
		eLinear			= VK_FILTER_LINEAR,
		eNearest		= VK_FILTER_NEAREST,
	};

	/*********************************************************************
	**************************    MipmapMode    **************************
	*********************************************************************/

	/**
	 *	@brief	Specify mipmap mode used for texture lookups.
	 */
	enum class MipmapMode
	{
		eLinear			= VK_SAMPLER_MIPMAP_MODE_LINEAR,
		eNearest		= VK_SAMPLER_MIPMAP_MODE_NEAREST,
	};

	/*********************************************************************
	*************************    AddressMode    **************************
	*********************************************************************/

	/**
	 *	@brief	Specify behavior of sampling with texture coordinates outside an image.
	 */
	enum class AddressMode
	{
		eRepeat					= VK_SAMPLER_ADDRESS_MODE_REPEAT,
		eClampToEdge			= VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
		eClampToBorder			= VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER,
		eMirroredRepeat			= VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT,
		eMirrorClampToEdge		= VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE,
	};

	/*********************************************************************
	*************************    BorderColor    **************************
	*********************************************************************/

	/**
	 *	@brief	Specify border color used for texture lookups.
	 */
	enum class BorderColor
	{
		eIntOpaqueWhite				= VK_BORDER_COLOR_INT_OPAQUE_WHITE,
		eIntOpaqueBlack				= VK_BORDER_COLOR_INT_OPAQUE_BLACK,
		eFloatOpaqueWhite			= VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE,
		eFloatOpaqueBlack			= VK_BORDER_COLOR_FLOAT_OPAQUE_BLACK,
		eIntTransparentBlack		= VK_BORDER_COLOR_INT_TRANSPARENT_BLACK,
		eFloatTransparentBlack		= VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK,
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
		eRedEXT						= VK_BLEND_OP_RED_EXT,
	};

	/*********************************************************************
	***********************    AttachmentLoadOp    ***********************
	*********************************************************************/

	/**
	 *	@brief	Specify how contents of an attachment are treated at the beginning of a subpass.
	 */
	enum class AttachmentLoadOp
	{
		eLoad			= VK_ATTACHMENT_LOAD_OP_LOAD,
		eClear			= VK_ATTACHMENT_LOAD_OP_CLEAR,
		eDontCare		= VK_ATTACHMENT_LOAD_OP_DONT_CARE,
	};

	/*********************************************************************
	**********************    AttachmentStoreOp    ***********************
	*********************************************************************/

	/**
	 *	@brief	Specify how contents of an attachment are treated at the end of a subpass.
	 */
	enum class AttachmentStoreOp
	{
		eStore			= VK_ATTACHMENT_STORE_OP_STORE,
		eDontCare		= VK_ATTACHMENT_STORE_OP_DONT_CARE,
	};

	/*********************************************************************
	***********************    SubpassContents    ************************
	*********************************************************************/

	/**
	 *	@brief	Specify how commands in the first subpass of a render pass are provided.
	 */
	enum class SubpassContents
	{
		eInline							= VK_SUBPASS_CONTENTS_INLINE,
		eSecondaryCommandBuffers		= VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS,
	};

	/*********************************************************************
	*************************    MemoryAccess    *************************
	*********************************************************************/

	/**
	 *	@brief	Bitmask specifying memory access types that will participate in a memory dependency.
	 */
	enum class MemoryAccess : VkFlags
	{
		eHostRead								= VK_ACCESS_HOST_READ_BIT,
		eHostWrite								= VK_ACCESS_HOST_WRITE_BIT,
		eIndexRead								= VK_ACCESS_INDEX_READ_BIT,
		eShaderRead								= VK_ACCESS_SHADER_READ_BIT,
		eMemoryRead								= VK_ACCESS_MEMORY_READ_BIT,
		eUniformRead							= VK_ACCESS_UNIFORM_READ_BIT,
		eMemoryWrite							= VK_ACCESS_MEMORY_WRITE_BIT,
		eShaderWrite							= VK_ACCESS_SHADER_WRITE_BIT,
		eTransferRead							= VK_ACCESS_TRANSFER_READ_BIT,
		eTransferWrite							= VK_ACCESS_TRANSFER_WRITE_BIT,
		eIndirectCommandRead					= VK_ACCESS_INDIRECT_COMMAND_READ_BIT,
		eVertexAttributeRead					= VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT,
		eInputAttachmentRead					= VK_ACCESS_INPUT_ATTACHMENT_READ_BIT,
		eColorAttachmentRead					= VK_ACCESS_COLOR_ATTACHMENT_READ_BIT,
		eColorAttachmentWrite					= VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
		eTransformFeedbackWriteEXT				= VK_ACCESS_TRANSFORM_FEEDBACK_WRITE_BIT_EXT,
		eDepthStencilAttachmentRead				= VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT,
		eDepthStencilAttachmentWrite			= VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT,
		eColorAttachmentReadNoncoherentEXT		= VK_ACCESS_COLOR_ATTACHMENT_READ_NONCOHERENT_BIT_EXT,
		eTransformFeedbackCounterWriteEXT		= VK_ACCESS_TRANSFORM_FEEDBACK_COUNTER_WRITE_BIT_EXT,
		eTransformFeedbackCounterReadEXT		= VK_ACCESS_TRANSFORM_FEEDBACK_COUNTER_READ_BIT_EXT,
		eAccelerationStructureWriteNV			= VK_ACCESS_ACCELERATION_STRUCTURE_WRITE_BIT_NV,
		eConditionalRenderingReadEXT			= VK_ACCESS_CONDITIONAL_RENDERING_READ_BIT_EXT,
		eAccelerationStructureReadNV			= VK_ACCESS_ACCELERATION_STRUCTURE_READ_BIT_NV,
		eFragmentDensityMapReadEXT				= VK_ACCESS_FRAGMENT_DENSITY_MAP_READ_BIT_EXT,
		eCommandProcessWriteNVX					= VK_ACCESS_COMMAND_PROCESS_WRITE_BIT_NVX,
		eShadingRateImageReadNV					= VK_ACCESS_SHADING_RATE_IMAGE_READ_BIT_NV,
		eCommandProcessReadNVX					= VK_ACCESS_COMMAND_PROCESS_READ_BIT_NVX,
	};

	/*********************************************************************
	**************************    IndexType    ***************************
	*********************************************************************/

	/**
	 *	@brief	Type of index buffer indices.
	 */
	enum class IndexType
	{
		eUint16		= VK_INDEX_TYPE_UINT16,
		eUint32		= VK_INDEX_TYPE_UINT32,
		eNoneNV		= VK_INDEX_TYPE_NONE_NV,
	};

	/*********************************************************************
	****************************    Format    ****************************
	*********************************************************************/

	/**
	 *	@brief	Common available image formats.
	 */
	enum class Format
	{
		eUndefined					= VK_FORMAT_UNDEFINED,

		eR8Uint						= VK_FORMAT_R8_UINT,
		eR8Sint						= VK_FORMAT_R8_SINT,
		eR8Srgb						= VK_FORMAT_R8_SRGB,
		eR8Unorm					= VK_FORMAT_R8_UNORM,
		eR8Snorm					= VK_FORMAT_R8_SNORM,

		eRG8Uint					= VK_FORMAT_R8G8_UINT,
		eRG8Sint					= VK_FORMAT_R8G8_SINT,
		eRG8Srgb					= VK_FORMAT_R8G8_SRGB,
		eRG8Unorm					= VK_FORMAT_R8G8_UNORM,
		eRG8Snorm					= VK_FORMAT_R8G8_SNORM,

		eRGB8Uint					= VK_FORMAT_R8G8B8_UINT,
		eRGB8Sint					= VK_FORMAT_R8G8B8_SINT,
		eRGB8Srgb					= VK_FORMAT_R8G8B8_SRGB,
		eRGB8Unorm					= VK_FORMAT_R8G8B8_UNORM,
		eRGB8Snorm					= VK_FORMAT_R8G8B8_SNORM,

		eBGR8Uint					= VK_FORMAT_B8G8R8_UINT,
		eBGR8Sint					= VK_FORMAT_B8G8R8_SINT,
		eBGR8Srgb					= VK_FORMAT_B8G8R8_SRGB,
		eBGR8Unorm					= VK_FORMAT_B8G8R8_UNORM,
		eBGR8Snorm					= VK_FORMAT_B8G8R8_SNORM,

		eRGBA8Uint					= VK_FORMAT_R8G8B8A8_UINT,
		eRGBA8Sint					= VK_FORMAT_R8G8B8A8_SINT,
		eRGBA8Srgb					= VK_FORMAT_R8G8B8A8_SRGB,
		eRGBA8Unorm					= VK_FORMAT_R8G8B8A8_UNORM,
		eRGBA8Snorm					= VK_FORMAT_R8G8B8A8_SNORM,

		eBGRA8Uint					= VK_FORMAT_B8G8R8A8_UINT,
		eBGRA8Sint					= VK_FORMAT_B8G8R8A8_SINT,
		eBGRA8Srgb					= VK_FORMAT_B8G8R8A8_SRGB,
		eBGRA8Unorm					= VK_FORMAT_B8G8R8A8_UNORM,
		eBGRA8Snorm					= VK_FORMAT_B8G8R8A8_SNORM,

		eR16Uint					= VK_FORMAT_R16_UINT,
		eR16Sint					= VK_FORMAT_R16_SINT,
		eR16Unorm					= VK_FORMAT_R16_UNORM,
		eR16Snorm					= VK_FORMAT_R16_SNORM,
		eR16Sfloat					= VK_FORMAT_R16_SFLOAT,

		eRG16Uint					= VK_FORMAT_R16G16_UINT,
		eRG16Sint					= VK_FORMAT_R16G16_SINT,
		eRG16Unorm					= VK_FORMAT_R16G16_UNORM,
		eRG16Snorm					= VK_FORMAT_R16G16_SNORM,
		eRG16Sfloat					= VK_FORMAT_R16G16_SFLOAT,

		eRGB16Uint					= VK_FORMAT_R16G16B16_UINT,
		eRGB16Sint					= VK_FORMAT_R16G16B16_SINT,
		eRGB16Unorm					= VK_FORMAT_R16G16B16_UNORM,
		eRGB16Snorm					= VK_FORMAT_R16G16B16_SNORM,
		eRGB16Sfloat				= VK_FORMAT_R16G16B16_SFLOAT,

		eRGBA16Uint					= VK_FORMAT_R16G16B16A16_UINT,
		eRGBA16Sint					= VK_FORMAT_R16G16B16A16_SINT,
		eRGBA16Unorm				= VK_FORMAT_R16G16B16A16_UNORM,
		eRGBA16Snorm				= VK_FORMAT_R16G16B16A16_SNORM,
		eRGBA16Sfloat				= VK_FORMAT_R16G16B16A16_SFLOAT,

		eR32Uint					= VK_FORMAT_R32_UINT,
		eR32Sint					= VK_FORMAT_R32_SINT,
		eR32Sfloat					= VK_FORMAT_R32_SFLOAT,

		eRG32Uint					= VK_FORMAT_R32G32_UINT,
		eRG32Sint					= VK_FORMAT_R32G32_SINT,
		eRG32Sfloat					= VK_FORMAT_R32G32_SFLOAT,

		eRGB32Uint					= VK_FORMAT_R32G32B32_UINT,
		eRGB32Sint					= VK_FORMAT_R32G32B32_SINT,
		eRGB32Sfloat				= VK_FORMAT_R32G32B32_SFLOAT,

		eRGBA32Uint					= VK_FORMAT_R32G32B32A32_UINT,
		eRGBA32Sint					= VK_FORMAT_R32G32B32A32_SINT,
		eRGBA32Sfloat				= VK_FORMAT_R32G32B32A32_SFLOAT,

		eR64Uint					= VK_FORMAT_R64_UINT,
		eR64Sint					= VK_FORMAT_R64_SINT,
		eR64Sfloat					= VK_FORMAT_R64_SFLOAT,

		eRG64Uint					= VK_FORMAT_R64G64_UINT,
		eRG64Sint					= VK_FORMAT_R64G64_SINT,
		eRG64Sfloat					= VK_FORMAT_R64G64_SFLOAT,

		eRGB64Uint					= VK_FORMAT_R64G64B64_UINT,
		eRGB64Sint					= VK_FORMAT_R64G64B64_SINT,
		eRGB64Sfloat				= VK_FORMAT_R64G64B64_SFLOAT,

		eRGBA64Uint					= VK_FORMAT_R64G64B64A64_UINT,
		eRGBA64Sint					= VK_FORMAT_R64G64B64A64_SINT,
		eRGBA64Sfloat				= VK_FORMAT_R64G64B64A64_SFLOAT,

		eS8Uint						= VK_FORMAT_S8_UINT,
		eD16Unorm					= VK_FORMAT_D16_UNORM,
		eD32Sfloat					= VK_FORMAT_D32_SFLOAT,
		eD16UnormS8Uint				= VK_FORMAT_D16_UNORM_S8_UINT,
		eD24UnormS8Uint				= VK_FORMAT_D24_UNORM_S8_UINT,
		eD32SfloatS8Uint			= VK_FORMAT_D32_SFLOAT_S8_UINT,
	};
}