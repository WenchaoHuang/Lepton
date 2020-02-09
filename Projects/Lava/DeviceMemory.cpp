/*************************************************************************
************************    Lava_DeviceMemory    *************************
*************************************************************************/

#include "DeviceMemory.h"
#include "LogicalDevice.h"
#include "PhysicalDevice.h"

using namespace Lava;

/*************************************************************************
***************************    DeviceMemory    ***************************
*************************************************************************/
DeviceMemory::UniqueHandle::UniqueHandle(VkDevice hDevice, VkDeviceMemory hDeviceMemory, VkDeviceSize allocateSize)
	: m_hDevice(hDevice), m_hDeviceMemory(hDeviceMemory), m_AllocateSize(allocateSize)
{

}


Result DeviceMemory::Allocate(const LogicalDevice * pLogicalDevice, VkMemoryRequirements memoryRequirements, Flags<MemoryProperty> eProperties)
{
	if (pLogicalDevice == nullptr)			return Result::eErrorInvalidDeviceHandle;
	if (!pLogicalDevice->IsReady())			return Result::eErrorInvalidDeviceHandle;

	uint32_t memoryTypeIndex = pLogicalDevice->GetPhysicalDevice()->GetMemoryTypeIndex(memoryRequirements.memoryTypeBits, eProperties);

	if (memoryTypeIndex == LAVA_INVALID_INDEX)		return Result::eErrorInvalidMemoryTypeBits;

	VkMemoryAllocateInfo				AllocateInfo = {};
	AllocateInfo.sType					= VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	AllocateInfo.pNext					= nullptr;
	AllocateInfo.allocationSize			= memoryRequirements.size;
	AllocateInfo.memoryTypeIndex		= memoryTypeIndex;

	VkDeviceMemory hDeviceMemory = VK_NULL_HANDLE;

	Result eResult = LAVA_RESULT_CAST(vkAllocateMemory(pLogicalDevice->Handle(), &AllocateInfo, nullptr, &hDeviceMemory));

	if (eResult == Result::eSuccess)
	{
		m_spUniqueHandle = std::make_shared<UniqueHandle>(pLogicalDevice->Handle(), hDeviceMemory, AllocateInfo.allocationSize);
	}

	return eResult;
}


Result DeviceMemory::Invalidate(VkDeviceSize offset, VkDeviceSize size) const
{
	VkMappedMemoryRange		MemoryRange = {};
	MemoryRange.sType		= VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
	MemoryRange.pNext		= nullptr;
	MemoryRange.memory		= m_spUniqueHandle->m_hDeviceMemory;
	MemoryRange.offset		= offset;
	MemoryRange.size		= size;

	return LAVA_RESULT_CAST(vkInvalidateMappedMemoryRanges(m_spUniqueHandle->m_hDevice, 1, &MemoryRange));
}


Result DeviceMemory::Flush(VkDeviceSize offset, VkDeviceSize size) const
{
	VkMappedMemoryRange		MemoryRange = {};
	MemoryRange.sType		= VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
	MemoryRange.pNext		= nullptr;
	MemoryRange.memory		= m_spUniqueHandle->m_hDeviceMemory;
	MemoryRange.offset		= offset;
	MemoryRange.size		= size;

	return LAVA_RESULT_CAST(vkFlushMappedMemoryRanges(m_spUniqueHandle->m_hDevice, 1, &MemoryRange));
}


Result DeviceMemory::Map(void ** ppData, VkDeviceSize offset, VkDeviceSize size) const
{
	return LAVA_RESULT_CAST(vkMapMemory(m_spUniqueHandle->m_hDevice, m_spUniqueHandle->m_hDeviceMemory, offset, size, 0, ppData));
}


DeviceMemory::UniqueHandle::~UniqueHandle() noexcept
{
	if (m_hDevice != VK_NULL_HANDLE)
	{
		vkFreeMemory(m_hDevice, m_hDeviceMemory, nullptr);
	}
}


/*************************************************************************
************************    DeviceLocalMemory    *************************
*************************************************************************/
DeviceLocalMemory::UniqueHandle::UniqueHandle(VkDevice hDevice, VkDeviceMemory hDeviceMemory, VkDeviceSize allocationSize)
	: m_hDevice(hDevice), m_hDeviceMemory(hDeviceMemory), m_SizeBytes(allocationSize)
{

}


Result DeviceLocalMemory::Allocate(const LogicalDevice * pLogicalDevice, VkMemoryRequirements memoryRequirements)
{
	if (pLogicalDevice == nullptr)			return Result::eErrorInvalidDeviceHandle;
	if (!pLogicalDevice->IsReady())			return Result::eErrorInvalidDeviceHandle;

	uint32_t memoryTypeIndex = pLogicalDevice->GetPhysicalDevice()->GetMemoryTypeIndex(memoryRequirements.memoryTypeBits, MemoryProperty::eDeviceLocal);

	if (memoryTypeIndex == LAVA_INVALID_INDEX)		return Result::eErrorInvalidMemoryTypeBits;

	VkMemoryAllocateInfo				AllocateInfo = {};
	AllocateInfo.sType					= VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	AllocateInfo.pNext					= nullptr;
	AllocateInfo.allocationSize			= memoryRequirements.size;
	AllocateInfo.memoryTypeIndex		= memoryTypeIndex;

	VkDeviceMemory hDeviceMemory = VK_NULL_HANDLE;

	Result eResult = LAVA_RESULT_CAST(vkAllocateMemory(pLogicalDevice->Handle(), &AllocateInfo, nullptr, &hDeviceMemory));

	if (eResult == Result::eSuccess)
	{
		m_spUniqueHandle = std::make_shared<UniqueHandle>(pLogicalDevice->Handle(), hDeviceMemory, memoryRequirements.size);
	}

	return eResult;
}


DeviceLocalMemory::UniqueHandle::~UniqueHandle() noexcept
{
	if (m_hDeviceMemory != VK_NULL_HANDLE)
	{
		vkFreeMemory(m_hDevice, m_hDeviceMemory, nullptr);
	}
}