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

		//!	@brief	Create buffer object.
		Buffer();

		//!	@brief	Destroy buffer object.
		~Buffer();

	public:

		//!	@brief	Convert to Vulkan handle.
		operator VkBuffer() const { return m_hBuffer; }

		//!	@brief	Memory copy from device to host.
		VkResult Read(void * pHostData, VkDeviceSize OffsetBytes, VkDeviceSize SizeBytes);

		//!	@brief	Memory copy from host to device.
		VkResult Write(const void * pHostData, VkDeviceSize OffsetBytes, VkDeviceSize SizeBytes);

		//!	@brief	Memory copy from device to device.
		VkResult CopyFrom(const Buffer * pSrcBuffer, VkDeviceSize SrcOffset, VkDeviceSize DstOffset, VkDeviceSize SizeBytes);

		//!	@brief	Filling data with 0.
		VkResult SetZero(VkDeviceSize OffsetBytes, VkDeviceSize SizeBytes);

		//!	@brief	If buffer handle is valid.
		VkBool32 IsEmpty() const { return m_hBuffer != VK_NULL_HANDLE; }

		//!	@brief	Return buffer size in bytes.
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
	****************************    Array    *****************************
	*********************************************************************/

	/**
	 *	@brief	Template for Vulkan buffer object.
	 */
	template<typename Type> class Array
	{

	public:

		//!	@brief	Resize array.
		VkResult Resize(VkDeviceSize Count)
		{
			return m_Buffer.Create(Count * sizeof(Type));
		}

		//!	@brief	Memory copy from device to host.
		VkResult Read(Type * pHostData, VkDeviceSize Offset, VkDeviceSize Count)
		{
			return m_Buffer.Read(pHostData, Offset * sizeof(Type), Count * sizeof(Type));
		}

		//!	@brief	Memory copy from host to device.
		VkResult Write(const void * pHostData, VkDeviceSize Offset, VkDeviceSize Count)
		{
			return m_Buffer.Write(pHostData, Offset * sizeof(Type), Count * sizeof(Type));
		}

		//!	@brief	Filling data with 0.
		VkResult SetZero(VkDeviceSize Offset, VkDeviceSize Count)
		{
			return m_Buffer.SetZero(Offset * sizeof(Type), Count * sizeof(Type));
		}

		//!	@brief	Return count of elements.
		VkDeviceSize Size() const { return m_Buffer.Bytes() / sizeof(Type); }

		//!	@brief	If array is empty.
		VkBool32 IsEmpty() const { return m_Buffer.IsEmpty(); }

		//!	@brief	Erase all.
		void Clear() noexcept { m_Buffer.Release(); }

	private:

		Buffer		m_Buffer;
	};
}