/*************************************************************************
*************************    VisualVk_Images    **************************
*************************************************************************/
#pragma once

#include "Enum.h"
#include "Flags.h"
#include "Format.h"
#include "Resource.h"
#include "DeviceMemory.h"

namespace Vk
{
	/*********************************************************************
	**************************    BaseImage    ***************************
	*********************************************************************/

	/**
	 *	@brief	Template for Vulkan image objects.
	 */
	template<VkImageType eImageType, VkImageViewType eViewType> class BaseImage : private Resource
	{

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
		VkBool32 IsValid() const { return m_hImage != VK_NULL_HANDLE; }

		//!	@brief	Return the count of samples.
		SampleCount GetSampleCount() const { return m_eSamples; }

		//!	@brief	Return the count of layers.
		uint32_t GetArrayLayers() const { return m_ArrayLayers; }

		//!	@brief	Return the number of mip-levels.
		uint32_t GetMipLevels() const { return m_MipLevels; }

		//!	@brief	Return the image extent.
		VkExtent3D GetExtent() const { return m_Extent3D; }

		//!	@brief	Return the image format.
		Format GetFormat() const { return m_eFormat; }

		//!	@brief	Release image.
		void Release() noexcept;

	protected:

		//!	@brief	Create a new image object.
		VkResult Create(Format eFormat, VkExtent3D Extent3D,uint32_t MipLevels, uint32_t ArrayLayers,
						SampleCount eSamples, Flags<ImageUsage> UsageFlags, VkImageCreateFlags eCreateFlags = 0);

		//!	@brief	Create a new image view object.
		VkResult CreateView(Flags<ImageAspect> AspectFlags);

	private:

		VkImage					m_hImage;

		Format					m_eFormat;

		VkExtent3D				m_Extent3D;

		SampleCount				m_eSamples;

		VkImageView				m_hImageView;

		DeviceMemory			m_DeviceMemory;

		uint32_t				m_ArrayLayers;

		uint32_t				m_MipLevels;
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
		VkResult Create(Format eFormat, uint32_t Width, uint32_t MipLevels, Flags<ImageUsage> UsageFlags, Flags<ImageAspect> AspectFlags)
		{
			VkResult eResult = BaseImage::Create(eFormat, { Width, 1, 1 }, MipLevels, 1, SampleCount::e1, UsageFlags);

			return (eResult == VK_SUCCESS) ? BaseImage::CreateView(AspectFlags) : eResult;
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
		VkResult Create(Format eFormat, uint32_t Width, uint32_t MipLevels, uint32_t ArrayLayers, Flags<ImageUsage> UsageFlags, Flags<ImageAspect> AspectFlags)
		{
			VkResult eResult = BaseImage::Create(eFormat, { Width, 1, 1 }, MipLevels, ArrayLayers, SampleCount::e1, UsageFlags);

			return (eResult == VK_SUCCESS) ? BaseImage::CreateView(AspectFlags) : eResult;
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
		VkResult Create(Format eFormat, VkExtent2D Extent2D, uint32_t MipLevels, SampleCount eSamples, Flags<ImageUsage> UsageFlags, Flags<ImageAspect> AspectFlags)
		{
			VkResult eResult = BaseImage::Create(eFormat, { Extent2D.width, Extent2D.height, 1 }, MipLevels, 1, eSamples, UsageFlags);

			return (eResult == VK_SUCCESS) ? BaseImage::CreateView(AspectFlags) : eResult;
		}

	public:

		//!	@brief	Create a new color attachment object.
		VkResult CreateColorAttachment(Format eFormat, VkExtent2D Extent2D, SampleCount eSamples = SampleCount::e1)
		{
			VkResult eResult = BaseImage::Create(eFormat, { Extent2D.width, Extent2D.height, 1 }, 1, 1, eSamples, ImageUsage::eColorAttachment);

			return (eResult == VK_SUCCESS) ? BaseImage::CreateView(ImageAspect::eColor) : eResult;
		}

		//!	@brief	Create a new 16-bit depth attachment object.
		VkResult CreateDepthAttachment16(VkExtent2D Extent2D, SampleCount eSamples = SampleCount::e1)
		{
			VkResult eResult = BaseImage::Create(Format::eD16Unorm, { Extent2D.width, Extent2D.height, 1 }, 1, 1, eSamples, ImageUsage::eDepthStencilAttachment);

			return (eResult == VK_SUCCESS) ? BaseImage::CreateView(ImageAspect::eDepth) : eResult;
		}

		//!	@brief	Create a new 32-bit depth attachment object.
		VkResult CreateDepthAttachment32(VkExtent2D Extent2D, SampleCount eSamples = SampleCount::e1)
		{
			VkResult eResult = BaseImage::Create(Format::eD32Sfloat, { Extent2D.width, Extent2D.height, 1 }, 1, 1, eSamples, ImageUsage::eDepthStencilAttachment);

			return (eResult == VK_SUCCESS) ? BaseImage::CreateView(ImageAspect::eDepth) : eResult;
		}

		//!	@brief	Create a new depth-stencil attachment object.
		VkResult CreateDepthStencilAttachment(VkExtent2D Extent2D, SampleCount eSamples = SampleCount::e1)
		{
			VkResult eResult = BaseImage::Create(Format::eD24UnormS8Uint, { Extent2D.width, Extent2D.height, 1 }, 1, 1, eSamples, ImageUsage::eDepthStencilAttachment);

			return (eResult == VK_SUCCESS) ? BaseImage::CreateView(ImageAspect::eDepth | ImageAspect::eStencil) : eResult;
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
		VkResult Create(Format eFormat, VkExtent2D Extent2D, uint32_t MipLevels, uint32_t ArrayLayers, SampleCount eSamples, Flags<ImageUsage> UsageFlags, Flags<ImageAspect> AspectFlags)
		{
			VkResult eResult = BaseImage::Create(eFormat, { Extent2D.width, Extent2D.height, 1 }, MipLevels, ArrayLayers, eSamples, UsageFlags);

			return (eResult == VK_SUCCESS) ? BaseImage::CreateView(AspectFlags) : eResult;
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
		VkResult Create(Format eFormat, VkExtent2D Extent2D, uint32_t MipLevels, Flags<ImageUsage> UsageFlags, Flags<ImageAspect> AspectFlags)
		{
			VkResult eResult = BaseImage::Create(eFormat, { Extent2D.width, Extent2D.height, 1 }, MipLevels, 6, SampleCount::e1, UsageFlags, VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT);

			return (eResult == VK_SUCCESS) ? BaseImage::CreateView(AspectFlags) : eResult;
		}
	};

	/*********************************************************************
	************************    ImageCubeArray    ************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan image cube array object.
	 */
	class ImageCubeArray : public BaseImage<VK_IMAGE_TYPE_2D, VK_IMAGE_VIEW_TYPE_CUBE_ARRAY>
	{

	public:

		//!	@brief	Create a new image cube array object.
		VkResult Create(Format eFormat, VkExtent2D Extent2D, uint32_t MipLevels, uint32_t ArrayLayers, Flags<ImageUsage> UsageFlags, Flags<ImageAspect> AspectFlags)
		{
			VkResult eResult = BaseImage::Create(eFormat, { Extent2D.width, Extent2D.height, 1 }, MipLevels, 6 * ArrayLayers, SampleCount::e1, UsageFlags, VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT);

			return (eResult == VK_SUCCESS) ? BaseImage::CreateView(AspectFlags) : eResult;
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
		VkResult Create(Format eFormat, VkExtent3D Extent3D, uint32_t MipLevels, Flags<ImageUsage> UsageFlags, Flags<ImageAspect> AspectFlags)
		{
			VkResult eResult = BaseImage::Create(eFormat, Extent3D, MipLevels, 1, SampleCount::e1, UsageFlags);

			return (eResult == VK_SUCCESS) ? BaseImage::CreateView(AspectFlags) : eResult;
		}
	};
}