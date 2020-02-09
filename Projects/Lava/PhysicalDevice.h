/*************************************************************************
***********************    Lava_PhysicalDevice    ************************
*************************************************************************/
#pragma once

#include <set>
#include "Vulkan.h"
#include "Win32Surface.h"

namespace Lava
{
	/*********************************************************************
	************************    PhysicalDevice    ************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan physical device object.
	 */
	class PhysicalDevice
	{
		friend class Instance;

	private:

		//!	@brief	Create physical device object.
		PhysicalDevice(Instance * pInstance, VkPhysicalDevice hPhysicalDevice);

		//!	@brief	Destroy physical device object.
		~PhysicalDevice() noexcept;

	public:

		//!	@brief	Return pointer to its parent object.
		const Instance * GetInstance() const { return m_pInstance; }

		//!	@brief	Return Vulkan type of this object.
		VkPhysicalDevice Handle() const { return m_hPhysicalDevice; }

		//!	@brief	Return array of available validation layers.
		const std::vector<VkLayerProperties> & GetAvailableLayers() const;

		//!	@brief	Return the queue family properties.
		const std::vector<VkQueueFamilyProperties> & GetQueueFamilies() const;

		//!	@brief	Query surface capabilities.
		SurfaceCapabilities GetSurfaceCapabilities(VkSurfaceKHR hSurface) const;

		//!	@brief	Get color formats supported by the surface.
		std::vector<SurfaceFormat> GetSurfaceFormats(VkSurfaceKHR hSurface) const;

		//!	@brief	Query supported presentation modes.
		std::vector<PresentMode> GetSurfacePresentModes(VkSurfaceKHR hSurface) const;

		//!	@brief	Query if presentation is supported.
		bool IsSurfaceSupported(VkSurfaceKHR hSurface, uint32_t queueFamilyIndex) const;

		//!	@brief	Get the index of a memory type that has all the requested property bits set.
		uint32_t GetMemoryTypeIndex(uint32_t memoryTypeBits, Flags<MemoryProperty> eProperties) const;

		//!	@brief	Return the physical properties.
		const VkPhysicalDeviceProperties & GetProperties() const { return m_Properties.properties; }

		//!	@brief	Return set of logical devices.
		const std::set<LogicalDevice*> GetLogicalDevices() const { return m_pLogicalDevices; }

		//!	@brief	Return the physical features.
		const VkPhysicalDeviceFeatures & GetFeatures() const { return m_Features; }

		//!	@brief	Return array of available extensions.
		const std::vector<VkExtensionProperties> & GetAvailableExtensions() const;

		//!	@brief	Find queue family that supported graphics, and return the queue family index.
		uint32_t GetGraphicsQueueFamilyIndex() const;

		//!	@brief	Find queue family that supported transfer, and return the queue family index.
		uint32_t GetTransferQueueFamilyIndex() const;

		//!	@brief	Find queue family that supported computing, and return the queue family index.
		uint32_t GetComputeQueueFamilyIndex() const;

		//!	@brief	Return the format properties.
		VkFormatProperties GetFormatProperties(Format eFormat) const;

		//!	@brief	Destroy a existed logical device.
		Result DestroyLogicalDevice(LogicalDevice * pLogicalDevice);

		//!	@brief	Check if device extension is available.
		bool IsExtensionAvailable(std::string extensionName) const;

		//!	@brief	Check if device layer is available.
		bool IsLayerAvailable(std::string layerName) const;

		//!	@brief	Create a logical device (not ready).
		LogicalDevice * CreateLogicalDevice();

	private:

		Instance * const						m_pInstance;

		const VkPhysicalDevice					m_hPhysicalDevice;

		std::set<LogicalDevice*>				m_pLogicalDevices;

	private:

		mutable VkPhysicalDeviceFeatures					m_Features;

		mutable VkPhysicalDeviceProperties2					m_Properties;

		mutable std::vector<VkLayerProperties>				m_AvailableLayers;

		mutable VkPhysicalDeviceMemoryProperties			m_MemoryProperties;

		mutable std::vector<VkExtensionProperties>			m_AvailableExtensions;

		mutable std::vector<VkQueueFamilyProperties>		m_QueueFamilyProperties;

		mutable VkPhysicalDeviceRayTracingPropertiesNV		m_RayTracingProperitesNV;
	};
}