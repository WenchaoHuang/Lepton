/*************************************************************************
************************    VisualVk_Resource    *************************
*************************************************************************/
#pragma once

#include "Instance.h"
#include "LogicalDevice.h"
#include "CommandBuffer.h"
#include "PhysicalDevice.h"

namespace Vk
{
	/*********************************************************************
	***************************    Resource    ***************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan resource object.
	 */
	class Resource
	{

	protected:

		Resource() {}

		Resource(const Resource&) = delete;

		void operator=(const Resource&) = delete;

	public:

		static void SetupDevice(PhysicalDevice * pPhysicalDevice, LogicalDevice * pLogicalDevice);

	protected:

		static Instance * sm_pInstance;

		static LogicalDevice * sm_pDevice;

		static PhysicalDevice *	sm_pPhyDevice;

		static CommandQueue * sm_pComputeQueue;

		static CommandQueue * sm_pGraphicsQueue;

		static CommandQueue * sm_pTransferQueue;

		static CommandPool * sm_pComputeCmdPool;

		static CommandPool * sm_pGraphicsCmdPool;

		static CommandPool * sm_pTransferCmdPool;
	};
}