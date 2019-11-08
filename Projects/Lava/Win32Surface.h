/*************************************************************************
************************    Lava_Win32Surface    *************************
*************************************************************************/
#pragma once

#include "Vulkan.h"

namespace Lava
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
		Flags<SurfaceTransform>				supportedTransforms			= 0;
		SurfaceTransform					currentTransform			= SurfaceTransform::eIdentity;
		Flags<AlphaCompositingMmode>		supportedCompositeAlpha		= 0;
		Flags<ImageUsage>					supportedUsageFlags			= 0;
	};

	static_assert(sizeof(SurfaceCapabilities) == sizeof(VkSurfaceCapabilitiesKHR), "Struct and wrapper have different size!");

	/*********************************************************************
	*************************    Win32Surface    *************************
	*********************************************************************/

	/**
	 *	@brief	Wrapper for Vulkan win32 surface object.
	 */
	class Win32Surface
	{
		VK_NONCOPYABLE(Win32Surface)

	public:

		//!	@brief	Create win32 surface object.
		Win32Surface();

		//!	@brief	Create and initialize immediately.
		explicit Win32Surface(VkInstance hInstance, HWND hWindow);

		//!	@brief	Destroy win32 surface object.
		~Win32Surface();

	public:

		//!	@brief	Convert to VkSurfaceKHR.
		operator VkSurfaceKHR() const { return m_hSurface; }

		//!	@brief	If Vulkan handle is valid.
		bool IsValid() const { return m_hSurface != VK_NULL_HANDLE; }

		//!	@brief	Create a new Win32 surface object.
		Result Create(VkInstance hInstance, HWND hWindow);

		//!	@brief	Destroy the surface.
		void Destroy();
		
	private:

		VkInstance			m_hInstance;

		VkSurfaceKHR		m_hSurface;
	};
}