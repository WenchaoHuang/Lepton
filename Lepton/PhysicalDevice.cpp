/*************************************************************************
**********************    Lepton_PhysicalDevice    ***********************
*************************************************************************/

#include "Commands.h"
#include "Instance.h"
#include "LogicalDevice.h"
#include "PhysicalDevice.h"

using namespace Lepton;

/*************************************************************************
**************************    PhysicalDevice    **************************
*************************************************************************/
PhysicalDevice::PhysicalDevice(Instance * pInstance, VkPhysicalDevice hPhysicalDevice) : m_pInstance(pInstance), m_hPhysicalDevice(hPhysicalDevice)
{
	m_Properties.sType					= VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
	m_Properties.pNext					= pInstance->IsExtensionEnabled(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME) ? m_Properties.pNext = &m_RayTracingProperitesNV : nullptr;
	m_RayTracingProperitesNV.sType		= VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PROPERTIES_NV;
	m_RayTracingProperitesNV.pNext		= nullptr;

	vkGetPhysicalDeviceMemoryProperties(m_hPhysicalDevice, &m_MemoryProperties);

	vkGetPhysicalDeviceProperties2(m_hPhysicalDevice, &m_Properties);

	vkGetPhysicalDeviceFeatures(m_hPhysicalDevice, &m_Features);

	this->GetAvailableExtensions();

	this->GetAvailableLayers();

	this->GetQueueFamilies();
}


LogicalDevice * PhysicalDevice::CreateLogicalDevice()
{
	LogicalDevice * pLogicalDevice = new LogicalDevice(this);

	m_pLogicalDevices.insert(pLogicalDevice);

	return pLogicalDevice;
}


Result PhysicalDevice::DestroyLogicalDevice(LogicalDevice * pLogicalDevice)
{
	if (m_pLogicalDevices.erase(pLogicalDevice) != 0)
	{
		delete pLogicalDevice;

		return Result::eSuccess;
	}

	return Result::eErrorInvalidDeviceHandle;
}


VkFormatProperties PhysicalDevice::GetFormatProperties(vk::Format eFormat) const
{
	VkFormatProperties FormatProperties = {};

	vkGetPhysicalDeviceFormatProperties(m_hPhysicalDevice, static_cast<VkFormat>(eFormat), &FormatProperties);

	return FormatProperties;
}


uint32_t PhysicalDevice::GetMemoryTypeIndex(uint32_t memoryTypeBits, vk::MemoryPropertyFlags eProperties) const
{
	for (uint32_t i = 0; i < m_MemoryProperties.memoryTypeCount; i++)
	{
		if ((memoryTypeBits & 0x0001u) == 0x0001u)
		{
			if ((vk::MemoryPropertyFlags(m_MemoryProperties.memoryTypes[i].propertyFlags) & eProperties) == eProperties)
			{
				return i;
			}
		}

		memoryTypeBits >>= 1;
	}

	return LAVA_INVALID_INDEX;
}


const std::vector<VkQueueFamilyProperties> & PhysicalDevice::GetQueueFamilies() const
{
	if (m_QueueFamilyProperties.empty())
	{
		uint32_t familyCount = 0;

		vkGetPhysicalDeviceQueueFamilyProperties(m_hPhysicalDevice, &familyCount, nullptr);

		m_QueueFamilyProperties.resize(familyCount);

		vkGetPhysicalDeviceQueueFamilyProperties(m_hPhysicalDevice, &familyCount, m_QueueFamilyProperties.data());
	}

	return m_QueueFamilyProperties;
}


uint32_t PhysicalDevice::GetGraphicsQueueFamilyIndex() const
{
	for (uint32_t i = 0; i < m_QueueFamilyProperties.size(); i++)
	{
		if (m_QueueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			return i;
		}
	}

	return LAVA_INVALID_INDEX;
}


uint32_t PhysicalDevice::GetTransferQueueFamilyIndex() const
{
	for (uint32_t i = 0; i < m_QueueFamilyProperties.size(); i++)
	{
		//	Find transfer queue but not graphics queue.
		if ((m_QueueFamilyProperties[i].queueFlags & VK_QUEUE_TRANSFER_BIT) &&
			((m_QueueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) == 0))
		{
			return i;
		}
	}

	//	No matching queue that supported transfer but not graphics, then find transfer queue.
	for (uint32_t i = 0; i < m_QueueFamilyProperties.size(); i++)
	{
		if (m_QueueFamilyProperties[i].queueFlags & VK_QUEUE_TRANSFER_BIT)
		{
			return i;
		}
	}

	return LAVA_INVALID_INDEX;
}


