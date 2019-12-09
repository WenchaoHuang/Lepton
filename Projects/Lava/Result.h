/*************************************************************************
***************************    Lava_Result    ****************************
*************************************************************************/
#pragma once

#include <vulkan/vulkan.h>

#define VK_ERROR_INVALID_SPIR_V_CODE					-2000000
#define VK_ERROR_INVALID_IMAGE_HANDLE					-2000001
#define VK_ERROR_INVALID_DEVICE_HANDLE					-2000002
#define VK_ERROR_INVALID_SURFACE_HANDLE					-2000003
#define VK_ERROR_INVALID_INSTANCE_HANDLE				-2000004
#define VK_ERROR_INVALID_MEMORY_TYPE_BITS				-2000005
#define VK_ERROR_INVALID_RENDER_PASS_HANDLE				-2000006
#define VK_ERROR_INVALID_PIPELINE_LAYOUT_HANDLE			-2000007
#define VK_ERROR_FAILED_TO_GET_PROCESS_ADDRESS			-2000008

namespace Lava
{
	/*********************************************************************
	****************************    Result    ****************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan command return codes.
	 */
	enum class Result
	{
		eSuccess											= VK_SUCCESS,
		eTimeout											= VK_TIMEOUT,
		eNotReady											= VK_NOT_READY,
		eEventSet											= VK_EVENT_SET,
		eEventReset											= VK_EVENT_RESET,
		eIncomplete											= VK_INCOMPLETE,

		eErrorDeviceLost									= VK_ERROR_DEVICE_LOST,
		eErrorFragmentedPool								= VK_ERROR_FRAGMENTED_POOL,
		eErrorTooManyObjects								= VK_ERROR_TOO_MANY_OBJECTS,
		eErrorLayerNotPresent								= VK_ERROR_LAYER_NOT_PRESENT,
		eErrorMemoryMapFailed								= VK_ERROR_MEMORY_MAP_FAILED,
		eErrorOutOfPoolMemory								= VK_ERROR_OUT_OF_POOL_MEMORY,
		eErrorOutOfHostMemory								= VK_ERROR_OUT_OF_HOST_MEMORY,
		eErrorOutOfDeviceMemory								= VK_ERROR_OUT_OF_DEVICE_MEMORY,
		eErrorFeatureNotPresent								= VK_ERROR_FEATURE_NOT_PRESENT,
		eErrorIncompatibleDriver							= VK_ERROR_INCOMPATIBLE_DRIVER,
		eErrorFormatNotSupported							= VK_ERROR_FORMAT_NOT_SUPPORTED,
		eErrorExtensionNotPresent							= VK_ERROR_EXTENSION_NOT_PRESENT,
		eErrorInitializationFailed							= VK_ERROR_INITIALIZATION_FAILED,
		eErrorInvalidExternalHandle							= VK_ERROR_INVALID_EXTERNAL_HANDLE,

		eSuboptimalKHR										= VK_SUBOPTIMAL_KHR,
		eErrorOutOfDateKHR									= VK_ERROR_OUT_OF_DATE_KHR,
		eErrorSurfaceLostKHR								= VK_ERROR_SURFACE_LOST_KHR,
		eErrorOutOfPoolMemoryKHR							= VK_ERROR_OUT_OF_POOL_MEMORY_KHR,
		eErrorNativeWindowInUseKHR							= VK_ERROR_NATIVE_WINDOW_IN_USE_KHR,
		eErrorIncompatibleDisplayKHR						= VK_ERROR_INCOMPATIBLE_DISPLAY_KHR,

		eErrorInvalidShaderNV								= VK_ERROR_INVALID_SHADER_NV,
		eErrorNotPermittedEXT								= VK_ERROR_NOT_PERMITTED_EXT,
		eErrorFragmentationEXT								= VK_ERROR_FRAGMENTATION_EXT,
		eErrorValidationFailedEXT							= VK_ERROR_VALIDATION_FAILED_EXT,
		eErrorInvalidDeviceAddressEXT						= VK_ERROR_INVALID_DEVICE_ADDRESS_EXT,
		eErrorInvalidDrmFormatModifierPlaneLayoutEXT		= VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT,

