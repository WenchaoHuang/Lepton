/*************************************************************************
*********************    VisualVk_PipelineLayout    **********************
*************************************************************************/
#include "PipelineLayout.h"

using namespace Vk;

/*************************************************************************
**************************    PipelineLayout    **************************
*************************************************************************/
VkResult PipelineLayout::Create(const PipelineLayoutInfo & LayoutInfo)
{
	std::vector<VkDescriptorSetLayoutBinding> LayoutBindings;

	LayoutBindings.reserve(LayoutInfo.m_LayoutBindings.size());

	for (auto layoutBinding : LayoutInfo.m_LayoutBindings)
	{
		VkDescriptorSetLayoutBinding						DescriptorSetLayoutBinding = {};
		DescriptorSetLayoutBinding.binding					= layoutBinding.first;
		DescriptorSetLayoutBinding.descriptorType			= static_cast<VkDescriptorType>(layoutBinding.second.descriptorType);
		DescriptorSetLayoutBinding.descriptorCount			= layoutBinding.second.descriptorCount;
		DescriptorSetLayoutBinding.stageFlags				= layoutBinding.second.stageFlags;
		DescriptorSetLayoutBinding.pImmutableSamplers		= nullptr;

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

	VkResult eResult = Context::GetDevice()->CreateDescriptorSetLayout(&DescriptorSetLayoutCreateInfo, &hDescriptorSetLayout);

	if (eResult == VK_SUCCESS)
	{
		VkPipelineLayoutCreateInfo							PipelineLayoutCreateInfo = {};
		PipelineLayoutCreateInfo.sType						= VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		PipelineLayoutCreateInfo.pNext						= nullptr;
		PipelineLayoutCreateInfo.flags						= 0;
		PipelineLayoutCreateInfo.setLayoutCount				= 1;
		PipelineLayoutCreateInfo.pSetLayouts				= &hDescriptorSetLayout;
		PipelineLayoutCreateInfo.pushConstantRangeCount		= static_cast<uint32_t>(LayoutInfo.m_ConstantRanges.size());
		PipelineLayoutCreateInfo.pPushConstantRanges		= LayoutInfo.m_ConstantRanges.data();

		m_hDescriptorSetLayout.Replace(Context::GetDeviceHandle(), hDescriptorSetLayout);

		eResult = Context::GetDevice()->CreatePipelineLayout(&PipelineLayoutCreateInfo, &hPipelineLayout);

		if (eResult == VK_SUCCESS)
		{
			m_PipelineLayoutInfo = LayoutInfo;

			PipelineLayoutH::Replace(Context::GetDeviceHandle(), hPipelineLayout);

			m_DescriptorPoolSizes.reserve(m_PipelineLayoutInfo.m_LayoutBindings.size());

			for (auto layoutBinding : m_PipelineLayoutInfo.m_LayoutBindings)
			{
				VkDescriptorPoolSize					DescriptorPoolSize = {};
				DescriptorPoolSize.type					= static_cast<VkDescriptorType>(layoutBinding.second.descriptorType);
				DescriptorPoolSize.descriptorCount		= layoutBinding.second.descriptorCount;

				m_DescriptorPoolSizes.push_back(DescriptorPoolSize);
			}

			return eResult;
		}
	}

	m_hDescriptorSetLayout.Invalidate();

	PipelineLayoutH::Invalidate();

	return eResult;
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

		if (Context::GetDevice()->CreateDescriptorPool(&CreateInfo, &hDescriptorPool) == VK_SUCCESS)
		{
			VkDescriptorSetLayout				hDescriptorSetLayout = m_hDescriptorSetLayout;

			VkDescriptorSetAllocateInfo			AllocateInfo = {};
			AllocateInfo.sType					= VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
			AllocateInfo.pNext					= nullptr;
			AllocateInfo.descriptorPool			= hDescriptorPool;
			AllocateInfo.descriptorSetCount		= 1;
			AllocateInfo.pSetLayouts			= &hDescriptorSetLayout;

			Context::GetDevice()->AllocateDescriptorSets(&AllocateInfo, &hDescriptorSet);
		}
	}

	std::shared_ptr<DescriptorSet> spDescriptorSet = std::make_shared<DescriptorSet>(hDescriptorSet, hDescriptorPool);

	spDescriptorSet->m_LayoutBindings = m_PipelineLayoutInfo.m_LayoutBindings;

	return spDescriptorSet;
}


