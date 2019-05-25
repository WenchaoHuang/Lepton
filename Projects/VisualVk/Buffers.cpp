/*************************************************************************
*************************    VisualVk_Buffers    *************************
*************************************************************************/
#include "Signals.h"
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

	VkResult eResult = sm_pDevice->CreateBuffer(&CreateInfo, &hNewBuffer);

	if (eResult == VK_SUCCESS)
	{
		VkMemoryRequirements Requirements;

		sm_pDevice->GetBufferMemoryRequirements(hNewBuffer, &Requirements);

		eResult = m_Memory.Allocate(Requirements, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		if (eResult != VK_SUCCESS)
		{
			sm_pDevice->DestroyBuffer(hNewBuffer);
		}
		else
		{
			this->Release();

			sm_pDevice->BindBufferMemory(hNewBuffer, m_Memory, 0);

			m_hBuffer = hNewBuffer;

			m_Bytes = SizeBytes;
		}
	}

	return eResult;
}


VkResult HostVisibleBuffer::CopyFrom(HostVisibleBuffer * pSrcBuffer, VkDeviceSize SrcOffset, VkDeviceSize DstOffset, VkDeviceSize SizeBytes)
{
	if ((DstOffset + SizeBytes <= m_Bytes) && (SrcOffset + SizeBytes <= pSrcBuffer->m_Bytes))
	{
		CommandBuffer * pCommandBuffer = sm_pTransferCmdPool->AllocateCommandBuffer();

		VkBufferCopy BufferCopy = { SrcOffset, DstOffset, SizeBytes };

		pCommandBuffer->BeginRecord(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);

		pCommandBuffer->CmdCopyBuffer(m_hBuffer, pSrcBuffer->m_hBuffer, 1, &BufferCopy);

		pCommandBuffer->EndRecord();

		Fence TempFence;

		pCommandBuffer->Submit(TempFence);	TempFence.Wait();

		sm_pTransferCmdPool->FreeCommandBuffer(pCommandBuffer);

		return VK_SUCCESS;
	}
	else
	{
		return VK_ERROR_OUT_OF_DEVICE_MEMORY;
	}
}


VkResult HostVisibleBuffer::Write(const void * pHostData, VkDeviceSize OffsetBytes, VkDeviceSize SizeBytes)
{
	void * pData = nullptr;

	VkResult eResult = m_Memory.Map(&pData, OffsetBytes, SizeBytes);

	if (eResult == VK_SUCCESS)
	{
		std::memcpy(pData, pHostData, (size_t)SizeBytes);

		m_Memory.Unmap();
	}

	return eResult;
}


VkResult HostVisibleBuffer::Read(void * pHostData, VkDeviceSize OffsetBytes, VkDeviceSize SizeBytes)
{
	void * pData = nullptr;

	VkResult eResult = m_Memory.Map(&pData, OffsetBytes, SizeBytes);

	if (eResult == VK_SUCCESS)
	{
		std::memcpy(pHostData, pData, (size_t)SizeBytes);

		m_Memory.Unmap();
	}

	return eResult;
}


VkResult HostVisibleBuffer::SetZero(VkDeviceSize OffsetBytes, VkDeviceSize SizeBytes)
{
	void * pData = nullptr;

	VkResult eResult = m_Memory.Map(&pData, OffsetBytes, SizeBytes);

	if (eResult == VK_SUCCESS)
	{
		std::memset(pData, 0, (size_t)SizeBytes);

		m_Memory.Unmap();
	}

	return eResult;
}


void HostVisibleBuffer::Release() noexcept
{
	if (m_hBuffer != VK_NULL_HANDLE)
	{
		sm_pDevice->DestroyBuffer(m_hBuffer);

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

	VkResult eResult = sm_pDevice->CreateBuffer(&CreateInfo, &hNewBuffer);

	if (eResult == VK_SUCCESS)
	{
		VkMemoryRequirements Requirements;

		sm_pDevice->GetBufferMemoryRequirements(hNewBuffer, &Requirements);

		eResult = m_Memory.Allocate(Requirements, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

		if (eResult != VK_SUCCESS)
		{
			sm_pDevice->DestroyBuffer(hNewBuffer);
		}
		else
		{
			this->Release();

			sm_pDevice->BindBufferMemory(hNewBuffer, m_Memory, 0);

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
		sm_pDevice->DestroyBuffer(m_hBuffer);

		m_hBuffer = VK_NULL_HANDLE;

		m_Memory.Free();

		m_Bytes = 0;
	}
}


DeviceLocalBuffer::~DeviceLocalBuffer()
{
	this->Release();
}