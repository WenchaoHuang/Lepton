/*************************************************************************
**********************    VisualVk_DeviceMemory    ***********************
*************************************************************************/
#include "PhysicalDevice.h"
#include "DeviceMemory.h"

using namespace Vk;

/*************************************************************************
***************************    DeviceMemory    ***************************
*************************************************************************/
DeviceMemory::DeviceMemory() : m_Bytes(0), m_hMemory(VK_NULL_HANDLE)
{

}


VkResult DeviceMemory::Allocate(VkDeviceSize SizeBytes, uint32_t MemoryTypeBits, Flags<MemoryProperty> PropertyFlags)
{
	uint32_t MemoryTypeIndex = m_pPhysDevice->GetMemoryTypeIndex(MemoryTypeBits, PropertyFlags);

	if (MemoryTypeIndex == VK_INVALID_INDEX)		return VK_ERROR_FORMAT_NOT_SUPPORTED;

	VkMemoryAllocateInfo				AllocateInfo = {};
	AllocateInfo.sType					= VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	AllocateInfo.pNext					= nullptr;
	AllocateInfo.allocationSize			= SizeBytes;
	AllocateInfo.memoryTypeIndex		= MemoryTypeIndex;

	VkDeviceMemory hMemory = VK_NULL_HANDLE;

	VkResult eResult = m_pDevice->AllocateMemory(&AllocateInfo, &hMemory);

	if (eResult == VK_SUCCESS)
	{
		this->Free();

		m_hMemory = hMemory;

		m_Bytes = SizeBytes;
	}

	return eResult;
}


VkResult DeviceMemory::Map(void ** ppData, VkDeviceSize OffsetBytes, VkDeviceSize SizeBytes)
{
	if (m_hMemory == VK_NULL_HANDLE)
	{
		return VK_ERROR_INVALID_EXTERNAL_HANDLE;
	}
	else if (OffsetBytes + SizeBytes > m_Bytes)
	{
		return VK_ERROR_OUT_OF_DEVICE_MEMORY;
	}
	else
	{
		return m_pDevice->MapMemory(m_hMemory, OffsetBytes, SizeBytes, ppData);
	}
}


VkResult DeviceMemory::Invalidate(VkDeviceSize OffsetBytes, VkDeviceSize SizeBytes)
{
	if (m_hMemory == VK_NULL_HANDLE)
	{
		return VK_ERROR_INVALID_EXTERNAL_HANDLE;
	}
	else if (OffsetBytes + SizeBytes > m_Bytes)
	{
		return VK_ERROR_OUT_OF_DEVICE_MEMORY;
	}
	else
	{
		VkMappedMemoryRange		MemoryRange;
		MemoryRange.sType		= VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
		MemoryRange.pNext		= nullptr;
		MemoryRange.memory		= m_hMemory;
		MemoryRange.offset		= OffsetBytes;
		MemoryRange.size		= SizeBytes;

		return m_pDevice->InvalidateMappedMemoryRanges(1, &MemoryRange);
	}
}


VkResult DeviceMemory::Flush(VkDeviceSize OffsetBytes, VkDeviceSize SizeBytes)
{
	if (m_hMemory == VK_NULL_HANDLE)
	{
		return VK_ERROR_INVALID_EXTERNAL_HANDLE;
	}
	else if (OffsetBytes + SizeBytes > m_Bytes)
	{
		return VK_ERROR_OUT_OF_DEVICE_MEMORY;
	}
	else
	{
		VkMappedMemoryRange		MemoryRange;
		MemoryRange.sType		= VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
		MemoryRange.pNext		= nullptr;
		MemoryRange.memory		= m_hMemory;
		MemoryRange.offset		= OffsetBytes;
		MemoryRange.size		= SizeBytes;

		return m_pDevice->FlushMappedMemoryRanges(1, &MemoryRange);
	}
}


void DeviceMemory::Unmap() noexcept
{
	if (m_hMemory != VK_NULL_HANDLE)
	{
		m_pDevice->UnmapMemory(m_hMemory);
	}
}


void DeviceMemory::Free() noexcept
{
	if (m_hMemory != VK_NULL_HANDLE)
	{
		m_pDevice->FreeMemory(m_hMemory);

		m_hMemory = VK_NULL_HANDLE;

		m_Bytes = 0;
	}
}


DeviceMemory::~DeviceMemory()
{
	this->Free();
}