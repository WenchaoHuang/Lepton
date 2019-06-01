/*************************************************************************
*********************    VisualVk_PipelineLayout    **********************
*************************************************************************/
#include "PipelineLayout.h"

using namespace Vk;

/*************************************************************************
************************    PipelineLayoutInfo    ************************
*************************************************************************/
void PipelineLayoutInfo::SetBinding(uint32_t Binding, VkShaderStageFlags eStageFlags, VkDescriptorType eDescriptorType, uint32_t DescriptorCount)
{
	LayoutBinding		NewBinding = {};
	NewBinding.descriptorType		= eDescriptorType;
	NewBinding.descriptorCount		= DescriptorCount;
	NewBinding.stageFlags			= eStageFlags;

	layoutBindings[Binding] = NewBinding;
}


void PipelineLayoutInfo::PushConstantRange(VkShaderStageFlags eStageFlags, uint32_t OffsetBytes, uint32_t SizeBytes)
{
	VkPushConstantRange		NewRange = {};
	NewRange.stageFlags		= eStageFlags;
	NewRange.offset			= OffsetBytes;
	NewRange.size			= SizeBytes;

	constantRanges.push_back(NewRange);
}


/*************************************************************************
**************************    PipelineLayout    **************************
*************************************************************************/
PipelineLayout::PipelineLayout(VkPipelineLayout hPipelineLayout, VkDescriptorSetLayout hDescriptorSetLayout, const PipelineLayoutInfo & LayoutInfo)
	: m_hPipelineLayout(hPipelineLayout), m_hDescriptorSetLayout(hDescriptorSetLayout), m_PipelineLayoutInfo(LayoutInfo)
{
	m_DescriptorPoolSizes.reserve(m_PipelineLayoutInfo.layoutBindings.size());

	for (auto layoutBinding : m_PipelineLayoutInfo.layoutBindings)
	{
		VkDescriptorPoolSize				DescriptorPoolSize = {};
		DescriptorPoolSize.type				= layoutBinding.second.descriptorType;
		DescriptorPoolSize.descriptorCount	= layoutBinding.second.descriptorCount;

		m_DescriptorPoolSizes.push_back(DescriptorPoolSize);
	}
}


std::shared_ptr<PipelineLayout> PipelineLayout::Create(const PipelineLayoutInfo & LayoutInfo)
{
	std::vector<VkDescriptorSetLayoutBinding> LayoutBindings;

	LayoutBindings.reserve(LayoutInfo.layoutBindings.size());

	for (auto layoutBinding : LayoutInfo.layoutBindings)
	{
		VkDescriptorSetLayoutBinding					DescriptorSetLayoutBinding = {};
		DescriptorSetLayoutBinding.binding				= layoutBinding.first;
		DescriptorSetLayoutBinding.descriptorType		= layoutBinding.second.descriptorType;
		DescriptorSetLayoutBinding.descriptorCount		= layoutBinding.second.descriptorCount;
		DescriptorSetLayoutBinding.stageFlags			= layoutBinding.second.stageFlags;
		DescriptorSetLayoutBinding.pImmutableSamplers	= nullptr;

		LayoutBindings.push_back(DescriptorSetLayoutBinding);
	}

	VkDescriptorSetLayoutCreateInfo					DescriptorSetLayoutCreateInfo = {};
	DescriptorSetLayoutCreateInfo.sType				= VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	DescriptorSetLayoutCreateInfo.pNext				= nullptr;
	DescriptorSetLayoutCreateInfo.flags				= 0;
	DescriptorSetLayoutCreateInfo.bindingCount		= (uint32_t)LayoutBindings.size();
	DescriptorSetLayoutCreateInfo.pBindings			= LayoutBindings.data();

	VkPipelineLayout hPipelineLayout = VK_NULL_HANDLE;

	VkDescriptorSetLayout hDescriptorSetLayout = VK_NULL_HANDLE;

	if (sm_pDevice->CreateDescriptorSetLayout(&DescriptorSetLayoutCreateInfo, &hDescriptorSetLayout) == VK_SUCCESS)
	{
		VkPipelineLayoutCreateInfo							PipelineLayoutCreateInfo = {};
		PipelineLayoutCreateInfo.sType						= VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		PipelineLayoutCreateInfo.pNext						= nullptr;
		PipelineLayoutCreateInfo.flags						= 0;
		PipelineLayoutCreateInfo.setLayoutCount				= 1;
		PipelineLayoutCreateInfo.pSetLayouts				= &hDescriptorSetLayout;
		PipelineLayoutCreateInfo.pushConstantRangeCount		= (uint32_t)LayoutInfo.constantRanges.size();
		PipelineLayoutCreateInfo.pPushConstantRanges		= LayoutInfo.constantRanges.data();

		sm_pDevice->CreatePipelineLayout(&PipelineLayoutCreateInfo, &hPipelineLayout);
	}

	return std::make_shared<PipelineLayout>(hPipelineLayout, hDescriptorSetLayout, LayoutInfo);
}


std::shared_ptr<DescriptorSet> PipelineLayout::CreateDescriptorSet()
{
	VkDescriptorSet hDescriptorSet = VK_NULL_HANDLE;

	VkDescriptorPool hDescriptorPool = VK_NULL_HANDLE;

	if (!m_DescriptorPoolSizes.empty() && (m_hDescriptorSetLayout != VK_NULL_HANDLE))
	{
		VkDescriptorPoolCreateInfo		CreateInfo = {};
		CreateInfo.sType				= VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		CreateInfo.pNext				= nullptr;
		CreateInfo.flags				= 0;
		CreateInfo.maxSets				= 1;
		CreateInfo.poolSizeCount		= (uint32_t)m_DescriptorPoolSizes.size();
		CreateInfo.pPoolSizes			= m_DescriptorPoolSizes.data();

		if (sm_pDevice->CreateDescriptorPool(&CreateInfo, &hDescriptorPool) == VK_SUCCESS)
		{
			VkDescriptorSetAllocateInfo			AllocateInfo = {};
			AllocateInfo.sType					= VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
			AllocateInfo.pNext					= nullptr;
			AllocateInfo.descriptorPool			= hDescriptorPool;
			AllocateInfo.descriptorSetCount		= 1;
			AllocateInfo.pSetLayouts			= &m_hDescriptorSetLayout;

			sm_pDevice->AllocateDescriptorSets(&AllocateInfo, &hDescriptorSet);
		}
	}

	return std::make_shared<DescriptorSet>(hDescriptorSet, hDescriptorPool);
}


PipelineLayout::~PipelineLayout() noexcept
{
	sm_pDevice->DestroyPipelineLayout(m_hPipelineLayout);

	sm_pDevice->DestroyDescriptorSetLayout(m_hDescriptorSetLayout);
}


/*************************************************************************
**************************    DescriptorSet    ***************************
*************************************************************************/
DescriptorSet::DescriptorSet(VkDescriptorSet hDescriptorSet, VkDescriptorPool hDescriptorPool)
	: m_hDescriptorSet(hDescriptorSet), m_hDescriptorPool(hDescriptorPool)
{

}


DescriptorSet::~DescriptorSet() noexcept
{
	sm_pDevice->DestroyDescriptorPool(m_hDescriptorPool);
}