/*************************************************************************
************************    VisualVk_Textures    *************************
*************************************************************************/

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <stb/stb_image_write.h>
#include <stb/stb_image.h>
#include "Textures.h"

using namespace Vk;

/*************************************************************************
***************************    BaseTexture    ****************************
*************************************************************************/
BaseTexture::BaseTexture() : m_hSampler(VK_NULL_HANDLE), m_eImageLayout(VK_IMAGE_LAYOUT_UNDEFINED)
{

}


std::vector<char> BaseTexture::ReadImage(std::string Path, int & Width, int & Height, int & Channels)
{
	void * pData = stbi_load(Path.c_str(), &Width, &Height, &Channels, 4);

	Channels = 4;

	std::vector<char> Data(Width * Height * Channels);

	memcpy(Data.data(), pData, Data.size());

	stbi_image_free(pData);

	return Data;
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