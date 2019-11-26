/*************************************************************************
***************************    Lava_Buffers    ***************************
*************************************************************************/

#include "Buffers.h"
#include "LogicalDevice.h"
#include "PhysicalDevice.h"

using namespace Lava;

/*************************************************************************
************************    HostVisibleBuffer    *************************
*************************************************************************/
HostVisibleBuffer::HostVisibleBuffer() : m_hBuffer(VK_NULL_HANDLE), m_Bytes(0)
{

}


HostVisibleBuffer::HostVisibleBuffer(const LogicalDevice * pLogicalDevice, VkDeviceSize size) : HostVisibleBuffer()
{
	this->Create(pLogicalDevice, size);
}


Result HostVisibleBuffer::Create(const LogicalDevice * pLogicalDevice, VkDeviceSize size)
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

	Result eResult = LAVA_RESULT_CAST(vkCreateBuffer(pLogicalDevice->GetHandle(), &CreateInfo, nullptr, &hNewBuffer));

	if (eResult == Result::eSuccess)
	{
		VkMemoryRequirements Requirements = {};

		vkGetBufferMemoryRequirements(pLogicalDevice->GetHandle(), hNewBuffer, &Requirements);

		eResult = m_Memory.Allocate(pLogicalDevice, Requirements, MemoryProperty::eHostVisible | MemoryProperty::eHostCoherent);

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
DeviceLocalBuffer::DeviceLocalBuffer() : m_hBuffer(VK_NULL_HANDLE)
{

}


Result DeviceLocalBuffer::Create(const LogicalDevice * pLogicalDevice, VkDeviceSize size)
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

	Result eResult = LAVA_RESULT_CAST(vkCreateBuffer(pLogicalDevice->GetHandle(), &CreateInfo, nullptr, &hNewBuffer));

	if (eResult == Result::eSuccess)
	{
		VkMemoryRequirements	Requirements = {};

		vkGetBufferMemoryRequirements(pLogicalDevice->GetHandle(), hNewBuffer, &Requirements);

		eResult = m_DeviceMemory.Allocate(pLogicalDevice, Requirements);

		if (eResult != Result::eSuccess)
		{
			vkDestroyBuffer(pLogicalDevice->GetHandle(), hNewBuffer, nullptr);
		}
		else
		{
			if (m_hBuffer != VK_NULL_HANDLE)
			{
				vkDestroyBuffer(m_DeviceMemory.GetDeviceHandle(), m_hBuffer, nullptr);
			}

			vkBindBufferMemory(pLogicalDevice->GetHandle(), hNewBuffer, m_DeviceMemory, 0);

			m_hBuffer = hNewBuffer;
		}
	}

	return eResult;
}


void DeviceLocalBuffer::Destroy()
{
	if (m_hBuffer != VK_NULL_HANDLE)
	{
		vkDestroyBuffer(m_DeviceMemory.GetDeviceHandle(), m_hBuffer, nullptr);

		m_hBuffer = VK_NULL_HANDLE;

		m_DeviceMemory.Free();
	}
}


DeviceLocalBuffer::~DeviceLocalBuffer()
{
	this->Destroy();
}