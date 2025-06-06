/*************************************************************************
*************************    Lepton_Instance    **************************
*************************************************************************/
#pragma once

#include <set>
#include "Vulkan.h"

namespace Lepton
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

		//!	@brief	Return array of available validation layers.
		static std::vector<VkLayerProperties> GetAvailableLayers();

		//!	@brief	Return array of available extensions.
		static std::vector<VkExtensionProperties> GetAvailableExtensions();

	public:

		//!	@brief	Return Vulkan type of this object.
		VkInstance Handle() const { return m_hInstance; }

		//!	@brief	If Vulkan handle is valid.
		bool IsValid() const { return m_hInstance != VK_NULL_HANDLE; }

		//!	@brief	Create a new instance object.
		Result Create(vk::ArrayProxy<const char*> pExtensions = nullptr, vk::ArrayProxy<const char*> pLayers = nullptr);

		//!	@brief	Return array of physical devices.
		const std::vector<PhysicalDevice*> & GetPhysicalDevices() const { return m_pPhysicalDevices; }

		//!	@brief	Check if extension is available.
		bool IsExtensionAvailable(std::string extensionName) const;

		//!	@brief	Check if extension is enabled.
		bool IsExtensionEnabled(std::string extensionName) const;

		//!	@brief	Check if validation layer is available.
		bool IsLayerAvailable(std::string layerName) const;

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