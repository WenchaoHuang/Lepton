/*************************************************************************
************************    VisualVk_Instance    *************************
*************************************************************************/
#pragma once

#include <set>
#include <vector>
#include <vulkan/vulkan.h>
#include "Result.h"

namespace Vk
{
	class PhysicalDevice;

	/*********************************************************************
	***************************    Instance    ***************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan instance object.
	 */
	class Instance
	{

	public:

		//!	@brief	Create Vulkan instance object (not ready).
		Instance();

		//!	@brief	Vulkan instance object is non-copyable.
		Instance(const Instance&) = delete;

		//!	@brief	Vulkan instance object is non-assignable.
		void operator=(const Instance&) = delete;

		//!	@brief	Destroy Vulkan instance object.
		~Instance();

	public:

		//!	@brief	Check if validation layer is available.
		static bool IsLayerAvilable(std::string layerName);

		//!	@brief	Check if extension is available.
		static bool IsExtensionAvilable(std::string extensionName);

		//!	@brief	Return array of available validation layers.
		static const std::vector<VkLayerProperties> & GetAvailableLayers();

		//!	@brief	Return array of available extensions.
		static const std::vector<VkExtensionProperties> & GetAvailableExtensions();

	public:

		//!	@brief	Invalidate instance.
		void Invalidate();

		//!	@brief	Validate instance object.
		Result Validate();

		//!	@brief	If Vulkan handle is valid.
		bool IsValid() const { return m_hInstance != VK_NULL_HANDLE; }

		//!	@brief	Enable validation layer (in preparation stage).
		bool EnableLayer(std::string layerName);

		//!	@brief	Enable extension (in preparation stage).
		bool EnableExtension(std::string extensionName);

		//!	@brief	Check if validation layer had already enabled.
		bool IsLayerEnabled(std::string layerName) const;

		//!	@brief	Check if extension had already enabled.
		bool IsExtensionEnabled(std::string extensionName) const;

		//!	@brief	Destroy a VkSurfaceKHR object.
		void DestroySurface(VkSurfaceKHR hSurface);

		//!	@brief	Create a slink:VkSurfaceKHR object for an Win32 native window.
		VkSurfaceKHR CreateSurface(HWND hWindow);

	private:

		//!	@brief	Return a function pointer for a command.
		PFN_vkVoidFunction GetProcAddr(const char * pName);

	private:

		VkInstance										m_hInstance;

		std::set<VkSurfaceKHR>							m_hSurfaces;

		std::vector<PhysicalDevice*>					m_pPhysicalDevices;

	private:

		std::set<const char*>							m_EnabledLayers;

		std::set<const char*>							m_EnabledExtensions;

		static std::vector<VkLayerProperties>			sm_AvailableLayers;

		static std::vector<VkExtensionProperties>		sm_AvailableExtensions;
	};
}