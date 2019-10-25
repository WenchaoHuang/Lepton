/*************************************************************************
**********************    VisualVk_DescriptorSet    **********************
*************************************************************************/
#pragma once

#include <set>
#include "Vulkan.h"

namespace Vk
{
	/*********************************************************************
	******************    DescriptorSetLayoutBinding    ******************
	*********************************************************************/

	/**
	 *	@brief	Structure specifying a descriptor set layout binding.
	 */
	struct DescriptorSetLayoutBinding
	{
		Flags<ShaderStage>		stageFlags			= ShaderStage::eAllGraphics;
		DescriptorType			descriptorType		= DescriptorType::eSampler;
		uint32_t				descriptorCount		= 1;
	};

	/*********************************************************************
	**********************    DescriptorPoolSize    **********************
	*********************************************************************/

	/**
	 *	@brief	Structure specifying descriptor pool size.
	 */
	struct DescriptorPoolSize
	{
		DescriptorType			type				= DescriptorType::eSampler;
		uint32_t				descriptorCount		= 0;
	};

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
		Result Create(VkDevice hDevice, ArrayProxy<const DescriptorSetLayoutBinding> pLayoutBindings);

		//!	@brief	Return descriptor bindings.
		const std::vector<DescriptorSetLayoutBinding> & GetLayoutBindings() const { return m_spUniqueHandle->m_LayoutBindings; }

		//!	@brief	Convert to VkDescriptorSetLayout.
		operator VkDescriptorSetLayout() const { return (m_spUniqueHandle != nullptr) ? m_spUniqueHandle->m_hDescriptorSetLayout : VK_NULL_HANDLE; }

	private:

		/**
		 *	@brief	Unique handle of descriptor set layout.
		 */
		struct UniqueHandle
		{
			VK_NONCOPYABLE(UniqueHandle)

		public:

			//!	@brief	Constructor (all handles must be generated outside).
			UniqueHandle(VkDevice, VkDescriptorSetLayout, const std::vector<DescriptorSetLayoutBinding>&);

			//!	@brief	Where resource will be released.
			~UniqueHandle() noexcept;

		public:

			const VkDevice										m_hDevice;
			const VkDescriptorSetLayout							m_hDescriptorSetLayout;
			const std::vector<DescriptorSetLayoutBinding>		m_LayoutBindings;
		};

		std::shared_ptr<UniqueHandle>							m_spUniqueHandle;
	};

	/*********************************************************************
	************************    DescriptorPool    ************************
	*********************************************************************/

	/**
	 *	@brief	Wrapper for Vulkan descriptor pool object.
	 */
	class DescriptorPool
	{
		VK_NONCOPYABLE(DescriptorPool)

	public:

		//!	@brief	Create descriptor pool object.
		DescriptorPool();

		//!	@brief	Create and initialize immediately.
		explicit DescriptorPool(VkDevice hDevice, ArrayProxy<const DescriptorPoolSize> pDescriptorPoolSizes, uint32_t maxSets);

		//!	@brief	Destroy descriptor pool object.
		~DescriptorPool();

	public:

		//!	@brief	Whether this descriptor pool handle is valid.
		bool IsValid() const { return m_hDescriptorPool != VK_NULL_HANDLE; }

		//!	@brief	Create a new descriptor pool object.
		Result Create(VkDevice hDevice, ArrayProxy<const DescriptorPoolSize> pDescriptorPoolSizes, uint32_t maxSets);

		//!	@brief	Allocate a new descriptor set object.
		DescriptorSet * AllocateDescriptorSet(DescriptorSetLayout descriptorSetLayout);

		//!	@brief	Free one descriptor set.
		void FreeDescriptorSet(DescriptorSet * pDescriptorSet);

		//!	@brief	Destroy the descriptor pool.
		void Destroy();

	private:

		uint32_t							m_MaxSets;

		VkDevice							m_hDevice;

		VkDescriptorPool					m_hDescriptorPool;

		std::set<DescriptorSet*>			m_pDescriptorSets;

		std::vector<DescriptorPoolSize>		m_DescriptorPoolSizes;
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

		//!	@brief	Convert to VkDescriptorSet.
		operator VkDescriptorSet() const { return m_hDescriptorSet; }

		//!	@brief	Whether this descriptor set handle is valid.
		bool IsValid() const { return m_hDescriptorSet != VK_NULL_HANDLE; }

		void UpdateImage(uint32_t dstBinding, uint32_t dstArrayElement, VkSampler hSampler, VkImageView hImageView, ImageLayout eImageLayout);

	private:

		const VkDevice					m_hDevice;
		
		const VkDescriptorSet			m_hDescriptorSet;

		const DescriptorSetLayout		m_DescriptorSetLayout;
	};
}