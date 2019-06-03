/*************************************************************************
*************************    VisualVk_Sampler    *************************
*************************************************************************/
#include "Sampler.h"

using namespace Vk;

/*************************************************************************
*****************************    Sampler    ******************************
*************************************************************************/
Sampler::Sampler() : m_hSampler(VK_NULL_HANDLE)
{

}


VkResult Sampler::Create(const SamplerInfo & CreateInfo)
{
	VkSampler hSampler = VK_NULL_HANDLE;

	VkResult eResult = sm_pDevice->CreateSampler(reinterpret_cast<const VkSamplerCreateInfo*>(&CreateInfo), &hSampler);

	if (eResult == VK_SUCCESS)
	{
		this->Release();

		m_hSampler = hSampler;

		m_CreateInfo = CreateInfo;
	}

	return eResult;
}


void Sampler::Release() noexcept
{
	if (m_hSampler != VK_NULL_HANDLE)
	{
		sm_pDevice->DestroySampler(m_hSampler);

		m_CreateInfo = SamplerInfo();

		m_hSampler = VK_NULL_HANDLE;
	}
}


Sampler::~Sampler()
{
	this->Release();
}