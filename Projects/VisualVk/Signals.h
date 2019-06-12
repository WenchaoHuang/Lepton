/*************************************************************************
*************************    VisualVk_Signals    *************************
*************************************************************************/
#pragma once

#include "Resource.h"

#define VK_DEFAULT_TIMEOUT			100000000000L		//!	100 seconds.

namespace Vk
{
	/*********************************************************************
	****************************    Fence    *****************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan fence object.
	 */
	class Fence : private Resource
	{

	public:

		//!	@brief	Create fence object.
		Fence();

		//!	@brief	Destroy fence object.
		~Fence();

	public:

		//!	@brief	Convert to VkFence handle.
		operator VkFence() const { return m_hFence; }

		//!	@brief	If fence handle is valid.
		VkBool32 IsValid() const { return m_hFence != VK_NULL_HANDLE; }

		//!	@brief	Reset to non-signaled state.
		VkResult Reset() { return m_pDevice->ResetFences(1, &m_hFence); }

		//!	@brief	Return the status of fence.
		VkResult GetStatus() { return m_pDevice->GetFenceStatus(m_hFence); }

		//!	@brief	Wait for fence to become signaled.
		VkResult Wait(uint64_t Timeout = VK_DEFAULT_TIMEOUT)
		{
			return m_pDevice->WaitForFences(1, &m_hFence, VK_TRUE, Timeout);
		}

	private:

		VkFence		m_hFence;
	};

	/*********************************************************************
	**************************    Semaphore    ***************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan semaphore object.
	 */
	class Semaphore : private Resource
	{

	public:

		//!	@brief	Create semaphore object.
		Semaphore();

		//!	@brief	Destroy semaphore object.
		~Semaphore();

	public:

		//!	@brief	Convert to VkSemaphore handle.
		operator VkSemaphore() const { return m_hSemaphore; }

		//!	@brief	If semaphore handle is valid.
		VkBool32 IsValid() const { return m_hSemaphore != VK_NULL_HANDLE; }

	private:

		VkSemaphore		m_hSemaphore;
	};

	/*********************************************************************
	****************************    Event    *****************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan event object.
	 */
	class Event : private Resource
	{

	public:

		//!	@brief	Create event object.
		Event();

		//!	@brief	Destroy event object.
		~Event();

	public:

		//!	@brief	Convert to VkEvent handle.
		operator VkEvent() const { return m_hEvent; }

		//!	@brief	If event handle is valid.
		VkBool32 IsValid() const { return m_hEvent != VK_NULL_HANDLE; }

		//!	@brief	Retrieve the status of event.
		VkResult GetStatus() { return m_pDevice->GetEventStatus(m_hEvent); }

		//!	@brief	Set event to signaled state.
		VkResult SetSignaled() { return m_pDevice->SetEvent(m_hEvent); }

		//!	@brief	Reset event to non-signaled state.
		VkResult Reset() { return m_pDevice->ResetEvent(m_hEvent); }

	private:

		VkEvent		m_hEvent;
	};
}