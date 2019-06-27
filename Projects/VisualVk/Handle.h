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

	using PFN_Destroy = void(VKAPI_CALL*)(VkDependency, VkResource, const VkAllocationCallbacks*);

	/*********************************************************************
	****************************    Handle    ****************************
	*********************************************************************/

	/**
	 *	@brief	Template for Vulkan resource handle.
	 */
	template<typename VkResource, typename VkDependency, PFN_Destroy<VkResource, VkDependency> DestroyFn>

	class Handle
	{

	public:

		//!	@brief	Default constructor.
		Handle() = default;

		//!	@brief	Constructed by Vulkan handle.
		Handle(VkResource hResource, VkDependency hDependency) : m_spInnerHandle(std::make_shared<InnerHandle>(hResource, hDependency)) {}

		//!	@brief	Convert to Vulkan handle.
		operator VkResource() const { return (m_spInnerHandle == nullptr) ? VK_NULL_HANDLE : m_spInnerHandle->m_hResource; }

		//!	@brief	If resource handle is valid.
		bool IsValid() const { return (m_spInnerHandle != nullptr) && (m_spInnerHandle->m_hResource != VK_NULL_HANDLE); }

		//!	@brief	Invalidate current handle.
		void Invalidate() { m_spInnerHandle.reset(); }

	private:

		/*****************************************************************
		***********************    InnerHandle    ************************
		*****************************************************************/

		/**
		 *	@brief	Inner handle object, which holds Vulkan handle.
		 */
		class InnerHandle
		{

		public:

			//!	@brief	Constructed by Vulkan handle.
			InnerHandle(VkResource hResource, VkDependency hDependency) : m_hResource(hResource), m_hDependency(hDependency) {}

			//!	@brief	Call Vulkan API to destroy resource object.
			~InnerHandle() { if (m_hDependency != VK_NULL_HANDLE) DestroyFn(m_hDependency, m_hResource, nullptr); }

		public:

			const VkResource			m_hResource;

			const VkDependency			m_hDependency;
		};

		std::shared_ptr<InnerHandle>	m_spInnerHandle;
	};

	/*********************************************************************
	*************************    Declarations    *************************
	*********************************************************************/

	using SamplerH			= Handle<VkSampler, VkDevice, vkDestroySampler>;
	using RenderPassH		= Handle<VkRenderPass, VkDevice, vkDestroyRenderPass>;
}