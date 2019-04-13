/*************************************************************************
************************    VisualVk_Resource    *************************
*************************************************************************/
#include "Resource.h"

using namespace Vk;

Instance * Resource::sm_pInstance = nullptr;

LogicalDevice * Resource::sm_pDevice = nullptr;

PhysicalDevice * Resource::sm_pPhyDevice = nullptr;

CommandQueue * Resource::sm_pComputeQueue = nullptr;

CommandQueue * Resource::sm_pGraphicsQueue = nullptr;

CommandQueue * Resource::sm_pTransferQueue = nullptr;

CommandPool * Resource::sm_pComputeCmdPool = nullptr;

CommandPool * Resource::sm_pGraphicsCmdPool = nullptr;

CommandPool * Resource::sm_pTransferCmdPool = nullptr;

/*************************************************************************
*****************************    Resource    *****************************
*************************************************************************/
void Resource::SetupDevice(PhysicalDevice * pPhysicalDevice, LogicalDevice * pLogicalDevice)
{
	sm_pInstance = Instance::GetCurrent();

	sm_pPhyDevice = pPhysicalDevice;

	sm_pDevice = pLogicalDevice;
}