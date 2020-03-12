/*************************************************************************
*******************    Lava_AccelerationStructureNV    *******************
*************************************************************************/

#include "LogicalDevice.h"
#include "PhysicalDevice.h"
#include "AccelerationStructureNV.h"

using namespace Lava;

/*************************************************************************
**********************    TopLevelAccelStructNV    ***********************
*************************************************************************/
TopLevelAccelStructNV::UniqueHandle::UniqueHandle(DeviceLocalMemory deviceMemory, VkAccelerationStructureNV hAccelStruct,  uint64_t handle)
	: m_DeviceMemory(deviceMemory), m_hAccelStruct(hAccelStruct), m_Handle(handle)
{

}


Result TopLevelAccelStructNV::Create(const LogicalDevice * pLogicalDevice, uint32_t instanceCount)
{
	if (pLogicalDevice == nullptr)							return Result::eErrorInvalidDeviceHandle;
	if (!pLogicalDevice->IsReady())							return Result::eErrorInvalidDeviceHandle;

	PFN_vkCreateAccelerationStructureNV						pfnCreateAccelStruct = nullptr;
	PFN_vkDestroyAccelerationStructureNV					pfnDestroyAccelStruct = nullptr;
	PFN_vkGetAccelerationStructureHandleNV					pfnGetAccelStructHandle = nullptr;
	PFN_vkBindAccelerationStructureMemoryNV					pfnBindAccelStructMem = nullptr;
	PFN_vkGetAccelerationStructureMemoryRequirementsNV		pfnGetAccelStructMemReq = nullptr;

	pfnCreateAccelStruct		= (PFN_vkCreateAccelerationStructureNV)vkGetDeviceProcAddr(pLogicalDevice->Handle(), "vkCreateAccelerationStructureNV");
	pfnDestroyAccelStruct		= (PFN_vkDestroyAccelerationStructureNV)vkGetDeviceProcAddr(pLogicalDevice->Handle(), "vkDestroyAccelerationStructureNV");
	pfnBindAccelStructMem		= (PFN_vkBindAccelerationStructureMemoryNV)vkGetDeviceProcAddr(pLogicalDevice->Handle(), "vkBindAccelerationStructureMemoryNV");
	pfnGetAccelStructHandle		= (PFN_vkGetAccelerationStructureHandleNV)vkGetDeviceProcAddr(pLogicalDevice->Handle(), "vkGetAccelerationStructureHandleNV");
	pfnGetAccelStructMemReq		= (PFN_vkGetAccelerationStructureMemoryRequirementsNV)vkGetDeviceProcAddr(pLogicalDevice->Handle(), "vkGetAccelerationStructureMemoryRequirementsNV");

	if (!pfnCreateAccelStruct)					return Result::eErrorFailedToGetProcessAddress;
	if (!pfnBindAccelStructMem)					return Result::eErrorFailedToGetProcessAddress;
	if (!pfnGetAccelStructHandle)				return Result::eErrorFailedToGetProcessAddress;
	if (!pfnGetAccelStructMemReq)				return Result::eErrorFailedToGetProcessAddress;

	VkAccelerationStructureCreateInfoNV			CreateInfo = {};
	CreateInfo.sType							= VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_NV;
	CreateInfo.pNext							= nullptr;
	CreateInfo.compactedSize					= 0;
	CreateInfo.info.sType						= VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_INFO_NV;
	CreateInfo.info.pNext						= nullptr;
	CreateInfo.info.type						= VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_NV;
	CreateInfo.info.flags						= 0;
	CreateInfo.info.instanceCount				= instanceCount;
	CreateInfo.info.geometryCount				= 0;
	CreateInfo.info.pGeometries					= nullptr;

	VkAccelerationStructureNV hAccelerationStructure = VK_NULL_HANDLE;

	Result eResult = LAVA_RESULT_CAST(pfnCreateAccelStruct(pLogicalDevice->Handle(), &CreateInfo, nullptr, &hAccelerationStructure));

	if (eResult == Result::eSuccess)
	{
		DeviceLocalMemory	deviceMemory;

		VkAccelerationStructureMemoryRequirementsInfoNV		RequirementsInfo = {};
		RequirementsInfo.sType								= VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_INFO_NV;
		RequirementsInfo.pNext								= nullptr;
		RequirementsInfo.type								= VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_OBJECT_NV;
		RequirementsInfo.accelerationStructure				= hAccelerationStructure;

		VkMemoryRequirements2		Requirements = {};
		Requirements.sType			= VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2;
		Requirements.pNext			= nullptr;

		pfnGetAccelStructMemReq(pLogicalDevice->Handle(), &RequirementsInfo, &Requirements);

		eResult = deviceMemory.Allocate(pLogicalDevice, Requirements.memoryRequirements);

		if (eResult == Result::eSuccess)
		{
			VkBindAccelerationStructureMemoryInfoNV		MemoryInfo = {};
			MemoryInfo.sType							= VK_STRUCTURE_TYPE_BIND_ACCELERATION_STRUCTURE_MEMORY_INFO_NV;
			MemoryInfo.pNext							= nullptr;
			MemoryInfo.accelerationStructure			= hAccelerationStructure;
			MemoryInfo.memory							= deviceMemory;
			MemoryInfo.memoryOffset						= 0;
			MemoryInfo.deviceIndexCount					= 0;
			MemoryInfo.pDeviceIndices					= nullptr;

			eResult = LAVA_RESULT_CAST(pfnBindAccelStructMem(pLogicalDevice->Handle(), 1, &MemoryInfo));

			if (eResult == Result::eSuccess)
			{
				uint64_t handle = 0;

				eResult = LAVA_RESULT_CAST(pfnGetAccelStructHandle(pLogicalDevice->Handle(), hAccelerationStructure, sizeof(uint64_t), &handle));

				if (eResult == Result::eSuccess)
				{
					m_spUniqueHandle = std::make_shared<UniqueHandle>(deviceMemory, hAccelerationStructure, handle);

					return Result::eSuccess;
				}
			}
		}

		pfnDestroyAccelStruct(pLogicalDevice->Handle(), hAccelerationStructure, nullptr);
	}

	return eResult;
}


