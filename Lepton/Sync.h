/*************************************************************************
***************************    Lepton_Sync    ****************************
*************************************************************************/
#pragma once

#include "Vulkan.h"

namespace Lepton
{
	/*********************************************************************
	****************************    Fence    *****************************
	*********************************************************************/

	/**
	 *	@brief	Wrapper for Vulkan fence object.
	 */
	class Fence
	{
		LAVA_UNIQUE_RESOURCE(Fence)

	public:

		//!	@brief	Create fence object.
		Fence();

		//!	@brief	Create and initialize immediately.
		explicit Fence(VkDevice hDevice);

		//!	@brief	Destroy fence object.
		~Fence();

	public:

		//!	@brief	Create a new fence object.
		Result Create(VkDevice hDevice);

		//!	@brief	Reset to non-signaled state.
		Result Reset() { return LAVA_RESULT_CAST(vkResetFences(m_hDevice, 1, &m_hFence)); }

		//!	@brief	Return the status of fence.
		Result Status() const { return LAVA_RESULT_CAST(vkGetFenceStatus(m_hDevice, m_hFence)); }

		//!	@brief	Wait for fence to become signaled.
		Result Wait(uint64_t timeout = LAVA_DEFAULT_TIMEOUT) const { return LAVA_RESULT_CAST(vkWaitForFences(m_hDevice, 1, &m_hFence, VK_TRUE, timeout)); }

		//!	@brief	Destroy the fence.
		void Destroy();
	};

	/*********************************************************************
	**************************    Semaphore    ***************************
	*********************************************************************/

	/**
	 *	@brief	Wrapper for Vulkan semaphore object.
	 */
	class Semaphore
	{
		LAVA_UNIQUE_RESOURCE(Semaphore)

	public:

		//!	@brief	Create semaphore object.
		Semaphore();

		//!	@brief	Create and initialize immediately.
		explicit Semaphore(VkDevice hDevice);

		//!	@brief	Destroy semaphore object.
		~Semaphore();

	public:

		//!	@brief	Create a new semaphore object.
		Result Create(VkDevice hDevice);

		//!	@brief	Destroy the semaphore.
		void Destroy();
	};

	/*********************************************************************
	****************************    Event    *****************************
	*********************************************************************/

	/**
	 *	@brief	Wrapper for Vulkan event object.
	 */
	class Event
	{
		LAVA_UNIQUE_RESOURCE(Event)

	public:

		//!	@brief	Create event object.
		Event();

		//!	@brief	Create and initialize immediately.
		explicit Event(VkDevice hDevice);

		//!	@brief	Destroy event object.
		~Event();

	public:

		//!	@brief	Create a new event object.
		Result Create(VkDevice hDevice);

		//!	@brief	Set event to signaled state.
		Result Signal() { return LAVA_RESULT_CAST(vkSetEvent(m_hDevice, m_hEvent)); }

		//!	@brief	Reset event to non-signaled state.
		Result Reset() { return LAVA_RESULT_CAST(vkResetEvent(m_hDevice, m_hEvent)); }

		//!	@brief	Retrieve the status of event.
		Result Status() const { return LAVA_RESULT_CAST(vkGetEventStatus(m_hDevice, m_hEvent)); }

		//!	@brief	Destroy the event.
		void Destroy();
	};
}