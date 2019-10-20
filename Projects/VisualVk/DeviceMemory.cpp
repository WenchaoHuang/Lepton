/*************************************************************************
**********************    VisualVk_DeviceMemory    ***********************
*************************************************************************/
#include "DeviceMemory.h"

using namespace Vk;

/*************************************************************************
***************************    DeviceMemory    ***************************
*************************************************************************/
DeviceMemory::UniqueHandle::UniqueHandle(VkDevice hDevice, VkDeviceMemory hDeviceMemory, VkDeviceSize allocateSize)
	: m_hDevice(hDevice), m_hDeviceMemory(hDeviceMemory), m_AllocateSize(allocateSize)
{

}


Result DeviceMemory::Allocate(VkDevice hDevice, VkDeviceSize allocationSize, uint32_t memoryTypeIndex)
{
	VkResult eResult = VK_ERROR_INVALID_EXTERNAL_HANDLE;

	if (hDevice != VK_NULL_HANDLE)
	{
		VkMemoryAllocateInfo				AllocateInfo = {};
		AllocateInfo.sType					= VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		AllocateInfo.pNext					= nullptr;
		AllocateInfo.allocationSize			= allocationSize;
		AllocateInfo.memoryTypeIndex		= memoryTypeIndex;

		VkDeviceMemory hMemory = VK_NULL_HANDLE;

		eResult = vkAllocateMemory(hDevice, &AllocateInfo, nullptr, &hMemory);

		if (eResult == VK_SUCCESS)
		{
			m_spHandle = std::make_shared<UniqueHandle>(hDevice, hMemory, allocationSize);
		}
	}

	return VK_RESULT_CAST(eResult);
}


Result DeviceMemory::Invalidate(VkDeviceSize offset, VkDeviceSize size) const
{
	VkMappedMemoryRange		MemoryRange = {};
	MemoryRange.sType		= VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
	MemoryRange.pNext		= nullptr;
	MemoryRange.memory		= m_spHandle->m_hDeviceMemory;
	MemoryRange.offset		= offset;
	MemoryRange.size		= size;

	return VK_RESULT_CAST(vkInvalidateMappedMemoryRanges(m_spHandle->m_hDevice, 1, &MemoryRange));
}


Result DeviceMemory::Flush(VkDeviceSize offset, VkDeviceSize size) const
{
	VkMappedMemoryRange		MemoryRange = {};
	MemoryRange.sType		= VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
	MemoryRange.pNext		= nullptr;
	MemoryRange.memory		= m_spHandle->m_hDeviceMemory;
	MemoryRange.offset		= offset;
	MemoryRange.size		= size;

	return VK_RESULT_CAST(vkFlushMappedMemoryRanges(m_spHandle->m_hDevice, 1, &MemoryRange));
}


Result DeviceMemory::Map(void ** ppData, VkDeviceSize offset, VkDeviceSize size) const
{
	return VK_RESULT_CAST(vkMapMemory(m_spHandle->m_hDevice, m_spHandle->m_hDeviceMemory, offset, size, 0, ppData));
}


DeviceMemory::UniqueHandle::~UniqueHandle() noexcept
{
	if (m_hDevice != VK_NULL_HANDLE)
	{
		vkFreeMemory(m_hDevice, m_hDeviceMemory, nullptr);
	}
}