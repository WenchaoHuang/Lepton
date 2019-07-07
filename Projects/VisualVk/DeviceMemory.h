/*************************************************************************
**********************    VisualVk_DeviceMemory    ***********************
*************************************************************************/
#pragma once

#include "Flags.h"
#include "Resource.h"

namespace Vk
{
	/*********************************************************************
	************************    MemoryProperty    ************************
	*********************************************************************/

	/**
	 *	@brief	Bitmask specifying properties for a memory type.
	 */
	enum class MemoryProperty : VkFlags
	{
		eProtected				= VK_MEMORY_PROPERTY_PROTECTED_BIT,
		eHostCached				= VK_MEMORY_PROPERTY_HOST_CACHED_BIT,
		eDeviceLocal			= VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
		eHostVisible			= VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
		eHostCoherent			= VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		eLazilyAllocated		= VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT
	};

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

		//!	@brief	Convert to VkDeviceMemory handle.
		operator VkDeviceMemory() const { return m_hMemory; }

		//!	@brief	Allocate memory.
		VkResult Allocate(VkDeviceSize SizeBytes, uint32_t MemoryTypeBits, Flags<MemoryProperty> PropertyFlags);

		//!	@brief	Map memory into application address space.
		VkResult Map(void ** ppData, VkDeviceSize OffsetBytes, VkDeviceSize SizeBytes);

		//!	@brief	Invalidate memory.
		VkResult Invalidate(VkDeviceSize OffsetBytes, VkDeviceSize SizeBytes);

		//!	@brief	Flush memory.
		VkResult Flush(VkDeviceSize OffsetBytes, VkDeviceSize SizeBytes);

		//!	@brief	Return the size of device memory.
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