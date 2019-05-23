/*************************************************************************
***********************    VisualVk_Descriptor    ************************
*************************************************************************/
#include "Descriptor.h"

using namespace Vk;

/*************************************************************************
***********************    DescriptorSetLayout    ************************
*************************************************************************/
DescriptorSetLayout::DescriptorSetLayout(VkDescriptorSetLayout hDescriptorSetLayout) : m_hDescriptorSetLayout(hDescriptorSetLayout)
{

}


std::shared_ptr<DescriptorSetLayout> DescriptorSetLayout::Create(const std::vector<VkDescriptorSetLayoutBinding> & Bindings)
{
	VkDescriptorSetLayoutCreateInfo		CreateInfo = {};
	CreateInfo.sType					= VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	CreateInfo.pNext					= nullptr;
	CreateInfo.flags					= 0;
	CreateInfo.bindingCount				= (uint32_t)Bindings.size();
	CreateInfo.pBindings				= Bindings.data();

	VkDescriptorSetLayout hDescriptorSetLayout = VK_NULL_HANDLE;

	sm_pDevice->CreateDescriptorSetLayout(&CreateInfo, &hDescriptorSetLayout);

	std::shared_ptr<DescriptorSetLayout> spDescriptorSetLayout = std::make_shared<DescriptorSetLayout>(hDescriptorSetLayout);

	if (spDescriptorSetLayout->IsValid())
	{
		spDescriptorSetLayout->m_Bindings = Bindings;
	}

	return spDescriptorSetLayout;
}


DescriptorSetLayout::~DescriptorSetLayout()
{
	sm_pDevice->DestroyDescriptorSetLayout(m_hDescriptorSetLayout);
}


/*************************************************************************
**************************    DescriptorPool    **************************
*************************************************************************/
DescriptorPool::DescriptorPool() : m_hDescriptorPool(VK_NULL_HANDLE)
{

}


VkResult DescriptorPool::Create(const std::vector<VkDescriptorPoolSize> & PoolSizes, uint32_t MaxSets)
{
	VkDescriptorPoolCreateInfo		CreateInfo = {};
	CreateInfo.sType				= VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	CreateInfo.pNext				= nullptr;
	CreateInfo.flags				= 0;
	CreateInfo.maxSets				= MaxSets;
	CreateInfo.poolSizeCount		= (uint32_t)PoolSizes.size();
	CreateInfo.pPoolSizes			= PoolSizes.data();

	VkDescriptorPool hDescriptorPool = VK_NULL_HANDLE;

	VkResult eResult = sm_pDevice->CreateDescriptorPool(&CreateInfo, &hDescriptorPool);

	if (eResult == VK_SUCCESS)
	{
		this->Release();

		m_hDescriptorPool = hDescriptorPool;
	}

	return eResult;
}


DescriptorSet * DescriptorPool::AllocateDescriptorSet(VkDescriptorSetLayout hDescriptorSetLayout)
{
	VkDescriptorSetAllocateInfo			AllocateInfo = {};
	AllocateInfo.sType					= VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	AllocateInfo.pNext					= nullptr;
	AllocateInfo.descriptorPool			= m_hDescriptorPool;
	AllocateInfo.descriptorSetCount		= 1;
	AllocateInfo.pSetLayouts			= &hDescriptorSetLayout;

	VkDescriptorSet hDescriptorSet = VK_NULL_HANDLE;

	if (sm_pDevice->AllocateDescriptorSets(&AllocateInfo, &hDescriptorSet) == VK_SUCCESS)
	{
		DescriptorSet * pDescriptorSet = new DescriptorSet(hDescriptorSet);

		m_pDescriptorSets.insert(pDescriptorSet);

		return pDescriptorSet;
	}

	return nullptr;
}


VkResult DescriptorPool::FreeDescriptorSet(DescriptorSet * pDescriptorSet)
{
	if (m_pDescriptorSets.erase(pDescriptorSet) != 0)
	{
		VkDescriptorSet hDescriptorSet = pDescriptorSet->m_hDescriptorSet;

		sm_pDevice->FreeDescriptorSets(m_hDescriptorPool, 1, &hDescriptorSet);

		delete pDescriptorSet;
	}

	return VK_ERROR_INVALID_EXTERNAL_HANDLE;
}


void DescriptorPool::Release() noexcept
{
	if (m_hDescriptorPool != VK_NULL_HANDLE)
	{
		sm_pDevice->DestroyDescriptorPool(m_hDescriptorPool);

		for (auto pDescriptorSet : m_pDescriptorSets)
		{
			delete pDescriptorSet;
		}

		m_hDescriptorPool = VK_NULL_HANDLE;

		m_pDescriptorSets.clear();
	}
}


DescriptorPool::~DescriptorPool()
{
	this->Release();
}


/*************************************************************************
**************************    DescriptorSet    ***************************
*************************************************************************/
DescriptorSet::DescriptorSet(VkDescriptorSet hDescriptorSet) : m_hDescriptorSet(hDescriptorSet)
{

}


void DescriptorSet::Write()
{
	VkDescriptorImageInfo	ImageInfo = {};
	ImageInfo.sampler		;
	ImageInfo.imageView		;
	ImageInfo.imageLayout	;

	VkWriteDescriptorSet					WriteDescriptorSet = {};
	WriteDescriptorSet.sType				= VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	WriteDescriptorSet.pNext				= nullptr;
	WriteDescriptorSet.dstSet				= m_hDescriptorSet;
	WriteDescriptorSet.dstBinding			;
	WriteDescriptorSet.dstArrayElement		;
	WriteDescriptorSet.descriptorCount		;
	WriteDescriptorSet.descriptorType		;
	WriteDescriptorSet.pImageInfo			= &ImageInfo;
	WriteDescriptorSet.pBufferInfo			= nullptr;
	WriteDescriptorSet.pTexelBufferView		= nullptr;

	sm_pDevice->UpdateDescriptorSets(1, &WriteDescriptorSet, 0, nullptr);
}


DescriptorSet::~DescriptorSet() noexcept
{

}