TopLevelAccelStructNV::UniqueHandle::~UniqueHandle() noexcept
{
	if (m_hAccelStruct != VK_NULL_HANDLE)
	{
		PFN_vkDestroyAccelerationStructureNV pfnDestroyAccelStruct = nullptr;

		pfnDestroyAccelStruct = (PFN_vkDestroyAccelerationStructureNV)vkGetDeviceProcAddr(m_DeviceMemory.GetDeviceHandle(), "vkDestroyAccelerationStructureNV");

		pfnDestroyAccelStruct(m_DeviceMemory.GetDeviceHandle(), m_hAccelStruct, nullptr);
	}
}


/*************************************************************************
*********************    BottomLevelAccelStructNV    *********************
*************************************************************************/
BottomLevelAccelStructNV::UniqueHandle::UniqueHandle(DeviceLocalMemory deviceMemory, VkAccelerationStructureNV hAccelStruct, uint64_t handle)
	: m_DeviceMemory(deviceMemory), m_hAccelStruct(hAccelStruct), m_Handle(handle)
{

}


Result BottomLevelAccelStructNV::Create(const LogicalDevice * pLogicalDevice, ArrayProxy<GeometryNV> pGeometries)
{
	if (pLogicalDevice == nullptr)							return Result::eErrorInvalidDeviceHandle;
	if (!pLogicalDevice->IsReady())							return Result::eErrorInvalidDeviceHandle;

	PFN_vkCreateAccelerationStructureNV						pfnCreateAccelStruct = nullptr;
	PFN_vkDestroyAccelerationStructureNV					pfnDestroyAccelStruct = nullptr;
	PFN_vkGetAccelerationStructureHandleNV					pfnGetAccelStructHandle = nullptr;
	PFN_vkBindAccelerationStructureMemoryNV					pfnBindAccelStructMem = nullptr;
	PFN_vkGetAccelerationStructureMemoryRequirementsNV		pfnGetAccelStructMemReq = nullptr;

	pfnCreateAccelStruct		= (PFN_vkCreateAccelerationStructureNV)vkGetDeviceProcAddr(pLogicalDevice->Handle(), "vkCreateAccelerationStructureNV");
	pfnDestroyAccelStruct		= (PFN_vkDestroyAccelerationStructureNV)vkGetDeviceProcAddr(pLogicalDevice->Handle(), "vkDestroyAccelerationStructureNV");
	pfnBindAccelStructMem		= (PFN_vkBindAccelerationStructureMemoryNV)vkGetDeviceProcAddr(pLogicalDevice->Handle(), "vkBindAccelerationStructureMemoryNV");
	pfnGetAccelStructHandle		= (PFN_vkGetAccelerationStructureHandleNV)vkGetDeviceProcAddr(pLogicalDevice->Handle(), "vkGetAccelerationStructureHandleNV");
	pfnGetAccelStructMemReq		= (PFN_vkGetAccelerationStructureMemoryRequirementsNV)vkGetDeviceProcAddr(pLogicalDevice->Handle(), "vkGetAccelerationStructureMemoryRequirementsNV");

	if (!pfnCreateAccelStruct)					return Result::eErrorFailedToGetProcessAddress;
	if (!pfnBindAccelStructMem)					return Result::eErrorFailedToGetProcessAddress;
	if (!pfnGetAccelStructHandle)				return Result::eErrorFailedToGetProcessAddress;
	if (!pfnGetAccelStructMemReq)				return Result::eErrorFailedToGetProcessAddress;

	VkAccelerationStructureCreateInfoNV			CreateInfo = {};
	CreateInfo.sType							= VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_NV;
	CreateInfo.pNext							= nullptr;
	CreateInfo.compactedSize					= 0;
	CreateInfo.info.sType						= VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_INFO_NV;
	CreateInfo.info.pNext						= nullptr;
	CreateInfo.info.type						= VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_NV;
	CreateInfo.info.flags						= 0;
	CreateInfo.info.instanceCount				= 0;
	CreateInfo.info.geometryCount				= pGeometries.size();
	CreateInfo.info.pGeometries					= reinterpret_cast<const VkGeometryNV*>(pGeometries.data());
	
	VkAccelerationStructureNV hAccelerationStructure = VK_NULL_HANDLE;

	Result eResult = LAVA_RESULT_CAST(pfnCreateAccelStruct(pLogicalDevice->Handle(), &CreateInfo, nullptr, &hAccelerationStructure));

	if (eResult == Result::eSuccess)
	{
		DeviceLocalMemory	deviceMemory;

		VkAccelerationStructureMemoryRequirementsInfoNV		RequirementsInfo = {};
		RequirementsInfo.sType								= VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_INFO_NV;
		RequirementsInfo.pNext								= nullptr;
		RequirementsInfo.type								= VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_OBJECT_NV;
		RequirementsInfo.accelerationStructure				= hAccelerationStructure;

		VkMemoryRequirements2		Requirements = {};
		Requirements.sType			= VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2;
		Requirements.pNext			= nullptr;

		pfnGetAccelStructMemReq(pLogicalDevice->Handle(), &RequirementsInfo, &Requirements);

		eResult = deviceMemory.Allocate(pLogicalDevice, Requirements.memoryRequirements);

		if (eResult == Result::eSuccess)
		{
			VkBindAccelerationStructureMemoryInfoNV		MemoryInfo = {};
			MemoryInfo.sType							= VK_STRUCTURE_TYPE_BIND_ACCELERATION_STRUCTURE_MEMORY_INFO_NV;
			MemoryInfo.pNext							= nullptr;
			MemoryInfo.accelerationStructure			= hAccelerationStructure;
			MemoryInfo.memory							= deviceMemory;
			MemoryInfo.memoryOffset						= 0;
			MemoryInfo.deviceIndexCount					= 0;
			MemoryInfo.pDeviceIndices					= nullptr;

			eResult = LAVA_RESULT_CAST(pfnBindAccelStructMem(pLogicalDevice->Handle(), 1, &MemoryInfo));

			if (eResult == Result::eSuccess)
			{
				uint64_t handle = 0;

				eResult = LAVA_RESULT_CAST(pfnGetAccelStructHandle(pLogicalDevice->Handle(), hAccelerationStructure, sizeof(uint64_t), &handle));

				if (eResult == Result::eSuccess)
				{
					m_spUniqueHandle = std::make_shared<UniqueHandle>(deviceMemory, hAccelerationStructure, handle);

					return Result::eSuccess;
				}
			}
		}

		pfnDestroyAccelStruct(pLogicalDevice->Handle(), hAccelerationStructure, nullptr);
	}

	return eResult;
}


BottomLevelAccelStructNV::UniqueHandle::~UniqueHandle() noexcept
{
	if (m_hAccelStruct != VK_NULL_HANDLE)
	{
		PFN_vkDestroyAccelerationStructureNV pfnDestroyAccelStruct = nullptr;

		pfnDestroyAccelStruct = (PFN_vkDestroyAccelerationStructureNV)vkGetDeviceProcAddr(m_DeviceMemory.GetDeviceHandle(), "vkDestroyAccelerationStructureNV");

		pfnDestroyAccelStruct(m_DeviceMemory.GetDeviceHandle(), m_hAccelStruct, nullptr);
	}
}