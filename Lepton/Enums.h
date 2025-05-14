/*************************************************************************
***************************    Lepton_Enums    ***************************
*************************************************************************/
#pragma once

#include <vulkan/vulkan.hpp>

namespace Lepton
{
	/*********************************************************************
	**************************    FrontFace    ***************************
	*********************************************************************/

	/**
	 *	@brief		Interpret polygon front-facing orientation.
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
	***************************    LogicOp    ****************************
	*********************************************************************/

	/**
	 *	@brief		Framebuffer logical operations.
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
	***************************    BlendOp    ****************************
	*********************************************************************/

	/**
	 *	@brief		Framebuffer blending operations.
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
	*************************    MemoryAccess    *************************
	*********************************************************************/

	/**
	 *	@brief		Bitmask specifying memory access types that will participate in a memory dependency.
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
		eCommandPreprocessWriteNV				= VK_ACCESS_COMMAND_PREPROCESS_WRITE_BIT_NV,
		eCommandPreprocessReadNV				= VK_ACCESS_COMMAND_PREPROCESS_READ_BIT_NV,
		eShadingRateImageReadNV					= VK_ACCESS_SHADING_RATE_IMAGE_READ_BIT_NV,
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

	/*********************************************************************
	****************************    Format    ****************************
	*********************************************************************/

	/**
	 *	@brief		Common available image formats.
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