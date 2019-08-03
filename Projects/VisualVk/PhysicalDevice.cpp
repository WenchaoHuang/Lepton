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

	this->GetQueueFamilyProperties();

	this->GetExtensionProperties();

	this->GetLayerProperties();
}


LogicalDevice * PhysicalDevice::CreateLogicalDevice()
{
	LogicalDevice * pLogicalDevice = new LogicalDevice(this);

	m_pLogicalDevices.insert(pLogicalDevice);

	return pLogicalDevice;
}


VkBool32 PhysicalDevice::IsSurfaceSupported(VkSurfaceKHR hSurface, uint32_t QueueFamilyIndex) const
{
	VkBool32 IsSupported = VK_FALSE;

	if (QueueFamilyIndex >= m_QueueFamilyProperties.size())			return VK_FALSE;

	vkGetPhysicalDeviceSurfaceSupportKHR(m_hPhysicalDevice, QueueFamilyIndex, hSurface, &IsSupported);

	return IsSupported;
}


std::vector<VkPresentModeKHR> PhysicalDevice::GetSurfacePresentModes(VkSurfaceKHR hSurface) const
{
	uint32_t PresentModeCount = 0;

	vkGetPhysicalDeviceSurfacePresentModesKHR(m_hPhysicalDevice, hSurface, &PresentModeCount, nullptr);

	std::vector<VkPresentModeKHR> PresentModes(PresentModeCount);

	vkGetPhysicalDeviceSurfacePresentModesKHR(m_hPhysicalDevice, hSurface, &PresentModeCount, PresentModes.data());

	return PresentModes;
}


std::vector<VkSurfaceFormatKHR> PhysicalDevice::GetSurfaceFormats(VkSurfaceKHR hSurface) const
{
	uint32_t SurfaceFormatCount = 0;

	vkGetPhysicalDeviceSurfaceFormatsKHR(m_hPhysicalDevice, hSurface, &SurfaceFormatCount, nullptr);

	std::vector<VkSurfaceFormatKHR> SurfaceFormats(SurfaceFormatCount);

	vkGetPhysicalDeviceSurfaceFormatsKHR(m_hPhysicalDevice, hSurface, &SurfaceFormatCount, SurfaceFormats.data());

	return SurfaceFormats;
}


VkSurfaceCapabilitiesKHR PhysicalDevice::GetSurfaceCapabilities(VkSurfaceKHR hSurface) const
{
	VkSurfaceCapabilitiesKHR SurfaceCapabilities;

	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_hPhysicalDevice, hSurface, &SurfaceCapabilities);

	return SurfaceCapabilities;
}


VkFormatProperties PhysicalDevice::GetFormatProperties(VkFormat eFormat) const
{
	VkFormatProperties FormatProperties;

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
		if (IsSurfaceSupported(hSurface, i))
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


const std::vector<VkQueueFamilyProperties> & PhysicalDevice::GetQueueFamilyProperties()
{
	if (m_QueueFamilyProperties.empty())
	{
		uint32_t QueueFamilyPropertyCount = 0;

		vkGetPhysicalDeviceQueueFamilyProperties(m_hPhysicalDevice, &QueueFamilyPropertyCount, nullptr);

		m_QueueFamilyProperties.resize(QueueFamilyPropertyCount);

		vkGetPhysicalDeviceQueueFamilyProperties(m_hPhysicalDevice, &QueueFamilyPropertyCount, m_QueueFamilyProperties.data());
	}

	return m_QueueFamilyProperties;
}


const std::vector<VkExtensionProperties> & PhysicalDevice::GetExtensionProperties()
{
	if (m_ExtensionProperties.empty())
	{
		uint32_t PropertyCount = 0;

		vkEnumerateDeviceExtensionProperties(m_hPhysicalDevice, nullptr, &PropertyCount, nullptr);

		m_ExtensionProperties.resize(PropertyCount);

		vkEnumerateDeviceExtensionProperties(m_hPhysicalDevice, nullptr, &PropertyCount, m_ExtensionProperties.data());
	}

	return m_ExtensionProperties;
}


const std::vector<VkLayerProperties> & PhysicalDevice::GetLayerProperties()
{
	if (m_LayerProperties.empty())
	{
		uint32_t PropertyCount = 0;

		vkEnumerateDeviceLayerProperties(m_hPhysicalDevice, &PropertyCount, nullptr);

		m_LayerProperties.resize(PropertyCount);

		vkEnumerateDeviceLayerProperties(m_hPhysicalDevice, &PropertyCount, m_LayerProperties.data());
	}

	return m_LayerProperties;
}


VkBool32 PhysicalDevice::IsExtensionAvailable(std::string extensionName) const
{
	for (size_t i = 0; i < m_ExtensionProperties.size(); i++)
	{
		if (extensionName == m_ExtensionProperties[i].extensionName)
		{
			return VK_TRUE;
		}
	}

	return VK_FALSE;
}


VkBool32 PhysicalDevice::IsLayerAvailable(std::string layerName) const
{
	for (size_t i = 0; i < m_LayerProperties.size(); i++)
	{
		if (layerName == m_LayerProperties[i].layerName)
		{
			return VK_TRUE;
		}
	}

	return VK_FALSE;
}


VkResult PhysicalDevice::DestroyLogicalDevice(LogicalDevice * pLogicalDevice)
{
	if (m_pLogicalDevices.erase(pLogicalDevice) != 0)
	{
		delete pLogicalDevice;

		return VK_SUCCESS;
	}

	return VK_ERROR_INVALID_EXTERNAL_HANDLE;
}


PhysicalDevice::~PhysicalDevice() noexcept
{
	for (auto pLogicalDevice : m_pLogicalDevices)
	{
		delete pLogicalDevice;
	}
}