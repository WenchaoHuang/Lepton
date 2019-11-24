/*************************************************************************
************************    Lava_Win32Surface    *************************
*************************************************************************/

#include "Win32Surface.h"

using namespace Lava;

/*************************************************************************
***************************    Win32Surface    ***************************
*************************************************************************/
Win32Surface::UniqueHandle::UniqueHandle(VkInstance hInstance, VkSurfaceKHR hSurface) : m_hInstance(hInstance), m_hSurface(hSurface)
{

}


Result Win32Surface::Create(VkInstance hInstance, HWND hWindow)
{
	if (hWindow == VK_NULL_HANDLE)		return Result::eErrorInvalidExternalHandle;
	if (hInstance == VK_NULL_HANDLE)	return Result::eErrorInvalidInstanceHandle;

	VkWin32SurfaceCreateInfoKHR			CreateInfo = {};
	CreateInfo.sType					= VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	CreateInfo.pNext					= nullptr;
	CreateInfo.flags					= 0;
	CreateInfo.hinstance				= GetModuleHandle(NULL);
	CreateInfo.hwnd						= hWindow;

	VkSurfaceKHR hSurface = VK_NULL_HANDLE;

	Result eResult = LAVA_RESULT_CAST(vkCreateWin32SurfaceKHR(hInstance, &CreateInfo, nullptr, &hSurface));

	if (eResult == Result::eSuccess)
	{
		m_spUniqueHandle = std::make_shared<UniqueHandle>(hInstance, hSurface);
	}

	return eResult;
}


Win32Surface::UniqueHandle::~UniqueHandle() noexcept
{
	if (m_hSurface != VK_NULL_HANDLE)
	{
		vkDestroySurfaceKHR(m_hInstance, m_hSurface, nullptr);
	}
}