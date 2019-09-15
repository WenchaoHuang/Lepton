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
PhysicalDevice::PhysicalDevice(Instance * pInstance, VkPhysicalDevice hPhysicalDevice) : m_pInstance(pInstance), m_hPhysicalDevice(hPhysicalDevice)
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


VkFormatProperties PhysicalDevice::GetFormatProperties(VkFormat eFormat) const
{
	VkFormatProperties FormatProperties = {};

	vkGetPhysicalDeviceFormatProperties(m_hPhysicalDevice, eFormat, &FormatProperties);

	return FormatProperties;
}


uint32_t PhysicalDevice::GetMemoryTypeIndex(uint32_t memoryTypeBits, Flags<MemoryProperty> ePropertyFlags) const
{
	for (uint32_t i = 0; i < m_MemoryProperties.memoryTypeCount; i++)
	{
		if ((memoryTypeBits & 0x0001u) == 0x0001u)
		{
			if ((m_MemoryProperties.memoryTypes[i].propertyFlags & ePropertyFlags) == ePropertyFlags)
			{
				return i;
			}
		}

		memoryTypeBits >>= 1;
	}

	return VK_INVALID_INDEX;
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