		eErrorInvalidSPIRVCode								= VK_ERROR_INVALID_SPIR_V_CODE,
		eErrorInvalidImageHandle							= VK_ERROR_INVALID_IMAGE_HANDLE,
		eErrorInvalidDeviceHandle							= VK_ERROR_INVALID_DEVICE_HANDLE,
		eErrorInvalidSurfaceHandle							= VK_ERROR_INVALID_SURFACE_HANDLE,
		eErrorInvalidInstanceHandle							= VK_ERROR_INVALID_INSTANCE_HANDLE,
		eErrorInvalidMemoryTypeBits							= VK_ERROR_INVALID_MEMORY_TYPE_BITS,
		eErrorInvalidRenderPassHandle						= VK_ERROR_INVALID_RENDER_PASS_HANDLE,
		eErrorInvalidPipelineLayoutHandle					= VK_ERROR_INVALID_PIPELINE_LAYOUT_HANDLE,
		eErrorFailedToGetProcessAddress						= VK_ERROR_FAILED_TO_GET_PROCESS_ADDRESS,
	};

	/*********************************************************************
	**************************    to_string    ***************************
	*********************************************************************/

	/**
	 *	@brief	Convert result to string.
	 */
	constexpr const char * to_string(Result eValue)
	{
		switch (eValue)
		{
		case Result::eSuccess:											return "Success";
		case Result::eTimeout:											return "Timeout";
		case Result::eNotReady:											return "Not ready";
		case Result::eEventSet:											return "Event set";
		case Result::eEventReset:										return "Event reset";
		case Result::eIncomplete:										return "Incomplete";

		case Result::eErrorDeviceLost:									return "Error: Device lost";
		case Result::eErrorTooManyObjects:								return "Error: Too many objects";
		case Result::eErrorFragmentedPool:								return "Error: Fragmented pool";
		case Result::eErrorMemoryMapFailed:								return "Error: Memory map failed";
		case Result::eErrorLayerNotPresent:								return "Error: Layer not present";
		case Result::eErrorOutOfHostMemory:								return "Error: Out of host memory";
		case Result::eErrorOutOfPoolMemory:								return "Error: Out of pool memory";
		case Result::eErrorOutOfDeviceMemory:							return "Error: Out of device memory";
		case Result::eErrorFeatureNotPresent:							return "Error: Feature not present";
		case Result::eErrorFormatNotSupported:							return "Error: Format not supported";
		case Result::eErrorIncompatibleDriver:							return "Error: Incompatible driver";
		case Result::eErrorExtensionNotPresent:							return "Error: Extension not present";
		case Result::eErrorInitializationFailed:						return "Error: Initialization failed";
		case Result::eErrorInvalidExternalHandle:						return "Error: Invalid external handle";

		case Result::eSuboptimalKHR:									return "Suboptimal KHR";
		case Result::eErrorOutOfDateKHR:								return "Error: Out of date KHR";
		case Result::eErrorSurfaceLostKHR:								return "Error: Surface lost KHR";
		case Result::eErrorNativeWindowInUseKHR:						return "Error: Native window in use KHR";
		case Result::eErrorIncompatibleDisplayKHR:						return "Error: Incompatible display KHR";

		case Result::eErrorInvalidShaderNV:								return "Error: Invalid shader NV";
		case Result::eErrorNotPermittedEXT:								return "Error: Not permitted EXT";
		case Result::eErrorFragmentationEXT:							return "Error: Fragmentation EXT";
		case Result::eErrorValidationFailedEXT:							return "Error: Validation failed EXT";
		case Result::eErrorInvalidDeviceAddressEXT:						return "Error: Invalid device address EXT";
		case Result::eErrorInvalidDrmFormatModifierPlaneLayoutEXT:		return "Error: Invalid DRM format modifier plane layout EXT";

		case Result::eErrorInvalidSPIRVCode:							return "Error: Invalid SPIR-V code";
		case Result::eErrorInvalidImageHandle:							return "Error: Invalid image handle";
		case Result::eErrorInvalidDeviceHandle:							return "Error: Invalid device handle";
		case Result::eErrorInvalidSurfaceHandle:						return "Error: Invalid surface handle";
		case Result::eErrorInvalidInstanceHandle:						return "Error: Invalid instance handle";
		case Result::eErrorInvalidMemoryTypeBits:						return "Error: Invalid memory type bits";
		case Result::eErrorInvalidRenderPassHandle:						return "Error: Invalid render pass handle";
		case Result::eErrorInvalidPipelineLayoutHandle:					return "Error: Invalid pipeline layout handle";
		case Result::eErrorFailedToGetProcessAddress:					return "Error: Failed to get process address";
		default:														return "Invalid";
		}
	}
}