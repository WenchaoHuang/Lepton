/*************************************************************************
*************************    VisualVk_Buffer    **************************
*************************************************************************/
#pragma once

#include "DeviceMemory.h"

namespace Vk
{
	/*********************************************************************
	****************************    Buffer    ****************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan buffer object.
	 */
	class Buffer : private Resource
	{

	public:

		Buffer();
		
		~Buffer();

	public:

		VkResult Create();

		VkBool32 IsEmpty() const { return m_hBuffer != VK_NULL_HANDLE; }

		VkDeviceSize Bytes() const { return m_Bytes; }

	private:

		VkBuffer		m_hBuffer;

		DeviceMemory	m_Memory;

		VkDeviceSize	m_Bytes;
	};
}