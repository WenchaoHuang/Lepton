/*************************************************************************
**********************    VisualVk_Win32Surface    ***********************
*************************************************************************/
#include "Win32Surface.h"

using namespace Vk;

/*************************************************************************
***************************    Win32Surface    ***************************
*************************************************************************/
Win32Surface::Win32Surface() : m_hInstance(VK_NULL_HANDLE), m_hSurface(VK_NULL_HANDLE)
{

}


Win32Surface::Win32Surface(VkInstance hInstance, HWND hWindow) : Win32Surface()
{
	this->Create(hInstance, hWindow);
}


Result Win32Surface::Create(VkInstance hInstance, HWND hWindow)
{
	if (hWindow == VK_NULL_HANDLE)		return Result::eErrorInvalidExternalHandle;
	if (hInstance == VK_NULL_HANDLE)	return Result::eErrorInvalidExternalHandle;

	VkWin32SurfaceCreateInfoKHR			CreateInfo = {};
	CreateInfo.sType					= VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	CreateInfo.pNext					= nullptr;
	CreateInfo.flags					= 0;
	CreateInfo.hinstance				= GetModuleHandle(NULL);
	CreateInfo.hwnd						= hWindow;

	VkSurfaceKHR hSurface = VK_NULL_HANDLE;

	Result eResult = VK_RESULT_CAST(vkCreateWin32SurfaceKHR(hInstance, &CreateInfo, nullptr, &hSurface));

	if (eResult == Result::eSuccess)
	{
		this->Destroy();

		m_hInstance = hInstance;

		m_hSurface = hSurface;
	}

	return eResult;
}


void Win32Surface::Destroy()
{
	if (m_hSurface != VK_NULL_HANDLE)
	{
		vkDestroySurfaceKHR(m_hInstance, m_hSurface, nullptr);

		m_hInstance = VK_NULL_HANDLE;

		m_hSurface = VK_NULL_HANDLE;
	}
}


Win32Surface::~Win32Surface()
{
	this->Destroy();
}