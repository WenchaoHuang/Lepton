/*************************************************************************
**********************    VisualVk_Win32Surface    ***********************
*************************************************************************/
#pragma once

#include "Vulkan.h"
#include <vulkan/vulkan.h>

namespace Vk
{
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

		Result Create(PhysicalDevice * pPhysicalDevicem, HWND hWindow);

		void Destroy();

	private:

		VkSurfaceKHR			m_hSurface;

		PhysicalDevice *		m_pPhysicalDevice;
	};
}