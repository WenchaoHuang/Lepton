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

		//!	@brief	Create memory object.
		DeviceMemory();

		//!	@brief	Destroy memory object.
		~DeviceMemory();

	public:

		//!	@brief	Allocate memory.
		VkResult Allocate(VkMemoryRequirements Requirements, VkMemoryPropertyFlags ePropertyFlags);

		//!	@brief	Map memory into application address space.
		VkResult Map(void ** ppData, VkDeviceSize OffsetBytes, VkDeviceSize SizeBytes);

		//!	@brief	Invalidate memory.
		VkResult Invalidate(VkDeviceSize OffsetBytes, VkDeviceSize SizeBytes);

		//!	@brief	Flush memory.
		VkResult Flush(VkDeviceSize OffsetBytes, VkDeviceSize SizeBytes);

		//!	@brief	Check if memory handle is valid.
		VkBool32 IsEmpty() const { return m_hMemory != VK_NULL_HANDLE; }

		//!	@brief	Return size of device memory.
		VkDeviceSize Bytes() const { return m_Bytes; }

		//!	@brief	Unmap previously mapped memory.
		void Unmap() noexcept;

		//!	@brief	Free memory.
		void Free() noexcept;

	private:

		VkDeviceSize		m_Bytes;

		VkDeviceMemory		m_hMemory;
	};
}