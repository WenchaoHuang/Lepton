/*************************************************************************
***********************    VisualVk_Framebuffer    ***********************
*************************************************************************/
#pragma once

#include "Enums.h"
#include "Flags.h"
#include "Handle.h"
#include "Context.h"

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
	*********************    AttachmentReference    **********************
	*********************************************************************/

	/**
	 *	@brief	Structure specifying an attachment reference.
	 */
	struct AttachmentReference
	{
		uint32_t		attachment		= 0;
		ImageLayout		layout			= ImageLayout::eUndefined;
	};

	static_assert(sizeof(AttachmentReference) == sizeof(VkAttachmentReference), "struct and wrapper have different size!");
	
	/*********************************************************************
	**********************    SubpassDescription    **********************
	*********************************************************************/

	/**
	 *	@brief	Structure specifying a subpass description.
	 */
	struct SubpassDescription
	{
		const VkFlags					flags						= 0;
		PipelineBindPoint				pipelineBindPoint			= PipelineBindPoint::eGraphics;
		uint32_t                        inputAttachmentCount		= 0;
		const AttachmentReference *		pInputAttachments			= nullptr;
		uint32_t						colorAttachmentCount		= 0;
		const AttachmentReference *		pColorAttachments			= nullptr;
		const AttachmentReference *		pResolveAttachments			= nullptr;
		const AttachmentReference *		pDepthStencilAttachment		= nullptr;
		uint32_t						preserveAttachmentCount		= 0;
		const uint32_t *				pPreserveAttachments		= nullptr;
	};

	static_assert(sizeof(SubpassDescription) == sizeof(VkSubpassDescription), "struct and wrapper have different size!");

	/*********************************************************************
	********************    AttachmentDescription    *********************
	*********************************************************************/

	/**
	 *	@brief	Structure specifying an attachment description.
	 */
	struct AttachmentDescription
	{
		const VkFlags			flags				= 0;
		Format					format				= Format::eUndefined;
		SampleCount				samples				= SampleCount::x1;
		AttachmentLoadOp		loadOp				= AttachmentLoadOp::eClear;
		AttachmentStoreOp		storeOp				= AttachmentStoreOp::eStore;
		AttachmentLoadOp		stencilLoadOp		= AttachmentLoadOp::eDontCare;
		AttachmentStoreOp		stencilStoreOp		= AttachmentStoreOp::eDontCare;
		ImageLayout				initialLayout		= ImageLayout::eUndefined;
		ImageLayout				finalLayout			= ImageLayout::eUndefined;
	};

	static_assert(sizeof(AttachmentDescription) == sizeof(VkAttachmentDescription), "struct and wrapper have different size!");

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

	static_assert(sizeof(SubpassDependency) == sizeof(VkSubpassDependency), "struct and wrapper have different size!");

	/*********************************************************************
	**************************    RenderPass    **************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan render pass object.
	 */
	class RenderPass : public RenderPassH
	{

	public:

		//!	@brief	Create a render pass object.
		VkResult Create(const std::vector<AttachmentDescription> & attachmentDescriptions,
						const std::vector<SubpassDescription> & subpassDescriptions,
						const std::vector<SubpassDependency> & subpassDependencies);
	};

	/*********************************************************************
	*************************    Framebuffer    **************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan frame buffer object.
	 */
	class Framebuffer : public FramebufferH
	{

	public:

		//!	@brief	Create framebuffer object.
		Framebuffer();

		//!	@brief	Destroy framebuffer object.
		~Framebuffer();

	public:

		//!	@brief	Create a new frame buffer object.
		VkResult Create(RenderPassH hRenderPass, const std::vector<VkImageView> & Attachments, VkExtent2D Extent2D);


		void BeginRenderPass(CommandBuffer * pCommandBuffer, VkRect2D RenderArea, uint32_t clearValueCount, const VkClearValue * pClearValues);

		//!	@brief	Return render pass handle.
		RenderPassH GetRenderPass() const { return m_hRenderPass; }

		//!	@brief	Return extent of framebuffer.
		VkExtent2D GetExtent() const { return m_Extent2D; }

		//!	@brief	Destroy framebuffer object.
		void Invalidate();

	private:

		VkExtent2D		m_Extent2D;

		RenderPassH		m_hRenderPass;
	};
}