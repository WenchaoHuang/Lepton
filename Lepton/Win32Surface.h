/*************************************************************************
***********************    Lepton_Win32Surface    ************************
*************************************************************************/
#pragma once

#include "Vulkan.h"

namespace Lepton
{
	/*********************************************************************
	*************************    Win32Surface    *************************
	*********************************************************************/

	/**
	 *	@brief	Wrapper for Vulkan win32 surface object.
	 */
	class Win32Surface
	{

	public:

		//!	@brief	Destroy the surface.
		void Destroy() { m_spUniqueHandle.reset(); }

		//!	@brief	Create a new Win32 surface object.
		Result Create(VkInstance hInstance, HWND hWindow);

		//!	@brief	If Vulkan handle is valid.
		bool IsValid() const { return m_spUniqueHandle != nullptr; }

		//!	@brief	Convert to VkSurfaceKHR.
		operator VkSurfaceKHR() const { return (m_spUniqueHandle != nullptr) ? m_spUniqueHandle->m_hSurface : VK_NULL_HANDLE; }
		
	private:

		/**
		 *	@brief	Unique handle of win32 surface.
		 */
		struct UniqueHandle
		{
			LAVA_NONCOPYABLE(UniqueHandle)

		public:

			//!	@brief	Constructor (handles must be initialized).
			UniqueHandle(VkInstance, VkSurfaceKHR);

			//!	@brief	Where resource will be released.
			~UniqueHandle() noexcept;

		public:

			const VkInstance				m_hInstance;
			const VkSurfaceKHR				m_hSurface;
		};

		std::shared_ptr<UniqueHandle>		m_spUniqueHandle;
	};
}