/*************************************************************************
**************************    DescriptorSet    ***************************
*************************************************************************/
DescriptorSet::DescriptorSet(VkDescriptorSet hDescriptorSet, VkDescriptorPool hDescriptorPool)
	: m_hDescriptorSet(hDescriptorSet), m_hDescriptorPool(hDescriptorPool)
{

}


VkBool32 DescriptorSet::WriteBuffer(uint32_t DstBinding, uint32_t DstArrayElement, VkBuffer hBuffer, VkDeviceSize OffsetBytes, VkDeviceSize SizeBytes)
{
	if (m_LayoutBindings.find(DstBinding) == m_LayoutBindings.end())			return VK_FALSE;

	if (DstArrayElement >= m_LayoutBindings[DstBinding].descriptorCount)		return VK_FALSE;

	if (m_hDescriptorSet == VK_NULL_HANDLE)										return VK_FALSE;

	VkDescriptorBufferInfo			BufferInfo = {};
	BufferInfo.buffer				= hBuffer;
	BufferInfo.offset				= OffsetBytes;
	BufferInfo.range				= SizeBytes;

	VkWriteDescriptorSet			WriteInfo = {};
	WriteInfo.sType					= VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	WriteInfo.pNext					= nullptr;
	WriteInfo.dstSet				= m_hDescriptorSet;
	WriteInfo.dstBinding			= DstBinding;
	WriteInfo.dstArrayElement		= DstArrayElement;
	WriteInfo.descriptorCount		= 1;
	WriteInfo.descriptorType		= static_cast<VkDescriptorType>(m_LayoutBindings[DstBinding].descriptorType);
	WriteInfo.pImageInfo			= nullptr;
	WriteInfo.pBufferInfo			= &BufferInfo;
	WriteInfo.pTexelBufferView		= nullptr;

	Context::GetDevice()->UpdateDescriptorSets(1, &WriteInfo, 0, nullptr);

	return VK_TRUE;
}


VkBool32 DescriptorSet::WriteSampler(uint32_t DstBinding, uint32_t DstArrayElement, VkSampler hSampler, VkImageView hImageView, ImageLayout eImageLayout)
{
	if (m_LayoutBindings.find(DstBinding) == m_LayoutBindings.end())			return VK_FALSE;

	if (DstArrayElement >= m_LayoutBindings[DstBinding].descriptorCount)		return VK_FALSE;

	if (m_hDescriptorSet == VK_NULL_HANDLE)										return VK_FALSE;

	VkDescriptorImageInfo			ImageInfo = {};
	ImageInfo.sampler				= hSampler;
	ImageInfo.imageView				= hImageView;
	ImageInfo.imageLayout			= static_cast<VkImageLayout>(eImageLayout);

	VkWriteDescriptorSet			WriteInfo = {};
	WriteInfo.sType					= VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	WriteInfo.pNext					= nullptr;
	WriteInfo.dstSet				= m_hDescriptorSet;
	WriteInfo.dstBinding			= DstBinding;
	WriteInfo.dstArrayElement		= DstArrayElement;
	WriteInfo.descriptorCount		= 1;
	WriteInfo.descriptorType		= static_cast<VkDescriptorType>(m_LayoutBindings[DstBinding].descriptorType);
	WriteInfo.pImageInfo			= &ImageInfo;
	WriteInfo.pBufferInfo			= nullptr;
	WriteInfo.pTexelBufferView		= nullptr;

	Context::GetDevice()->UpdateDescriptorSets(1, &WriteInfo, 0, nullptr);

	return VK_TRUE;
}


DescriptorSet::~DescriptorSet() noexcept
{
	Context::GetDevice()->DestroyDescriptorPool(m_hDescriptorPool);
}