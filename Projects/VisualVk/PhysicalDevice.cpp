/*************************************************************************
*********************    VisualVk_PhysicalDevice    **********************
*************************************************************************/
#include "PhysicalDevice.h"
#include "LogicalDevice.h"
#include "CommandBuffer.h"

using namespace Vk;

/*************************************************************************
**************************    PhysicalDevice    **************************
*************************************************************************/
PhysicalDevice::PhysicalDevice(VkPhysicalDevice hPhysicalDevice) : m_hPhysicalDevice(hPhysicalDevice)
{
	vkGetPhysicalDeviceMemoryProperties(m_hPhysicalDevice, &m_MemoryProperties);

	vkGetPhysicalDeviceProperties(m_hPhysicalDevice, &m_Properties);

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

	return Result::eErrorInvalidExternalHandle;
}


bool PhysicalDevice::IsSurfaceSupported(VkSurfaceKHR hSurface, uint32_t queueFamilyIndex) const
{
	VkBool32 isSupported = VK_FALSE;

	if ((hSurface != VK_NULL_HANDLE) && (queueFamilyIndex < m_QueueFamilyProperties.size()))
	{
		vkGetPhysicalDeviceSurfaceSupportKHR(m_hPhysicalDevice, queueFamilyIndex, hSurface, &isSupported);
	}

	return isSupported == VK_TRUE;
}


std::vector<VkPresentModeKHR> PhysicalDevice::GetSurfacePresentModes(VkSurfaceKHR hSurface) const
{
	uint32_t presentModeCount = 0;

	std::vector<VkPresentModeKHR> PresentModes;

	if (hSurface != VK_NULL_HANDLE)
	{
		vkGetPhysicalDeviceSurfacePresentModesKHR(m_hPhysicalDevice, hSurface, &presentModeCount, nullptr);

		PresentModes.resize(presentModeCount);

		vkGetPhysicalDeviceSurfacePresentModesKHR(m_hPhysicalDevice, hSurface, &presentModeCount, PresentModes.data());
	}

	return PresentModes;
}


std::vector<VkSurfaceFormatKHR> PhysicalDevice::GetSurfaceFormats(VkSurfaceKHR hSurface) const
{
	uint32_t SurfaceFormatCount = 0;

	std::vector<VkSurfaceFormatKHR> SurfaceFormats;

	if (hSurface != VK_NULL_HANDLE)
	{
		vkGetPhysicalDeviceSurfaceFormatsKHR(m_hPhysicalDevice, hSurface, &SurfaceFormatCount, nullptr);

		SurfaceFormats.resize(SurfaceFormatCount);

		vkGetPhysicalDeviceSurfaceFormatsKHR(m_hPhysicalDevice, hSurface, &SurfaceFormatCount, SurfaceFormats.data());
	}

	return SurfaceFormats;
}


VkSurfaceCapabilitiesKHR PhysicalDevice::GetSurfaceCapabilities(VkSurfaceKHR hSurface) const
{
	VkSurfaceCapabilitiesKHR SurfaceCapabilities = {};

	if (hSurface != VK_NULL_HANDLE)
	{
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_hPhysicalDevice, hSurface, &SurfaceCapabilities);
	}

	return SurfaceCapabilities;
}


VkFormatProperties PhysicalDevice::GetFormatProperties(VkFormat eFormat) const
{
	VkFormatProperties FormatProperties = {};

	vkGetPhysicalDeviceFormatProperties(m_hPhysicalDevice, eFormat, &FormatProperties);

	return FormatProperties;
}


uint32_t PhysicalDevice::GetMemoryTypeIndex(uint32_t MemoryTypeBits, VkMemoryPropertyFlags ePropertyFlags) const
{
	for (uint32_t i = 0; i < m_MemoryProperties.memoryTypeCount; i++)
	{
		if ((MemoryTypeBits & 0x00000001u) == 0x00000001u)
		{
			if ((m_MemoryProperties.memoryTypes[i].propertyFlags & ePropertyFlags) == ePropertyFlags)
			{
				return i;
			}
		}

		MemoryTypeBits >>= 1;
	}

	return VK_INVALID_INDEX;
}


uint32_t PhysicalDevice::GetPresentQueueFamilyIndex(VkSurfaceKHR hSurface) const
{
	for (uint32_t i = 0; i < m_QueueFamilyProperties.size(); i++)
	{
		if (this->IsSurfaceSupported(hSurface, i))
		{
			return i;
		}
	}

	return VK_INVALID_INDEX;
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

	return VK_INVALID_INDEX;
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

	return VK_INVALID_INDEX;
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

	return VK_INVALID_INDEX;
}


const std::vector<VkQueueFamilyProperties> & PhysicalDevice::GetQueueFamilies() const
{
	if (m_QueueFamilyProperties.empty())
	{
		uint32_t propertyCount = 0;

		vkGetPhysicalDeviceQueueFamilyProperties(m_hPhysicalDevice, &propertyCount, nullptr);

		m_QueueFamilyProperties.resize(propertyCount);

		vkGetPhysicalDeviceQueueFamilyProperties(m_hPhysicalDevice, &propertyCount, m_QueueFamilyProperties.data());
	}

	return m_QueueFamilyProperties;
}


const std::vector<VkExtensionProperties> & PhysicalDevice::GetAvailableExtensions() const
{
	if (m_AvailableExtensions.empty())
	{
		uint32_t propertyCount = 0;

		vkEnumerateDeviceExtensionProperties(m_hPhysicalDevice, nullptr, &propertyCount, nullptr);

		m_AvailableExtensions.resize(propertyCount);

		vkEnumerateDeviceExtensionProperties(m_hPhysicalDevice, nullptr, &propertyCount, m_AvailableExtensions.data());
	}

	return m_AvailableExtensions;
}


const std::vector<VkLayerProperties> & PhysicalDevice::GetAvailableLayers() const
{
	if (m_AvailableLayers.empty())
	{
		uint32_t propertyCount = 0;

		vkEnumerateDeviceLayerProperties(m_hPhysicalDevice, &propertyCount, nullptr);

		m_AvailableLayers.resize(propertyCount);

		vkEnumerateDeviceLayerProperties(m_hPhysicalDevice, &propertyCount, m_AvailableLayers.data());
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