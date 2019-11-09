/*************************************************************************
***************************    Lava_Images    ****************************
*************************************************************************/

#include "Images.h"
#include "LogicalDevice.h"
#include "PhysicalDevice.h"

using namespace Lava;

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
template<VkImageType eImageType, VkImageViewType eViewType> BaseImage<eImageType, eViewType>::
UniqueHandle::UniqueHandle(VkImage hImage, VkImageView hImageView, DeviceMemory deviceMemory, const ImageParam & Param)
	: m_hImage(hImage), m_hImageView(hImageView), m_DeviceMemory(deviceMemory), m_Parameter(Param)
{

}


template<VkImageType eImageType, VkImageViewType eViewType>
Result BaseImage<eImageType, eViewType>::Create(LogicalDevice * pLogicalDevice,
												Format eFormat,
												VkExtent3D extent,
												uint32_t mipLevels,
												uint32_t arrayLayers,
												SampleCount eSamples,
												Flags<ImageUsage> eUsages,
												Flags<ImageAspect> eAspects,
												VkImageCreateFlags eCreateFlags)
{
	if (!pLogicalDevice->IsReady())			return Result::eErrorInvalidDeviceHandle;
	
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

	VkImage hImage = VK_NULL_HANDLE;

	Result eResult = LAVA_RESULT_CAST(vkCreateImage(pLogicalDevice->GetHandle(), &CreateInfo, nullptr, &hImage));

	if (eResult == Result::eSuccess)
	{
		DeviceMemory deviceMemory;

		VkMemoryRequirements Requirements = {};

		vkGetImageMemoryRequirements(pLogicalDevice->GetHandle(), hImage, &Requirements);

		uint32_t memoryTypeIndex = pLogicalDevice->GetPhysicalDevice()->GetMemoryTypeIndex(Requirements.memoryTypeBits, MemoryProperty::eDeviceLocal);

		eResult = deviceMemory.Allocate(pLogicalDevice->GetHandle(), Requirements.size, memoryTypeIndex);

		if (eResult == Result::eSuccess)
		{
			eResult = LAVA_RESULT_CAST(vkBindImageMemory(pLogicalDevice->GetHandle(), hImage, deviceMemory, 0));

			if (eResult == Result::eSuccess)
			{
				VkImageViewCreateInfo								ViewCreateInfo = {};
				ViewCreateInfo.sType								= VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
				ViewCreateInfo.pNext								= nullptr;
				ViewCreateInfo.flags								= 0;
				ViewCreateInfo.image								= hImage;
				ViewCreateInfo.viewType								= eViewType;
				ViewCreateInfo.format								= static_cast<VkFormat>(eFormat);
				ViewCreateInfo.components.r							= VK_COMPONENT_SWIZZLE_R;
				ViewCreateInfo.components.g							= VK_COMPONENT_SWIZZLE_G;
				ViewCreateInfo.components.b							= VK_COMPONENT_SWIZZLE_B;
				ViewCreateInfo.components.a							= VK_COMPONENT_SWIZZLE_A;
				ViewCreateInfo.subresourceRange.baseArrayLayer		= 0;
				ViewCreateInfo.subresourceRange.baseMipLevel		= 0;
				ViewCreateInfo.subresourceRange.aspectMask			= eAspects;
				ViewCreateInfo.subresourceRange.layerCount			= arrayLayers;
				ViewCreateInfo.subresourceRange.levelCount			= mipLevels;

				VkImageView hImageView = VK_NULL_HANDLE;

				eResult = LAVA_RESULT_CAST(vkCreateImageView(pLogicalDevice->GetHandle(), &ViewCreateInfo, nullptr, &hImageView));

				if (eResult == Result::eSuccess)
				{
					ImageParam					imageParam;
					imageParam.format			= eFormat;
					imageParam.extent			= extent;
					imageParam.mipLevels		= mipLevels;
					imageParam.arrayLayers		= arrayLayers;
					imageParam.samples			= eSamples;
					imageParam.usage			= eUsages;
					imageParam.aspectMask		= eAspects;

					m_spUniqueHandle = std::make_shared<UniqueHandle>(hImage, hImageView, deviceMemory, imageParam);

					return Result::eSuccess;
				}
			}
		}

		vkDestroyImage(pLogicalDevice->GetHandle(), hImage, nullptr);
	}

	return eResult;
}


template<VkImageType eImageType, VkImageViewType eViewType> BaseImage<eImageType, eViewType>::UniqueHandle::~UniqueHandle()
{
	if ((m_hImage != VK_NULL_HANDLE) && (m_hImageView != VK_NULL_HANDLE))
	{
		vkDestroyImageView(m_DeviceMemory.GetDeviceHandle(), m_hImageView, nullptr);

		vkDestroyImage(m_DeviceMemory.GetDeviceHandle(), m_hImage, nullptr);
	}
}