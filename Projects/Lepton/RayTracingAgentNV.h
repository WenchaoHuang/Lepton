/*************************************************************************
*********************    Lepton_RayTracingAgentNV    *********************
*************************************************************************/
#pragma once

#include "Vulkan.h"

namespace Lepton
{

	class RayTracingAgentNV
	{
		LAVA_NONCOPYABLE(RayTracingAgentNV)

	public:

		RayTracingAgentNV();

		~RayTracingAgentNV();

	public:

		Result GetAuthorization(const LogicalDevice * pLogicalDevice);

		


	private:

		const LogicalDevice *									m_pLogicalDevice;
		PFN_vkCmdTraceRaysNV									m_pfnCmdTraceRays;
		PFN_vkCompileDeferredNV									m_pfnCompileDeferred;
		PFN_vkCreateRayTracingPipelinesNV						m_pfnCreateRayTracingPipelines;
		PFN_vkCreateAccelerationStructureNV						m_pfnCreateAccelerationStructure;
		PFN_vkDestroyAccelerationStructureNV					m_pfnDestroyAccelerationStructure;
		PFN_vkCmdCopyAccelerationStructureNV					m_pfnCmdCopyAccelerationStructure;
		PFN_vkCmdBuildAccelerationStructureNV					m_pfnCmdBuildAccelerationStructure;
		PFN_vkGetAccelerationStructureHandleNV					m_pfnGetAccelerationStructureHandle;
		PFN_vkGetRayTracingShaderGroupHandlesNV					m_pfnGetRayTracingShaderGroupHandles;
		PFN_vkBindAccelerationStructureMemoryNV					m_pfnBindAccelerationStructureMemory;
		PFN_vkCmdWriteAccelerationStructuresPropertiesNV		m_pfnCmdWriteAccelerationStructuresProperties;
		PFN_vkGetAccelerationStructureMemoryRequirementsNV		m_pfnGetAccelerationStructureMemoryRequirements;
	};
}