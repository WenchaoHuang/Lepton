/*************************************************************************
*********************    VisualVk_PhysicalDevice    **********************
*************************************************************************/
#include "PhysicalDevice.h"
#include "LogicalDevice.h"

using namespace Vk;

/*************************************************************************
**************************    PhysicalDevice    **************************
*************************************************************************/
PhysicalDevice::PhysicalDevice(VkPhysicalDevice hDevice) : m_hPhysicalDevice(hDevice)
{

}


VkBool32 PhysicalDevice::IsSurfaceSupported(VkSurfaceKHR hSurface, uint32_t QueueFamilyIndex) const
{
	VkBool32 IsSupported = VK_FALSE;

	if (QueueFamilyIndex >= m_QueueFamilyProperties.size())		return VK_FALSE;

	vkGetPhysicalDeviceSurfaceSupportKHR(m_hPhysicalDevice, QueueFamilyIndex, hSurface, &IsSupported);

	return IsSupported;
}


std::vector<VkPresentModeKHR> PhysicalDevice::GetSurfacePresentModes(VkSurfaceKHR hSurface) const
{
	uint32_t PresentModeCount = 0;

	vkGetPhysicalDeviceSurfacePresentModesKHR(m_hPhysicalDevice, hSurface, &PresentModeCount, nullptr);

	std::vector<VkPresentModeKHR> SurfacePresentModes(PresentModeCount);

	vkGetPhysicalDeviceSurfacePresentModesKHR(m_hPhysicalDevice, hSurface, &PresentModeCount, SurfacePresentModes.data());

	return SurfacePresentModes;
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


const std::vector<VkQueueFamilyProperties> & PhysicalDevice::GetQueueFamilyProperties() const
{
	return m_QueueFamilyProperties;
}


const std::vector<VkExtensionProperties> & PhysicalDevice::GetExtensionProperties() const
{
	return m_ExtensionProperties;
}


const VkPhysicalDeviceMemoryProperties & PhysicalDevice::GetMemoryProperties() const
{
	return m_MemoryProperties;
}


const std::vector<VkLayerProperties> & PhysicalDevice::GetLayerProperties() const
{
	return m_LayerProperties;
}


const VkPhysicalDeviceProperties & PhysicalDevice::GetProperties() const
{
	return m_Properties;
}


const VkPhysicalDeviceFeatures & PhysicalDevice::GetFeatures() const
{
	return m_Features;
}


VkBool32 PhysicalDevice::IsExtensionAvailable(std::string TargetName) const
{
	for (size_t i = 0; i < m_ExtensionProperties.size(); i++)
	{
		if (TargetName == m_ExtensionProperties[i].extensionName)
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