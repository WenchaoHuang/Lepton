/*************************************************************************
*************************    VisualVk_Result    **************************
*************************************************************************/
#pragma once

#include <vulkan/vulkan.h>

namespace Vk
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
		eErrorOutOfPoolMemory								= VK_ERROR_OUT_OF_POOL_MEMORY,
		eErrorOutOfHostMemory								= VK_ERROR_OUT_OF_HOST_MEMORY,
		eErrorMemoryMapFailed								= VK_ERROR_MEMORY_MAP_FAILED,
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
		eErrorInvalidExternalHandleKHR						= VK_ERROR_INVALID_EXTERNAL_HANDLE_KHR,

		eErrorInvalidShaderNV								= VK_ERROR_INVALID_SHADER_NV,
		eErrorNotPermittedEXT								= VK_ERROR_NOT_PERMITTED_EXT,
		eErrorFragmentationEXT								= VK_ERROR_FRAGMENTATION_EXT,
		eErrorValidationFailedEXT							= VK_ERROR_VALIDATION_FAILED_EXT,
		eErrorInvalidDeviceAddressEXT						= VK_ERROR_INVALID_DEVICE_ADDRESS_EXT,
		eErrorInvalidDrmFormatModifierPlaneLayoutEXT		= VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT,
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
		case Result::eNotReady:											return "NotReady";
		case Result::eEventSet:											return "EventSet";
		case Result::eEventReset:										return "EventReset";
		case Result::eIncomplete:										return "Incomplete";

		case Result::eErrorDeviceLost:									return "ErrorDeviceLost";
		case Result::eErrorTooManyObjects:								return "ErrorTooManyObjects";
		case Result::eErrorFragmentedPool:								return "ErrorFragmentedPool";
		case Result::eErrorMemoryMapFailed:								return "ErrorMemoryMapFailed";
		case Result::eErrorLayerNotPresent:								return "ErrorLayerNotPresent";
		case Result::eErrorOutOfHostMemory:								return "ErrorOutOfHostMemory";
		case Result::eErrorOutOfPoolMemory:								return "ErrorOutOfPoolMemory";
		case Result::eErrorOutOfDeviceMemory:							return "ErrorOutOfDeviceMemory";
		case Result::eErrorFeatureNotPresent:							return "ErrorFeatureNotPresent";
		case Result::eErrorFormatNotSupported:							return "ErrorFormatNotSupported";
		case Result::eErrorIncompatibleDriver:							return "ErrorIncompatibleDriver";
		case Result::eErrorExtensionNotPresent:							return "ErrorExtensionNotPresent";
		case Result::eErrorInitializationFailed:						return "ErrorInitializationFailed";
		case Result::eErrorInvalidExternalHandle:						return "ErrorInvalidExternalHandle";

		case Result::eSuboptimalKHR:									return "SuboptimalKHR";
		case Result::eErrorOutOfDateKHR:								return "ErrorOutOfDateKHR";
		case Result::eErrorSurfaceLostKHR:								return "ErrorSurfaceLostKHR";
		case Result::eErrorNativeWindowInUseKHR:						return "ErrorNativeWindowInUseKHR";
		case Result::eErrorIncompatibleDisplayKHR:						return "ErrorIncompatibleDisplayKHR";

		case Result::eErrorInvalidShaderNV:								return "ErrorInvalidShaderNV";
		case Result::eErrorNotPermittedEXT:								return "ErrorNotPermittedEXT";
		case Result::eErrorFragmentationEXT:							return "ErrorFragmentationEXT";
		case Result::eErrorValidationFailedEXT:							return "ErrorValidationFailedEXT";
		case Result::eErrorInvalidDeviceAddressEXT:						return "ErrorInvalidDeviceAddressEXT";
		case Result::eErrorInvalidDrmFormatModifierPlaneLayoutEXT:		return "ErrorInvalidDrmFormatModifierPlaneLayoutEXT";
		default:														return "Invalid";
		}
	}
}