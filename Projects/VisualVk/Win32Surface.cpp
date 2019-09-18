/*************************************************************************
**********************    VisualVk_Win32Surface    ***********************
*************************************************************************/
#include "PhysicalDevice.h"
#include "Win32Surface.h"
#include "Instance.h"

using namespace Vk;

/*************************************************************************
***************************    Win32Surface    ***************************
*************************************************************************/
Win32Surface::Win32Surface() : m_hSurface(VK_NULL_HANDLE), m_pPhysicalDevice(nullptr)
{

}


Result Win32Surface::Create(PhysicalDevice * pPhysicalDevice, HWND hWindow)
{
	VkWin32SurfaceCreateInfoKHR		CreateInfo = {};
	CreateInfo.sType				= VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	CreateInfo.pNext				= nullptr;
	CreateInfo.flags				= 0;
	CreateInfo.hinstance			= GetModuleHandle(NULL);
	CreateInfo.hwnd					= hWindow;

	VkSurfaceKHR hSurface = VK_NULL_HANDLE;

	VkResult eResult = vkCreateWin32SurfaceKHR(*pPhysicalDevice->GetInstance(), &CreateInfo, nullptr, &hSurface);

	if (eResult == VK_SUCCESS)
	{
		this->Destroy();

		m_hSurface = hSurface;

		m_pPhysicalDevice = pPhysicalDevice;
	}

	return static_cast<Result>(eResult);
}


const std::vector<SurfaceFormat> & Win32Surface::GetAvailableSurfaceFormats() const
{
	if (m_AvailableSurfaceFormats.empty() && (m_hSurface != VK_NULL_HANDLE) && (m_pPhysicalDevice != nullptr))
	{
		uint32_t surfaceFormatCount = 0;

		vkGetPhysicalDeviceSurfaceFormatsKHR(*m_pPhysicalDevice, m_hSurface, &surfaceFormatCount, nullptr);

		m_AvailableSurfaceFormats.resize(surfaceFormatCount);

		vkGetPhysicalDeviceSurfaceFormatsKHR(*m_pPhysicalDevice, m_hSurface, &surfaceFormatCount, reinterpret_cast<VkSurfaceFormatKHR*>(m_AvailableSurfaceFormats.data()));
	}

	return m_AvailableSurfaceFormats;
}


const std::vector<PresentMode> & Win32Surface::GetAvailablePresentModes() const
{
	if (m_AvailablePresentModes.empty() && (m_hSurface != VK_NULL_HANDLE) && (m_pPhysicalDevice != nullptr))
	{
		uint32_t presentModeCount = 0;

		vkGetPhysicalDeviceSurfacePresentModesKHR(*m_pPhysicalDevice, m_hSurface, &presentModeCount, nullptr);

		m_AvailablePresentModes.resize(presentModeCount);

		vkGetPhysicalDeviceSurfacePresentModesKHR(*m_pPhysicalDevice, m_hSurface, &presentModeCount, reinterpret_cast<VkPresentModeKHR*>(m_AvailablePresentModes.data()));
	}

	return m_AvailablePresentModes;
}


bool Win32Surface::IsSurfaceFormatAvailable(SurfaceFormat eSrufaceFormat) const
{
	auto & AvailableFormats = this->GetAvailableSurfaceFormats();

	for (size_t i = 0; i < AvailableFormats.size(); i++)
	{
		if ((AvailableFormats[i].format == eSrufaceFormat.format) && (AvailableFormats[i].colorSpace == eSrufaceFormat.colorSpace))
		{
			return true;
		}
	}

	return false;
}


bool Win32Surface::IsQueueFamilySupported(uint32_t queueFamilyIndex) const
{
	VkBool32 isSupported = VK_FALSE;

	if ((m_hSurface != VK_NULL_HANDLE) && (m_pPhysicalDevice != nullptr))
	{
		vkGetPhysicalDeviceSurfaceSupportKHR(*m_pPhysicalDevice, queueFamilyIndex, m_hSurface, &isSupported);
	}

	return isSupported == VK_TRUE;
}


const SurfaceCapabilities & Win32Surface::GetCapabilities() const
{
	if ((m_hSurface != VK_NULL_HANDLE) && (m_pPhysicalDevice != nullptr))
	{
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(*m_pPhysicalDevice, m_hSurface, reinterpret_cast<VkSurfaceCapabilitiesKHR*>(&m_SurfaceCapabilities));
	}

	return m_SurfaceCapabilities;
}


bool Win32Surface::IsPresentModeSupported(PresentMode eMode) const
{
	auto & AvailablePresentModes = this->GetAvailablePresentModes();

	for (size_t i = 0; i < AvailablePresentModes.size(); i++)
	{
		if (AvailablePresentModes[i] == eMode)
		{
			return true;
		}
	}

	return false;
}


void Win32Surface::Destroy()
{
	if (m_hSurface != VK_NULL_HANDLE)
	{
		vkDestroySurfaceKHR(*m_pPhysicalDevice->GetInstance(), m_hSurface, nullptr);

		m_SurfaceCapabilities = SurfaceCapabilities();

		m_AvailableSurfaceFormats.clear();

		m_AvailablePresentModes.clear();

		m_pPhysicalDevice = nullptr;

		m_hSurface = VK_NULL_HANDLE;
	}
}


Win32Surface::~Win32Surface()
{
	this->Destroy();
}