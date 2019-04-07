/*************************************************************************
**********************    VisualVk_DeviceMemory    ***********************
*************************************************************************/
#pragma once

#include "Resource.h"

namespace Vk
{
	/*********************************************************************
	*************************    DeviceMemory    *************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan device memory object.
	 */
	class DeviceMemory : private Resource
	{

	public:

		DeviceMemory();

		~DeviceMemory();

	public:

		//!	@brief	If device memory is empty.
		VkBool32 IsEmpty() const { return m_hMemory == VK_NULL_HANDLE; }

		//!	@brief	Return size of device memory.
		VkDeviceSize Bytes() const { return m_Bytes; }

		void Free() noexcept;

	private:

		VkDeviceSize		m_Bytes;

		VkDeviceMemory		m_hMemory;
	};
}