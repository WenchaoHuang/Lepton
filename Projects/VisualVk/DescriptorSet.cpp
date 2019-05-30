
#include "DescriptorSet.h"

using namespace Vk;

void DescriptorSetLayout::SetBinding(uint32_t Binding, VkDescriptorType eDescriptorType, uint32_t DescriptorCount, VkShaderStageFlags eStageFlags)
{
	for (size_t i = 0; i < std::vector<VkDescriptorSetLayoutBinding>::size(); i++)
	{
		VkDescriptorSetLayoutBinding & LayoutBinding = std::vector<VkDescriptorSetLayoutBinding>::operator[](i);

		if (LayoutBinding.binding == Binding)
		{
			LayoutBinding.descriptorCount = DescriptorCount;

			LayoutBinding.descriptorType = eDescriptorType;

			LayoutBinding.stageFlags = eStageFlags;

			return;
		}
	}

	VkDescriptorSetLayoutBinding		NewBinding = {};
	NewBinding.binding					= Binding;
	NewBinding.descriptorType			= eDescriptorType;
	NewBinding.descriptorCount			= DescriptorCount;
	NewBinding.stageFlags				= eStageFlags;
	NewBinding.pImmutableSamplers		= nullptr;

	std::vector<VkDescriptorSetLayoutBinding>::push_back(NewBinding);
}