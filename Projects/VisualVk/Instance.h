/*************************************************************************
************************    VisualVk_Instance    *************************
*************************************************************************/
#pragma once

#include <set>
#include <vector>
#include "Vulkan.h"
#include <vulkan/vulkan.h>

namespace Vk
{
	/*********************************************************************
	***************************    Instance    ***************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan instance object.
	 */
	class Instance
	{
		VK_NONCOPYABLE(Instance)

	public:

		//!	@brief	Create Vulkan instance object (not ready).
		Instance();

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

		//!	@brief	Return Vulkan type of this object.
		operator VkInstance() const { return m_hInstance; }

		//!	@brief	If Vulkan handle is valid.
		bool IsValid() const { return m_hInstance != VK_NULL_HANDLE; }

		//!	@brief	Create a new instance object.
		Result Create(ArrayProxy<const char*> extensions = nullptr, ArrayProxy<const char*> layers = nullptr);

		//!	@brief	Return array of physical devices.
		const std::vector<PhysicalDevice*> & GetPhysicalDevices() const { return m_pPhysicalDevices; }

		//!	@brief	Destroy a VkSurfaceKHR object.
		void DestroySurface(VkSurfaceKHR hSurface);

		//!	@brief	Create a VkSurfaceKHR object for native Win32 window.
		VkSurfaceKHR CreateSurface(HWND hWindow);

		//!	@brief	Destory instance.
		void Destroy();

	private:

		//!	@brief	Return a function pointer for a command.
		PFN_vkVoidFunction GetProcAddr(const char * pName);

	private:

		VkInstance										m_hInstance;

		std::set<VkSurfaceKHR>							m_hSurfaces;

		std::vector<PhysicalDevice*>					m_pPhysicalDevices;

		static std::vector<VkLayerProperties>			sm_AvailableLayers;

		static std::vector<VkExtensionProperties>		sm_AvailableExtensions;
	};
}