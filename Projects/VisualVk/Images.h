/*************************************************************************
*************************    VisualVk_Images    **************************
*************************************************************************/
#pragma once

#include "DeviceMemory.h"

namespace Vk
{
	/*********************************************************************
	****************************    Image    *****************************
	*********************************************************************/

	/**
	 *	@brief	Template for Vulkan image object.
	 */
	template<VkImageType eImageType, VkImageViewType eViewType>

	class VKAPI Image : private Resource
	{

	protected:

		//!	@brief	Create image object.
		Image();

		//!	@brief	Destroy image object.
		~Image();

	public:

		//!	@brief	Converts to handle.
		operator VkImage() { return m_hImage; }

		//!	@brief	Return image format.
		VkFormat GetFormat() const { return m_eFormat; }

		//!	@brief	Return image extent.
		VkExtent3D GetExtent() const { return m_Extent3D; }

		//!	@brief	Return image view.
		VkImageView GetView() const { return m_hImageView; }

		//!	@brief	Return number of mip-levels.
		uint32_t GetMipLevels() const { return m_MipLevels; }

		//!	@brief	Return count of layers.
		uint32_t GetArrayLayers() const { return m_ArrayLayers; }

		//!	@brief	Whether image handle is valid.
		VkBool32 IsValid() const { return m_hImage != VK_NULL_HANDLE; }

		//!	@brief	Return count of samples.
		VkSampleCountFlagBits GetSampleCount() const { return m_eSampleCount; }

		//!	@brief	Release image.
		void Release();

	protected:

		//!	@brief	Create new image object.
		VkResult Create(VkFormat eFormat, VkExtent3D Extent3D,uint32_t MipLevels, uint32_t ArrayLayers,
						VkSampleCountFlagBits eSamples, VkImageUsageFlags eUsage, VkImageCreateFlags eCreateFlags = 0);

		//!	@brief	Create new image view object.
		VkResult CreateView(VkImageAspectFlags eAspectMask);

	private:

		VkImage						m_hImage;

		VkFormat					m_eFormat;

		VkExtent3D					m_Extent3D;

		VkImageView					m_hImageView;

		VkSampleCountFlagBits		m_eSampleCount;

		DeviceMemory				m_DeviceMemory;

		uint32_t					m_ArrayLayers;

		uint32_t					m_MipLevels;
	};

	/*********************************************************************
	***************************    Image1D    ****************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan image 1D object.
	 */
	class VKAPI Image1D : public Image<VK_IMAGE_TYPE_1D, VK_IMAGE_VIEW_TYPE_1D>
	{

	public:

		//!	@brief	Create new image 1D object.
		VkResult Create(VkFormat eFormat, uint32_t Width, uint32_t MipLevels,
					   VkImageUsageFlags eUsage, VkImageAspectFlags eAspectMask)
		{
			VkResult eResult = Image::Create(eFormat, { Width, 1, 1 }, MipLevels, 1, VK_SAMPLE_COUNT_1_BIT, eUsage);

			if (eResult == VK_SUCCESS)
			{
				eResult = Image::CreateView(eAspectMask);
			}

			return eResult;
		}
	};

	/*********************************************************************
	*************************    Image1DArray    *************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan image 1D array object.
	 */
	class VKAPI Image1DArray : public Image<VK_IMAGE_TYPE_1D, VK_IMAGE_VIEW_TYPE_1D_ARRAY>
	{

	public:

		//!	@brief	Create new image 1D array object.
		VkResult Create(VkFormat eFormat, uint32_t Width, uint32_t MipLevels,
					   uint32_t ArrayLayers, VkImageUsageFlags eUsage, VkImageAspectFlags eAspectMask)
		{
			VkResult eResult = Image::Create(eFormat, { Width, 1, 1 }, MipLevels, ArrayLayers, VK_SAMPLE_COUNT_1_BIT, eUsage);

			if (eResult == VK_SUCCESS)
			{
				eResult = Image::CreateView(eAspectMask);
			}

			return eResult;
		}
	};

	/*********************************************************************
	***************************    Image2D    ****************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan image 2D object.
	 */
	class VKAPI Image2D : public Image<VK_IMAGE_TYPE_2D, VK_IMAGE_VIEW_TYPE_2D>
	{

	public:

