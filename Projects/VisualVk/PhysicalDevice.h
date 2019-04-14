/*************************************************************************
*********************    VisualVk_PhysicalDevice    **********************
*************************************************************************/
#pragma once

#include <set>
#include "Common.h"

namespace Vk
{
	class LogicalDevice;

	/*********************************************************************
	************************    PhysicalDevice    ************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan physical device object.
	 */
	class VKAPI PhysicalDevice
	{

	private:

		//!	@brief	Only created by Instance.
		friend class Instance;

		//!	@brief	Create physical device object.
		PhysicalDevice(VkPhysicalDevice hDevice);

		//!	@brief	Destroy physical device object.
		~PhysicalDevice() noexcept;

	public:

		//!	@brief	Create logical device that has queues on all queue family.
		LogicalDevice * CreateLogicalDevice();

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

		//!	@brief	Get the index of a memory type that has all the requested property bits set.
		uint32_t GetMemoryTypeIndex(uint32_t MemoryTypeBits, VkMemoryPropertyFlags ePropertyFlags) const;

		//!	@brief	Find queue family that supported presentation, and return the queue family index.
		uint32_t GetPresentQueueFamilyIndex(VkSurfaceKHR hSurface) const;

		//!	@brief	Find queue family that supported graphics, and return the queue family index.
		uint32_t GetGraphicsQueueFamilyIndex() const;

		//!	@brief	Find queue family that supported transfer, and return the queue family index.
		uint32_t GetTransferQueueFamilyIndex() const;

		//!	@brief	Find queue family that supported computing, and return the queue family index.
		uint32_t GetComputeQueueFamilyIndex() const;

		//!	@brief	Return queue family properties.
		const std::vector<VkQueueFamilyProperties> & GetQueueFamilyProperties();

		//!	@brief	Return extension properties.
		const std::vector<VkExtensionProperties> & GetExtensionProperties();

		//!	@brief	Return memory properties.
		const VkPhysicalDeviceMemoryProperties & GetMemoryProperties();

		//!	@brief	Return layer properties.
		const std::vector<VkLayerProperties> & GetLayerProperties();

		//!	@brief	Return physical properties.
		const VkPhysicalDeviceProperties & GetProperties();

		//!	@brief	Return physical features.
		const VkPhysicalDeviceFeatures & GetFeatures();

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