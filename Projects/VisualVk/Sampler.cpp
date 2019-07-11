/*************************************************************************
*************************    VisualVk_Sampler    *************************
*************************************************************************/
#include "Sampler.h"

using namespace Vk;

/*************************************************************************
*****************************    Sampler    ******************************
*************************************************************************/
Sampler::Sampler()
{

}


VkResult Sampler::Create(const SamplerInfo & CreateInfo)
{
	VkSamplerCreateInfo								SamplerCreateInfo = {};
	SamplerCreateInfo.sType							= VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
	SamplerCreateInfo.pNext							= nullptr;
	SamplerCreateInfo.flags							= 0;
	SamplerCreateInfo.magFilter						= static_cast<VkFilter>(CreateInfo.magFilter);
	SamplerCreateInfo.minFilter						= static_cast<VkFilter>(CreateInfo.minFilter);
	SamplerCreateInfo.mipmapMode					= static_cast<VkSamplerMipmapMode>(CreateInfo.mipmapMode);
	SamplerCreateInfo.addressModeU					= static_cast<VkSamplerAddressMode>(CreateInfo.addressModeU);
	SamplerCreateInfo.addressModeV					= static_cast<VkSamplerAddressMode>(CreateInfo.addressModeV);
	SamplerCreateInfo.addressModeW					= static_cast<VkSamplerAddressMode>(CreateInfo.addressModeW);
	SamplerCreateInfo.mipLodBias					= CreateInfo.mipLodBias;
	SamplerCreateInfo.anisotropyEnable				= CreateInfo.anisotropyEnable;
	SamplerCreateInfo.maxAnisotropy					= CreateInfo.maxAnisotropy;
	SamplerCreateInfo.compareEnable					= CreateInfo.compareEnable;
	SamplerCreateInfo.compareOp						= static_cast<VkCompareOp>(CreateInfo.compareOp);
	SamplerCreateInfo.minLod						= CreateInfo.minLod;
	SamplerCreateInfo.maxLod						= CreateInfo.maxLod;
	SamplerCreateInfo.borderColor					= static_cast<VkBorderColor>(CreateInfo.borderColor);
	SamplerCreateInfo.unnormalizedCoordinates		= CreateInfo.unnormalizedCoordinates;

	VkSampler hSampler = VK_NULL_HANDLE;

	VkResult eResult = m_pDevice->CreateSampler(&SamplerCreateInfo, &hSampler);

	if (eResult == VK_SUCCESS)
	{
		static_cast<SamplerH&>(*this) = SamplerH(hSampler, *m_pDevice);

		m_CreateInfo = CreateInfo;
	}

	return eResult;
}


Sampler::~Sampler()
{
	
}