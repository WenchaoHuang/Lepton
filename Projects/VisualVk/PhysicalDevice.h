/*************************************************************************
*********************    VisualVk_PhysicalDevice    **********************
*************************************************************************/
#pragma once

#include <set>
#include <vector>
#include <vulkan/vulkan_core.h>

namespace Vk
{
	class LogicalDevice;

	/*********************************************************************
	************************    PhysicalDevice    ************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan physical device object.
	 */
	class PhysicalDevice
	{

	private:

		friend class Instance;

		//!	@brief	Create physical device object.
		PhysicalDevice(VkPhysicalDevice hDevice);

		//!	@brief	Destroy physical device object.
		~PhysicalDevice() noexcept;

	public:




	private:

		const VkPhysicalDevice					m_hPhysicalDevice;

		std::set<LogicalDevice*>				m_pLogicalDevices;

		VkPhysicalDeviceFeatures				m_Features;

		VkPhysicalDeviceProperties				m_Properties;

		std::vector<VkLayerProperties>			m_LayerProperties;

		VkPhysicalDeviceMemoryProperties		m_MemoryProperties;

		std::vector<VkExtensionProperties>		m_ExtensionProperties;

		std::vector<VkQueueFamilyProperties>	m_QueueFamilyProperties;
	};
}