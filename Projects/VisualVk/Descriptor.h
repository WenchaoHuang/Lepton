/*************************************************************************
***********************    VisualVk_Descriptor    ************************
*************************************************************************/
#pragma once

#include "Resource.h"

namespace Vk
{
	class DescriptorSet;

	/*********************************************************************
	************************    DescriptorPool    ************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan descriptor pool object.
	 */
	class DescriptorPool : private Resource
	{

	public:

		//!	@brief	Create descriptor pool object.
		DescriptorPool();

		//!	@brief	Destroy descriptor pool object.
		~DescriptorPool();

	public:

		//!	@brief	Free descriptor set.
		VkResult FreeDescriptorSet(DescriptorSet * pDescriptorSet);

		//!	@brief	Creates a new descriptor pool object.
		VkResult Create(const std::vector<VkDescriptorPoolSize> & PoolSizes, uint32_t MaxSets);

		//!	@brief	Allocate descriptor set.
		DescriptorSet * AllocateDescriptorSet(VkDescriptorSetLayout hDescriptorSetLayout);

		//!	@brief	Destroy descriptor pool.
		void Release() noexcept;

	private:

		VkDescriptorPool				m_hDescriptorPool;

		std::set<DescriptorSet*>		m_pDescriptorSets;
	};

	/*********************************************************************
	************************    DescriptorSet    *************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan descriptor set object.
	 */
	class DescriptorSet : private Resource
	{

	private:

		friend class DescriptorPool;

		//!	@brief	Create descriptor set object.
		DescriptorSet(VkDescriptorSet hDescriptorSet);

		//!	@brief	Destroy descriptor set object.
		~DescriptorSet() noexcept;

	public:



	private:

		const VkDescriptorSet		m_hDescriptorSet;
	};

	/*********************************************************************
	*********************    DescriptorSetLayout    **********************
	*********************************************************************/

	/**
	 *	@brief	Vulkan descriptor set layout object.
	 */
	class DescriptorSetLayout : private Resource
	{

	public:

		//!	@brief	Create descriptor set layout object.
		DescriptorSetLayout();

		//!	@brief	Destroy descriptor set layout object.
		~DescriptorSetLayout();

	public:

		//!	@brief	Convert to Vulkan handle.
		operator VkDescriptorSetLayout() { return m_hDescriptorSetLayout; }

		//!	@brief	Create a new descriptor set layout object.
		VkResult Create(const std::vector<VkDescriptorSetLayoutBinding> & Bindings = std::vector<VkDescriptorSetLayoutBinding>());

		//!	@brief	Is descriptor set layout handle is valid.
		VkBool32 IsValid() const { return m_hDescriptorSetLayout != VK_NULL_HANDLE; }

		//!	@brief	Destroy descriptor set layout object.
		void Release() noexcept;

	private:

		VkDescriptorSetLayout			m_hDescriptorSetLayout;

		std::vector<VkDescriptorSetLayoutBinding>	m_Bindings;
	};
}