/*************************************************************************
*******************    Lava_AccelerationStructureNV    *******************
*************************************************************************/

#include "AccelerationStructureNV.h"

using namespace Lava;

/*************************************************************************
*********************    AccelerationStructureNV    **********************
*************************************************************************/

Result AccelerationStructureNV::Create(VkDevice hDevice, AccelerationStructureTypeNV eType, Flags<BuildAccelerationStructureFlagNV> eBuildFlags,
									   VkDeviceSize compactedSize, uint32_t instanceCount, ArrayProxy<const GeometryDataNV> pGeometries)
{
	if (hDevice == VK_NULL_HANDLE)			return Result::eErrorInvalidDeviceHandle;

	VkAccelerationStructureCreateInfoNV		CreateInfo = {};
	CreateInfo.sType						= VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_NV;
	CreateInfo.pNext						= nullptr;
	CreateInfo.compactedSize				= compactedSize;
	CreateInfo.info.sType					= VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_INFO_NV;
	CreateInfo.info.pNext					= nullptr;
	CreateInfo.info.type					= static_cast<VkAccelerationStructureTypeNV>(eType);
	CreateInfo.info.flags					= eBuildFlags;
	CreateInfo.info.instanceCount			= instanceCount;
	CreateInfo.info.geometryCount			= pGeometries.size();
	CreateInfo.info.pGeometries				= reinterpret_cast<const VkGeometryNV*>(pGeometries.data());

	VkAccelerationStructureNV hAccelerationStructure = VK_NULL_HANDLE;

	Result eResult = LAVA_RESULT_CAST(vkCreateAccelerationStructureNV(hDevice, &CreateInfo, nullptr, &hAccelerationStructure));

	if (eResult == Result::eSuccess)
	{
	//	m_spUniqueHandle = std::make_shared<UniqueHandle>();
	}

	return eResult;
}