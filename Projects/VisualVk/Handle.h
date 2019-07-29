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
		Handle() : m_spInternalHandle(nullptr) {}

		//!	@brief	Constructed by given resource handle.
		Handle(VkDevice hDevice, VkResource hResource) : m_spInternalHandle(std::make_shared<InternalHandle>(hDevice, hResource)) {}

		//!	@brief	Convert to Vulkan resource handle.
		operator VkResource() const { return (m_spInternalHandle == nullptr) ? VK_NULL_HANDLE : m_spInternalHandle->m_hResource; }

		//!	@brief	If resource handle is valid.
		bool IsValid() const { return (m_spInternalHandle != nullptr) && (m_spInternalHandle->m_hResource != VK_NULL_HANDLE); }

		//!	@brief	Invalidate current handle.
		void Invalidate() { m_spInternalHandle.reset(); }

	protected:

		//!	@brief	Replace resource handle.
		void Replace(VkDevice hDevice, VkResource hResource)
		{
			m_spInternalHandle = std::make_shared<InternalHandle>(hDevice, hResource);
		}

	private:

		/*****************************************************************
		**********************    InternalHandle    **********************
		*****************************************************************/

		/**
		 *	@brief	Internal handle object, which holds Vulkan handle really.
		 */
		class InternalHandle
		{

		public:

			//!	@brief	Constructed by Vulkan handle.
			InternalHandle(VkDevice hDevice, VkResource hResource) : m_hDevice(hDevice), m_hResource(hResource) {}

			//!	@brief	Call Vulkan API to destroy resource object.
			~InternalHandle() { if (m_hDevice != VK_NULL_HANDLE) pfnDestroy(m_hDevice, m_hResource, nullptr); }

		public:

			const VkDevice					m_hDevice;

			const VkResource				m_hResource; 
		};

		std::shared_ptr<InternalHandle>		m_spInternalHandle;
	};

	/*********************************************************************
	*************************    Declarations    *************************
	*********************************************************************/

	using EventH					= Handle<VkEvent, vkDestroyEvent>;
	using FenceH					= Handle<VkFence, vkDestroyFence>;
	using SamplerH					= Handle<VkSampler, vkDestroySampler>;
	using PipelineH					= Handle<VkPipeline, vkDestroyPipeline>;
	using SemaphoreH				= Handle<VkSemaphore, vkDestroySemaphore>;
	using RenderPassH				= Handle<VkRenderPass, vkDestroyRenderPass>;
	using FramebufferH				= Handle<VkFramebuffer, vkDestroyFramebuffer>;
	using ShaderModuleH				= Handle<VkShaderModule, vkDestroyShaderModule>;
	using PipelineLayoutH			= Handle<VkPipelineLayout, vkDestroyPipelineLayout>;
	using DescriptorSetLayoutH		= Handle<VkDescriptorSetLayout, vkDestroyDescriptorSetLayout>;
}