/*************************************************************************
*************************    VisualVk_Signals    *************************
*************************************************************************/
#include "Signals.h"

using namespace Vk;

/*************************************************************************
******************************    Fence    *******************************
*************************************************************************/
Fence::Fence() : m_hDevice(VK_NULL_HANDLE), m_hFence(VK_NULL_HANDLE)
{

}


Fence::Fence(VkDevice hDevice) : Fence()
{
	this->Create(hDevice);
}


Result Fence::Create(VkDevice hDevice)
{
	VkResult eResult = VK_ERROR_INVALID_EXTERNAL_HANDLE;

	if (hDevice != VK_NULL_HANDLE)
	{
		VkFenceCreateInfo		CreateInfo = {};
		CreateInfo.sType		= VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		CreateInfo.pNext		= nullptr;
		CreateInfo.flags		= 0;

		VkFence hFence = VK_NULL_HANDLE;

		eResult = vkCreateFence(hDevice, &CreateInfo, nullptr, &hFence);

		if (eResult == VK_SUCCESS)
		{
			this->Destroy();

			m_hFence = hFence;

			m_hDevice = hDevice;
		}
	}

	return VK_RESULT_CAST(eResult);
}


void Fence::Destroy()
{
	if (m_hFence != VK_NULL_HANDLE)
	{
		vkDestroyFence(m_hDevice, m_hFence, nullptr);

		m_hDevice = VK_NULL_HANDLE;

		m_hFence = VK_NULL_HANDLE;
	}
}


Fence::~Fence()
{
	this->Destroy();
}


/*************************************************************************
****************************    Semaphore    *****************************
*************************************************************************/
Semaphore::Semaphore() : m_hDevice(VK_NULL_HANDLE), m_hSemaphore(VK_NULL_HANDLE)
{

}


Semaphore::Semaphore(VkDevice hDevice) : Semaphore()
{
	this->Create(hDevice);
}


Result Semaphore::Create(VkDevice hDevice)
{
	VkResult eResult = VK_ERROR_INVALID_EXTERNAL_HANDLE;

	if (hDevice != VK_NULL_HANDLE)
	{
		VkSemaphoreCreateInfo		CreateInfo = {};
		CreateInfo.sType			= VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
		CreateInfo.pNext			= nullptr;
		CreateInfo.flags			= 0;
		
		VkSemaphore hSemaphore = VK_NULL_HANDLE;

		eResult = vkCreateSemaphore(hDevice, &CreateInfo, nullptr, &hSemaphore);

		if (eResult == VK_SUCCESS)
		{
			this->Destroy();

			m_hDevice = hDevice;

			m_hSemaphore = hSemaphore;
		}
	}

	return VK_RESULT_CAST(eResult);
}


void Semaphore::Destroy()
{
	if (m_hSemaphore != VK_NULL_HANDLE)
	{
		vkDestroySemaphore(m_hDevice, m_hSemaphore, nullptr);

		m_hSemaphore = VK_NULL_HANDLE;

		m_hDevice = VK_NULL_HANDLE;
	}
}


Semaphore::~Semaphore()
{
	this->Destroy();
}


/*************************************************************************
******************************    Event    *******************************
*************************************************************************/
Event::Event() : m_hDevice(VK_NULL_HANDLE), m_hEvent(VK_NULL_HANDLE)
{

}


Event::Event(VkDevice hDevice) : Event()
{
	this->Create(hDevice);
}


Result Event::Create(VkDevice hDevice)
{
	VkResult eResult = VK_ERROR_INVALID_EXTERNAL_HANDLE;

	if (hDevice != VK_NULL_HANDLE)
	{
		VkEventCreateInfo		CreateInfo = {};
		CreateInfo.sType		= VK_STRUCTURE_TYPE_EVENT_CREATE_INFO;
		CreateInfo.pNext		= nullptr;
		CreateInfo.flags		= 0;
		
		VkEvent hEvent = VK_NULL_HANDLE;

		eResult = vkCreateEvent(hDevice, &CreateInfo, nullptr, &hEvent);

		if (eResult == VK_SUCCESS)
		{
			this->Destroy();

			m_hEvent = hEvent;

			m_hDevice = hDevice;
		}
	}

	return VK_RESULT_CAST(eResult);
}


void Event::Destroy()
{
	if (m_hEvent != VK_NULL_HANDLE)
	{
		vkDestroyEvent(m_hDevice, m_hEvent, nullptr);

		m_hDevice = VK_NULL_HANDLE;

		m_hEvent = VK_NULL_HANDLE;
	}
}


Event::~Event()
{
	this->Destroy();
}