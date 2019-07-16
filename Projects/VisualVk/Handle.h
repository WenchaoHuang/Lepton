/*************************************************************************
*************************    VisualVk_Handle    **************************
*************************************************************************/
#pragma once

#include <memory>
#include <vulkan/vulkan_core.h>

namespace Vk
{
	//!	@brief	Template for any Vulkan destroy function.
	template<typename VkResource, typename VkDependency>

	using PFN_vkDestroy = void(VKAPI_CALL*)(VkDependency, VkResource, const VkAllocationCallbacks*);

	/*********************************************************************
	****************************    Handle    ****************************
	*********************************************************************/

	/**
	 *	@brief	Template for Vulkan resource handle.
	 */
	template<typename VkResource, typename VkDependency, PFN_vkDestroy<VkResource, VkDependency> pfnDestroy>

	class Handle
	{

	public:

		//!	@brief	Default constructor.
		Handle() : m_spInternalHandle(nullptr) {}

		//!	@brief	Convert to Vulkan resource handle.
		operator VkResource() const { return (m_spInternalHandle == nullptr) ? VK_NULL_HANDLE : m_spInternalHandle->m_hResource; }

		//!	@brief	If resource handle is valid.
		bool IsValid() const { return (m_spInternalHandle != nullptr) && (m_spInternalHandle->m_hResource != VK_NULL_HANDLE); }

		//!	@brief	Invalidate current handle.
		void Invalidate() { m_spInternalHandle.reset(); }

	protected:

		//!	@brief	Replace resource handle.
		void Replace(VkResource hResource, VkDependency hDependency)
		{
			m_spInternalHandle = std::make_shared<InternalHandle>(hResource, hDependency);
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
			InternalHandle(VkResource hResource, VkDependency hDependency) : m_hResource(hResource), m_hDependency(hDependency) {}

			//!	@brief	Call Vulkan API to destroy resource object.
			~InternalHandle() { if (m_hDependency != VK_NULL_HANDLE) pfnDestroy(m_hDependency, m_hResource, nullptr); }

		public:

			const VkResource				m_hResource;

			const VkDependency				m_hDependency;
		};

		std::shared_ptr<InternalHandle>		m_spInternalHandle;
	};

	/*********************************************************************
	*************************    Declarations    *************************
	*********************************************************************/

	using SamplerH			= Handle<VkSampler, VkDevice, vkDestroySampler>;
	using RenderPassH		= Handle<VkRenderPass, VkDevice, vkDestroyRenderPass>;
	using ShaderModuleH		= Handle<VkShaderModule, VkDevice, vkDestroyShaderModule>;
}