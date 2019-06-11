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

		//!	@brief	Creates Vulkan instance object (private).
		Instance(VkInstance hInstance);

		//!	@brief	Destroys Vulkan instance object (private).
		~Instance() noexcept;

	public:

		//!	@brief	Destroys surface.
		void DestroySurface(VkSurfaceKHR hSurface);

		//!	@brief	Creates win32 surface.
		VkSurfaceKHR CreateWin32Surface(HWND hWindow);

		//!	@brief	Returns a function pointer for a command.
		PFN_vkVoidFunction GetProcAddress(const char * pName) const;

		//!	@brief	Returns physical devices array.
		const std::vector<PhysicalDevice*> & GetPhysicalDevices() const;

		//!	@brief	Creates a debug report callback.
		VkDebugReportCallbackEXT CreateDebugReportCallback(VkDebugReportFlagsEXT eFlags,
														   PFN_vkDebugReportCallbackEXT pfnCallback);
		//!	@brief	Destroys a debug report callback.
		void DestroyDebugReportCallback(VkDebugReportCallbackEXT hDebugReportCallback);

		//!	@brief	Returns extension properties array.
		static const std::vector<VkExtensionProperties> & GetExtensionProperties();

		//!	@brief	Returns layer properties array.
		static const std::vector<VkLayerProperties> & GetLayerProperties();

		//!	@brief	Check if extension is available.
		static VkBool32 IsExtensionAvailable(std::string TargetName);

		//!	@brief	Returns the Vulkan instance (singleton).
		static Instance * GetCurrent();

		//!	@brief	Destroys the Vulkan instance.
		static void Destroy();

	private:

		const VkInstance							m_hInstance;

		std::vector<PhysicalDevice*>				m_pPhysicalDevices;

		static std::vector<VkLayerProperties>		sm_LayerProperties;

		static std::vector<VkExtensionProperties>	sm_ExtensionProperties;
	};
}