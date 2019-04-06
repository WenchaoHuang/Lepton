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

		//!	@brief	If device extension is available.
		VkBool32 IsExtensionAvailable(std::string TargetName) const;

		//!	@brief	Destroy logical device.
		VkResult DestroyLogicalDevice(LogicalDevice * pLogicalDevice);

		//!	@brief	Return format properties.
		VkFormatProperties GetFormatProperties(VkFormat eFormat) const;

		//!	@brief	Return surface capabilities.
		VkSurfaceCapabilitiesKHR GetSurfaceCapabilities(VkSurfaceKHR hSurface) const;

		//!	@brief	Return surface formats.
		std::vector<VkSurfaceFormatKHR> GetSurfaceFormats(VkSurfaceKHR hSurface) const;

		//!	@brief	Return surface present modes.
		std::vector<VkPresentModeKHR> GetSurfacePresentModes(VkSurfaceKHR hSurface) const;

		//!	@brief	If present surface is supported by specify queue family.
		VkBool32 IsSurfaceSupported(VkSurfaceKHR hSurface, uint32_t QueueFamilyIndex) const;

		//!	@brief	Return queue family properties.
		const std::vector<VkQueueFamilyProperties> & GetQueueFamilyProperties() const;

		//!	@brief	Return extension properties.
		const std::vector<VkExtensionProperties> & GetExtensionProperties() const;

		//!	@brief	Return memory properties.
		const VkPhysicalDeviceMemoryProperties & GetMemoryProperties() const;

		//!	@brief	Return layer properties.
		const std::vector<VkLayerProperties> & GetLayerProperties() const;

		//!	@brief	Return physical properties.
		const VkPhysicalDeviceProperties & GetProperties()const;

		//!	@brief	Return physical features.
		const VkPhysicalDeviceFeatures & GetFeatures() const;

	private:

		const VkPhysicalDevice					m_hPhysicalDevice;

		std::set<LogicalDevice*>				m_pLogicalDevices;

	private:

		VkPhysicalDeviceFeatures				m_Features;

		VkPhysicalDeviceProperties				m_Properties;

		std::vector<VkLayerProperties>			m_LayerProperties;

		VkPhysicalDeviceMemoryProperties		m_MemoryProperties;

		std::vector<VkExtensionProperties>		m_ExtensionProperties;

		std::vector<VkQueueFamilyProperties>	m_QueueFamilyProperties;
	};
}