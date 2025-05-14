/*************************************************************************
***************************    Lepton_Enums    ***************************
*************************************************************************/
#pragma once

#include <vulkan/vulkan.hpp>

namespace Lepton
{
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