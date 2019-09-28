/*************************************************************************
**********************    VisualVk_DeviceMemory    ***********************
*************************************************************************/
#include "DeviceMemory.h"

using namespace Vk;

/*************************************************************************
***************************    DeviceMemory    ***************************
*************************************************************************/
DeviceMemory::DeviceMemory() : m_hDevice(VK_NULL_HANDLE), m_hDeviceMemory(VK_NULL_HANDLE), m_SizeBytes(0)
{

}


DeviceMemory::DeviceMemory(VkDevice hDevice, VkDeviceSize allocationSize, uint32_t memoryTypeIndex) : DeviceMemory()
{
	this->Allocate(hDevice, allocationSize, memoryTypeIndex);
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
			this->Free();

			m_SizeBytes = allocationSize;

			m_hDeviceMemory = hMemory;

			m_hDevice = hDevice;
		}
	}

	return VK_RESULT_CAST(eResult);
}


Result DeviceMemory::Invalidate(VkDeviceSize offset, VkDeviceSize size)
{
	VkMappedMemoryRange		MemoryRange = {};
	MemoryRange.sType		= VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
	MemoryRange.pNext		= nullptr;
	MemoryRange.memory		= m_hDeviceMemory;
	MemoryRange.offset		= offset;
	MemoryRange.size		= size;

	return VK_RESULT_CAST(vkInvalidateMappedMemoryRanges(m_hDevice, 1, &MemoryRange));
}


Result DeviceMemory::Flush(VkDeviceSize offset, VkDeviceSize size)
{
	VkMappedMemoryRange		MemoryRange = {};
	MemoryRange.sType		= VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
	MemoryRange.pNext		= nullptr;
	MemoryRange.memory		= m_hDeviceMemory;
	MemoryRange.offset		= offset;
	MemoryRange.size		= size;

	return VK_RESULT_CAST(vkFlushMappedMemoryRanges(m_hDevice, 1, &MemoryRange));
}


Result DeviceMemory::Map(void ** ppData, VkDeviceSize offset, VkDeviceSize size)
{
	return VK_RESULT_CAST(vkMapMemory(m_hDevice, m_hDeviceMemory, offset, size, 0, ppData));
}


VkDeviceSize DeviceMemory::GetCommitment() const
{
	VkDeviceSize committedMemoryInBytes = 0;

	vkGetDeviceMemoryCommitment(m_hDevice, m_hDeviceMemory, &committedMemoryInBytes);

	return committedMemoryInBytes;
}


void DeviceMemory::Free()
{
	if (m_hDeviceMemory != VK_NULL_HANDLE)
	{
		vkFreeMemory(m_hDevice, m_hDeviceMemory, nullptr);

		m_hDeviceMemory = VK_NULL_HANDLE;

		m_hDevice = VK_NULL_HANDLE;

		m_SizeBytes = 0;
	}
}


DeviceMemory::~DeviceMemory()
{
	this->Free();
}