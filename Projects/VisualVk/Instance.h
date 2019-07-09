/*************************************************************************
************************    VisualVk_Instance    *************************
*************************************************************************/
#pragma once

#include <vector>
#include <vulkan/vulkan.h>

namespace Vk
{
	class PhysicalDevice;

	/*********************************************************************
	***************************    Instance    ***************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan instance object (singleton).
	 */
	class Instance
	{

	private:

		//!	@brief	Create Vulkan instance object (private).
		Instance(VkInstance hInstance);

		//!	@brief	Destroy Vulkan instance object (private).
		~Instance() noexcept;

	public:

		//!	@brief	Destroy VkSurfaceKHR object.
		void DestroySurface(VkSurfaceKHR hSurface);

		//!	@brief	Create a win32 surface.
		VkSurfaceKHR CreateWin32Surface(HWND hWindow);

		//!	@brief	Return a function pointer for a command.
		PFN_vkVoidFunction GetProcAddress(const char * pName) const;

		//!	@brief	Return physical devices array.
		const std::vector<PhysicalDevice*> & GetPhysicalDevices() const;

		//!	@brief	Create a debug report callback.
		VkDebugReportCallbackEXT CreateDebugReportCallback(VkDebugReportFlagsEXT eFlags,
														   PFN_vkDebugReportCallbackEXT pfnCallback);
		//!	@brief	Destroy a debug report callback.
		void DestroyDebugReportCallback(VkDebugReportCallbackEXT hDebugReportCallback);

		//!	@brief	Return extension properties array.
		static const std::vector<VkExtensionProperties> & GetExtensionProperties();

		//!	@brief	Return layer properties array.
		static const std::vector<VkLayerProperties> & GetLayerProperties();

		//!	@brief	Check if extension is available.
		static VkBool32 IsExtensionAvailable(std::string TargetName);

		//!	@brief	Return the Vulkan instance (singleton).
		static Instance * GetCurrent();

		//!	@brief	Destroy the Vulkan instance.
		static void Destroy();

	private:

		const VkInstance								m_hInstance;

		std::vector<PhysicalDevice*>					m_pPhysicalDevices;

		static std::vector<VkLayerProperties>			sm_LayerProperties;

		static std::vector<VkExtensionProperties>		sm_ExtensionProperties;
	};
}