		//!	@brief	Create new image 2D object.
		VkResult Create(VkFormat eFormat, uint32_t Width, uint32_t Height, uint32_t MipLevels,
					   VkSampleCountFlagBits eSamples, VkImageUsageFlags eUsage, VkImageAspectFlags eAspectMask)
		{
			VkResult eResult = Image::Create(eFormat, { Width, Height, 1 }, MipLevels, 1, eSamples, eUsage);

			if (eResult == VK_SUCCESS)
			{
				eResult = Image::CreateView(eAspectMask);
			}

			return eResult;
		}

		//!	@brief	Create a new color attachment object.
		VkResult CreateColorAttachment(VkFormat eFormat, uint32_t Width, uint32_t Height,
									   uint32_t MipLevels, VkSampleCountFlagBits eSamples = VK_SAMPLE_COUNT_1_BIT)
		{
			VkResult eResult = Image::Create(eFormat, { Width, Height, 1 }, MipLevels, 1, eSamples, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT);

			if (eResult == VK_SUCCESS)
			{
				eResult = Image::CreateView(VK_IMAGE_ASPECT_COLOR_BIT);
			}

			return eResult;
		}

		//!	@brief	Create a new depth attachment object.
		VkResult CreateDepthAttachment(VkFormat eFormat, uint32_t Width, uint32_t Height,
									   uint32_t MipLevels, VkSampleCountFlagBits eSamples = VK_SAMPLE_COUNT_1_BIT)
		{
			VkResult eResult = Image::Create(eFormat, { Width, Height, 1 }, MipLevels, 1, eSamples, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT);

			if (eResult == VK_SUCCESS)
			{
				eResult = Image::CreateView(VK_IMAGE_ASPECT_DEPTH_BIT);
			}

			return eResult;
		}
	};

	/*********************************************************************
	*************************    Image2DArray    *************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan image 2D object.
	 */
	class VKAPI Image2DArray : public Image<VK_IMAGE_TYPE_2D, VK_IMAGE_VIEW_TYPE_2D_ARRAY>
	{

	public:

		//!	@brief	Create new image 2D object.
		VkResult Create(VkFormat eFormat, uint32_t Width, uint32_t Height, uint32_t MipLevels, uint32_t ArrayLayers,
					   VkSampleCountFlagBits eSamples, VkImageUsageFlags eUsage, VkImageAspectFlags eAspectMask)
		{
			VkResult eResult = Image::Create(eFormat, { Width, Height, 1 }, MipLevels, ArrayLayers, eSamples, eUsage);

			if (eResult == VK_SUCCESS)
			{
				eResult = Image::CreateView(eAspectMask);
			}

			return eResult;
		}
	};

	/*********************************************************************
	**************************    ImageCube    ***************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan image cube object.
	 */
	class VKAPI ImageCube : public Image<VK_IMAGE_TYPE_2D, VK_IMAGE_VIEW_TYPE_CUBE>
	{

	public:

		//!	@brief	Create new image cube object.
		VkResult Create(VkFormat eFormat, uint32_t Width, uint32_t Height,
					   uint32_t MipLevels, VkImageUsageFlags eUsage, VkImageAspectFlags eAspectMask)
		{
			VkResult eResult = Image::Create(eFormat, { Width, Height, 1 }, MipLevels, 6,
											 VK_SAMPLE_COUNT_1_BIT, eUsage, VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT);
			if (eResult == VK_SUCCESS)
			{
				eResult = Image::CreateView(eAspectMask);
			}

			return eResult;
		}
	};

	/*********************************************************************
	***************************    Image3D    ****************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan image 3D object.
	 */
	class VKAPI Image3D : public Image<VK_IMAGE_TYPE_3D, VK_IMAGE_VIEW_TYPE_3D>
	{

	public:

		//!	@brief	Create new image 3D object.
		VkResult Create(VkFormat eFormat, uint32_t Width, uint32_t Height, uint32_t Depth,
					   uint32_t MipLevels, VkImageUsageFlags eUsage, VkImageAspectFlags eAspectMask)
		{
			VkResult eResult = Image::Create(eFormat, { Width, Height, Depth }, MipLevels, 1, VK_SAMPLE_COUNT_1_BIT, eUsage);

			if (eResult == VK_SUCCESS)
			{
				eResult = Image::CreateView(eAspectMask);
			}

			return eResult;
		}
	};
}