/*************************************************************************
***********************    Lepton_DescriptorSet    ***********************
*************************************************************************/

#include "DescriptorSet.h"

using namespace Lepton;

/*************************************************************************
***********************    DescriptorSetLayout    ************************
*************************************************************************/
DescriptorSetLayout::UniqueHandle::UniqueHandle(VkDevice hDevice, VkDescriptorSetLayout hDescriptorSetLayout, const std::vector<vk::DescriptorSetLayoutBinding> & LayoutBindings)
	: m_hDevice(hDevice), m_hDescriptorSetLayout(hDescriptorSetLayout), m_LayoutBindings(LayoutBindings)
{

}


Result DescriptorSetLayout::Create(VkDevice hDevice, vk::ArrayProxy<vk::DescriptorSetLayoutBinding> pLayoutBindings)
{
	Result eResult = Result::eErrorInvalidDeviceHandle;

	if (hDevice != VK_NULL_HANDLE)
	{
		std::vector<VkDescriptorSetLayoutBinding>		layoutBindings(pLayoutBindings.size());

		for (uint32_t i = 0; i < pLayoutBindings.size(); i++)
		{
			layoutBindings[i].binding					= i;
			layoutBindings[i].stageFlags				= (VkFlags)(pLayoutBindings.data() + i)->stageFlags;
			layoutBindings[i].descriptorType			= static_cast<VkDescriptorType>((pLayoutBindings.data() + i)->descriptorType);
			layoutBindings[i].descriptorCount			= (pLayoutBindings.data() + i)->descriptorCount;
			layoutBindings[i].pImmutableSamplers		= nullptr;
		}

		VkDescriptorSetLayoutCreateInfo		CreateInfo = {};
		CreateInfo.sType					= VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		CreateInfo.pNext					= nullptr;
		CreateInfo.flags					= 0;
		CreateInfo.bindingCount				= static_cast<uint32_t>(layoutBindings.size());
		CreateInfo.pBindings				= layoutBindings.data();

		VkDescriptorSetLayout hDescriptorSetLayout = VK_NULL_HANDLE;

		eResult = LAVA_RESULT_CAST(vkCreateDescriptorSetLayout(hDevice, &CreateInfo, nullptr, &hDescriptorSetLayout));

		if (eResult == Result::eSuccess)
		{
			std::vector<vk::DescriptorSetLayoutBinding>		LayoutBindings(pLayoutBindings.size());

			for (uint32_t i = 0; i < pLayoutBindings.size(); i++)
			{
				LayoutBindings[i] = *(pLayoutBindings.data() + i);
			}

			m_spUniqueHandle = std::make_shared<UniqueHandle>(hDevice, hDescriptorSetLayout, LayoutBindings);
		}
	}

	return eResult;
}


DescriptorSetLayout::UniqueHandle::~UniqueHandle() noexcept
{
	if (m_hDescriptorSetLayout != VK_NULL_HANDLE)
	{
		vkDestroyDescriptorSetLayout(m_hDevice, m_hDescriptorSetLayout, nullptr);
	}
}


/*************************************************************************
**************************    DescriptorPool    **************************
*************************************************************************/
DescriptorPool::DescriptorPool() : m_hDevice(VK_NULL_HANDLE), m_hDescriptorPool(VK_NULL_HANDLE), m_MaxSets(0)
{
	
}


DescriptorPool::DescriptorPool(VkDevice hDevice, vk::ArrayProxy<vk::DescriptorPoolSize> pDescriptorPoolSizes, uint32_t maxSets) : DescriptorPool()
{
	this->Create(hDevice, pDescriptorPoolSizes, maxSets);
}


Result DescriptorPool::Create(VkDevice hDevice, vk::ArrayProxy<vk::DescriptorPoolSize> pDescriptorPoolSizes, uint32_t maxSets, vk::DescriptorPoolCreateFlags flags)
{
	Result eResult = Result::eErrorInvalidDeviceHandle;

	if (hDevice != VK_NULL_HANDLE)
	{
		VkDescriptorPoolCreateInfo		CreateInfo = {};
		CreateInfo.sType				= VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		CreateInfo.pNext				= nullptr;
		CreateInfo.flags				= (VkFlags)flags;
		CreateInfo.maxSets				= maxSets;
		CreateInfo.poolSizeCount		= pDescriptorPoolSizes.size();
		CreateInfo.pPoolSizes			= reinterpret_cast<const VkDescriptorPoolSize*>(pDescriptorPoolSizes.data());

		VkDescriptorPool hDescriptorPool = VK_NULL_HANDLE;

		eResult = LAVA_RESULT_CAST(vkCreateDescriptorPool(hDevice, &CreateInfo, nullptr, &hDescriptorPool));

		if (eResult == Result::eSuccess)
		{
			this->Destroy();

			m_DescriptorPoolSizes.resize(pDescriptorPoolSizes.size());

			for (uint32_t i = 0; i < pDescriptorPoolSizes.size(); i++)
			{
				m_DescriptorPoolSizes[i] = *(pDescriptorPoolSizes.data() + i);
			}

			m_hDescriptorPool = hDescriptorPool;

			m_hDevice = hDevice;

			m_MaxSets = maxSets;
		}
	}

	return eResult;
}


