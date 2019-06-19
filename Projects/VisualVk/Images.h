/*************************************************************************
*************************    VisualVk_Images    **************************
*************************************************************************/
#pragma once

#include "DeviceMemory.h"

namespace Vk
{
	/*********************************************************************
	**************************    BaseImage    ***************************
	*********************************************************************/

	/**
	 *	@brief	Template for Vulkan image object.
	 */
	template<VkImageType eImageType, VkImageViewType eViewType>

	class BaseImage : private Resource
	{

	protected:

		//!	@brief	Create image object.
		BaseImage();

		//!	@brief	Destroy image object.
		~BaseImage();

	public:

		//!	@brief	Convert to VkImage handle.
		operator VkImage() const { return m_hImage; }

		//!	@brief	Return the image format.
		VkFormat GetFormat() const { return m_eFormat; }

		//!	@brief	Return the image extent.
		VkExtent3D GetExtent() const { return m_Extent3D; }

		//!	@brief	Return the image view.
		VkImageView GetView() const { return m_hImageView; }

		//!	@brief	Return the number of mip-levels.
		uint32_t GetMipLevels() const { return m_MipLevels; }

		//!	@brief	Return the count of layers.
		uint32_t GetArrayLayers() const { return m_ArrayLayers; }

		//!	@brief	Return the count of samples.
		VkSampleCountFlagBits GetSampleCount() const { return m_eSampleCount; }

		//!	@brief	Whether image handle is valid.
		VkBool32 IsValid() const { return m_hImage != VK_NULL_HANDLE; }

		//!	@brief	Release image.
		void Release() noexcept;

	protected:

		//!	@brief	Create a new image object.
		VkResult Create(VkFormat eFormat, VkExtent3D Extent3D,uint32_t MipLevels, uint32_t ArrayLayers, VkSampleCountFlagBits eSamples, VkImageUsageFlags eUsage, VkImageCreateFlags eCreateFlags = 0);

		//!	@brief	Create a new image view object.
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
	class Image1D : public BaseImage<VK_IMAGE_TYPE_1D, VK_IMAGE_VIEW_TYPE_1D>
	{

	public:

		//!	@brief	Create a new image 1D object.
		VkResult Create(VkFormat eFormat, uint32_t Width, uint32_t MipLevels, VkImageUsageFlags eUsage, VkImageAspectFlags eAspectMask)
		{
			VkResult eResult = BaseImage::Create(eFormat, { Width, 1, 1 }, MipLevels, 1, VK_SAMPLE_COUNT_1_BIT, eUsage);

			return (eResult == VK_SUCCESS) ? BaseImage::CreateView(eAspectMask) : eResult;
		}
	};

	/*********************************************************************
	*************************    Image1DArray    *************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan image 1D array object.
	 */
	class Image1DArray : public BaseImage<VK_IMAGE_TYPE_1D, VK_IMAGE_VIEW_TYPE_1D_ARRAY>
	{

	public:

		//!	@brief	Create a new image 1D array object.
		VkResult Create(VkFormat eFormat, uint32_t Width, uint32_t MipLevels, uint32_t ArrayLayers, VkImageUsageFlags eUsage, VkImageAspectFlags eAspectMask)
		{
			VkResult eResult = BaseImage::Create(eFormat, { Width, 1, 1 }, MipLevels, ArrayLayers, VK_SAMPLE_COUNT_1_BIT, eUsage);

			return (eResult == VK_SUCCESS) ? BaseImage::CreateView(eAspectMask) : eResult;
		}
	};

	/*********************************************************************
	***************************    Image2D    ****************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan image 2D object.
	 */
	class Image2D : public BaseImage<VK_IMAGE_TYPE_2D, VK_IMAGE_VIEW_TYPE_2D>
	{

	public:

		//!	@brief	Create a new image 2D object.
		VkResult Create(VkFormat eFormat, uint32_t Width, uint32_t Height, uint32_t MipLevels, VkSampleCountFlagBits eSamples, VkImageUsageFlags eUsage, VkImageAspectFlags eAspectMask)
		{
			VkResult eResult = BaseImage::Create(eFormat, { Width, Height, 1 }, MipLevels, 1, eSamples, eUsage);

			return (eResult == VK_SUCCESS) ? BaseImage::CreateView(eAspectMask) : eResult;
		}

