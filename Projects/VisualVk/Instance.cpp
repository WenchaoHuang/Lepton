/*************************************************************************
************************    VisualVk_Instance    *************************
*************************************************************************/
#include "PhysicalDevice.h"
#include "Instance.h"

using namespace Vk;

static Instance * sg_pInstance			= nullptr;

std::vector<VkLayerProperties>			Instance::sm_AvailableLayers;

std::vector<VkExtensionProperties>		Instance::sm_AvailableExtensions;

#define VK_INSTANCE_PROC_ADDR(name)		(PFN_##name)vkGetInstanceProcAddr(m_hInstance, #name)

/*************************************************************************
*****************************    Instance    *****************************
*************************************************************************/
Instance::Instance(VkInstance hInstance) : m_hInstance(hInstance), m_hDebugReport(VK_NULL_HANDLE)
{
	uint32_t PhysicalDeviceCount = 0;

	vkEnumeratePhysicalDevices(m_hInstance, &PhysicalDeviceCount, nullptr);

	std::vector<VkPhysicalDevice> hPhysicalDevices(PhysicalDeviceCount);

	vkEnumeratePhysicalDevices(m_hInstance, &PhysicalDeviceCount, hPhysicalDevices.data());

	for (size_t i = 0; i < hPhysicalDevices.size(); i++)
	{
		m_pPhysicalDevices.push_back(new PhysicalDevice(hPhysicalDevices[i]));
	}
}


Instance * Instance::GetCurrent()
{
	if (sg_pInstance != nullptr)	return sg_pInstance;

	std::vector<const char*>		pLayers;
	std::vector<const char*>		pExtensions;

	if (IsExtensionAvailable(VK_KHR_SURFACE_EXTENSION_NAME))
		pExtensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);

	if (IsExtensionAvailable(VK_KHR_WIN32_SURFACE_EXTENSION_NAME))
		pExtensions.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
#if defined(_DEBUG)
	if (IsExtensionAvailable(VK_EXT_DEBUG_REPORT_EXTENSION_NAME))
		pExtensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);

	pLayers.push_back("VK_LAYER_LUNARG_standard_validation");

	Instance::GetLayerProperties();
#endif

	VkApplicationInfo						AppInfo = {};
	AppInfo.sType							= VK_STRUCTURE_TYPE_APPLICATION_INFO;
	AppInfo.pNext							= nullptr;
	AppInfo.pEngineName						= "VisualVk";
	AppInfo.pApplicationName				= "VisualVk";
	AppInfo.applicationVersion				= VK_MAKE_VERSION(1, 0, 0);
	AppInfo.engineVersion					= VK_MAKE_VERSION(1, 0, 0);
	AppInfo.apiVersion						= VK_API_VERSION_1_0;

	VkInstanceCreateInfo					CreateInfo = {};
	CreateInfo.sType						= VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	CreateInfo.pNext						= nullptr;
	CreateInfo.flags						= 0;
	CreateInfo.pApplicationInfo				= &AppInfo;
	CreateInfo.enabledExtensionCount		= static_cast<uint32_t>(pExtensions.size());
	CreateInfo.ppEnabledExtensionNames		= pExtensions.data();
	CreateInfo.enabledLayerCount			= static_cast<uint32_t>(pLayers.size());
	CreateInfo.ppEnabledLayerNames			= pLayers.data();

	VkInstance hInstance = VK_NULL_HANDLE;

	if (vkCreateInstance(&CreateInfo, nullptr, &hInstance) == VK_SUCCESS)
	{
		sg_pInstance = new Instance(hInstance);
	}

	return sg_pInstance;
}


void Instance::RegisterDebugReportCallback(VkDebugReportFlagsEXT eFlags, PFN_vkDebugReportCallbackEXT pfnCallback)
{
	VkDebugReportCallbackEXT hDebugReportCallback = VK_NULL_HANDLE;

	PFN_vkCreateDebugReportCallbackEXT pfnCreateDebugReportCallback = nullptr;

	pfnCreateDebugReportCallback = VK_INSTANCE_PROC_ADDR(vkCreateDebugReportCallbackEXT);

	if (pfnCreateDebugReportCallback != nullptr)
	{
		VkDebugReportCallbackCreateInfoEXT		CreateInfo = {};
		CreateInfo.sType						= VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
		CreateInfo.pNext						= nullptr;
		CreateInfo.flags						= eFlags;
		CreateInfo.pfnCallback					= pfnCallback;
		CreateInfo.pUserData					= nullptr;

		if (pfnCreateDebugReportCallback(m_hInstance, &CreateInfo, nullptr, &hDebugReportCallback) == VK_SUCCESS)
		{
			this->UnregisterDebugReportCallback();

			m_hDebugReport = hDebugReportCallback;
		}
	}
}


