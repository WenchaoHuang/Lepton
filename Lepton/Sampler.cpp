/*************************************************************************
**************************    Lepton_Sampler    **************************
*************************************************************************/

#include "Sampler.h"

using namespace Lepton;

/*************************************************************************
*****************************    Sampler    ******************************
*************************************************************************/
Sampler::UniqueHandle::UniqueHandle(VkDevice hDevice, VkSampler hSampler, const SamplerParam & Param)
	: m_hDevice(hDevice), m_hSampler(hSampler), m_Parameter(Param)
{

}


Result Sampler::Create(VkDevice hDevice, const SamplerParam & Param)
{
	if (hDevice == VK_NULL_HANDLE)			return Result::eErrorInvalidDeviceHandle;

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

	Result eResult = LAVA_RESULT_CAST(vkCreateSampler(hDevice, &CreateInfo, nullptr, &hSampler));

	if (eResult == Result::eSuccess)
	{
		m_spUniqueHandle = std::make_shared<UniqueHandle>(hDevice, hSampler, Param);
	}

	return eResult;
}


Sampler::UniqueHandle::~UniqueHandle() noexcept
{
	if (m_hSampler != VK_NULL_HANDLE)
	{
		vkDestroySampler(m_hDevice, m_hSampler, nullptr);
	}
}