/*************************************************************************
*************************    VisualVk_Buffers    *************************
*************************************************************************/
#include "Buffers.h"

using namespace Vk;

/*************************************************************************
************************    HostVisibleBuffer    *************************
*************************************************************************/
HostVisibleBuffer::HostVisibleBuffer() : m_Bytes(0), m_hBuffer(VK_NULL_HANDLE)
{

}


VkResult HostVisibleBuffer::Create(VkDeviceSize SizeBytes)
{
	if (SizeBytes == 0)					return VK_ERROR_OUT_OF_DEVICE_MEMORY;
	else if (SizeBytes == m_Bytes)		return VK_SUCCESS;

	VkBufferCreateInfo					CreateInfo = {};
	CreateInfo.sType					= VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	CreateInfo.pNext					= nullptr;
	CreateInfo.flags					= 0;
	CreateInfo.size						= SizeBytes;
	CreateInfo.usage					= 0x00001FFF;		//!	For all usages.
	CreateInfo.sharingMode				= VK_SHARING_MODE_EXCLUSIVE;
	CreateInfo.queueFamilyIndexCount	= 0;
	CreateInfo.pQueueFamilyIndices		= nullptr;

	VkBuffer hNewBuffer = VK_NULL_HANDLE;

	VkResult eResult = m_pDevice->CreateBuffer(&CreateInfo, &hNewBuffer);

	if (eResult == VK_SUCCESS)
	{
		VkMemoryRequirements Requirements;

		m_pDevice->GetBufferMemoryRequirements(hNewBuffer, &Requirements);

		eResult = m_Memory.Allocate(Requirements, MemoryProperty::eHostVisible | MemoryProperty::eHostCoherent);

		if (eResult != VK_SUCCESS)
		{
			m_pDevice->DestroyBuffer(hNewBuffer);
		}
		else
		{
			this->Release();

			m_pDevice->BindBufferMemory(hNewBuffer, m_Memory, 0);

			m_hBuffer = hNewBuffer;

			m_Bytes = SizeBytes;
		}
	}

	return eResult;
}


VkResult HostVisibleBuffer::Write(const void * pHostData, VkDeviceSize OffsetBytes, VkDeviceSize SizeBytes)
{
	void * pBufferData = nullptr;

	VkResult eResult = m_Memory.Map(&pBufferData, OffsetBytes, SizeBytes);

	if (eResult == VK_SUCCESS)
	{
		std::memcpy(pBufferData, pHostData, (size_t)SizeBytes);

		m_Memory.Unmap();
	}

	return eResult;
}


VkResult HostVisibleBuffer::Read(void * pHostData, VkDeviceSize OffsetBytes, VkDeviceSize SizeBytes)
{
	void * pBufferData = nullptr;

	VkResult eResult = m_Memory.Map(&pBufferData, OffsetBytes, SizeBytes);

	if (eResult == VK_SUCCESS)
	{
		std::memcpy(pHostData, pBufferData, (size_t)SizeBytes);

		m_Memory.Unmap();
	}

	return eResult;
}


VkResult HostVisibleBuffer::SetZero(VkDeviceSize OffsetBytes, VkDeviceSize SizeBytes)
{
	void * pBufferData = nullptr;

	VkResult eResult = m_Memory.Map(&pBufferData, OffsetBytes, SizeBytes);

	if (eResult == VK_SUCCESS)
	{
		std::memset(pBufferData, 0, (size_t)SizeBytes);

		m_Memory.Unmap();
	}

	return eResult;
}


void HostVisibleBuffer::Release() noexcept
{
	if (m_hBuffer != VK_NULL_HANDLE)
	{
		m_pDevice->DestroyBuffer(m_hBuffer);

		m_hBuffer = VK_NULL_HANDLE;

		m_Memory.Free();

		m_Bytes = 0;
	}
}


HostVisibleBuffer::~HostVisibleBuffer()
{
	this->Release();
}


/*************************************************************************
************************    DeviceLocalBuffer    *************************
*************************************************************************/
DeviceLocalBuffer::DeviceLocalBuffer() : m_Bytes(0), m_hBuffer(VK_NULL_HANDLE)
{

}


VkResult DeviceLocalBuffer::Create(VkDeviceSize SizeBytes)
{
	if (SizeBytes == 0)					return VK_ERROR_OUT_OF_DEVICE_MEMORY;
	else if (SizeBytes == m_Bytes)		return VK_SUCCESS;

	VkBufferCreateInfo					CreateInfo = {};
	CreateInfo.sType					= VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	CreateInfo.pNext					= nullptr;
	CreateInfo.flags					= 0;
	CreateInfo.size						= SizeBytes;
	CreateInfo.usage					= 0x00001FFF;		//!	For all usages.
	CreateInfo.sharingMode				= VK_SHARING_MODE_EXCLUSIVE;
	CreateInfo.queueFamilyIndexCount	= 0;
	CreateInfo.pQueueFamilyIndices		= nullptr;

	VkBuffer hNewBuffer = VK_NULL_HANDLE;

	VkResult eResult = m_pDevice->CreateBuffer(&CreateInfo, &hNewBuffer);

	if (eResult == VK_SUCCESS)
	{
		VkMemoryRequirements Requirements;

		m_pDevice->GetBufferMemoryRequirements(hNewBuffer, &Requirements);

		eResult = m_Memory.Allocate(Requirements, MemoryProperty::eDeviceLocal);

		if (eResult != VK_SUCCESS)
		{
			m_pDevice->DestroyBuffer(hNewBuffer);
		}
		else
		{
			this->Release();

			m_pDevice->BindBufferMemory(hNewBuffer, m_Memory, 0);

			m_hBuffer = hNewBuffer;

			m_Bytes = SizeBytes;
		}
	}

	return eResult;
}


void DeviceLocalBuffer::Release() noexcept
{
	if (m_hBuffer != VK_NULL_HANDLE)
	{
		m_pDevice->DestroyBuffer(m_hBuffer);

		m_hBuffer = VK_NULL_HANDLE;

		m_Memory.Free();

		m_Bytes = 0;
	}
}


DeviceLocalBuffer::~DeviceLocalBuffer()
{
	this->Release();
}