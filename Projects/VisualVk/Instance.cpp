/*************************************************************************
************************    VisualVk_Instance    *************************
*************************************************************************/
#include "PhysicalDevice.h"
#include "Instance.h"

using namespace Vk;

std::vector<VkLayerProperties>			Instance::sm_AvailableLayers;
std::vector<VkExtensionProperties>		Instance::sm_AvailableExtensions;

/*************************************************************************
*****************************    Instance    *****************************
*************************************************************************/
Instance::Instance() : m_hInstance(VK_NULL_HANDLE)
{

}


Result Instance::Create(ArrayProxy<const char*> pExtensions, ArrayProxy<const char*> pLayers)
{
	if (m_hInstance == VK_NULL_HANDLE)
	{
		VkApplicationInfo							AppInfo = {};
		AppInfo.sType								= VK_STRUCTURE_TYPE_APPLICATION_INFO;
		AppInfo.pNext								= nullptr;
		AppInfo.pEngineName							= "VisualVk";
		AppInfo.pApplicationName					= "VisualVk";
		AppInfo.applicationVersion					= VK_MAKE_VERSION(1, 0, 0);
		AppInfo.engineVersion						= VK_MAKE_VERSION(1, 0, 0);
		AppInfo.apiVersion							= VK_API_VERSION_1_0;

		VkInstanceCreateInfo						CreateInfo = {};
		CreateInfo.sType							= VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		CreateInfo.pNext							= nullptr;
		CreateInfo.flags							= 0;
		CreateInfo.pApplicationInfo					= &AppInfo;
		CreateInfo.enabledExtensionCount			= pExtensions.size();
		CreateInfo.ppEnabledExtensionNames			= pExtensions.data();
		CreateInfo.enabledLayerCount				= pLayers.size();
		CreateInfo.ppEnabledLayerNames				= pLayers.data();

		VkResult eResult = vkCreateInstance(&CreateInfo, nullptr, &m_hInstance);

		if (eResult == VK_SUCCESS)
		{
			uint32_t physicalDeviceCount = 0;

			vkEnumeratePhysicalDevices(m_hInstance, &physicalDeviceCount, nullptr);

			std::vector<VkPhysicalDevice> hPhysicalDevices(physicalDeviceCount);

			vkEnumeratePhysicalDevices(m_hInstance, &physicalDeviceCount, hPhysicalDevices.data());

			m_pPhysicalDevices.resize(physicalDeviceCount);

			for (size_t i = 0; i < hPhysicalDevices.size(); i++)
			{
				m_pPhysicalDevices[i] = new PhysicalDevice(this, hPhysicalDevices[i]);
			}
		}

		return static_cast<Result>(eResult);
	}

	return Result::eSuccess;
}


VkSurfaceKHR Instance::CreateSurface(HWND hWindow)
{
	VkWin32SurfaceCreateInfoKHR		CreateInfo = {};
	CreateInfo.sType				= VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	CreateInfo.pNext				= nullptr;
	CreateInfo.flags				= 0;
	CreateInfo.hinstance			= GetModuleHandle(nullptr);
	CreateInfo.hwnd					= hWindow;

	VkSurfaceKHR hSurface = VK_NULL_HANDLE;

	if (m_hInstance != VK_NULL_HANDLE)
	{
		if (vkCreateWin32SurfaceKHR(m_hInstance, &CreateInfo, nullptr, &hSurface) == VK_SUCCESS)
		{
			m_hSurfaces.insert(hSurface);
		}
	}

	return hSurface;
}


void Instance::DestroySurface(VkSurfaceKHR hSurface)
{
	if (m_hSurfaces.erase(hSurface) != 0)
	{
		vkDestroySurfaceKHR(m_hInstance, hSurface, nullptr);
	}
}


const std::vector<VkExtensionProperties> & Instance::GetAvailableExtensions()
{
	if (sm_AvailableExtensions.empty())
	{
		uint32_t extensionCount = 0;

		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

		sm_AvailableExtensions.resize(extensionCount);

		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, sm_AvailableExtensions.data());
	}

	return sm_AvailableExtensions;
}


const std::vector<VkLayerProperties> & Instance::GetAvailableLayers()
{
	if (sm_AvailableLayers.empty())
	{
		uint32_t layerCount = 0;

		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		sm_AvailableLayers.resize(layerCount);

		vkEnumerateInstanceLayerProperties(&layerCount, sm_AvailableLayers.data());
	}

	return sm_AvailableLayers;
}


bool Instance::IsExtensionAvilable(std::string extensionName)
{
	auto & AvailableExtensions = Instance::GetAvailableExtensions();

	for (size_t i = 0; i < AvailableExtensions.size(); i++)
	{
		if (extensionName == AvailableExtensions[i].extensionName)
		{
			return true;
		}
	}

	return false;
}


bool Instance::IsLayerAvilable(std::string layerName)
{
	auto & AvailableLayers = Instance::GetAvailableLayers();

	for (size_t i = 0; i < AvailableLayers.size(); i++)
	{
		if (layerName == AvailableLayers[i].layerName)
		{
			return true;
		}
	}

	return false;
}


PFN_vkVoidFunction Instance::GetProcAddr(const char * pName)
{
	if (m_hInstance != VK_NULL_HANDLE)
	{
		return vkGetInstanceProcAddr(m_hInstance, pName);
	}

	return nullptr;
}


void Instance::Destroy()
{
	if (m_hInstance != VK_NULL_HANDLE)
	{
		for (size_t i = 0; i < m_pPhysicalDevices.size(); i++)
		{
			delete m_pPhysicalDevices[i];
		}

		vkDestroyInstance(m_hInstance, nullptr);

		m_hInstance = VK_NULL_HANDLE;

		m_pPhysicalDevices.clear();

		m_hSurfaces.clear();
	}
}


Instance::~Instance()
{
	this->Destroy();
}