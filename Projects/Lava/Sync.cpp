/*************************************************************************
****************************    Lava_Sync    *****************************
*************************************************************************/

#include "Sync.h"

using namespace Lava;

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
	if (hDevice == VK_NULL_HANDLE)		return Result::eErrorInvalidDeviceHandle;

	VkFenceCreateInfo		CreateInfo = {};
	CreateInfo.sType		= VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	CreateInfo.pNext		= nullptr;
	CreateInfo.flags		= 0;

	VkFence hFence = VK_NULL_HANDLE;

	Result eResult = LAVA_RESULT_CAST(vkCreateFence(hDevice, &CreateInfo, nullptr, &hFence));

	if (eResult == Result::eSuccess)
	{
		this->Destroy();

		m_hFence = hFence;

		m_hDevice = hDevice;
	}

	return eResult;
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
	if (hDevice == VK_NULL_HANDLE)		return Result::eErrorInvalidDeviceHandle;

	VkSemaphoreCreateInfo		CreateInfo;
	CreateInfo.sType			= VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	CreateInfo.pNext			= nullptr;
	CreateInfo.flags			= 0;

	VkSemaphore hSemaphore = VK_NULL_HANDLE;

	Result eResult = LAVA_RESULT_CAST(vkCreateSemaphore(hDevice, &CreateInfo, nullptr, &hSemaphore));

	if (eResult == Result::eSuccess)
	{
		this->Destroy();

		m_hDevice = hDevice;

		m_hSemaphore = hSemaphore;
	}

	return eResult;
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
	if (hDevice == VK_NULL_HANDLE)		return Result::eErrorInvalidDeviceHandle;

	VkEventCreateInfo		CreateInfo;
	CreateInfo.sType		= VK_STRUCTURE_TYPE_EVENT_CREATE_INFO;
	CreateInfo.pNext		= nullptr;
	CreateInfo.flags		= 0;

	VkEvent hEvent = VK_NULL_HANDLE;

	Result eResult = LAVA_RESULT_CAST(vkCreateEvent(hDevice, &CreateInfo, nullptr, &hEvent));

	if (eResult == Result::eSuccess)
	{
		this->Destroy();

		m_hEvent = hEvent;

		m_hDevice = hDevice;
	}

	return eResult;
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