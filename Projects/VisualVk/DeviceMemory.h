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


		//!	@brief	Return size of device memory.
		VkDeviceSize Bytes() const { return m_Bytes; }

	private:

		VkDeviceSize		m_Bytes;

		VkDeviceMemory		m_hMemory;
	};
}