/*************************************************************************
**************************    Lava_Instance    ***************************
*************************************************************************/
#pragma once

#include <set>
#include "Vulkan.h"

namespace Lava
{
	/*********************************************************************
	***************************    Instance    ***************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan instance object.
	 */
	class Instance
	{
		LAVA_NONCOPYABLE(Instance)

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

		//!	@brief	If Vulkan handle is valid.
		bool IsValid() const { return m_hInstance != VK_NULL_HANDLE; }

		//!	@brief	Create a new instance object.
		Result Create(ArrayProxy<const char*> pExtensions = nullptr, ArrayProxy<const char*> pLayers = nullptr);

		//!	@brief	Return array of available extensions.
		const std::vector<VkExtensionProperties> & GetAvailableExtensions() const { return m_AvailableExtensions; }

		//!	@brief	Return array of physical devices.
		const std::vector<PhysicalDevice*> & GetPhysicalDevices() const { return m_pPhysicalDevices; }

		//!	@brief	Return array of available validation layers.
		const std::vector<VkLayerProperties> & GetAvailableLayers() const;

		//!	@brief	Check if extension is available.
		bool IsExtensionAvilable(std::string extensionName) const;

		//!	@brief	Check if extension is enabled.
		bool IsExtensionEnabled(std::string extensionName) const;

		//!	@brief	Check if validation layer is available.
		bool IsLayerAvilable(std::string layerName) const;

		//!	@brief	Destroy instance object.
		void Destroy();

	private:

		VkInstance										m_hInstance;

		std::set<std::string>							m_pExtensions;

		std::vector<PhysicalDevice*>					m_pPhysicalDevices;

		mutable std::vector<VkLayerProperties>			m_AvailableLayers;

		mutable std::vector<VkExtensionProperties>		m_AvailableExtensions;
	};
}