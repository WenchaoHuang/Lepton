#pragma once

#include <map>
#include "Resource.h"

namespace Vk
{


	class DescriptorSetLayout : private std::vector<VkDescriptorSetLayoutBinding>
	{

	public:

		void SetBinding(uint32_t Binding, VkDescriptorType eDescriptorType, uint32_t DescriptorCount, VkShaderStageFlags eStageFlags);
		
	};





}