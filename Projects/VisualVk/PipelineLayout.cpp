/*************************************************************************
*********************    VisualVk_PipelineLayout    **********************
*************************************************************************/
#include "PipelineLayout.h"

using namespace Vk;

/*************************************************************************
**************************    PipelineLayout    **************************
*************************************************************************/
PipelineLayout::PipelineLayout(VkDevice hDevice,
							   ArrayProxy<const DescriptorSetLayout> descriptorSetLayouts,
							   ArrayProxy<const PushConstantRange> pushConstantRanges)
	: m_hDevice(VK_NULL_HANDLE), m_hPipelineLayout(VK_NULL_HANDLE)
{
	if (hDevice == VK_NULL_HANDLE)		return;

	VkResult eResult = VK_SUCCESS;

	std::vector<VkDescriptorSetLayout>	hDescriptorSetLayouts;

	for (uint32_t i = 0; i < descriptorSetLayouts.size(); i++)
	{
		std::vector<VkDescriptorSetLayoutBinding>	layoutBindings;

		layoutBindings.reserve(descriptorSetLayouts.size());

		for (auto iter : descriptorSetLayouts[i])
		{
			VkDescriptorSetLayoutBinding		newBinding = {};
			newBinding.binding					= iter.first;
			newBinding.descriptorType			= static_cast<VkDescriptorType>(iter.second.descriptorType);
			newBinding.descriptorCount			= iter.second.descriptorCount;
			newBinding.stageFlags				= iter.second.stageFlags;
			newBinding.pImmutableSamplers		= nullptr;

			layoutBindings.push_back(newBinding);
		}

		VkDescriptorSetLayoutCreateInfo		CreateInfo = {};
		CreateInfo.sType					= VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		CreateInfo.pNext					= nullptr;
		CreateInfo.flags					= 0;
		CreateInfo.bindingCount				= static_cast<uint32_t>(layoutBindings.size());
		CreateInfo.pBindings				= layoutBindings.data();

		VkDescriptorSetLayout hDescriptorSetLayout = VK_NULL_HANDLE;

		eResult = vkCreateDescriptorSetLayout(hDevice, &CreateInfo, nullptr, &hDescriptorSetLayout);

		if (eResult == VK_SUCCESS)
		{
			hDescriptorSetLayouts.push_back(hDescriptorSetLayout);
		}
		else
		{
			break;
		}
	}

	if (eResult == VK_SUCCESS)
	{
		VkPipelineLayoutCreateInfo				CreateInfo = {};
		CreateInfo.sType						= VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		CreateInfo.pNext						= nullptr;
		CreateInfo.flags						= 0;
		CreateInfo.setLayoutCount				= static_cast<uint32_t>(hDescriptorSetLayouts.size());
		CreateInfo.pSetLayouts					= hDescriptorSetLayouts.data();
		CreateInfo.pushConstantRangeCount		= pushConstantRanges.size();
		CreateInfo.pPushConstantRanges			= reinterpret_cast<const VkPushConstantRange*>(pushConstantRanges.data());

		VkPipelineLayout hPipelineLayout = VK_NULL_HANDLE;

		eResult = vkCreatePipelineLayout(hDevice, &CreateInfo, nullptr, &hPipelineLayout);

		if (eResult == VK_SUCCESS)
		{
			for (uint32_t i = 0; i < descriptorSetLayouts.size(); i++)
			{
				m_DescriptorSetLayouts.emplace_back(descriptorSetLayouts[i]);
			}

			for (uint32_t i = 0; i < pushConstantRanges.size(); i++)
			{
				m_PushConstantRanges.emplace_back(static_cast<PushConstantRange>(pushConstantRanges[i]));
			}

			m_hDescriptorSetLayouts.swap(hDescriptorSetLayouts);

			m_hPipelineLayout = hPipelineLayout;

			m_hDevice = hDevice;

			return;
		}
	}

	for (size_t i = 0; i < hDescriptorSetLayouts.size(); i++)
	{
		vkDestroyDescriptorSetLayout(hDevice, hDescriptorSetLayouts[i], nullptr);
	}
}


