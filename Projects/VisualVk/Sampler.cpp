/*************************************************************************
*************************    VisualVk_Sampler    *************************
*************************************************************************/
#include "Sampler.h"

using namespace Vk;

/*************************************************************************
*****************************    Sampler    ******************************
*************************************************************************/
Result Sampler::Create(const SamplerParam & Param)
{
	VkSamplerCreateInfo						CreateInfo = {};
	CreateInfo.sType						= VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
	CreateInfo.pNext						= nullptr;
	CreateInfo.flags						= 0;
	CreateInfo.magFilter					= static_cast<VkFilter>(Param.magFilter);
	CreateInfo.minFilter					= static_cast<VkFilter>(Param.minFilter);
	CreateInfo.mipmapMode					= static_cast<VkSamplerMipmapMode>(Param.mipmapMode);
	CreateInfo.addressModeU					= static_cast<VkSamplerAddressMode>(Param.addressModeU);
	CreateInfo.addressModeV					= static_cast<VkSamplerAddressMode>(Param.addressModeV);
	CreateInfo.addressModeW					= static_cast<VkSamplerAddressMode>(Param.addressModeW);
	CreateInfo.mipLodBias					= Param.mipLodBias;
	CreateInfo.anisotropyEnable				= Param.anisotropyEnable;
	CreateInfo.maxAnisotropy				= Param.maxAnisotropy;
	CreateInfo.compareEnable				= Param.compareEnable;
	CreateInfo.compareOp					= static_cast<VkCompareOp>(Param.compareOp);
	CreateInfo.minLod						= Param.minLod;
	CreateInfo.maxLod						= Param.maxLod;
	CreateInfo.borderColor					= static_cast<VkBorderColor>(Param.borderColor);
	CreateInfo.unnormalizedCoordinates		= Param.unnormalizedCoordinates;

	VkSampler hSampler = VK_NULL_HANDLE;

	VkResult eResult = Context::GetDevice()->CreateSampler(&CreateInfo, &hSampler);

	if (eResult == VK_SUCCESS)
	{
		SamplerH::Replace(Context::GetDeviceHandle(), hSampler);

		m_Param = Param;
	}

	return static_cast<Result>(eResult);
}


Result Sampler::SetMagFilter(Filter eMagFilter)
{
	SamplerParam Param = m_Param;

	Param.magFilter = eMagFilter;

	return this->Create(Param);
}


Result Sampler::SetMinFilter(Filter eMinFilter)
{
	SamplerParam Param = m_Param;

	Param.minFilter = eMinFilter;

	return this->Create(Param);
}