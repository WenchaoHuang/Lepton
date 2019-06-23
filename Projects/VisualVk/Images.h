/*************************************************************************
*************************    VisualVk_Images    **************************
*************************************************************************/
#pragma once

#include "Flags.h"
#include "Resource.h"
#include "DeviceMemory.h"

namespace Vk
{
	/*********************************************************************
	*************************    SampleCount    **************************
	*********************************************************************/

	/**
	 *	@brief	Bitmask specifying sample counts supported for an image used for storage operations.
	 */
	enum class SampleCount : VkFlags
	{
		e1		= VK_SAMPLE_COUNT_1_BIT,
		e2		= VK_SAMPLE_COUNT_2_BIT,
		e4		= VK_SAMPLE_COUNT_4_BIT,
		e8		= VK_SAMPLE_COUNT_8_BIT,
		e16		= VK_SAMPLE_COUNT_16_BIT,
		e32		= VK_SAMPLE_COUNT_32_BIT,
		e64		= VK_SAMPLE_COUNT_64_BIT
	};

	/*********************************************************************
	**************************    ImageUsage    **************************
	*********************************************************************/

	/**
	 *	@brief	Bitmask specifying intended usage of an image.
	 */
	enum class ImageUsage : VkFlags
	{
		eSampled					= VK_IMAGE_USAGE_SAMPLED_BIT,
		eStorage					= VK_IMAGE_USAGE_STORAGE_BIT,
		eTransferSrc				= VK_IMAGE_USAGE_TRANSFER_SRC_BIT,
		eTransferDst				= VK_IMAGE_USAGE_TRANSFER_DST_BIT,
		eColorAttachment			= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
		eInputAttachment			= VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT,
		eTransientAttachment		= VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT,
		eDepthStencilAttachment		= VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
		eFragmentDensityMapEXT		= VK_IMAGE_USAGE_FRAGMENT_DENSITY_MAP_BIT_EXT,
		eShadingRateImageNV			= VK_IMAGE_USAGE_SHADING_RATE_IMAGE_BIT_NV
	};

	/*********************************************************************
	*************************    ImageAspect    **************************
	*********************************************************************/

	/**
	 *	@brief	Bitmask specifying which aspects of an image are included in a view.
	 */
	enum class ImageAspect : VkFlags
	{
		eColor					= VK_IMAGE_ASPECT_COLOR_BIT,
		eDepth					= VK_IMAGE_ASPECT_DEPTH_BIT,
		eStencil				= VK_IMAGE_ASPECT_STENCIL_BIT,
		eMetadata				= VK_IMAGE_ASPECT_METADATA_BIT,
		ePlane0					= VK_IMAGE_ASPECT_PLANE_0_BIT,
		ePlane1					= VK_IMAGE_ASPECT_PLANE_1_BIT,
		ePlane2					= VK_IMAGE_ASPECT_PLANE_2_BIT,
		ePlane0KHR				= VK_IMAGE_ASPECT_PLANE_0_BIT_KHR,
		ePlane1KHR				= VK_IMAGE_ASPECT_PLANE_1_BIT_KHR,
		ePlane2KHR				= VK_IMAGE_ASPECT_PLANE_2_BIT_KHR,
		eMemoryPlane0EXT		= VK_IMAGE_ASPECT_MEMORY_PLANE_0_BIT_EXT,
		eMemoryPlane1EXT		= VK_IMAGE_ASPECT_MEMORY_PLANE_1_BIT_EXT,
		eMemoryPlane2EXT		= VK_IMAGE_ASPECT_MEMORY_PLANE_2_BIT_EXT,
		eMemoryPlane3EXT		= VK_IMAGE_ASPECT_MEMORY_PLANE_3_BIT_EXT
	};

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
		SampleCount GetSampleCount() const { return m_eSampleCount; }

		//!	@brief	Whether image handle is valid.
		VkBool32 IsValid() const { return m_hImage != VK_NULL_HANDLE; }

		//!	@brief	Release image.
		void Release() noexcept;

	protected:

		//!	@brief	Create a new image object.
		VkResult Create(VkFormat eFormat, VkExtent3D Extent3D,uint32_t MipLevels, uint32_t ArrayLayers, SampleCount eSamples, Flags<ImageUsage> UsageFlags, VkImageCreateFlags eCreateFlags = 0);

		//!	@brief	Create a new image view object.
		VkResult CreateView(Flags<ImageAspect> AspectFlags);

