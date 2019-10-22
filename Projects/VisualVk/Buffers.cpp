/*************************************************************************
*************************    VisualVk_Buffers    *************************
*************************************************************************/

#include "Buffers.h"
#include "LogicalDevice.h"
#include "PhysicalDevice.h"

using namespace Vk;

/*************************************************************************
************************    HostVisibleBuffer    *************************
*************************************************************************/
HostVisibleBuffer::HostVisibleBuffer() : m_hBuffer(VK_NULL_HANDLE), m_Bytes(0)
{

}


HostVisibleBuffer::HostVisibleBuffer(LogicalDevice * pLogicalDevice, VkDeviceSize size) : HostVisibleBuffer()
{
	this->Create(pLogicalDevice, size);
}


Result HostVisibleBuffer::Create(LogicalDevice * pLogicalDevice, VkDeviceSize size)
{
	if (size == 0)							return Result::eErrorOutOfDeviceMemory;
	if (!pLogicalDevice->IsReady())			return Result::eErrorInvalidDeviceHandle;

	VkBufferCreateInfo						CreateInfo = {};
	CreateInfo.sType						= VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	CreateInfo.pNext						= nullptr;
	CreateInfo.flags						= 0;
	CreateInfo.size							= size;
	CreateInfo.usage						= 0x00001FFF;		//!	For all usages.
	CreateInfo.sharingMode					= VK_SHARING_MODE_EXCLUSIVE;
	CreateInfo.queueFamilyIndexCount		= 0;
	CreateInfo.pQueueFamilyIndices			= nullptr;

	VkBuffer hNewBuffer = VK_NULL_HANDLE;

	Result eResult = VK_RESULT_CAST(vkCreateBuffer(pLogicalDevice->GetHandle(), &CreateInfo, nullptr, &hNewBuffer));

	if (eResult == Result::eSuccess)
	{
		VkMemoryRequirements Requirements = {};

		vkGetBufferMemoryRequirements(pLogicalDevice->GetHandle(), hNewBuffer, &Requirements);

		uint32_t memoryTypeIndex = pLogicalDevice->GetPhysicalDevice()->GetMemoryTypeIndex(Requirements.memoryTypeBits, MemoryProperty::eHostVisible | MemoryProperty::eHostCoherent);

		eResult = m_Memory.Allocate(pLogicalDevice->GetHandle(), Requirements.size, memoryTypeIndex);

		if (eResult != Result::eSuccess)
		{
			vkDestroyBuffer(pLogicalDevice->GetHandle(), hNewBuffer, nullptr);
		}
		else
		{
			if (m_hBuffer != VK_NULL_HANDLE)
			{
				vkDestroyBuffer(m_Memory.GetDeviceHandle(), m_hBuffer, nullptr);
			}

			vkBindBufferMemory(pLogicalDevice->GetHandle(), hNewBuffer, m_Memory, 0);

			m_hBuffer = hNewBuffer;

			m_Bytes = size;
		}
	}

	return eResult;
}


Result HostVisibleBuffer::Write(const void * pHostData, VkDeviceSize offset, VkDeviceSize size)
{
	void * pBufferData = nullptr;

	Result eResult = m_Memory.Map(&pBufferData, offset, size);

	if (eResult == Result::eSuccess)
	{
		std::memcpy(pBufferData, pHostData, static_cast<size_t>(size));

		m_Memory.Unmap();
	}

	return eResult;
}


Result HostVisibleBuffer::Read(void * pHostData, VkDeviceSize offset, VkDeviceSize size)
{
	void * pBufferData = nullptr;

	Result eResult = m_Memory.Map(&pBufferData, offset, size);

	if (eResult == Result::eSuccess)
	{
		std::memcpy(pHostData, pBufferData, static_cast<size_t>(size));

		m_Memory.Unmap();
	}

	return eResult;
}


Result HostVisibleBuffer::SetZero(VkDeviceSize offset, VkDeviceSize size)
{
	void * pBufferData = nullptr;

	Result eResult = m_Memory.Map(&pBufferData, offset, size);

	if (eResult == Result::eSuccess)
	{
		std::memset(pBufferData, 0, static_cast<size_t>(size));

		m_Memory.Unmap();
	}

	return eResult;
}


void HostVisibleBuffer::Destroy()
{
	if (m_hBuffer != VK_NULL_HANDLE)
	{
		vkDestroyBuffer(m_Memory.GetDeviceHandle(), m_hBuffer, nullptr);

		m_hBuffer = VK_NULL_HANDLE;

		m_Memory.Free();

		m_Bytes = 0;
	}
}


HostVisibleBuffer::~HostVisibleBuffer()
{
	this->Destroy();
}


/*************************************************************************
************************    DeviceLocalBuffer    *************************
*************************************************************************/
DeviceLocalBuffer::DeviceLocalBuffer() : m_hBuffer(VK_NULL_HANDLE), m_Bytes(0)
{

}


Result DeviceLocalBuffer::Create(LogicalDevice * pLogicalDevice, VkDeviceSize size)
{
	if (size == 0)							return Result::eErrorOutOfDeviceMemory;
	if (!pLogicalDevice->IsReady())			return Result::eErrorInvalidDeviceHandle;

	VkBufferCreateInfo						CreateInfo = {};
	CreateInfo.sType						= VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	CreateInfo.pNext						= nullptr;
	CreateInfo.flags						= 0;
	CreateInfo.size							= size;
	CreateInfo.usage						= 0x00001FFF;		//!	For all usages.
	CreateInfo.sharingMode					= VK_SHARING_MODE_EXCLUSIVE;
	CreateInfo.queueFamilyIndexCount		= 0;
	CreateInfo.pQueueFamilyIndices			= nullptr;

	VkBuffer hNewBuffer = VK_NULL_HANDLE;

	Result eResult = VK_RESULT_CAST(vkCreateBuffer(pLogicalDevice->GetHandle(), &CreateInfo, nullptr, &hNewBuffer));

	if (eResult == Result::eSuccess)
	{
		VkMemoryRequirements Requirements = {};

		vkGetBufferMemoryRequirements(pLogicalDevice->GetHandle(), hNewBuffer, &Requirements);

		uint32_t memoryTypeIndex = pLogicalDevice->GetPhysicalDevice()->GetMemoryTypeIndex(Requirements.memoryTypeBits, MemoryProperty::eDeviceLocal);

		eResult = m_Memory.Allocate(pLogicalDevice->GetHandle(), Requirements.size, memoryTypeIndex);

		if (eResult != Result::eSuccess)
		{
			vkDestroyBuffer(pLogicalDevice->GetHandle(), hNewBuffer, nullptr);
		}
		else
		{
			if (m_hBuffer != VK_NULL_HANDLE)
			{
				vkDestroyBuffer(m_Memory.GetDeviceHandle(), m_hBuffer, nullptr);
			}

			vkBindBufferMemory(pLogicalDevice->GetHandle(), hNewBuffer, m_Memory, 0);

			m_hBuffer = hNewBuffer;

			m_Bytes = size;
		}
	}

	return eResult;
}


void DeviceLocalBuffer::Destroy()
{
	if (m_hBuffer != VK_NULL_HANDLE)
	{
		vkDestroyBuffer(m_Memory.GetDeviceHandle(), m_hBuffer, nullptr);

		m_hBuffer = VK_NULL_HANDLE;

		m_Memory.Free();

		m_Bytes = 0;
	}
}


DeviceLocalBuffer::~DeviceLocalBuffer()
{
	this->Destroy();
}