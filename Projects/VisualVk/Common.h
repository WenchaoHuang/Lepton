/*************************************************************************
**************************    VisualVk_Common    *************************
*************************************************************************/
#pragma once

#include <string>
#include <vector>
#include <vulkan/vulkan_core.h>

#if defined(_WINDLL)
	#define VK_DLL_EXPORT		__declspec(dllexport)
	#define VK_DLL_IMPORT		__declspec(dllimport)
#else
	#define VK_DLL_EXPORT
	#define VK_DLL_IMPORT
#endif

#if defined(VKAPI_BUILD)
	#define	VKAPI				VK_DLL_EXPORT
#else
	#define	VKAPI				VK_DLL_IMPORT
#endif

#define VK_INVALID_INDEX		UINT_MAX

#pragma warning(disable: 4251)

/*************************************************************************
**************************    VisualVk_Common    *************************
*************************************************************************/
namespace Vk
{
	inline std::string to_string(VkResult eResult)
	{
		switch (eResult)
		{
		case VK_SUCCESS :							return "Success";
		case VK_TIMEOUT :							return "Timeout";
		case VK_NOT_READY :							return "Not Ready";
		case VK_EVENT_SET :							return "Event Set";
		case VK_INCOMPLETE :						return "Incomplete";
		case VK_EVENT_RESET :						return "Event Reset";
		case VK_SUBOPTIMAL_KHR :					return "Suboptimal";
		case VK_ERROR_DEVICE_LOST :					return "Device Lost";
		case VK_ERROR_FRAGMENTED_POOL :				return "Fragmented Pool";
		case VK_ERROR_OUT_OF_DATE_KHR :				return "Out Of Date";
		case VK_ERROR_SURFACE_LOST_KHR :			return "Surface Lost";
		case VK_ERROR_TOO_MANY_OBJECTS :			return "Too Many Objects";
		case VK_ERROR_LAYER_NOT_PRESENT :			return "Layer Not Present";
		case VK_ERROR_MEMORY_MAP_FAILED :			return "Memory Map Failed";
		case VK_ERROR_INVALID_SHADER_NV :			return "Invalid Shader";
		case VK_ERROR_FRAGMENTATION_EXT :			return "Fragmentation";
		case VK_ERROR_NOT_PERMITTED_EXT :			return "Not Permitted";
		case VK_ERROR_OUT_OF_POOL_MEMORY :			return "Out Of Pool Memory";
		case VK_ERROR_OUT_OF_HOST_MEMORY :			return "Out Of Host Memory";
		case VK_ERROR_FEATURE_NOT_PRESENT :			return "Feature Not Present";
		case VK_ERROR_INCOMPATIBLE_DRIVER :			return "Incompatible Driver";
		case VK_ERROR_OUT_OF_DEVICE_MEMORY :		return "Out Of Device Memory";
		case VK_ERROR_FORMAT_NOT_SUPPORTED :		return "Format Not Supported";
		case VK_ERROR_INITIALIZATION_FAILED :		return "Initialization Failed";
		case VK_ERROR_EXTENSION_NOT_PRESENT :		return "Extension Not Present";
		case VK_ERROR_VALIDATION_FAILED_EXT :		return "Validation Failed";
		case VK_ERROR_INVALID_EXTERNAL_HANDLE :		return "Invalid External Handle";
		case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR :	return "Native Window In Use";
		case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR :	return "Incompatible Display";
		default :									return "Unknown Error";
		}
	}
}