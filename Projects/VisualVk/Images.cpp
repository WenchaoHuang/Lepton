/*************************************************************************
*************************    VisualVk_Images    **************************
*************************************************************************/

#include "Images.h"
#include "LogicalDevice.h"
#include "PhysicalDevice.h"

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
	:	m_hDevice(VK_NULL_HANDLE), m_hImage(VK_NULL_HANDLE), m_hImageView(VK_NULL_HANDLE), m_eFormat(Format::eUndefined),
		m_eSamples(SampleCount::x1), m_MipLevels(0), m_ArrayLayers(0)
{
	m_Extent = { 0, 0, 0 };
}


template<VkImageType eImageType, VkImageViewType eViewType>
Result BaseImage<eImageType, eViewType>::Create(LogicalDevice * pLogicalDevice,
												Format eFormat,
												VkExtent3D extent,
												uint32_t mipLevels,
												uint32_t arrayLayers,
												SampleCount eSamples,
												Flags<ImageUsage> eUsages,
												VkImageCreateFlags eCreateFlags)
{
	if (!pLogicalDevice->IsReady())			return Result::eErrorInvalidExternalHandle;
	
	VkImageCreateInfo						CreateInfo = {};
	CreateInfo.sType						= VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	CreateInfo.pNext						= nullptr;
	CreateInfo.flags						= static_cast<VkImageCreateFlags>(eCreateFlags);
	CreateInfo.imageType					= eImageType;
	CreateInfo.format						= static_cast<VkFormat>(eFormat);
	CreateInfo.extent						= extent;
	CreateInfo.mipLevels					= mipLevels;
	CreateInfo.arrayLayers					= arrayLayers;
	CreateInfo.samples						= static_cast<VkSampleCountFlagBits>(eSamples);
	CreateInfo.tiling						= VK_IMAGE_TILING_OPTIMAL;
	CreateInfo.usage						= eUsages;
	CreateInfo.sharingMode					= VK_SHARING_MODE_EXCLUSIVE;
	CreateInfo.queueFamilyIndexCount		= 0;
	CreateInfo.pQueueFamilyIndices			= nullptr;
	CreateInfo.initialLayout				= VK_IMAGE_LAYOUT_UNDEFINED;

	VkImage hNewImage = VK_NULL_HANDLE;

	Result eResult = VK_RESULT_CAST(vkCreateImage(pLogicalDevice->GetHandle(), &CreateInfo, nullptr, &hNewImage));

	if (eResult == Result::eSuccess)
	{
		VkMemoryRequirements Requirements = {};

		vkGetImageMemoryRequirements(pLogicalDevice->GetHandle(), hNewImage, &Requirements);

		uint32_t memoryTypeIndex = pLogicalDevice->GetPhysicalDevice()->GetMemoryTypeIndex(Requirements.memoryTypeBits, MemoryProperty::eDeviceLocal);

		eResult = m_DeviceMemory.Allocate(pLogicalDevice->GetHandle(), Requirements.size, memoryTypeIndex);

		if (eResult != Result::eSuccess)
		{
			vkDestroyImage(pLogicalDevice->GetHandle(), hNewImage, nullptr);
		}
		else
		{
			this->Destroy();

			vkBindImageMemory(pLogicalDevice->GetHandle(), hNewImage, m_DeviceMemory, 0);

			m_hDevice = pLogicalDevice->GetHandle();

			m_ArrayLayers = arrayLayers;

			m_MipLevels = mipLevels;

			m_eSamples = eSamples;

			m_hImage = hNewImage;

			m_eFormat = eFormat;

			m_Extent = extent;
		}
	}

	return eResult;
}


template<VkImageType eImageType, VkImageViewType eViewType> Result BaseImage<eImageType, eViewType>::CreateView(Flags<ImageAspect> eAspects)
{
	if (m_hImage == VK_NULL_HANDLE)					return Result::eErrorInvalidExternalHandle;

	VkImageViewCreateInfo							CreateInfo = {};
	CreateInfo.sType								= VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	CreateInfo.pNext								= nullptr;
	CreateInfo.flags								= 0;
	CreateInfo.image								= m_hImage;
	CreateInfo.viewType								= eViewType;
	CreateInfo.format								= static_cast<VkFormat>(m_eFormat);
	CreateInfo.components.r							= VK_COMPONENT_SWIZZLE_R;
	CreateInfo.components.g							= VK_COMPONENT_SWIZZLE_G;
	CreateInfo.components.b							= VK_COMPONENT_SWIZZLE_B;
	CreateInfo.components.a							= VK_COMPONENT_SWIZZLE_A;
	CreateInfo.subresourceRange.baseArrayLayer		= 0;
	CreateInfo.subresourceRange.baseMipLevel		= 0;
	CreateInfo.subresourceRange.aspectMask			= eAspects;
	CreateInfo.subresourceRange.layerCount			= m_ArrayLayers;
	CreateInfo.subresourceRange.levelCount			= m_MipLevels;

	VkImageView hImageView = VK_NULL_HANDLE;

	VkResult eResult = vkCreateImageView(m_hDevice, &CreateInfo, nullptr, &hImageView);

	if (eResult == VK_SUCCESS)
	{
		vkDestroyImageView(m_hDevice, m_hImageView, nullptr);

		m_hImageView = hImageView;
	}

	return VK_RESULT_CAST(eResult);
}


template<VkImageType eImageType, VkImageViewType eViewType> void BaseImage<eImageType, eViewType>::Destroy()
{
	if (m_hImage != VK_NULL_HANDLE)
	{
		m_DeviceMemory.Free();

		vkDestroyImage(m_hDevice, m_hImage, nullptr);

		vkDestroyImageView(m_hDevice, m_hImageView, nullptr);

		m_eFormat = Format::eUndefined;

		m_hImageView = VK_NULL_HANDLE;

		m_eSamples = SampleCount::x1;

		m_hDevice = VK_NULL_HANDLE;

		m_hImage = VK_NULL_HANDLE;

		m_Extent = { 0, 0, 0 };

		m_ArrayLayers = 0;

		m_MipLevels = 0;
	}
}


template<VkImageType eImageType, VkImageViewType eViewType> BaseImage<eImageType, eViewType>::~BaseImage()
{
	this->Destroy();
}