DescriptorSet * DescriptorPool::AllocateDescriptorSet(DescriptorSetLayout descriptorSetLayout)
{
	DescriptorSet * pDescriptorSet = nullptr;

	if ((m_hDescriptorPool != nullptr) && descriptorSetLayout.IsValid())
	{
		VkDescriptorSetLayout				hDescriptorSetLayout = descriptorSetLayout;

		VkDescriptorSetAllocateInfo			AllocateInfo = {};
		AllocateInfo.sType					= VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		AllocateInfo.pNext					= nullptr;
		AllocateInfo.descriptorPool			= m_hDescriptorPool;
		AllocateInfo.descriptorSetCount		= 1;
		AllocateInfo.pSetLayouts			= &hDescriptorSetLayout;

		VkDescriptorSet hDescriptorSet = VK_NULL_HANDLE;

		if (vkAllocateDescriptorSets(m_hDevice, &AllocateInfo, &hDescriptorSet) == VK_SUCCESS)
		{
			pDescriptorSet = new DescriptorSet(m_hDevice, hDescriptorSet, descriptorSetLayout);

			m_pDescriptorSets.insert(pDescriptorSet);
		}
	}

	return pDescriptorSet;
}


void DescriptorPool::FreeDescriptorSet(DescriptorSet * pDescriptorSet)
{
	if (m_pDescriptorSets.erase(pDescriptorSet) != 0)
	{
		vkFreeDescriptorSets(m_hDevice, m_hDescriptorPool, 1, &pDescriptorSet->m_hDescriptorSet);

		delete pDescriptorSet;
	}
}


void DescriptorPool::Destroy()
{
	if (m_hDescriptorPool != VK_NULL_HANDLE)
	{
		vkDestroyDescriptorPool(m_hDevice, m_hDescriptorPool, nullptr);

		for (auto pDescriptorSets : m_pDescriptorSets)
		{
			delete pDescriptorSets;
		}

		m_hDescriptorPool = VK_NULL_HANDLE;

		m_DescriptorPoolSizes.clear();

		m_hDevice = VK_NULL_HANDLE;

		m_pDescriptorSets.clear();

		m_MaxSets = 0;
	}
}


DescriptorPool::~DescriptorPool()
{
	this->Destroy();
}


/*************************************************************************
**************************    DescriptorSet    ***************************
*************************************************************************/
DescriptorSet::DescriptorSet(VkDevice hDevice, VkDescriptorSet hDescriptorSet, DescriptorSetLayout descriptorSetLayout)
	: m_hDevice(hDevice), m_hDescriptorSet(hDescriptorSet), m_DescriptorSetLayout(descriptorSetLayout)
{

}


void DescriptorSet::UpdateImage(uint32_t dstBinding, uint32_t dstArrayElement, VkSampler hSampler, VkImageView hImageView, vk::ImageLayout eImageLayout)
{
	auto & LayoutBindings = m_DescriptorSetLayout.GetLayoutBindings();

	VkDescriptorImageInfo					ImageInfo = {};
	ImageInfo.sampler						= hSampler;
	ImageInfo.imageView						= hImageView;
	ImageInfo.imageLayout					= static_cast<VkImageLayout>(eImageLayout);

	VkWriteDescriptorSet					DescriptorWrite = {};
	DescriptorWrite.sType					= VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	DescriptorWrite.pNext					= nullptr;
	DescriptorWrite.dstSet					= m_hDescriptorSet;
	DescriptorWrite.dstBinding				= dstBinding;
	DescriptorWrite.dstArrayElement			= dstArrayElement;
	DescriptorWrite.descriptorCount			= 1;
	DescriptorWrite.descriptorType			= static_cast<VkDescriptorType>(LayoutBindings[dstBinding].descriptorType);
	DescriptorWrite.pImageInfo				= &ImageInfo;
	DescriptorWrite.pBufferInfo				= nullptr;
	DescriptorWrite.pTexelBufferView		= nullptr;

	vkUpdateDescriptorSets(m_hDevice, 1, &DescriptorWrite, 0, nullptr);
}


DescriptorSet::~DescriptorSet() noexcept
{

}