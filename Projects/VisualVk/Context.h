/*************************************************************************
*************************    VisualVk_Context    *************************
*************************************************************************/
#pragma once

#include "LogicalDevice.h"

namespace Vk
{
	class CommandBuffer;

	/*********************************************************************
	***************************    Context    ****************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan context.
	 */
	class Context
	{

	private:

		Context() {}

		~Context() {}

	public:

		static LogicalDevice * GetDevice() { return sm_pLogicalDevice; }

		static VkDevice GetDeviceHandle() { return *sm_pLogicalDevice; }

		static void SetDevice(LogicalDevice * pLogicalDevice)
		{
			sm_pLogicalDevice = pLogicalDevice;
		}

	private:

		static LogicalDevice *		sm_pLogicalDevice;
	};
}