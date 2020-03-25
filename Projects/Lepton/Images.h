/*************************************************************************
**************************    Lepton_Images    ***************************
*************************************************************************/
#pragma once

#include "DeviceMemory.h"

namespace Lepton
{
	/*********************************************************************
	**************************    ImageParam    **************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan image parameters.
	 */
	struct ImageParam
	{
		Format					format			= Format::eUndefined;
		VkExtent3D				extent			= { 0, 0, 0 };
		uint32_t				mipLevels		= 1;
		uint32_t				arrayLayers		= 1;
		SampleCount				samples			= SampleCount::x1;
		Flags<ImageUsage>		usage			= 0;
		Flags<ImageAspect>		aspectMask		= 0;
	};

	/*********************************************************************
	**************************    BaseImage    ***************************
	*********************************************************************/

	/**
	 *	@brief	Template for Vulkan image objects.
	 */
	template<VkImageType eImageType, VkImageViewType eViewType> class BaseImage
	{

	public:

		//!	@brief	Destroy image object.
		void Destroy() { m_spUniqueHandle.reset(); }

		//!	@brief	Whether image handle is valid.
		bool IsValid() const { return m_spUniqueHandle != nullptr; }

		//!	@brief	Return constant reference to its parameter (must be valid).
		const ImageParam & GetParam() const { return m_spUniqueHandle->m_Parameter; }

		//!	@brief	Convert to VkImage.
		operator VkImage() const { return (m_spUniqueHandle != nullptr) ? m_spUniqueHandle->m_hImage : VK_NULL_HANDLE; }

		//!	@brief	Convert to VkImageView.
		operator VkImageView() const { return (m_spUniqueHandle != nullptr) ? m_spUniqueHandle->m_hImageView : VK_NULL_HANDLE; }

	protected:

		//!	@brief	Create a new image object.
		Result Create(const LogicalDevice * pLogicalDevice, Format eFormat, VkExtent3D extent, uint32_t mipLevels, uint32_t arrayLayers,
					  SampleCount eSamples, Flags<ImageUsage> eUsages, Flags<ImageAspect> eAspects, VkImageCreateFlags eCreateFlags = 0);

	private:

		/**
		 *	@brief	Unique handle of image.
		 */
		struct UniqueHandle
		{
			LAVA_NONCOPYABLE(UniqueHandle)

		public:

			//!	@brief	Constructor (handles must be initialized).
			UniqueHandle(DeviceLocalMemory, VkImage, VkImageView, const ImageParam&);

			//!	@brief	Where resource will be released.
			~UniqueHandle() noexcept;

		public:

			const VkImage					m_hImage;
			const ImageParam				m_Parameter;
			const VkImageView				m_hImageView;
			const DeviceLocalMemory			m_DeviceMemory;
		};

		std::shared_ptr<UniqueHandle>		m_spUniqueHandle;
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
		Result Create(const LogicalDevice * pLogicalDevice, Format eFormat, uint32_t width, uint32_t mipLevels,
					  Flags<ImageUsage> usageFlags, Flags<ImageAspect> eAspects)
		{
			return BaseImage::Create(pLogicalDevice, eFormat, { width, 1, 1 }, mipLevels, 1, SampleCount::x1, usageFlags, eAspects);
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
		Result Create(const LogicalDevice * pLogicalDevice, Format eFormat, uint32_t width, uint32_t mipLevels, uint32_t arrayLayers,
					  Flags<ImageUsage> usageFlags, Flags<ImageAspect> eAspects)
		{
			return BaseImage::Create(pLogicalDevice, eFormat, { width, 1, 1 }, mipLevels, arrayLayers, SampleCount::x1, usageFlags, eAspects);
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
		Result Create(const LogicalDevice * pLogicalDevice, Format eFormat, VkExtent2D extent, uint32_t mipLevels, SampleCount eSamples,
					  Flags<ImageUsage> usageFlags, Flags<ImageAspect> eAspects)
		{
			return BaseImage::Create(pLogicalDevice, eFormat, { extent.width, extent.height, 1 }, mipLevels, 1, eSamples, usageFlags, eAspects);
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
		Result Create(const LogicalDevice * pLogicalDevice, Format eFormat, VkExtent2D extent, uint32_t mipLevels, uint32_t arrayLayers, SampleCount eSamples,
					  Flags<ImageUsage> usageFlags, Flags<ImageAspect> eAspects)
		{
			return BaseImage::Create(pLogicalDevice, eFormat, { extent.width, extent.height, 1 }, mipLevels, arrayLayers, eSamples, usageFlags, eAspects);
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
		Result Create(const LogicalDevice * pLogicalDevice, Format eFormat, VkExtent2D extent, uint32_t mipLevels,
					  Flags<ImageUsage> usageFlags, Flags<ImageAspect> eAspects)
		{
			return BaseImage::Create(pLogicalDevice, eFormat, { extent.width, extent.height, 1 },  mipLevels, 6, SampleCount::x1,
									 usageFlags, eAspects, VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT);
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
		Result Create(const LogicalDevice * pLogicalDevice, Format eFormat, VkExtent2D extent, uint32_t mipLevels, uint32_t arrayLayers,
					  Flags<ImageUsage> usageFlags, Flags<ImageAspect> eAspects)
		{
			return BaseImage::Create(pLogicalDevice, eFormat, { extent.width, extent.height, 1 }, mipLevels, 6 * arrayLayers, SampleCount::x1,
									 usageFlags, eAspects, VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT);
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
		Result Create(const LogicalDevice * pLogicalDevice, Format eFormat, VkExtent3D Extent3D, uint32_t mipLevels,
					  Flags<ImageUsage> usageFlags, Flags<ImageAspect> eAspects)
		{
			return BaseImage::Create(pLogicalDevice, eFormat, Extent3D, mipLevels, 1, SampleCount::x1, usageFlags, eAspects);
		}
	};
}