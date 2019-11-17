/*************************************************************************
***********************    Lava_PipelineLayout    ************************
*************************************************************************/

#include "PipelineLayout.h"

using namespace Lava;

/*************************************************************************
**************************    PipelineLayout    **************************
*************************************************************************/
PipelineLayout::UniqueHandle::UniqueHandle(VkDevice hDevice, VkPipelineLayout hPipelineLayout,
										   const std::vector<DescriptorSetLayout> & DescriptorSetLayouts,
										   const std::vector<PushConstantRange> & PushConstantRanges)
	: m_hDevice(hDevice), m_hPipelineLayout(hPipelineLayout), m_DescriptorSetLayouts(DescriptorSetLayouts), m_PushConstantRanges(PushConstantRanges)
{

}


Result PipelineLayout::Create(VkDevice hDevice, ArrayProxy<const DescriptorSetLayout> pDescriptorSetLayouts, ArrayProxy<const PushConstantRange> pPushConstantRanges)
{
	Result eResult = Result::eErrorInvalidDeviceHandle;

	if (hDevice != VK_NULL_HANDLE)
	{
		std::vector<VkDescriptorSetLayout>	hDescriptorSetLayouts;

		hDescriptorSetLayouts.resize(pDescriptorSetLayouts.size());

		for (uint32_t i = 0; i < pDescriptorSetLayouts.size(); i++)
		{
			if (pDescriptorSetLayouts[i].GetDeviceHandle() != hDevice)		return eResult;
			
			hDescriptorSetLayouts[i] = pDescriptorSetLayouts[i];
		}

		VkPipelineLayoutCreateInfo				CreateInfo = {};
		CreateInfo.sType						= VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		CreateInfo.pNext						= nullptr;
		CreateInfo.flags						= 0;
		CreateInfo.setLayoutCount				= pDescriptorSetLayouts.size();
		CreateInfo.pSetLayouts					= hDescriptorSetLayouts.data();
		CreateInfo.pushConstantRangeCount		= pPushConstantRanges.size();
		CreateInfo.pPushConstantRanges			= reinterpret_cast<const VkPushConstantRange*>(pPushConstantRanges.data());

		VkPipelineLayout hPipelineLayou = VK_NULL_HANDLE;

		eResult = LAVA_RESULT_CAST(vkCreatePipelineLayout(hDevice, &CreateInfo, nullptr, &hPipelineLayou));

		if (eResult == Result::eSuccess)
		{
			std::vector<PushConstantRange>		PushConstantRanges(pPushConstantRanges.size());
			std::vector<DescriptorSetLayout>	DescriptorSetLayouts(pDescriptorSetLayouts.size());

			for (uint32_t i = 0; i < PushConstantRanges.size(); i++)
			{
				PushConstantRanges[i] = pPushConstantRanges[i];
			}

			for (uint32_t i = 0; i < DescriptorSetLayouts.size(); i++)
			{
				DescriptorSetLayouts[i] = pDescriptorSetLayouts[i];
			}

			m_spUniqueHandle = std::make_shared<UniqueHandle>(hDevice, hPipelineLayou, DescriptorSetLayouts, PushConstantRanges);
		}
	}

	return eResult;
}


PipelineLayout::UniqueHandle::~UniqueHandle() noexcept
{
	if (m_hPipelineLayout != VK_NULL_HANDLE)
	{
		vkDestroyPipelineLayout(m_hDevice, m_hPipelineLayout, nullptr);
	}
}