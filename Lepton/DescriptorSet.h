/*************************************************************************
***********************    Lepton_DescriptorSet    ***********************
*************************************************************************/
#pragma once

#include <set>
#include "Vulkan.h"

namespace Lepton
{
	/*********************************************************************
	*********************    DescriptorSetLayout    **********************
	*********************************************************************/

	/**
	 *	@brief	Wrapper for Vulkan descriptor set layout object.
	 */
	class DescriptorSetLayout
	{

	public:

		//!	@brief	Invalidate this resource handle.
		void Destroy() { m_spUniqueHandle.reset(); }

		//!	@brief	Whether this resource handle is valid.
		bool IsValid() const { return m_spUniqueHandle != nullptr; }

		//!	@brief	Create a new descriptor set layout object.
		Result Create(VkDevice hDevice, vk::ArrayProxy<vk::DescriptorSetLayoutBinding> pLayoutBindings);

		//!	@brief	Return descriptor bindings.
		const std::vector<vk::DescriptorSetLayoutBinding> & GetLayoutBindings() const { return m_spUniqueHandle->m_LayoutBindings; }

		//!	@brief	Return VkDevice handle.
		VkDevice GetDeviceHandle() const { return (m_spUniqueHandle != nullptr) ? m_spUniqueHandle->m_hDevice : VK_NULL_HANDLE; }

		//!	@brief	Convert to VkDescriptorSetLayout.
		operator VkDescriptorSetLayout() const { return (m_spUniqueHandle != nullptr) ? m_spUniqueHandle->m_hDescriptorSetLayout : VK_NULL_HANDLE; }

	private:

		/**
		 *	@brief	Unique handle of descriptor set layout.
		 */
		struct UniqueHandle
		{
			LAVA_NONCOPYABLE(UniqueHandle)

		public:

			//!	@brief	Constructor (handles must be initialized).
			UniqueHandle(VkDevice, VkDescriptorSetLayout, const std::vector<vk::DescriptorSetLayoutBinding>&);

			//!	@brief	Where resource will be released.
			~UniqueHandle() noexcept;

		public:

			const VkDevice											m_hDevice;
			const VkDescriptorSetLayout								m_hDescriptorSetLayout;
			const std::vector<vk::DescriptorSetLayoutBinding>		m_LayoutBindings;
		};

		std::shared_ptr<UniqueHandle>								m_spUniqueHandle;
	};

	/*********************************************************************
	************************    DescriptorPool    ************************
	*********************************************************************/

	/**
	 *	@brief	Wrapper for Vulkan descriptor pool object.
	 */
	class DescriptorPool
	{
		LAVA_NONCOPYABLE(DescriptorPool)

	public:

		//!	@brief	Create descriptor pool object.
		DescriptorPool();

		//!	@brief	Create and initialize immediately.
		explicit DescriptorPool(VkDevice hDevice, vk::ArrayProxy<vk::DescriptorPoolSize> pDescriptorPoolSizes, uint32_t maxSets);

		//!	@brief	Destroy descriptor pool object.
		~DescriptorPool();

	public:

		//!	@brief	Return VkDescriptorPool handle.
		VkDescriptorPool Handle() const { return m_hDescriptorPool; }

		//!	@brief	Whether this descriptor pool handle is valid.
		bool IsValid() const { return m_hDescriptorPool != VK_NULL_HANDLE; }

		//!	@brief	Create a new descriptor pool object.
		Result Create(VkDevice hDevice, vk::ArrayProxy<vk::DescriptorPoolSize> pDescriptorPoolSizes, uint32_t maxSets, vk::DescriptorPoolCreateFlags flags = vk::DescriptorPoolCreateFlagBits::eFreeDescriptorSet);

		//!	@brief	Allocate a new descriptor set object.
		DescriptorSet * AllocateDescriptorSet(DescriptorSetLayout descriptorSetLayout);

		//!	@brief	Free one descriptor set.
		void FreeDescriptorSet(DescriptorSet * pDescriptorSet);

		//!	@brief	Destroy the descriptor pool.
		void Destroy();

	private:

		uint32_t								m_MaxSets;

		VkDevice								m_hDevice;

		VkDescriptorPool						m_hDescriptorPool;

		std::set<DescriptorSet*>				m_pDescriptorSets;

		std::vector<vk::DescriptorPoolSize>		m_DescriptorPoolSizes;
	};

	/*********************************************************************
	************************    DescriptorSet    *************************
	*********************************************************************/

	/**
	 *	@brief	Wrapper for Vulkan descriptor set object.
	*/
	class DescriptorSet
	{
		friend class DescriptorPool;

	private:

		//!	@brief	Create descriptor set object.
		explicit DescriptorSet(VkDevice hDevice, VkDescriptorSet hDescriptorSet, DescriptorSetLayout LayoutBinding);

		//!	@brief	Destroy this descriptor set.
		~DescriptorSet() noexcept;

	public:

		//!	@brief	Return Vulkan type of this object.
		VkDescriptorSet Handle() const { return m_hDescriptorSet; }

		//!	@brief	Whether this descriptor set handle is valid.
		bool IsValid() const { return m_hDescriptorSet != VK_NULL_HANDLE; }

		void UpdateImage(uint32_t dstBinding, uint32_t dstArrayElement, VkSampler hSampler, VkImageView hImageView, vk::ImageLayout eImageLayout);

	private:

		const VkDevice					m_hDevice;
		
		const VkDescriptorSet			m_hDescriptorSet;

		const DescriptorSetLayout		m_DescriptorSetLayout;
	};
}