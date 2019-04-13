/*************************************************************************
*************************    VisualVk_Buffer    **************************
*************************************************************************/
#include "Signals.h"
#include "Buffer.h"

using namespace Vk;

/*************************************************************************
******************************    Buffer    ******************************
*************************************************************************/
Buffer::Buffer() : m_Bytes(0), m_hBuffer(VK_NULL_HANDLE)
{

}


VkResult Buffer::Create(VkDeviceSize SizeBytes)
{
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
			sm_pDevice->BindBufferMemory(hNewBuffer, m_Memory, 0);

			sm_pDevice->DestroyBuffer(m_hBuffer);

			m_hBuffer = hNewBuffer;

			m_Bytes = SizeBytes;
		}
	}

	return eResult;
}


VkResult Buffer::CopyFrom(const Buffer * pSrcBuffer, VkDeviceSize SrcOffset, VkDeviceSize DstOffset, VkDeviceSize SizeBytes)
{
	if ((DstOffset + SizeBytes <= m_Bytes) && (SrcOffset + SizeBytes <= pSrcBuffer->m_Bytes))
	{
		CommandBuffer * pCommandBuffer = sm_pTransferCmdPool->AllocateCommandBuffer();

		VkBufferCopy BufferCopy = { SrcOffset, DstOffset, SizeBytes };

		pCommandBuffer->Begin(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);

		pCommandBuffer->CmdCopyBuffer(m_hBuffer, pSrcBuffer->m_hBuffer, 1, &BufferCopy);

		pCommandBuffer->End();

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


VkResult Buffer::Write(const void * pHostData, VkDeviceSize OffsetBytes, VkDeviceSize SizeBytes)
{
	void * pDevData = nullptr;

	if (OffsetBytes + SizeBytes > m_Bytes)		return VK_ERROR_OUT_OF_DEVICE_MEMORY;

	VkResult eResult = m_Memory.Map(&pDevData, OffsetBytes, SizeBytes);

	if (eResult == VK_SUCCESS)
	{
		memcpy(pDevData, pHostData, (size_t)SizeBytes);

		m_Memory.Unmap();
	}

	return eResult;
}


VkResult Buffer::Read(void * pHostData, VkDeviceSize OffsetBytes, VkDeviceSize SizeBytes)
{
	void * pDevData = nullptr;

	if (OffsetBytes + SizeBytes > m_Bytes)		return VK_ERROR_OUT_OF_DEVICE_MEMORY;

	VkResult eResult = m_Memory.Map(&pDevData, OffsetBytes, SizeBytes);

	if (eResult == VK_SUCCESS)
	{
		memcpy(pHostData, pDevData, (size_t)SizeBytes);

		m_Memory.Unmap();
	}

	return eResult;
}


void Buffer::Release() noexcept
{
	m_Memory.Free();

	sm_pDevice->DestroyBuffer(m_hBuffer);

	m_hBuffer = VK_NULL_HANDLE;

	m_Bytes = 0;
}


Buffer::~Buffer()
{
	sm_pDevice->DestroyBuffer(m_hBuffer);
}