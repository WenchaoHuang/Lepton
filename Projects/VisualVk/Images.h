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
	 *	@brief	Template for Vulkan image objects.
	 */
	template<VkImageType eImageType, VkImageViewType eViewType> class BaseImage
	{
		VK_NONCOPYABLE(BaseImage)

	protected:

		//!	@brief	Create image object.
		BaseImage();

		//!	@brief	Destroy image object.
		~BaseImage();

	public:

		//!	@brief	Convert to VkImage handle.
		operator VkImage() const { return m_hImage; }

		//!	@brief	Convert to VkImageView handle.
		operator VkImageView() const { return m_hImageView; }

		//!	@brief	Whether image handle is valid.
		bool IsValid() const { return m_hImage != VK_NULL_HANDLE; }

		//!	@brief	Return image layout.
		ImageLayout GetImageLayout() const { return m_eImageLayout; }

		//!	@brief	Return the count of samples.
		SampleCount GetSampleCount() const { return m_eSamples; }

		//!	@brief	Return the count of layers.
		uint32_t GetArrayLayers() const { return m_ArrayLayers; }

		//!	@brief	Return the number of mip-levels.
		uint32_t GetMipLevels() const { return m_MipLevels; }

		//!	@brief	Return the image extent.
		VkExtent3D GetExtent() const { return m_Extent; }

		//!	@brief	Return the image format.
		Format GetFormat() const { return m_eFormat; }

		//!	@brief	Destroy the image.
		void Destroy();

	protected:

		//!	@brief	Create a new image object.
		Result Create(LogicalDevice * pLogicalDevice, Format eFormat, VkExtent3D extent, uint32_t mipLevels,
					  uint32_t arrayLayers, SampleCount eSamples, Flags<ImageUsage> usageFlags, VkImageCreateFlags eCreateFlags = 0);

		//!	@brief	Create a new image view object.
		Result CreateView(Flags<ImageAspect> aspectFlags);

	private:

		VkImage				m_hImage;

		VkDevice			m_hDevice;

		Format				m_eFormat;

		VkExtent3D			m_Extent;

		SampleCount			m_eSamples;

		VkImageView			m_hImageView;

		ImageLayout			m_eImageLayout;

		DeviceMemory		m_DeviceMemory;

		uint32_t			m_ArrayLayers;

		uint32_t			m_MipLevels;
	};

	/*********************************************************************
	***************************    Image1D    ****************************
	*********************************************************************/

	/**
	 *	@brief	Wrapper for Vulkan image 1D object.
	 */
	class Image1D : public BaseImage<VK_IMAGE_TYPE_1D, VK_IMAGE_VIEW_TYPE_1D>
	{

	public:

		//!	@brief	Create a new image 1D object.
		Result Create(LogicalDevice * pLogicalDevice, Format eFormat, uint32_t width,
					  uint32_t mipLevels, Flags<ImageUsage> usageFlags, Flags<ImageAspect> aspectFlags)
		{
			Result eResult = BaseImage::Create(pLogicalDevice, eFormat, { width, 1, 1 }, mipLevels, 1, SampleCount::x1, usageFlags);

			return (eResult == Result::eSuccess) ? BaseImage::CreateView(aspectFlags) : eResult;
		}
	};

	/*********************************************************************
	*************************    Image1DArray    *************************
	*********************************************************************/

	/**
	 *	@brief	Wrapper for Vulkan image 1D array object.
	 */
	class Image1DArray : public BaseImage<VK_IMAGE_TYPE_1D, VK_IMAGE_VIEW_TYPE_1D_ARRAY>
	{

	public:

		//!	@brief	Create a new image 1D array object.
		Result Create(LogicalDevice * pLogicalDevice, Format eFormat, uint32_t width, uint32_t mipLevels,
					  uint32_t arrayLayers, Flags<ImageUsage> usageFlags, Flags<ImageAspect> aspectFlags)
		{
			Result eResult = BaseImage::Create(pLogicalDevice, eFormat, { width, 1, 1 }, mipLevels, arrayLayers, SampleCount::x1, usageFlags);

			return (eResult == Result::eSuccess) ? BaseImage::CreateView(aspectFlags) : eResult;
		}
	};

	/*********************************************************************
	***************************    Image2D    ****************************
	*********************************************************************/

	/**
	 *	@brief	Wrapper for Vulkan image 2D object.
	 */
	class Image2D : public BaseImage<VK_IMAGE_TYPE_2D, VK_IMAGE_VIEW_TYPE_2D>
	{

	public:

		//!	@brief	Create a new image 2D object.
		Result Create(LogicalDevice * pLogicalDevice, Format eFormat, VkExtent2D extent, uint32_t mipLevels,
					  SampleCount eSamples, Flags<ImageUsage> usageFlags, Flags<ImageAspect> aspectFlags)
		{
			Result eResult = BaseImage::Create(pLogicalDevice, eFormat, { extent.width, extent.height, 1 }, mipLevels, 1, eSamples, usageFlags);

			return (eResult == Result::eSuccess) ? BaseImage::CreateView(aspectFlags) : eResult;
		}
	};

	/*********************************************************************
	*************************    Image2DArray    *************************
	*********************************************************************/

	/**
	 *	@brief	Wrapper for Vulkan image 2D object.
	 */
	class Image2DArray : public BaseImage<VK_IMAGE_TYPE_2D, VK_IMAGE_VIEW_TYPE_2D_ARRAY>
	{

	public:

		//!	@brief	Create a new image 2D object.
		Result Create(LogicalDevice * pLogicalDevice, Format eFormat, VkExtent2D extent, uint32_t mipLevels,
					  uint32_t arrayLayers, SampleCount eSamples, Flags<ImageUsage> usageFlags, Flags<ImageAspect> aspectFlags)
		{
			Result eResult = BaseImage::Create(pLogicalDevice, eFormat, { extent.width, extent.height, 1 }, mipLevels, arrayLayers, eSamples, usageFlags);

			return (eResult == Result::eSuccess) ? BaseImage::CreateView(aspectFlags) : eResult;
		}
	};

	/*********************************************************************
	**************************    ImageCube    ***************************
	*********************************************************************/

	/**
	 *	@brief	Wrapper for Vulkan image cube object.
	 */
	class ImageCube : public BaseImage<VK_IMAGE_TYPE_2D, VK_IMAGE_VIEW_TYPE_CUBE>
	{

	public:

		//!	@brief	Create a new image cube object.
		Result Create(LogicalDevice * pLogicalDevice, Format eFormat, VkExtent2D extent,
					  uint32_t mipLevels, Flags<ImageUsage> usageFlags, Flags<ImageAspect> aspectFlags)
		{
			Result eResult = BaseImage::Create(pLogicalDevice, eFormat, { extent.width, extent.height, 1 },
											   mipLevels, 6, SampleCount::x1, usageFlags, VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT);

			return (eResult == Result::eSuccess) ? BaseImage::CreateView(aspectFlags) : eResult;
		}
	};

	/*********************************************************************
	************************    ImageCubeArray    ************************
	*********************************************************************/

	/**
	 *	@brief	Wrapper for Vulkan image cube array object.
	 */
	class ImageCubeArray : public BaseImage<VK_IMAGE_TYPE_2D, VK_IMAGE_VIEW_TYPE_CUBE_ARRAY>
	{

	public:

		//!	@brief	Create a new image cube array object.
		Result Create(LogicalDevice * pLogicalDevice, Format eFormat, VkExtent2D extent, uint32_t mipLevels,
					  uint32_t arrayLayers, Flags<ImageUsage> usageFlags, Flags<ImageAspect> aspectFlags)
		{
			Result eResult = BaseImage::Create(pLogicalDevice, eFormat, { extent.width, extent.height, 1 }, mipLevels,
											   6 * arrayLayers, SampleCount::x1, usageFlags, VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT);

			return (eResult == Result::eSuccess) ? BaseImage::CreateView(aspectFlags) : eResult;
		}
	};

	/*********************************************************************
	***************************    Image3D    ****************************
	*********************************************************************/

	/**
	 *	@brief	Wrapper for Vulkan image 3D object.
	 */
	class Image3D : public BaseImage<VK_IMAGE_TYPE_3D, VK_IMAGE_VIEW_TYPE_3D>
	{

	public:

		//!	@brief	Create a new image 3D object.
		Result Create(LogicalDevice * pLogicalDevice, Format eFormat, VkExtent3D Extent3D,
					  uint32_t mipLevels, Flags<ImageUsage> usageFlags, Flags<ImageAspect> aspectFlags)
		{
			Result eResult = BaseImage::Create(pLogicalDevice, eFormat, Extent3D, mipLevels, 1, SampleCount::x1, usageFlags);

			return (eResult == Result::eSuccess) ? BaseImage::CreateView(aspectFlags) : eResult;
		}
	};
}