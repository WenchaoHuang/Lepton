/*************************************************************************
*************************    VisualVk_Buffer    **************************
*************************************************************************/
#include "Signals.h"
#include "Buffer.h"

using namespace Vk;

/*************************************************************************
****************************    HostBuffer    ****************************
*************************************************************************/
HostBuffer::HostBuffer() : m_Bytes(0), m_pData(nullptr), m_hBuffer(VK_NULL_HANDLE)
{

}


VkResult HostBuffer::Create(VkDeviceSize SizeBytes)
{
	if (SizeBytes == 0)					return VK_ERROR_OUT_OF_DEVICE_MEMORY;
	else if (SizeBytes == m_Bytes)		return VK_SUCCESS;

	VkBufferCreateInfo					CreateInfo = {};
	CreateInfo.sType					= VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	CreateInfo.pNext					= nullptr;
	CreateInfo.flags					= 0;
	CreateInfo.size						= SizeBytes;
	CreateInfo.usage					= 0x00001FFF;	//!	For all usages.
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


VkResult HostBuffer::CopyFrom(const HostBuffer * pSrcBuffer, VkDeviceSize SrcOffset, VkDeviceSize DstOffset, VkDeviceSize SizeBytes)
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


VkResult HostBuffer::Write(const void * pHostData, VkDeviceSize OffsetBytes, VkDeviceSize SizeBytes)
{
	if (OffsetBytes + SizeBytes > m_Bytes)		return VK_ERROR_OUT_OF_DEVICE_MEMORY;

	VkResult eResult = m_Memory.Map(&m_pData, OffsetBytes, SizeBytes);

	if (eResult == VK_SUCCESS)
	{
		std::memcpy(m_pData, pHostData, (size_t)SizeBytes);

		m_Memory.Unmap();
	}

	return eResult;
}


VkResult HostBuffer::Read(void * pHostData, VkDeviceSize OffsetBytes, VkDeviceSize SizeBytes)
{
	if (OffsetBytes + SizeBytes > m_Bytes)		return VK_ERROR_OUT_OF_DEVICE_MEMORY;

	VkResult eResult = m_Memory.Map(&m_pData, OffsetBytes, SizeBytes);

	if (eResult == VK_SUCCESS)
	{
		std::memcpy(pHostData, m_pData, (size_t)SizeBytes);

		m_Memory.Unmap();
	}

	return eResult;
}


VkResult HostBuffer::SetZero(VkDeviceSize OffsetBytes, VkDeviceSize SizeBytes)
{
	if (OffsetBytes + SizeBytes > m_Bytes)		return VK_ERROR_OUT_OF_DEVICE_MEMORY;

	VkResult eResult = m_Memory.Map(&m_pData, OffsetBytes, SizeBytes);

	if (eResult == VK_SUCCESS)
	{
		std::memset((void*)((size_t)m_pData + OffsetBytes), 0, (size_t)SizeBytes);

		m_Memory.Unmap();
	}

	return eResult;
}


void HostBuffer::Release() noexcept
{
	if (m_hBuffer != VK_NULL_HANDLE)
	{
		sm_pDevice->DestroyBuffer(m_hBuffer);

		m_hBuffer = VK_NULL_HANDLE;

		m_pData = nullptr;

		m_Memory.Free();

		m_Bytes = 0;
	}
}


HostBuffer::~HostBuffer()
{
	this->Release();
}


/*************************************************************************
***************************    DeviceBuffer    ***************************
*************************************************************************/
DeviceBuffer::DeviceBuffer() : m_Bytes(0), m_hBuffer(VK_NULL_HANDLE)
{

}


VkResult DeviceBuffer::Create(VkDeviceSize SizeBytes)
{
	if (SizeBytes == 0)					return VK_ERROR_OUT_OF_DEVICE_MEMORY;
	else if (SizeBytes == m_Bytes)		return VK_SUCCESS;

	VkBufferCreateInfo					CreateInfo = {};
	CreateInfo.sType					= VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	CreateInfo.pNext					= nullptr;
	CreateInfo.flags					= 0;
	CreateInfo.size						= SizeBytes;
	CreateInfo.usage					= 0x00001FFF;	//!	For all usages.
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


void DeviceBuffer::Release() noexcept
{
	if (m_hBuffer != VK_NULL_HANDLE)
	{
		sm_pDevice->DestroyBuffer(m_hBuffer);

		m_hBuffer = VK_NULL_HANDLE;

		m_Memory.Free();

		m_Bytes = 0;
	}
}


DeviceBuffer::~DeviceBuffer()
{
	this->Release();
}