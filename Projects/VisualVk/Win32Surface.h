/*************************************************************************
**********************    VisualVk_Win32Surface    ***********************
*************************************************************************/
#pragma once

#include "Vulkan.h"

namespace Vk
{
	/*********************************************************************
	************************    SurfaceFormat    *************************
	*********************************************************************/

	/**
	 *	@brief	Structure describing a supported swapchain format-color space pair.
	 */
	struct SurfaceFormat
	{
		Format			format			= Format::eUndefined;
		ColorSpace		colorSpace		= ColorSpace::eSrgbNonlinear;
	};

	static_assert(sizeof(SurfaceFormat) == sizeof(VkSurfaceKHR), "Struct and wrapper have different size!");

	/*********************************************************************
	*********************    SurfaceCapabilities    **********************
	*********************************************************************/

	/**
	 *	@brief	Structure describing capabilities of a surface.
	 */
	struct SurfaceCapabilities
	{
		uint32_t							minImageCount				= 0;
		uint32_t							maxImageCount				= 0;
		VkExtent2D							currentExtent				= { 0, 0 };
		VkExtent2D							minImageExtent				= { 0, 0 };
		VkExtent2D							maxImageExtent				= { 0, 0 };
		uint32_t							maxImageArrayLayers			= 0;
		Flags<PresentationTransform>		supportedTransforms			= 0;
		PresentationTransform				currentTransform			= PresentationTransform::eIdentity;
		Flags<AlphaCompositingMmode>		supportedCompositeAlpha		= 0;
		Flags<ImageUsage>					supportedUsageFlags			= 0;
	};

	static_assert(sizeof(SurfaceCapabilities) == sizeof(VkSurfaceCapabilitiesKHR), "Struct and wrapper have different size!");

	/*********************************************************************
	*************************    Win32Surface    *************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan win32 surface object.
	 */
	class Win32Surface
	{
		VK_NONCOPYABLE(Win32Surface)

	public:

		//!	@brief	Create win32 surface object.
		Win32Surface();

		//!	@brief	Destroy win32 surface object.
		~Win32Surface();

	public:

		//!	@brief	Return Vulkan type of this object.
		operator VkSurfaceKHR() const { return m_hSurface; }

		bool IsValid() const { return m_hSurface != VK_NULL_HANDLE; }

		Result Create(PhysicalDevice * pPhysicalDevicem, HWND hWindow);

		const std::vector<PresentMode> & GetAvailablePresentModes() const;

		const std::vector<SurfaceFormat> & GetAvailableSurfaceFormats() const;

		bool IsQueueFamilySupported(uint32_t queueFamilyIndex) const;

		bool IsSurfaceFormatAvailable(SurfaceFormat eFormat) const;

		bool IsPresentModeSupported(PresentMode eMode) const;

		const SurfaceCapabilities & GetCapabilities() const;

		void Destroy();
		
	private:

		VkSurfaceKHR							m_hSurface;

		PhysicalDevice *						m_pPhysicalDevice;

		mutable SurfaceCapabilities				m_SurfaceCapabilities;

		mutable std::vector<PresentMode>		m_AvailablePresentModes;

		mutable std::vector<SurfaceFormat>		m_AvailableSurfaceFormats;
	};
}