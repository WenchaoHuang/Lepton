/*************************************************************************
***************************    Lava_Result    ****************************
*************************************************************************/
#pragma once

#include <vulkan/vulkan.h>

#define VK_ERROR_INVALID_SPIR_V_CODE				-2000000
#define VK_ERROR_INVALID_IMAGE_HANDLE				-2000001
#define VK_ERROR_INVALID_DEVICE_HANDLE				-2000002
#define VK_ERROR_INVALID_SURFACE_HANDLE				-2000003
#define VK_ERROR_INVALID_RENDER_PASS_HANDLE			-2000004

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
		eErrorInvalidRenderPassHandle						= VK_ERROR_INVALID_RENDER_PASS_HANDLE,
	};

	/*********************************************************************
	**************************    to_string    ***************************
	*********************************************************************/

	/**
	 *	@brief	Convert result to string.
	 */
	inline const char * to_string(Result eValue)
	{
		switch (eValue)
		{
		case Result::eSuccess:											return "Success";
		case Result::eTimeout:											return "Timeout";
		case Result::eNotReady:											return "Not Ready";
		case Result::eEventSet:											return "Event Set";
		case Result::eEventReset:										return "Event Reset";
		case Result::eIncomplete:										return "Incomplete";

		case Result::eErrorDeviceLost:									return "Error Device Lost";
		case Result::eErrorTooManyObjects:								return "Error Too Many Objects";
		case Result::eErrorFragmentedPool:								return "Error Fragmented Pool";
		case Result::eErrorMemoryMapFailed:								return "Error Memory Map Failed";
		case Result::eErrorLayerNotPresent:								return "Error Layer Not Present";
		case Result::eErrorOutOfHostMemory:								return "Error Out Of Host Memory";
		case Result::eErrorOutOfPoolMemory:								return "Error Out Of Pool Memory";
		case Result::eErrorOutOfDeviceMemory:							return "Error Out Of Device Memory";
		case Result::eErrorFeatureNotPresent:							return "Error Feature Not Present";
		case Result::eErrorFormatNotSupported:							return "Error Format Not Supported";
		case Result::eErrorIncompatibleDriver:							return "Error Incompatible Driver";
		case Result::eErrorExtensionNotPresent:							return "Error Extension Not Present";
		case Result::eErrorInitializationFailed:						return "Error Initialization Failed";
		case Result::eErrorInvalidExternalHandle:						return "Error Invalid External Handle";

		case Result::eSuboptimalKHR:									return "Suboptimal KHR";
		case Result::eErrorOutOfDateKHR:								return "Error Out Of Date KHR";
		case Result::eErrorSurfaceLostKHR:								return "Error Surface Lost KHR";
		case Result::eErrorNativeWindowInUseKHR:						return "Error Native Window In Use KHR";
		case Result::eErrorIncompatibleDisplayKHR:						return "Error Incompatible Display KHR";

		case Result::eErrorInvalidShaderNV:								return "Error Invalid Shader NV";
		case Result::eErrorNotPermittedEXT:								return "Error Not Permitted EXT";
		case Result::eErrorFragmentationEXT:							return "Error Fragmentation EXT";
		case Result::eErrorValidationFailedEXT:							return "Error Validation Failed EXT";
		case Result::eErrorInvalidDeviceAddressEXT:						return "Error Invalid Device Address EXT";
		case Result::eErrorInvalidDrmFormatModifierPlaneLayoutEXT:		return "Error Invalid DRM Format Modifier Plane Layout EXT";

		case Result::eErrorInvalidSPIRVCode:							return "Error Invalid SPIR-V Code";
		case Result::eErrorInvalidImageHandle:							return "Error Invalid Image Handle";
		case Result::eErrorInvalidDeviceHandle:							return "Error Invalid Device Handle";
		case Result::eErrorInvalidSurfaceHandle:						return "Error Invalid Surface Handle";
		case Result::eErrorInvalidRenderPassHandle:						return "Error Invalid RenderPass Handle";
		default:														return "Invalid";
		}
	}
}