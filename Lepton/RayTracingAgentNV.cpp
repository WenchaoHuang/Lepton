/*************************************************************************
*********************    Lepton_RayTracingAgentNV    *********************
*************************************************************************/

#include "LogicalDevice.h"
#include "RayTracingAgentNV.h"

using namespace Lepton;

/*************************************************************************
************************    RayTracingAgentNV    *************************
*************************************************************************/
RayTracingAgentNV::RayTracingAgentNV() : m_pLogicalDevice(nullptr)
{

}


Result RayTracingAgentNV::GetAuthorization(const LogicalDevice * pLogicalDevice)
{
	if (pLogicalDevice == nullptr)						return Result::eErrorInvalidDeviceHandle;
	if (!pLogicalDevice->IsReady())						return Result::eErrorInvalidDeviceHandle;

	m_pfnCmdTraceRays									= reinterpret_cast<PFN_vkCmdTraceRaysNV>(vkGetDeviceProcAddr(pLogicalDevice->Handle(), "vkCmdTraceRaysNV"));
	m_pfnCompileDeferred								= reinterpret_cast<PFN_vkCompileDeferredNV>(vkGetDeviceProcAddr(pLogicalDevice->Handle(), "vkCompileDeferredNV"));
	m_pfnCreateRayTracingPipelines						= reinterpret_cast<PFN_vkCreateRayTracingPipelinesNV>(vkGetDeviceProcAddr(pLogicalDevice->Handle(), "vkCreateRayTracingPipelinesNV"));
	m_pfnCreateAccelerationStructure					= reinterpret_cast<PFN_vkCreateAccelerationStructureNV>(vkGetDeviceProcAddr(pLogicalDevice->Handle(), "vkCreateAccelerationStructureNV"));
	m_pfnDestroyAccelerationStructure					= reinterpret_cast<PFN_vkDestroyAccelerationStructureNV>(vkGetDeviceProcAddr(pLogicalDevice->Handle(), "vkDestroyAccelerationStructureNV"));
	m_pfnCmdCopyAccelerationStructure					= reinterpret_cast<PFN_vkCmdCopyAccelerationStructureNV>(vkGetDeviceProcAddr(pLogicalDevice->Handle(), "vkCmdCopyAccelerationStructureNV"));
	m_pfnCmdBuildAccelerationStructure					= reinterpret_cast<PFN_vkCmdBuildAccelerationStructureNV>(vkGetDeviceProcAddr(pLogicalDevice->Handle(), "vkCmdBuildAccelerationStructureNV"));
	m_pfnGetAccelerationStructureHandle					= reinterpret_cast<PFN_vkGetAccelerationStructureHandleNV>(vkGetDeviceProcAddr(pLogicalDevice->Handle(), "vkGetAccelerationStructureHandleNV"));
	m_pfnGetRayTracingShaderGroupHandles				= reinterpret_cast<PFN_vkGetRayTracingShaderGroupHandlesNV>(vkGetDeviceProcAddr(pLogicalDevice->Handle(), "vkGetRayTracingShaderGroupHandlesNV"));
	m_pfnBindAccelerationStructureMemory				= reinterpret_cast<PFN_vkBindAccelerationStructureMemoryNV>(vkGetDeviceProcAddr(pLogicalDevice->Handle(), "vkBindAccelerationStructureMemoryNV"));
	m_pfnCmdWriteAccelerationStructuresProperties		= reinterpret_cast<PFN_vkCmdWriteAccelerationStructuresPropertiesNV>(vkGetDeviceProcAddr(pLogicalDevice->Handle(), "vkCmdWriteAccelerationStructuresPropertiesNV"));
	m_pfnGetAccelerationStructureMemoryRequirements		= reinterpret_cast<PFN_vkGetAccelerationStructureMemoryRequirementsNV>(vkGetDeviceProcAddr(pLogicalDevice->Handle(), "vkGetAccelerationStructureMemoryRequirementsNV"));

	if (m_pfnCmdTraceRays == nullptr)									return Result::eErrorFailedToGetProcessAddress;
	if (m_pfnCompileDeferred == nullptr)								return Result::eErrorFailedToGetProcessAddress;
	if (m_pfnCreateRayTracingPipelines == nullptr)						return Result::eErrorFailedToGetProcessAddress;
	if (m_pfnCreateAccelerationStructure == nullptr)					return Result::eErrorFailedToGetProcessAddress;
	if (m_pfnDestroyAccelerationStructure == nullptr)					return Result::eErrorFailedToGetProcessAddress;
	if (m_pfnCmdCopyAccelerationStructure == nullptr)					return Result::eErrorFailedToGetProcessAddress;
	if (m_pfnCmdBuildAccelerationStructure == nullptr)					return Result::eErrorFailedToGetProcessAddress;
	if (m_pfnGetAccelerationStructureHandle == nullptr)					return Result::eErrorFailedToGetProcessAddress;
	if (m_pfnGetRayTracingShaderGroupHandles == nullptr)				return Result::eErrorFailedToGetProcessAddress;
	if (m_pfnBindAccelerationStructureMemory == nullptr)				return Result::eErrorFailedToGetProcessAddress;
	if (m_pfnCmdWriteAccelerationStructuresProperties == nullptr)		return Result::eErrorFailedToGetProcessAddress;
	if (m_pfnGetAccelerationStructureMemoryRequirements == nullptr)		return Result::eErrorFailedToGetProcessAddress;

	m_pLogicalDevice = pLogicalDevice;

	return Result::eSuccess;
}


RayTracingAgentNV::~RayTracingAgentNV()
{

}