uint32_t PhysicalDevice::GetComputeQueueFamilyIndex() const
{
	for (uint32_t i = 0; i < m_QueueFamilyProperties.size(); i++)
	{
		//	Find computing queue but not graphics queue.
		if ((m_QueueFamilyProperties[i].queueFlags & VK_QUEUE_COMPUTE_BIT) &&
			((m_QueueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) == 0))
		{
			return i;
		}
	}

	//	No matching queue that supported computing but not graphics, then find computing queue.
	for (uint32_t i = 0; i < m_QueueFamilyProperties.size(); i++)
	{
		if (m_QueueFamilyProperties[i].queueFlags & VK_QUEUE_COMPUTE_BIT)
		{
			return i;
		}
	}

	return LAVA_INVALID_INDEX;
}


std::vector<vk::SurfaceFormatKHR> PhysicalDevice::GetSurfaceFormats(VkSurfaceKHR hSurface) const
{
	std::vector<vk::SurfaceFormatKHR> SurfaceFormats;

	if (hSurface != VK_NULL_HANDLE)
	{
		uint32_t surfaceFormatCount = 0;

		vkGetPhysicalDeviceSurfaceFormatsKHR(m_hPhysicalDevice, hSurface, &surfaceFormatCount, nullptr);

		SurfaceFormats.resize(surfaceFormatCount);

		vkGetPhysicalDeviceSurfaceFormatsKHR(m_hPhysicalDevice, hSurface, &surfaceFormatCount, reinterpret_cast<VkSurfaceFormatKHR*>(SurfaceFormats.data()));
	}

	return SurfaceFormats;
}


std::vector<vk::PresentModeKHR> PhysicalDevice::GetSurfacePresentModes(VkSurfaceKHR hSurface) const
{
	std::vector<vk::PresentModeKHR> PresentModes;

	if (hSurface != VK_NULL_HANDLE)
	{
		uint32_t presentModeCount = 0;

		vkGetPhysicalDeviceSurfacePresentModesKHR(m_hPhysicalDevice, hSurface, &presentModeCount, nullptr);

		PresentModes.resize(presentModeCount);

		vkGetPhysicalDeviceSurfacePresentModesKHR(m_hPhysicalDevice, hSurface, &presentModeCount, reinterpret_cast<VkPresentModeKHR*>(PresentModes.data()));
	}

	return PresentModes;
}


vk::SurfaceCapabilitiesKHR PhysicalDevice::GetSurfaceCapabilities(VkSurfaceKHR hSurface) const
{
	vk::SurfaceCapabilitiesKHR capabilities;

	if (hSurface != VK_NULL_HANDLE)
	{
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_hPhysicalDevice, hSurface, reinterpret_cast<VkSurfaceCapabilitiesKHR*>(&capabilities));
	}

	return capabilities;
}


bool PhysicalDevice::IsSurfaceSupported(VkSurfaceKHR hSurface, uint32_t queueFamilyIndex) const
{
	if (hSurface != VK_NULL_HANDLE)
	{
		VkBool32 isSupported = VK_FALSE;

		vkGetPhysicalDeviceSurfaceSupportKHR(m_hPhysicalDevice, queueFamilyIndex, hSurface, &isSupported);

		return isSupported == VK_TRUE;
	}

	return false;
}


const std::vector<VkExtensionProperties> & PhysicalDevice::GetAvailableExtensions() const
{
	if (m_AvailableExtensions.empty())
	{
		uint32_t extensionCount = 0;

		vkEnumerateDeviceExtensionProperties(m_hPhysicalDevice, nullptr, &extensionCount, nullptr);

		m_AvailableExtensions.resize(extensionCount);

		vkEnumerateDeviceExtensionProperties(m_hPhysicalDevice, nullptr, &extensionCount, m_AvailableExtensions.data());
	}

	return m_AvailableExtensions;
}


const std::vector<VkLayerProperties> & PhysicalDevice::GetAvailableLayers() const
{
	if (m_AvailableLayers.empty())
	{
		uint32_t layerCount = 0;

		vkEnumerateDeviceLayerProperties(m_hPhysicalDevice, &layerCount, nullptr);

		m_AvailableLayers.resize(layerCount);

		vkEnumerateDeviceLayerProperties(m_hPhysicalDevice, &layerCount, m_AvailableLayers.data());
	}

	return m_AvailableLayers;
}


bool PhysicalDevice::IsExtensionAvailable(std::string extensionName) const
{
	auto & AvailableExtensions = this->GetAvailableExtensions();

	for (size_t i = 0; i < AvailableExtensions.size(); i++)
	{
		if (extensionName == AvailableExtensions[i].extensionName)
		{
			return true;
		}
	}

	return false;
}


bool PhysicalDevice::IsLayerAvailable(std::string layerName) const
{
	auto & AvailableLayers = this->GetAvailableLayers();

	for (size_t i = 0; i < AvailableLayers.size(); i++)
	{
		if (layerName == AvailableLayers[i].layerName)
		{
			return true;
		}
	}

	return false;
}


PhysicalDevice::~PhysicalDevice() noexcept
{
	for (auto pLogicalDevice : m_pLogicalDevices)
	{
		delete pLogicalDevice;
	}
}