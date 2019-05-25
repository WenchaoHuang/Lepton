/*************************************************************************
************************    VisualVk_Textures    *************************
*************************************************************************/
#pragma once

#include "Images.h"

namespace Vk
{
	/*********************************************************************
	*************************    BaseTexture    **************************
	*********************************************************************/

	class BaseTexture : private Resource
	{

	public:

		BaseTexture();

		~BaseTexture();

	public:

		void Release() noexcept;


	protected:


		VkResult CreateSampler()
		{
			VkSamplerCreateInfo	CreateInfo = {};
			CreateInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
			CreateInfo.pNext = nullptr;
			CreateInfo.flags = 0;
			CreateInfo.magFilter = VK_FILTER_LINEAR;
			CreateInfo.minFilter = VK_FILTER_LINEAR;
			CreateInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_NEAREST;
			CreateInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
			CreateInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
			CreateInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
			CreateInfo.mipLodBias = 0.0f;
			CreateInfo.anisotropyEnable = VK_FALSE;
			CreateInfo.maxAnisotropy = 1.0f;
			CreateInfo.compareEnable = VK_FALSE;
			CreateInfo.compareOp = VK_COMPARE_OP_ALWAYS;
			CreateInfo.minLod = 0.0f;
			CreateInfo.maxLod = 0.0f;
			CreateInfo.borderColor = VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK;
			CreateInfo.unnormalizedCoordinates = VK_FALSE;

			VkSampler hSampler = VK_NULL_HANDLE;

			VkResult eResult = sm_pDevice->CreateSampler(&CreateInfo, &hSampler);

			if (eResult == VK_SUCCESS)
			{
				sm_pDevice->DestroySampler(m_hSampler);

				m_hSampler = hSampler;
			}

			return eResult;
		}


	protected:

		VkSampler			m_hSampler;

		VkImageLayout		m_eImageLayout;
	};

	/*********************************************************************
	**************************    Texture1D    ***************************
	*********************************************************************/

	class Texture1D : public BaseTexture
	{

	public:


	private:

		Image1D			m_Image1D;
	};

	/*********************************************************************
	************************    Texture1DArray    ************************
	*********************************************************************/

	class Texture1DArray : public BaseTexture
	{

	public:


	private:

		Image1DArray		m_Image1DArray;
	};

	/*********************************************************************
	**************************    Texture2D    ***************************
	*********************************************************************/

	class Texture2D : public BaseTexture
	{

	public:


	private:

		Image2D			m_Image2D;
	};

	/*********************************************************************
	************************    Texture2DArray    ************************
	*********************************************************************/

	class Texture2DArray : public BaseTexture
	{

	public:


	private:

		Image2DArray		m_Image2DArray;
	};

	/*********************************************************************
	*************************    TextureCube    **************************
	*********************************************************************/

	class TextureCube : public BaseTexture
	{

	public:


	private:

		ImageCube			m_ImageCube;
	};

	/*********************************************************************
	**************************    Texture3D    ***************************
	*********************************************************************/

	class Texture3D : public BaseTexture
	{

	public:

	private:

		Image3D			m_Image3D;
	};
}