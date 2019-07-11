/*************************************************************************
***********************    VisualVk_Framebuffer    ***********************
*************************************************************************/
#pragma once

#include "Enum.h"
#include "Flags.h"
#include "Format.h"
#include "Handle.h"
#include "Resource.h"

namespace Vk
{
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
	**********************    DependencyFlagBits    **********************
	*********************************************************************/

	/**
	 *	@brief	Bitmask specifying how execution and memory dependencies are formed.
	 */
	enum class DependencyFlagBits : VkFlags
	{
		eByRegion			= VK_DEPENDENCY_BY_REGION_BIT,
		eViewLocal			= VK_DEPENDENCY_VIEW_LOCAL_BIT,
		eDeviceGroup		= VK_DEPENDENCY_DEVICE_GROUP_BIT
	};
	
	/*********************************************************************
	************************    AccessFlagBits    ************************
	*********************************************************************/

	/**
	 *	@brief	Bitmask specifying memory access types that will participate in a memory dependency.
	 */
	enum class AccessFlagBits : VkFlags
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
		eCommandProcessReadNVX					= VK_ACCESS_COMMAND_PROCESS_READ_BIT_NVX
	};

	/*********************************************************************
	********************    AttachmentDescription    *********************
	*********************************************************************/

	/**
	 *	@brief	Structure specifying an attachment description.
	 */
	struct AttachmentDescription
	{
		Format					format				= Format::eUndefined;
		SampleCount				samples				= SampleCount::e1;
		AttachmentLoadOp		loadOp				= AttachmentLoadOp::eClear;
		AttachmentStoreOp		storeOp				= AttachmentStoreOp::eStore;
		AttachmentLoadOp		stencilLoadOp		= AttachmentLoadOp::eDontCare;
		AttachmentStoreOp		stencilStoreOp		= AttachmentStoreOp::eDontCare;
		ImageLayout				initialLayout		= ImageLayout::eUndefined;
		ImageLayout				finalLayout			= ImageLayout::eUndefined;
	};

	/*********************************************************************
	**********************    SubpassDependency    ***********************
	*********************************************************************/

	/**
	 *	@brief	Structure specifying a subpass dependency.
	 */
	struct SubpassDependency
	{
		uint32_t						srcSubpass			= 0;
		uint32_t						dstSubpass			= 0;
		Flags<PipelineStage>			srcStageMask		= 0;
		Flags<PipelineStage>			dstStageMask		= 0;
		Flags<AccessFlagBits>			srcAccessMask		= 0;
		Flags<AccessFlagBits>			dstAccessMask		= 0;
		Flags<DependencyFlagBits>		dependencyFlags		= 0;
	};

	/*********************************************************************
	**************************    RenderPass    **************************
	*********************************************************************/

	/**
	 *	@brief	Base class for Vulkan render pass object.
	 */
	class RenderPass : private Resource, public RenderPassH
	{

	public:

		//!	@brief	Create render pass object.
		RenderPass();

		//!	@brief	Destroy render pass object.
		~RenderPass();

	public:

		//!	@brief	Create a render pass object.
		VkResult Create(const std::vector<AttachmentDescription> & attachmentDescriptions,
						const std::vector<VkSubpassDescription> & subpassDescriptions,
						const std::vector<SubpassDependency> & subpassDependencies);

	private:

		std::vector<SubpassDependency>			m_SubpassDependencies;
		std::vector<VkSubpassDescription>		m_SubpassDescriptions;
		std::vector<AttachmentDescription>		m_AttachmentDescriptions;
	};

	/*********************************************************************
	*************************    Framebuffer    **************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan frame buffer object.
	 */
	class Framebuffer : private Resource
	{

	public:

		//!	@brief	Create framebuffer object.
		Framebuffer();

		//!	@brief	Destroy framebuffer object.
		~Framebuffer();

	public:

		//!	@brief	Convert to VkFramebuffer handle.
		operator VkFramebuffer() const { return m_hFramebuffer; }

		//!	@brief	Create a new frame buffer object.
		VkResult Create(RenderPassH hRenderPass, const std::vector<VkImageView> & Attachments, VkExtent2D Extent2D);

		//!	@brief	Return render pass handle.
		RenderPassH GetRenderPass() const { return m_hRenderPass; }

		//!	@brief	Return extent of framebuffer.
		VkExtent2D GetExtent() const { return m_Extent2D; }

		//!	@brief	Invalidate framebuffer.
		void Release();

	private:

		VkExtent2D						m_Extent2D;

		RenderPassH						m_hRenderPass;

		VkFramebuffer					m_hFramebuffer;

		std::vector<VkImageView>		m_Attachments;
	};
}