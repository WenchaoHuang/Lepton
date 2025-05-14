/*************************************************************************
**************************    Lepton_Images    ***************************
*************************************************************************/

#include "Images.h"
#include "LogicalDevice.h"

using namespace Lepton;

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
UniqueHandle::UniqueHandle(DeviceLocalMemory deviceMemory, VkImage hImage, VkImageView hImageView, const ImageParam & Param)
	: m_DeviceMemory(deviceMemory), m_hImage(hImage), m_hImageView(hImageView), m_Parameter(Param)
{

}


template<VkImageType eImageType, VkImageViewType eViewType>
Result BaseImage<eImageType, eViewType>::Create(const LogicalDevice * pLogicalDevice,
												vk::Format eFormat, VkExtent3D extent,
												uint32_t mipLevels, uint32_t arrayLayers,
												vk::SampleCountFlagBits eSamples, vk::ImageUsageFlags eUsages,
												vk::ImageAspectFlags eAspects, VkImageCreateFlags eCreateFlags)
{
	if (pLogicalDevice == nullptr)			return Result::eErrorInvalidDeviceHandle;
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
	CreateInfo.usage						= VkFlags(eUsages);
	CreateInfo.sharingMode					= VK_SHARING_MODE_EXCLUSIVE;
	CreateInfo.queueFamilyIndexCount		= 0;
	CreateInfo.pQueueFamilyIndices			= nullptr;
	CreateInfo.initialLayout				= VK_IMAGE_LAYOUT_UNDEFINED;

	VkImage hImage = VK_NULL_HANDLE;

	Result eResult = LAVA_RESULT_CAST(vkCreateImage(pLogicalDevice->Handle(), &CreateInfo, nullptr, &hImage));

	if (eResult == Result::eSuccess)
	{
		DeviceLocalMemory	deviceMemory;

		VkMemoryRequirements Requirements = {};

		vkGetImageMemoryRequirements(pLogicalDevice->Handle(), hImage, &Requirements);

		eResult = deviceMemory.Allocate(pLogicalDevice, Requirements);

		if (eResult == Result::eSuccess)
		{
			eResult = LAVA_RESULT_CAST(vkBindImageMemory(pLogicalDevice->Handle(), hImage, deviceMemory, 0));

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
				ViewCreateInfo.subresourceRange.aspectMask			= (VkFlags)eAspects;
				ViewCreateInfo.subresourceRange.layerCount			= arrayLayers;
				ViewCreateInfo.subresourceRange.levelCount			= mipLevels;

				VkImageView hImageView = VK_NULL_HANDLE;

				eResult = LAVA_RESULT_CAST(vkCreateImageView(pLogicalDevice->Handle(), &ViewCreateInfo, nullptr, &hImageView));

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

					m_spUniqueHandle = std::make_shared<UniqueHandle>(deviceMemory, hImage, hImageView, imageParam);

					return Result::eSuccess;
				}
			}
		}

		vkDestroyImage(pLogicalDevice->Handle(), hImage, nullptr);
	}

	return eResult;
}


template<VkImageType eImageType, VkImageViewType eViewType> BaseImage<eImageType, eViewType>::UniqueHandle::~UniqueHandle() noexcept
{
	if (m_hImage != VK_NULL_HANDLE)
	{
		vkDestroyImageView(m_DeviceMemory.GetDeviceHandle(), m_hImageView, nullptr);

		vkDestroyImage(m_DeviceMemory.GetDeviceHandle(), m_hImage, nullptr);
	}
}