/*************************************************************************
*********************    VisualVk_PhysicalDevice    **********************
*************************************************************************/
#pragma once

#include <set>
#include <vector>
#include <vulkan/vulkan_core.h>

#include "Enums.h"
#include "Result.h"

#define VK_INVALID_INDEX			UINT32_MAX

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

		//!	@brief	Only created by Instance.
		friend class Instance;

		//!	@brief	Open to logical device.
		friend class LogicalDevice;

		//!	@brief	Create physical device object.
		PhysicalDevice(VkPhysicalDevice hPhysicalDevice);

		//!	@brief	Destroy physical device object.
		~PhysicalDevice() noexcept;

	public:

		//!	@brief	Create a logical device (not ready).
		LogicalDevice * CreateLogicalDevice();

		//!	@brief	If device layer is available.
		bool IsLayerAvailable(std::string layerName) const;

		//!	@brief	If device extension is available.
		bool IsExtensionAvailable(std::string extensionName) const;

		//!	@brief	Destroy a logical device.
		Result DestroyLogicalDevice(LogicalDevice * pLogicalDevice);

		//!	@brief	If present surface is supported by specify queue family.
		bool IsSurfaceSupported(VkSurfaceKHR hSurface, uint32_t queueFamilyIndex) const;

		//!	@brief	Return the surface present modes.
		std::vector<PresentMode> GetSurfacePresentModes(VkSurfaceKHR hSurface) const;

		//!	@brief	Return array of available extensions.
		const std::vector<VkExtensionProperties> & GetAvailableExtensions() const;

		//!	@brief	Return array of available validation layers.
		const std::vector<VkLayerProperties> & GetAvailableLayers() const;





		//!	@brief	Return the memory properties.
		const VkPhysicalDeviceMemoryProperties & GetMemoryProperties() const { return m_MemoryProperties; }

		//!	@brief	Return the physical properties.
		const VkPhysicalDeviceProperties & GetProperties() const { return m_Properties; }

		//!	@brief	Return the physical features.
		const VkPhysicalDeviceFeatures & GetFeatures() const { return m_Features; }



		//!	@brief	Return the format properties.
		VkFormatProperties GetFormatProperties(VkFormat eFormat) const;

		//!	@brief	Return the surface capabilities.
		VkSurfaceCapabilitiesKHR GetSurfaceCapabilities(VkSurfaceKHR hSurface) const;

		//!	@brief	Return the surface formats.
		std::vector<VkSurfaceFormatKHR> GetSurfaceFormats(VkSurfaceKHR hSurface) const;

		//!	@brief	Get the index of a memory type that has all the requested property bits set.
		uint32_t GetMemoryTypeIndex(uint32_t memoryTypeBits, VkMemoryPropertyFlags ePropertyFlags) const;

		//!	@brief	Find queue family that supported presentation, and return the queue family index.
		uint32_t GetPresentQueueFamilyIndex(VkSurfaceKHR hSurface) const;

		//!	@brief	Find queue family that supported graphics, and return the queue family index.
		uint32_t GetGraphicsQueueFamilyIndex() const;

		//!	@brief	Find queue family that supported transfer, and return the queue family index.
		uint32_t GetTransferQueueFamilyIndex() const;

		//!	@brief	Find queue family that supported computing, and return the queue family index.
		uint32_t GetComputeQueueFamilyIndex() const;



		//!	@brief	Return the queue family properties.
		const std::vector<VkQueueFamilyProperties> & GetQueueFamilies() const;


	private:

		const VkPhysicalDevice					m_hPhysicalDevice;

		std::set<LogicalDevice*>				m_pLogicalDevices;

	private:

		mutable VkPhysicalDeviceFeatures					m_Features;

		mutable VkPhysicalDeviceProperties					m_Properties;

		mutable std::vector<VkLayerProperties>				m_AvailableLayers;

		mutable VkPhysicalDeviceMemoryProperties			m_MemoryProperties;

		mutable std::vector<VkExtensionProperties>			m_AvailableExtensions;

		mutable std::vector<VkQueueFamilyProperties>		m_QueueFamilyProperties;
	};
}