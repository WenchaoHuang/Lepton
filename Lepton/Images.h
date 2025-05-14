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
		vk::Format					format			= vk::Format::eUndefined;
		VkExtent3D					extent			= { 0, 0, 0 };
		uint32_t					mipLevels		= 1;
		uint32_t					arrayLayers		= 1;
		vk::SampleCountFlagBits		samples			= vk::SampleCountFlagBits::e1;
		vk::ImageUsageFlags			usage			= vk::ImageUsageFlags(0);
		vk::ImageAspectFlags		aspectMask		= vk::ImageAspectFlags(0);
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
		Result Create(const LogicalDevice * pLogicalDevice, vk::Format eFormat, VkExtent3D extent, uint32_t mipLevels, uint32_t arrayLayers,
					  vk::SampleCountFlagBits eSamples, vk::ImageUsageFlags eUsages, vk::ImageAspectFlags eAspects, VkImageCreateFlags eCreateFlags = 0);

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
		Result Create(const LogicalDevice * pLogicalDevice, vk::Format eFormat, uint32_t width, uint32_t mipLevels,
					  vk::ImageUsageFlags usageFlags, vk::ImageAspectFlags eAspects)
		{
			return BaseImage::Create(pLogicalDevice, eFormat, { width, 1, 1 }, mipLevels, 1, vk::SampleCountFlagBits::e1, usageFlags, eAspects);
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
		Result Create(const LogicalDevice * pLogicalDevice, vk::Format eFormat, uint32_t width, uint32_t mipLevels, uint32_t arrayLayers,
					  vk::ImageUsageFlags usageFlags, vk::ImageAspectFlags eAspects)
		{
			return BaseImage::Create(pLogicalDevice, eFormat, { width, 1, 1 }, mipLevels, arrayLayers, vk::SampleCountFlagBits::e1, usageFlags, eAspects);
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
		Result Create(const LogicalDevice * pLogicalDevice, vk::Format eFormat, VkExtent2D extent, uint32_t mipLevels, vk::SampleCountFlagBits eSamples,
					  vk::ImageUsageFlags usageFlags, vk::ImageAspectFlags eAspects)
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
		Result Create(const LogicalDevice * pLogicalDevice, vk::Format eFormat, VkExtent2D extent, uint32_t mipLevels, uint32_t arrayLayers, vk::SampleCountFlagBits eSamples,
					  vk::ImageUsageFlags usageFlags, vk::ImageAspectFlags eAspects)
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
		Result Create(const LogicalDevice * pLogicalDevice, vk::Format eFormat, VkExtent2D extent, uint32_t mipLevels,
					  vk::ImageUsageFlags usageFlags, vk::ImageAspectFlags eAspects)
		{
			return BaseImage::Create(pLogicalDevice, eFormat, { extent.width, extent.height, 1 },  mipLevels, 6, vk::SampleCountFlagBits::e1,
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
		Result Create(const LogicalDevice * pLogicalDevice, vk::Format eFormat, VkExtent2D extent, uint32_t mipLevels, uint32_t arrayLayers,
					  vk::ImageUsageFlags usageFlags, vk::ImageAspectFlags eAspects)
		{
			return BaseImage::Create(pLogicalDevice, eFormat, { extent.width, extent.height, 1 }, mipLevels, 6 * arrayLayers, vk::SampleCountFlagBits::e1,
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
		Result Create(const LogicalDevice * pLogicalDevice, vk::Format eFormat, VkExtent3D Extent3D, uint32_t mipLevels,
					  vk::ImageUsageFlags usageFlags, vk::ImageAspectFlags eAspects)
		{
			return BaseImage::Create(pLogicalDevice, eFormat, Extent3D, mipLevels, 1, vk::SampleCountFlagBits::e1, usageFlags, eAspects);
		}
	};
}