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
	class VKAPI Buffer : private Resource
	{

	public:

		//!	@brief	Create buffer object.
		Buffer();

		//!	@brief	Destroy buffer object.
		~Buffer();

	public:

		//!	@brief	Convert to handle.
		operator VkBuffer() { return m_hBuffer; }

		//!	@brief	Return buffer size in bytes.
		VkDeviceSize Bytes() const { return m_Bytes; }

		//!	@brief	If buffer handle is valid.
		VkBool32 IsValid() const { return m_hBuffer != VK_NULL_HANDLE; }

		//!	@brief	Memory copy from device to device.
		VkResult CopyFrom(const Buffer * pSrcBuffer, VkDeviceSize SrcOffset, VkDeviceSize DstOffset, VkDeviceSize SizeBytes);

		//!	@brief	Memory copy from host to device.
		VkResult Write(const void * pHostData, VkDeviceSize OffsetBytes, VkDeviceSize SizeBytes);

		//!	@brief	Memory copy from device to host.
		VkResult Read(void * pHostData, VkDeviceSize OffsetBytes, VkDeviceSize SizeBytes);

		void * GetMappedPointer()
		{
			void * pDevData = nullptr;

			m_Memory.Map(&pDevData, 0, m_Bytes);

			return pDevData;
		}

		//!	@brief	Resize buffer.
		VkResult Create(VkDeviceSize SizeBytes);

		//!	@brief	Clear buffer.
		void Release() noexcept;

	private:

		VkBuffer			m_hBuffer;

		DeviceMemory		m_Memory;

		VkDeviceSize		m_Bytes;
	};
}