		//!	@brief	Create a new color attachment object.
		VkResult CreateColorAttachment(VkFormat eFormat, uint32_t Width, uint32_t Height, VkSampleCountFlagBits eSamples = VK_SAMPLE_COUNT_1_BIT)
		{
			VkResult eResult = BaseImage::Create(eFormat, { Width, Height, 1 }, 1, 1, eSamples, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT);

			return (eResult == VK_SUCCESS) ? BaseImage::CreateView(VK_IMAGE_ASPECT_COLOR_BIT) : eResult;
		}

		//!	@brief	Create a new 16-bit depth attachment object.
		VkResult CreateDepthAttachment16(uint32_t Width, uint32_t Height, VkSampleCountFlagBits eSamples = VK_SAMPLE_COUNT_1_BIT)
		{
			VkResult eResult = BaseImage::Create(VK_FORMAT_D16_UNORM, { Width, Height, 1 }, 1, 1, eSamples, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT);

			return (eResult == VK_SUCCESS) ? BaseImage::CreateView(VK_IMAGE_ASPECT_DEPTH_BIT) : eResult;
		}

		//!	@brief	Create a new 32-bit depth attachment object.
		VkResult CreateDepthAttachment32(uint32_t Width, uint32_t Height, VkSampleCountFlagBits eSamples = VK_SAMPLE_COUNT_1_BIT)
		{
			VkResult eResult = BaseImage::Create(VK_FORMAT_D32_SFLOAT, { Width, Height, 1 }, 1, 1, eSamples, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT);

			return (eResult == VK_SUCCESS) ? BaseImage::CreateView(VK_IMAGE_ASPECT_DEPTH_BIT) : eResult;
		}

		//!	@brief	Create a new depth-stencil attachment object.
		VkResult CreateDepthStencilAttachment(uint32_t Width, uint32_t Height, VkSampleCountFlagBits eSamples = VK_SAMPLE_COUNT_1_BIT)
		{
			VkResult eResult = BaseImage::Create(VK_FORMAT_D24_UNORM_S8_UINT, { Width, Height, 1 }, 1, 1, eSamples, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT);

			return (eResult == VK_SUCCESS) ? BaseImage::CreateView(VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT) : eResult;
		}
	};

	/*********************************************************************
	*************************    Image2DArray    *************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan image 2D object.
	 */
	class Image2DArray : public BaseImage<VK_IMAGE_TYPE_2D, VK_IMAGE_VIEW_TYPE_2D_ARRAY>
	{

	public:

		//!	@brief	Create a new image 2D object.
		VkResult Create(VkFormat eFormat, uint32_t Width, uint32_t Height, uint32_t MipLevels, uint32_t ArrayLayers, VkSampleCountFlagBits eSamples, VkImageUsageFlags eUsage, VkImageAspectFlags eAspectMask)
		{
			VkResult eResult = BaseImage::Create(eFormat, { Width, Height, 1 }, MipLevels, ArrayLayers, eSamples, eUsage);

			return (eResult == VK_SUCCESS) ? BaseImage::CreateView(eAspectMask) : eResult;
		}
	};

	/*********************************************************************
	**************************    ImageCube    ***************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan image cube object.
	 */
	class ImageCube : public BaseImage<VK_IMAGE_TYPE_2D, VK_IMAGE_VIEW_TYPE_CUBE>
	{

	public:

		//!	@brief	Create a new image cube object.
		VkResult Create(VkFormat eFormat, uint32_t Width, uint32_t Height, uint32_t MipLevels, VkImageUsageFlags eUsage, VkImageAspectFlags eAspectMask)
		{
			VkResult eResult = BaseImage::Create(eFormat, { Width, Height, 1 }, MipLevels, 6, VK_SAMPLE_COUNT_1_BIT, eUsage, VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT);

			return (eResult == VK_SUCCESS) ? BaseImage::CreateView(eAspectMask) : eResult;
		}
	};

	/*********************************************************************
	***************************    Image3D    ****************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan image 3D object.
	 */
	class Image3D : public BaseImage<VK_IMAGE_TYPE_3D, VK_IMAGE_VIEW_TYPE_3D>
	{

	public:

		//!	@brief	Create a new image 3D object.
		VkResult Create(VkFormat eFormat, uint32_t Width, uint32_t Height, uint32_t Depth, uint32_t MipLevels, VkImageUsageFlags eUsage, VkImageAspectFlags eAspectMask)
		{
			VkResult eResult = BaseImage::Create(eFormat, { Width, Height, Depth }, MipLevels, 1, VK_SAMPLE_COUNT_1_BIT, eUsage);

			return (eResult == VK_SUCCESS) ? BaseImage::CreateView(eAspectMask) : eResult;
		}
	};
}