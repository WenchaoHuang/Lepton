/*************************************************************************
************************    VisualVk_Instance    *************************
*************************************************************************/
#pragma once

#include "Vulkan.h"

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

		//!	@brief	Convert to VkInstance.
		operator VkInstance() const { return m_hInstance; }

		//!	@brief	Return Vulkan type of this object.
		VkInstance GetHandle() const { return m_hInstance; }

		//!	@brief	Check if validation layer is available.
		static bool IsLayerAvilable(std::string layerName);

		//!	@brief	Check if extension is available.
		static bool IsExtensionAvilable(std::string extensionName);

		//!	@brief	Return array of available validation layers.
		static const std::vector<VkLayerProperties> & GetAvailableLayers();

		//!	@brief	Return array of available extensions.
		static const std::vector<VkExtensionProperties> & GetAvailableExtensions();

	public:

		//!	@brief	Create a new instance object.
		Result Create(ArrayProxy<const char*> pExtensions = nullptr, ArrayProxy<const char*> pLayers = nullptr);

		//!	@brief	Return array of physical devices.
		const std::vector<PhysicalDevice*> & GetPhysicalDevices() const { return m_pPhysicalDevices; }

		//!	@brief	If Vulkan handle is valid.
		bool IsValid() const { return m_hInstance != VK_NULL_HANDLE; }

		//!	@brief	Destroy instance object.
		void Destroy();

	private:

		VkInstance										m_hInstance;

		std::vector<PhysicalDevice*>					m_pPhysicalDevices;

		static std::vector<VkLayerProperties>			sm_AvailableLayers;

		static std::vector<VkExtensionProperties>		sm_AvailableExtensions;
	};
}