	private:

		VkImage					m_hImage;

		VkFormat				m_eFormat;

		VkExtent3D				m_Extent3D;

		VkImageView				m_hImageView;

		SampleCount				m_eSampleCount;

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
		VkResult Create(VkFormat eFormat, uint32_t Width, uint32_t MipLevels, Flags<ImageUsage> UsageFlags, Flags<ImageAspect> AspectFlags)
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
		VkResult Create(VkFormat eFormat, uint32_t Width, uint32_t MipLevels, uint32_t ArrayLayers, Flags<ImageUsage> UsageFlags, Flags<ImageAspect> AspectFlags)
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
		VkResult Create(VkFormat eFormat, VkExtent2D Extent2D, uint32_t MipLevels, SampleCount eSamples, Flags<ImageUsage> UsageFlags, Flags<ImageAspect> AspectFlags)
		{
			VkResult eResult = BaseImage::Create(eFormat, { Extent2D.width, Extent2D.height, 1 }, MipLevels, 1, eSamples, UsageFlags);

			return (eResult == VK_SUCCESS) ? BaseImage::CreateView(AspectFlags) : eResult;
		}

		//!	@brief	Create a new color attachment object.
		VkResult CreateColorAttachment(VkFormat eFormat, VkExtent2D Extent2D, SampleCount eSamples = SampleCount::e1)
		{
			VkResult eResult = BaseImage::Create(eFormat, { Extent2D.width, Extent2D.height, 1 }, 1, 1, eSamples, ImageUsage::eColorAttachment);

			return (eResult == VK_SUCCESS) ? BaseImage::CreateView(ImageAspect::eColor) : eResult;
		}

		//!	@brief	Create a new 16-bit depth attachment object.
		VkResult CreateDepthAttachment16(VkExtent2D Extent2D, SampleCount eSamples = SampleCount::e1)
		{
			VkResult eResult = BaseImage::Create(VK_FORMAT_D16_UNORM, { Extent2D.width, Extent2D.height, 1 }, 1, 1, eSamples, ImageUsage::eDepthStencilAttachment);

			return (eResult == VK_SUCCESS) ? BaseImage::CreateView(ImageAspect::eDepth) : eResult;
		}

		//!	@brief	Create a new 32-bit depth attachment object.
		VkResult CreateDepthAttachment32(VkExtent2D Extent2D, SampleCount eSamples = SampleCount::e1)
		{
			VkResult eResult = BaseImage::Create(VK_FORMAT_D32_SFLOAT, { Extent2D.width, Extent2D.height, 1 }, 1, 1, eSamples, ImageUsage::eDepthStencilAttachment);

			return (eResult == VK_SUCCESS) ? BaseImage::CreateView(ImageAspect::eDepth) : eResult;
		}

		//!	@brief	Create a new depth-stencil attachment object.
		VkResult CreateDepthStencilAttachment(VkExtent2D Extent2D, SampleCount eSamples = SampleCount::e1)
		{
			VkResult eResult = BaseImage::Create(VK_FORMAT_D24_UNORM_S8_UINT, { Extent2D.width, Extent2D.height, 1 }, 1, 1, eSamples, ImageUsage::eDepthStencilAttachment);

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
		VkResult Create(VkFormat eFormat, VkExtent2D Extent2D, uint32_t MipLevels, uint32_t ArrayLayers, SampleCount eSamples, Flags<ImageUsage> UsageFlags, Flags<ImageAspect> AspectFlags)
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
		VkResult Create(VkFormat eFormat, VkExtent2D Extent2D, uint32_t MipLevels, Flags<ImageUsage> UsageFlags, Flags<ImageAspect> AspectFlags)
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
		VkResult Create(VkFormat eFormat, VkExtent2D Extent2D, uint32_t MipLevels, uint32_t ArrayLayers, Flags<ImageUsage> UsageFlags, Flags<ImageAspect> AspectFlags)
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
		VkResult Create(VkFormat eFormat, VkExtent3D Extent3D, uint32_t MipLevels, Flags<ImageUsage> UsageFlags, Flags<ImageAspect> AspectFlags)
		{
			VkResult eResult = BaseImage::Create(eFormat, Extent3D, MipLevels, 1, SampleCount::e1, UsageFlags);

			return (eResult == VK_SUCCESS) ? BaseImage::CreateView(AspectFlags) : eResult;
		}
	};
}