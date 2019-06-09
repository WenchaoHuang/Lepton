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
	LayoutBinding					NewBinding = {};
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
	DescriptorSetLayoutCreateInfo.bindingCount		= static_cast<uint32_t>(LayoutBindings.size());
	DescriptorSetLayoutCreateInfo.pBindings			= LayoutBindings.data();

	VkPipelineLayout hPipelineLayout = VK_NULL_HANDLE;

	VkDescriptorSetLayout hDescriptorSetLayout = VK_NULL_HANDLE;

	if (sm_pLogicalDevice->CreateDescriptorSetLayout(&DescriptorSetLayoutCreateInfo, &hDescriptorSetLayout) == VK_SUCCESS)
	{
		VkPipelineLayoutCreateInfo							PipelineLayoutCreateInfo = {};
		PipelineLayoutCreateInfo.sType						= VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		PipelineLayoutCreateInfo.pNext						= nullptr;
		PipelineLayoutCreateInfo.flags						= 0;
		PipelineLayoutCreateInfo.setLayoutCount				= 1;
		PipelineLayoutCreateInfo.pSetLayouts				= &hDescriptorSetLayout;
		PipelineLayoutCreateInfo.pushConstantRangeCount		= static_cast<uint32_t>(LayoutInfo.constantRanges.size());
		PipelineLayoutCreateInfo.pPushConstantRanges		= LayoutInfo.constantRanges.data();

		sm_pLogicalDevice->CreatePipelineLayout(&PipelineLayoutCreateInfo, &hPipelineLayout);
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
		CreateInfo.poolSizeCount		= static_cast<uint32_t>(m_DescriptorPoolSizes.size());
		CreateInfo.pPoolSizes			= m_DescriptorPoolSizes.data();

		if (m_pDevice->CreateDescriptorPool(&CreateInfo, &hDescriptorPool) == VK_SUCCESS)
		{
			VkDescriptorSetAllocateInfo			AllocateInfo = {};
			AllocateInfo.sType					= VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
			AllocateInfo.pNext					= nullptr;
			AllocateInfo.descriptorPool			= hDescriptorPool;
			AllocateInfo.descriptorSetCount		= 1;
			AllocateInfo.pSetLayouts			= &m_hDescriptorSetLayout;

			m_pDevice->AllocateDescriptorSets(&AllocateInfo, &hDescriptorSet);
		}
	}

	std::shared_ptr<DescriptorSet> spDescriptorSet = std::make_shared<DescriptorSet>(hDescriptorSet, hDescriptorPool);

	spDescriptorSet->m_LayoutBindings = m_PipelineLayoutInfo.layoutBindings;

	return spDescriptorSet;
}


PipelineLayout::~PipelineLayout() noexcept
{
	m_pDevice->DestroyPipelineLayout(m_hPipelineLayout);

	m_pDevice->DestroyDescriptorSetLayout(m_hDescriptorSetLayout);
}


/*************************************************************************
**************************    DescriptorSet    ***************************
*************************************************************************/
DescriptorSet::DescriptorSet(VkDescriptorSet hDescriptorSet, VkDescriptorPool hDescriptorPool)
	: m_hDescriptorSet(hDescriptorSet), m_hDescriptorPool(hDescriptorPool)
{

}


VkBool32 DescriptorSet::Write(uint32_t DstBinding, uint32_t EstArrayElement, const VkDescriptorImageInfo & ImageInfo)
{
	if (m_LayoutBindings.find(DstBinding) == m_LayoutBindings.end())			return VK_FALSE;

	if (EstArrayElement >= m_LayoutBindings[DstBinding].descriptorCount)		return VK_FALSE;

	if (m_hDescriptorSet == VK_NULL_HANDLE)										return VK_FALSE;

	VkWriteDescriptorSet			WriteInfo = {};
	WriteInfo.sType					= VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	WriteInfo.pNext					= nullptr;
	WriteInfo.dstSet				= m_hDescriptorSet;
	WriteInfo.dstBinding			= DstBinding;
	WriteInfo.dstArrayElement		= EstArrayElement;
	WriteInfo.descriptorCount		= 1;
	WriteInfo.descriptorType		= m_LayoutBindings[DstBinding].descriptorType;
	WriteInfo.pImageInfo			= &ImageInfo;
	WriteInfo.pBufferInfo			= nullptr;
	WriteInfo.pTexelBufferView		= nullptr;

	m_pDevice->UpdateDescriptorSets(1, &WriteInfo, 0, nullptr);

	return VK_TRUE;
}


VkBool32 DescriptorSet::Write(uint32_t DstBinding, uint32_t EstArrayElement, const VkDescriptorBufferInfo & BufferInfo)
{
	if (m_LayoutBindings.find(DstBinding) == m_LayoutBindings.end())			return VK_FALSE;

	if (EstArrayElement >= m_LayoutBindings[DstBinding].descriptorCount)		return VK_FALSE;

	if (m_hDescriptorSet == VK_NULL_HANDLE)										return VK_FALSE;

	VkWriteDescriptorSet			WriteInfo = {};
	WriteInfo.sType					= VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	WriteInfo.pNext					= nullptr;
	WriteInfo.dstSet				= m_hDescriptorSet;
	WriteInfo.dstBinding			= DstBinding;
	WriteInfo.dstArrayElement		= EstArrayElement;
	WriteInfo.descriptorCount		= 1;
	WriteInfo.descriptorType		= m_LayoutBindings[DstBinding].descriptorType;
	WriteInfo.pImageInfo			= nullptr;
	WriteInfo.pBufferInfo			= &BufferInfo;
	WriteInfo.pTexelBufferView		= nullptr;

	m_pDevice->UpdateDescriptorSets(1, &WriteInfo, 0, nullptr);

	return VK_TRUE;
}


DescriptorSet::~DescriptorSet() noexcept
{
	m_pDevice->DestroyDescriptorPool(m_hDescriptorPool);
}