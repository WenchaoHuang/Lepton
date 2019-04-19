/*************************************************************************
*************************    VisualVk_Images    **************************
*************************************************************************/
#include "Images.h"

using namespace Vk;

template class BaseImage<VK_IMAGE_TYPE_1D, VK_IMAGE_VIEW_TYPE_1D>;
template class BaseImage<VK_IMAGE_TYPE_2D, VK_IMAGE_VIEW_TYPE_2D>;
template class BaseImage<VK_IMAGE_TYPE_3D, VK_IMAGE_VIEW_TYPE_3D>;
template class BaseImage<VK_IMAGE_TYPE_2D, VK_IMAGE_VIEW_TYPE_CUBE>;
template class BaseImage<VK_IMAGE_TYPE_1D, VK_IMAGE_VIEW_TYPE_1D_ARRAY>;
template class BaseImage<VK_IMAGE_TYPE_2D, VK_IMAGE_VIEW_TYPE_2D_ARRAY>;
template class BaseImage<VK_IMAGE_TYPE_2D, VK_IMAGE_VIEW_TYPE_CUBE_ARRAY>;

/*************************************************************************
****************************    BaseImage    *****************************
*************************************************************************/
template<VkImageType eImageType, VkImageViewType eViewType> BaseImage<eImageType, eViewType>::BaseImage()
	: m_hImage(VK_NULL_HANDLE), m_hImageView(VK_NULL_HANDLE), m_eFormat(VK_FORMAT_UNDEFINED), m_eSampleCount(VK_SAMPLE_COUNT_1_BIT)
{
	m_MipLevels = 0;	m_ArrayLayers = 0;		m_Extent3D = { 0, 0, 0 };
}


template<VkImageType eImageType, VkImageViewType eViewType>
VkResult BaseImage<eImageType, eViewType>::Create(VkFormat eFormat,
												  VkExtent3D Extent,
												  uint32_t MipLevels,
												  uint32_t ArrayLayers,
												  VkSampleCountFlagBits eSamples,
												  VkImageUsageFlags eUsage,
												  VkImageCreateFlags eCreateFlags)
{
	VkImageCreateInfo					CreateInfo = {};
	CreateInfo.sType					= VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	CreateInfo.pNext					= nullptr;
	CreateInfo.flags					= eCreateFlags;
	CreateInfo.imageType				= eImageType;
	CreateInfo.format					= eFormat;
	CreateInfo.extent					= Extent;
	CreateInfo.mipLevels				= MipLevels;
	CreateInfo.arrayLayers				= ArrayLayers;
	CreateInfo.samples					= eSamples;
	CreateInfo.tiling					= VK_IMAGE_TILING_OPTIMAL;
	CreateInfo.usage					= eUsage;
	CreateInfo.sharingMode				= VK_SHARING_MODE_EXCLUSIVE;
	CreateInfo.queueFamilyIndexCount	= 0;
	CreateInfo.pQueueFamilyIndices		= nullptr;
	CreateInfo.initialLayout			= VK_IMAGE_LAYOUT_UNDEFINED;

	VkImage hNewImage = VK_NULL_HANDLE;

	VkResult eResult = sm_pDevice->CreateImage(&CreateInfo, &hNewImage);

	if (eResult == VK_SUCCESS)
	{
		VkMemoryRequirements Requirements;

		sm_pDevice->GetImageMemoryRequirements(hNewImage, &Requirements);

		eResult = m_DeviceMemory.Allocate(Requirements, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

		if (eResult != VK_SUCCESS)
		{
			sm_pDevice->DestroyImage(hNewImage);
		}
		else
		{
			sm_pDevice->BindImageMemory(hNewImage, m_DeviceMemory, 0);

			sm_pDevice->DestroyImageView(m_hImageView);

			sm_pDevice->DestroyImage(m_hImage);

			m_hImageView = VK_NULL_HANDLE;

			m_ArrayLayers = ArrayLayers;

			m_eSampleCount = eSamples;

			m_MipLevels = MipLevels;

			m_hImage = hNewImage;

			m_eFormat = eFormat;

			m_Extent3D = Extent;
		}
	}

	return eResult;
}


template<VkImageType eImageType, VkImageViewType eViewType>
VkResult BaseImage<eImageType, eViewType>::CreateView(VkImageAspectFlags eAspectMask)
{
	if (m_hImage == VK_NULL_HANDLE)				return VK_INCOMPLETE;

	VkImageViewCreateInfo						CreateInfo = {};
	CreateInfo.sType							= VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	CreateInfo.pNext							= nullptr;
	CreateInfo.flags							= 0;
	CreateInfo.image							= m_hImage;
	CreateInfo.viewType							= eViewType;
	CreateInfo.format							= m_eFormat;
	CreateInfo.components.r						= VK_COMPONENT_SWIZZLE_R;
	CreateInfo.components.g						= VK_COMPONENT_SWIZZLE_G;
	CreateInfo.components.b						= VK_COMPONENT_SWIZZLE_B;
	CreateInfo.components.a						= VK_COMPONENT_SWIZZLE_A;
	CreateInfo.subresourceRange.baseArrayLayer	= 0;
	CreateInfo.subresourceRange.baseMipLevel	= 0;
	CreateInfo.subresourceRange.aspectMask		= eAspectMask;
	CreateInfo.subresourceRange.layerCount		= m_ArrayLayers;
	CreateInfo.subresourceRange.levelCount		= m_MipLevels;

	VkImageView hImageView = VK_NULL_HANDLE;

	VkResult eResult = sm_pDevice->CreateImageView(&CreateInfo, &hImageView);

	if (eResult == VK_SUCCESS)
	{
		sm_pDevice->DestroyImageView(m_hImageView);

		m_hImageView = hImageView;
	}

	return eResult;
}


template<VkImageType eImageType, VkImageViewType eViewType> void BaseImage<eImageType, eViewType>::Release() noexcept
{
	m_DeviceMemory.Free();

	sm_pDevice->DestroyImage(m_hImage);

	sm_pDevice->DestroyImageView(m_hImageView);

	m_eSampleCount = VK_SAMPLE_COUNT_1_BIT;

	m_eFormat = VK_FORMAT_UNDEFINED;

	m_Extent3D = { 0, 0, 0 };

	m_ArrayLayers = 0;

	m_MipLevels = 0;
}


template<VkImageType eImageType, VkImageViewType eViewType> BaseImage<eImageType, eViewType>::~BaseImage()
{
	this->Release();
}