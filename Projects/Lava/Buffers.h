/*************************************************************************
***************************    Lava_Buffers    ***************************
*************************************************************************/
#pragma once

#include "DeviceMemory.h"

namespace Lava
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

		//!	@brief	Create and initialize immediately.
		explicit HostVisibleBuffer(const LogicalDevice * pLogicalDevice, VkDeviceSize size);

		//!	@brief	Destroy buffer object.
		~HostVisibleBuffer();

	public:

		//!	@brief	Convert to VkBuffer.
		operator VkBuffer() const { return m_hBuffer; }

		//!	@brief	Return Vulkan type of this object.
		VkBuffer GetHandle() const { return m_hBuffer; }

		//!	@brief	If buffer handle is valid.
		bool IsEmpty() const { return m_hBuffer != VK_NULL_HANDLE; }

		//!	@brief	Memory copy from device to host.
		Result Read(void * pHostData, VkDeviceSize offset, VkDeviceSize size);

		//!	@brief	Create a new buffer object.
		Result Create(const LogicalDevice * pLogicalDevice, VkDeviceSize size);

		//!	@brief	Memory copy from host to device.
		Result Write(const void * pHostData, VkDeviceSize offset, VkDeviceSize size);

		//!	@brief	Filling data with 0.
		Result SetZero(VkDeviceSize offset, VkDeviceSize size);

		//!	@brief	Return the buffer size in bytes.
		VkDeviceSize Bytes() const { return m_Bytes; }

		//!	@brief	Destroy the buffer.
		void Destroy();

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

		//!	@brief	Convert to VkBuffer.
		operator VkBuffer() const { return m_hBuffer; }

		//!	@brief	Return Vulkan type of this object.
		VkBuffer GetHandle() const { return m_hBuffer; }

		//!	@brief	Return the buffer size in bytes.
		VkDeviceSize Size() const { return m_DeviceMemory.Size(); }

		//!	@brief	If buffer handle is valid.
		bool IsEmpty() const { return m_hBuffer != VK_NULL_HANDLE; }

		//!	@brief	Resize buffer.
		Result Create(const LogicalDevice * pLogicalDevice, VkDeviceSize sizeBytes);

		//!	@brief	Destroy the buffer.
		void Destroy();

	private:

		VkBuffer				m_hBuffer;

		DeviceLocalMemory		m_DeviceMemory;
	};
}