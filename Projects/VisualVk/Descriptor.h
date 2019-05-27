/*************************************************************************
***********************    VisualVk_Descriptor    ************************
*************************************************************************/
#pragma once

#include <memory>
#include <utility>
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

		//!	@brief	Update the contents of a descriptor set object.
		void Update();

	private:

		const VkDescriptorSet		m_hDescriptorSet;
	};
}