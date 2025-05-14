/*************************************************************************
***************************    Lepton_Enums    ***************************
*************************************************************************/
#pragma once

#include <vulkan/vulkan.hpp>

namespace Lepton
{
	/*********************************************************************
	***************************    CullMode    ***************************
	*********************************************************************/

	/**
	 *	@brief		Bitmask controlling triangle culling.
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
	 *	@brief		Control polygon rasterization mode.
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
	 *	@brief		Supported primitive topologies.
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
	 *	@brief		Framebuffer blending factors.
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
	 *	@brief		Indicate which dynamic state is taken from dynamic state commands.
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
	 *	@brief		Bitmask specifying intended usage of an image.
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
	 *	@brief		Bitmask specifying which aspects of an image are included in a view.
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
	 *	@brief		Layout of image and image subresources.
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
	 *	@brief		Stencil comparison function.
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
	 *	@brief		Stencil comparison function.
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
	****************************    Filter    ****************************
	*********************************************************************/

	/**
	 *	@brief		Specify filters used for texture lookups.
	 */
	enum class Filter
	{
		eLinear			= VK_FILTER_LINEAR,
		eNearest		= VK_FILTER_NEAREST,
		eCubicImg		= VK_FILTER_CUBIC_IMG,
	};

	/*********************************************************************
	**************************    MipmapMode    **************************
	*********************************************************************/

	/**
	 *	@brief		Specify mipmap mode used for texture lookups.
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
	 *	@brief		Specify behavior of sampling with texture coordinates outside an image.
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
	 *	@brief		Specify border color used for texture lookups.
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
	***********************    AttachmentLoadOp    ***********************
	*********************************************************************/

	/**
	 *	@brief		Specify how contents of an attachment are treated at the beginning of a subpass.
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
	 *	@brief		Specify how contents of an attachment are treated at the end of a subpass.
	 */
	enum class AttachmentStoreOp
	{
		eStore			= VK_ATTACHMENT_STORE_OP_STORE,
		eDontCare		= VK_ATTACHMENT_STORE_OP_DONT_CARE,
		eNoneQCOM		= VK_ATTACHMENT_STORE_OP_NONE_QCOM,
	};

	/*********************************************************************
	***********************    SubpassContents    ************************
	*********************************************************************/

	/**
	 *	@brief		Specify how commands in the first subpass of a render pass are provided.
	 */
	enum class SubpassContents
	{
		eInline							= VK_SUBPASS_CONTENTS_INLINE,
		eSecondaryCommandBuffers		= VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS,
	};

	/*********************************************************************
	**************************    IndexType    ***************************
	*********************************************************************/

	/**
	 *	@brief		Type of index buffer indices.
	 */
	enum class IndexType
	{
		eUint16		= VK_INDEX_TYPE_UINT16,
		eUint32		= VK_INDEX_TYPE_UINT32,
		eNoneNV		= VK_INDEX_TYPE_NONE_NV,
		eUint8EXT	= VK_INDEX_TYPE_UINT8_EXT,
	};
}