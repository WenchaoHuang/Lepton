/*************************************************************************
************************    VisualVk_Resource    *************************
*************************************************************************/
#pragma once

#include "LogicalDevice.h"

namespace Vk
{
	class CommandPool;
	class CommandQueue;
	class CommandBuffer;
	class PhysicalDevice;

	/*********************************************************************
	***************************    Resource    ***************************
	*********************************************************************/

	/**
	 *	@brief	Base class for Vulkan resource object.
	 */
	class Resource
	{

	public:

		//!	@brief	Initialize devices.
		Resource() : m_pDevice(sm_pLogicalDevice), m_pPhysDevice(sm_pPhysicalDevice) {}

		//!	@brief	Set current physical device and logical device.
		static void SetDevice(PhysicalDevice * pPhysicalDevice, LogicalDevice * pLogicalDevice)
		{
			sm_pPhysicalDevice = pPhysicalDevice;

			sm_pLogicalDevice = pLogicalDevice;
		}

	protected:

		LogicalDevice * const		m_pDevice;

		PhysicalDevice * const		m_pPhysDevice;

		static LogicalDevice *		sm_pLogicalDevice;

		static PhysicalDevice *		sm_pPhysicalDevice;
	};
}