DescriptorSet * PipelineLayout::CreateDescriptorSet()
{
	if (m_hDevice != VK_NULL_HANDLE)
	{
		VkDescriptorPoolCreateInfo		CreateInfo = {};
		CreateInfo.sType				= VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		CreateInfo.pNext				= nullptr;
		CreateInfo.flags				= 0;
		CreateInfo.maxSets				= 1;
		CreateInfo.poolSizeCount		;	//!	TODO
		CreateInfo.pPoolSizes			;	//!	TODO

		VkDescriptorPool hDescriptorPool = VK_NULL_HANDLE;

		VkResult eResult = vkCreateDescriptorPool(m_hDevice, &CreateInfo, nullptr, &hDescriptorPool);

		if (eResult == VK_SUCCESS)
		{
			VkDescriptorSetAllocateInfo			AllocateInfo = {};
			AllocateInfo.sType					= VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
			AllocateInfo.pNext					= nullptr;
			AllocateInfo.descriptorPool			= hDescriptorPool;
			AllocateInfo.descriptorSetCount		= 1;
			AllocateInfo.pSetLayouts			;	//!	TODO

			VkDescriptorSet hDescriptorSet = VK_NULL_HANDLE;

			eResult = vkAllocateDescriptorSets(m_hDevice, &AllocateInfo, &hDescriptorSet);

			if (eResult != VK_SUCCESS)
			{
				vkDestroyDescriptorPool(m_hDevice, hDescriptorPool, nullptr);
			}
			else
			{
				DescriptorSet * pDescriptorSet = new DescriptorSet(m_hDevice, hDescriptorPool, hDescriptorSet);

				m_pDescriptorSets.insert(pDescriptorSet);

				return pDescriptorSet;
			}
		}
	}

	return nullptr;
}


Result PipelineLayout::DestroyDescriptorSet(DescriptorSet * pDescriptor)
{
	if (m_pDescriptorSets.erase(pDescriptor) != 0)
	{
		vkFreeDescriptorSets(m_hDevice, pDescriptor->m_hDescriptorPool, 1, &pDescriptor->m_hDescriptorSet);

		vkDestroyDescriptorPool(m_hDevice, pDescriptor->m_hDescriptorPool, nullptr);

		delete pDescriptor;

		return Result::eSuccess;
	}

	return Result::eErrorInvalidExternalHandle;
}


PipelineLayout::~PipelineLayout()
{
	if (m_hPipelineLayout != VK_NULL_HANDLE)
	{
		for (auto pDescriptor : m_pDescriptorSets)
		{
			vkFreeDescriptorSets(m_hDevice, pDescriptor->m_hDescriptorPool, 1, &pDescriptor->m_hDescriptorSet);

			vkDestroyDescriptorPool(m_hDevice, pDescriptor->m_hDescriptorPool, nullptr);

			delete pDescriptor;
		}

		for (size_t i = 0; i < m_hDescriptorSetLayouts.size(); i++)
		{
			vkDestroyDescriptorSetLayout(m_hDevice, m_hDescriptorSetLayouts[i], nullptr);
		}

		vkDestroyPipelineLayout(m_hDevice, m_hPipelineLayout, nullptr);

		m_hPipelineLayout = VK_NULL_HANDLE;

		m_hDescriptorSetLayouts.clear();

		m_DescriptorSetLayouts.clear();

		m_PushConstantRanges.clear();

		m_hDevice = VK_NULL_HANDLE;

		m_pDescriptorSets.clear();
	}
}


/*************************************************************************
**************************    DescriptorSet    ***************************
*************************************************************************/
DescriptorSet::DescriptorSet(VkDevice hDevice, VkDescriptorPool hDescriptorPool, VkDescriptorSet hDescriptorSet)
	: m_hDevice(hDevice), m_hDescriptorPool(hDescriptorPool), m_hDescriptorSet(hDescriptorSet)
{

}


DescriptorSet::~DescriptorSet() noexcept
{

}