/*************************************************************************
*************************    VisualVk_Signals    *************************
*************************************************************************/
#include "Signals.h"

using namespace Vk;

/*************************************************************************
******************************    Fence    *******************************
*************************************************************************/
Fence::Fence() : m_hFence(VK_NULL_HANDLE)
{
	VkFenceCreateInfo CreateInfo = { VK_STRUCTURE_TYPE_FENCE_CREATE_INFO, nullptr, 0 };

	sm_pDevice->CreateFence(&CreateInfo, &m_hFence);
}


Fence::~Fence()
{
	sm_pDevice->DestroyFence(m_hFence);
}


/*************************************************************************
****************************    Semaphore    *****************************
*************************************************************************/
Semaphore::Semaphore() : m_hSemaphore(VK_NULL_HANDLE)
{
	VkSemaphoreCreateInfo CreateInfo = { VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO, nullptr, 0 };

	sm_pDevice->CreateSemaphore(&CreateInfo, &m_hSemaphore);
}


Semaphore::~Semaphore()
{
	sm_pDevice->DestroySemaphore(m_hSemaphore);
}


/*************************************************************************
******************************    Event    *******************************
*************************************************************************/
Event::Event() : m_hEvent(VK_NULL_HANDLE)
{
	VkEventCreateInfo CreateInfo = { VK_STRUCTURE_TYPE_EVENT_CREATE_INFO, nullptr, 0 };

	sm_pDevice->CreateEvent(&CreateInfo, &m_hEvent);
}


Event::~Event()
{
	sm_pDevice->DestroyEvent(m_hEvent);
}