void Instance::UnregisterDebugReportCallback()
{
	if (m_hDebugReport != VK_NULL_HANDLE)
	{
		PFN_vkDestroyDebugReportCallbackEXT pfnDestroyDebugReportCallback = nullptr;

		pfnDestroyDebugReportCallback = VK_INSTANCE_PROC_ADDR(vkDestroyDebugReportCallbackEXT);

		if (pfnDestroyDebugReportCallback != nullptr)
		{
			pfnDestroyDebugReportCallback(m_hInstance, m_hDebugReport, nullptr);

			m_hDebugReport = VK_NULL_HANDLE;
		}
	}
}


VkSurfaceKHR Instance::CreateWin32Surface(HWND hWindow)
{
	VkWin32SurfaceCreateInfoKHR		CreateInfo = {};
	CreateInfo.sType				= VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	CreateInfo.pNext				= nullptr;
	CreateInfo.flags				= 0;
	CreateInfo.hinstance			= GetModuleHandle(nullptr);
	CreateInfo.hwnd					= hWindow;

	VkSurfaceKHR hSurface = VK_NULL_HANDLE;

	vkCreateWin32SurfaceKHR(m_hInstance, &CreateInfo, nullptr, &hSurface);

	return hSurface;
}


const std::vector<PhysicalDevice*> & Instance::GetPhysicalDevices() const
{
	return m_pPhysicalDevices;
}


const std::vector<VkLayerProperties> & Instance::GetLayerProperties()
{
	if (sm_AvailableLayers.empty())
	{
		uint32_t PropertyCount = 0;

		vkEnumerateInstanceLayerProperties(&PropertyCount, nullptr);

		sm_AvailableLayers.resize(PropertyCount);

		vkEnumerateInstanceLayerProperties(&PropertyCount, sm_AvailableLayers.data());
	}

	return sm_AvailableLayers;
}


const std::vector<VkExtensionProperties> & Instance::GetExtensionProperties()
{
	if (sm_AvailableExtensions.empty())
	{
		uint32_t PropertyCount = 0;

		vkEnumerateInstanceExtensionProperties(nullptr, &PropertyCount, nullptr);

		sm_AvailableExtensions.resize(PropertyCount);

		vkEnumerateInstanceExtensionProperties(nullptr, &PropertyCount, sm_AvailableExtensions.data());
	}

	return sm_AvailableExtensions;
}


VkBool32 Instance::IsExtensionAvailable(std::string extensionName)
{
	auto & extensionProperties = GetExtensionProperties();

	for (size_t i = 0; i < extensionProperties.size(); i++)
	{
		if (extensionName == extensionProperties[i].extensionName)
		{
			return VK_TRUE;
		}
	}

	return VK_FALSE;
}


VkBool32 Instance::IsLayerAvailable(std::string layerName)
{
	auto & layerProperties = Instance::GetLayerProperties();

	for (size_t i = 0; i < layerProperties.size(); i++)
	{
		if (layerName == layerProperties[i].layerName)
		{
			return VK_TRUE;
		}
	}

	return VK_FALSE;
}


void Instance::DestroySurface(VkSurfaceKHR hSurface)
{
	vkDestroySurfaceKHR(m_hInstance, hSurface, nullptr);
}


Instance::~Instance()
{
	for (auto pPhysicalDevice : m_pPhysicalDevices)
	{
		delete pPhysicalDevice;
	}

	vkDestroyInstance(m_hInstance, nullptr);
}


void Instance::Destroy()
{
	if (sg_pInstance != nullptr)
	{
		delete sg_pInstance;

		sg_pInstance = nullptr;
	}
}