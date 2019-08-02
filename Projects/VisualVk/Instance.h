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

		//!	@brief	Create Vulkan instance object.
		Instance(VkInstance hInstance);

		//!	@brief	Destroy Vulkan instance object.
		~Instance() noexcept;

	public:

		//!	@brief	Destroy the Vulkan instance.
		static void Destroy();

		//!	@brief	Return the Vulkan instance (singleton).
		static Instance * GetCurrent();

		//!	@brief	Check if layer is available.
		static VkBool32 IsLayerAvailable(std::string LayerName);

		//!	@brief	Check if extension is available.
		static VkBool32 IsExtensionAvailable(std::string ExtensionName);

		//!	@brief	Return global layer properties array.
		static const std::vector<VkLayerProperties> & GetLayerProperties();

		//!	@brief	Return global extension properties.
		static const std::vector<VkExtensionProperties> & GetExtensionProperties();

	public:

		//!	@brief	Register debug report callback.
		void RegisterDebugReportCallback(VkDebugReportFlagsEXT eFlags, PFN_vkDebugReportCallbackEXT pfnCallback);

		//!	@brief	Return physical devices array.
		const std::vector<PhysicalDevice*> & GetPhysicalDevices() const;

		//!	@brief	Return pointer to physical device.
		PhysicalDevice * GetPhysicalDevice(size_t Index) const;

		//!	@brief	Create a win32 surface.
		VkSurfaceKHR CreateWin32Surface(HWND hWindow);

		//!	@brief	Destroy VkSurfaceKHR object.
		void DestroySurface(VkSurfaceKHR hSurface);

		//!	@brief	Destroy debug report callback.
		void UnregisterDebugReportCallback();

	private:

		const VkInstance								m_hInstance;

		VkDebugReportCallbackEXT						m_hDebugReport;

		std::vector<PhysicalDevice*>					m_pPhysicalDevices;

	private:

		static std::vector<VkLayerProperties>			sm_AvailableLayers;

		static std::vector<VkExtensionProperties>		sm_AvailableExtensions;
	};
}