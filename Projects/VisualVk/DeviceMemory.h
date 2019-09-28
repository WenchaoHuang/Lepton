/*************************************************************************
**********************    VisualVk_DeviceMemory    ***********************
*************************************************************************/
#pragma once

#include "Vulkan.h"

namespace Vk
{
	/*********************************************************************
	*************************    DeviceMemory    *************************
	*********************************************************************/

	/**
	 *	@brief	Wrapper for Vulkan device memory object.
	 */
	class DeviceMemory
	{
		VK_UNIQUE_RESOURCE(DeviceMemory)

	public:

		//!	@brief	Create memory object.
		DeviceMemory();

		//!	@brief	Create and initialize immediately.
		explicit DeviceMemory(VkDevice hDevice, VkDeviceSize allocationSize, uint32_t memoryTypeIndex);

		//!	@brief	Destroy memory object.
		~DeviceMemory();

	public:

		//!	@brief	Query the current commitment for a VkDeviceMemory.
		VkDeviceSize GetCommitment() const;

		//!	@brief	Invalidate range of mapped memory object.
		Result Invalidate(VkDeviceSize offset, VkDeviceSize size);

		//!	@brief	Allocate device memory.
		Result Allocate(VkDevice hDevice, VkDeviceSize allocationSize, uint32_t memoryTypeIndex);

		//!	@brief	Map memory into application address space.
		Result Map(void ** ppData, VkDeviceSize offset, VkDeviceSize size);

		//!	@brief	Flush mapped memory range.
		Result Flush(VkDeviceSize OffsetBytes, VkDeviceSize SizeBytes);

		//!	@brief	Unmap previously mapped memory.
		void Unmap() { vkUnmapMemory(m_hDevice, m_hDeviceMemory); }

		//!	@brief	Return the size of device memory.
		VkDeviceSize Size() const { return m_SizeBytes; }

		//!	@brief	Free memory.
		void Free();

	private:

		VkDeviceSize		m_SizeBytes;
	};
}