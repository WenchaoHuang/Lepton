/*************************************************************************
*************************    VisualVk_Handle    **************************
*************************************************************************/
#pragma once

#include <memory>
#include <vulkan/vulkan_core.h>

namespace Vk
{
	//!	@brief	Template for any Vulkan destroy function.
	template<typename VkResource>

	using PFN_vkDestroy = void(VKAPI_CALL*)(VkDevice, VkResource, const VkAllocationCallbacks*);

	/*********************************************************************
	****************************    Handle    ****************************
	*********************************************************************/

	/**
	 *	@brief	Template for Vulkan resource handle.
	 */
	template<typename VkResource, PFN_vkDestroy<VkResource> pfnDestroy>
	
	class Handle
	{

	public:

		//!	@brief	Default constructor.
		Handle() : m_spHandle(nullptr) {}

		//!	@brief	Constructed by given resource handle.
		Handle(VkDevice hDevice, VkResource hResource) : m_spHandle(std::make_shared<InteriorHandle>(hDevice, hResource)) {}

		//!	@brief	Convert to Vulkan resource handle.
		operator VkResource() const { return (m_spHandle == nullptr) ? VK_NULL_HANDLE : m_spHandle->m_hResource; }

		//!	@brief	If resource handle is valid.
		bool IsValid() const { return (m_spHandle != nullptr) && (m_spHandle->m_hResource != VK_NULL_HANDLE); }

		//!	@brief	Invalidate current handle.
		void Invalidate() { m_spHandle.reset(); }

	protected:

		//!	@brief	Replace resource handle.
		void Replace(VkDevice hDevice, VkResource hResource)
		{
			m_spHandle = std::make_shared<InteriorHandle>(hDevice, hResource);
		}

	private:

		/*****************************************************************
		**********************    InteriorHandle    **********************
		*****************************************************************/

		/**
		 *	@brief	Interior handle object, which holds Vulkan handle really.
		 */
		class InteriorHandle
		{

		public:

			//!	@brief	Constructed by Vulkan handle.
			InteriorHandle(VkDevice hDevice, VkResource hResource) : m_hDevice(hDevice), m_hResource(hResource) {}

			//!	@brief	Call Vulkan API to destroy resource object.
			~InteriorHandle() { if (m_hDevice != VK_NULL_HANDLE) pfnDestroy(m_hDevice, m_hResource, nullptr); }

		public:

			const VkDevice				m_hDevice;

			const VkResource			m_hResource; 
		};

		std::shared_ptr<InteriorHandle>		m_spHandle;
	};

	/*********************************************************************
	*************************    Declarations    *************************
	*********************************************************************/

	using EventH					= Handle<VkEvent, vkDestroyEvent>;
	using FenceH					= Handle<VkFence, vkDestroyFence>;
	using ImageH					= Handle<VkImage, vkDestroyImage>;
	using BufferH					= Handle<VkBuffer, vkDestroyBuffer>;
	using SamplerH					= Handle<VkSampler, vkDestroySampler>;
	using PipelineH					= Handle<VkPipeline, vkDestroyPipeline>;
	using SemaphoreH				= Handle<VkSemaphore, vkDestroySemaphore>;
	using ImageViewH				= Handle<VkImageView, vkDestroyImageView>;
	using BufferViewH				= Handle<VkBufferView, vkDestroyBufferView>;
	using RenderPassH				= Handle<VkRenderPass, vkDestroyRenderPass>;
	using FramebufferH				= Handle<VkFramebuffer, vkDestroyFramebuffer>;
	using ShaderModuleH				= Handle<VkShaderModule, vkDestroyShaderModule>;
	using PipelineLayoutH			= Handle<VkPipelineLayout, vkDestroyPipelineLayout>;
	using DescriptorSetLayoutH		= Handle<VkDescriptorSetLayout, vkDestroyDescriptorSetLayout>;
}