/*************************************************************************
************************    VisualVk_Textures    *************************
*************************************************************************/
#include "Textures.h"

using namespace Vk;

/*************************************************************************
***************************    BaseTexture    ****************************
*************************************************************************/
BaseTexture::BaseTexture() : m_hSampler(VK_NULL_HANDLE), m_eImageLayout(VK_IMAGE_LAYOUT_UNDEFINED)
{

}


void BaseTexture::Release() noexcept
{
	m_eImageLayout = VK_IMAGE_LAYOUT_UNDEFINED;

	sm_pDevice->DestroySampler(m_hSampler);

	m_hSampler = VK_NULL_HANDLE;
}


BaseTexture::~BaseTexture()
{
	this->Release();
}