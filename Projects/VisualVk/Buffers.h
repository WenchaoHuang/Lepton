/*************************************************************************
*************************    VisualVk_Buffers    *************************
*************************************************************************/
#pragma once

#include "DeviceMemory.h"

namespace Vk
{
	/*********************************************************************
	**********************    HostVisibleBuffer    ***********************
	*********************************************************************/

	/**
	 *	@brief	Vulkan host-visible buffer object.
	 */
	class HostVisibleBuffer
	{

	public:

		//!	@brief	Create buffer object.
		HostVisibleBuffer();

		//!	@brief	Create buffer object and allocate memory.
		HostVisibleBuffer(VkDeviceSize SizeBytes) : HostVisibleBuffer() { this->Create(SizeBytes); }

		//!	@brief	Destroy buffer object.
		~HostVisibleBuffer();

	public:

		//!	@brief	Convert to VkBuffer handle.
		operator VkBuffer() const { return m_hBuffer; }

		//!	@brief	Filling data with 0.
		VkResult SetZero(VkDeviceSize OffsetBytes, VkDeviceSize SizeBytes);

		//!	@brief	Memory copy from device to host.
		VkResult Read(void * pHostData, VkDeviceSize OffsetBytes, VkDeviceSize SizeBytes);

		//!	@brief	Memory copy from host to device.
		VkResult Write(const void * pHostData, VkDeviceSize OffsetBytes, VkDeviceSize SizeBytes);

		//!	@brief	If buffer handle is valid.
		VkBool32 IsEmpty() const { return m_hBuffer != VK_NULL_HANDLE; }

		//!	@brief	Return the buffer size in bytes.
		VkDeviceSize Bytes() const { return m_Bytes; }

		//!	@brief	Resize buffer.
		VkResult Create(VkDeviceSize SizeBytes);

		//!	@brief	Clear buffer.
		void Release() noexcept;

	private:

		VkBuffer			m_hBuffer;

		DeviceMemory		m_Memory;

		VkDeviceSize		m_Bytes;
	};

	/*********************************************************************
	**********************    DeviceLocalBuffer    ***********************
	*********************************************************************/

	/**
	 *	@brief	Vulkan device-local buffer object (device local).
	 */
	class DeviceLocalBuffer
	{

	public:

		//!	@brief	Create buffer object.
		DeviceLocalBuffer();

		//!	@brief	Destroy buffer object.
		~DeviceLocalBuffer();

	public:

		//!	@brief	Convert to VkBuffer handle.
		operator VkBuffer() const { return m_hBuffer; }

		//!	@brief	If buffer handle is valid.
		VkBool32 IsEmpty() const { return m_hBuffer != VK_NULL_HANDLE; }

		//!	@brief	Return the buffer size in bytes.
		VkDeviceSize Bytes() const { return m_Bytes; }

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