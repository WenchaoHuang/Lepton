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


void Win32Surface::Destroy()
{
	if (m_hSurface != VK_NULL_HANDLE)
	{
		vkDestroySurfaceKHR(*m_pPhysicalDevice->GetInstance(), m_hSurface, nullptr);

		m_hSurface = VK_NULL_HANDLE;

		m_pPhysicalDevice = nullptr;
	}
}


Win32Surface::~Win32Surface()
{
	this->Destroy();
}