/*************************************************************************
************************    VisualVk_Instance    *************************
*************************************************************************/
#include "PhysicalDevice.h"
#include "Instance.h"

using namespace Vk;

static Instance * sg_pInstance			= nullptr;

std::vector<VkLayerProperties>			Instance::sm_LayerProperties;

std::vector<VkExtensionProperties>		Instance::sm_ExtensionProperties;

#define VK_INSTANCE_PROC_ADDR(name)		(PFN_##name)GetProcAddress(#name)

/*************************************************************************
*****************************    Instance    *****************************
*************************************************************************/
Instance::Instance(VkInstance hInstance) : m_hInstance(hInstance)
{
	uint32_t PhysicalDeviceCount = 0;

	vkEnumeratePhysicalDevices(m_hInstance, &PhysicalDeviceCount, nullptr);

	std::vector<VkPhysicalDevice> hPhysicalDevices(PhysicalDeviceCount);

	vkEnumeratePhysicalDevices(m_hInstance, &PhysicalDeviceCount, hPhysicalDevices.data());

	m_pPhysicalDevices.resize(hPhysicalDevices.size());

	for (size_t i = 0; i < m_pPhysicalDevices.size(); i++)
	{
		m_pPhysicalDevices[i] = new PhysicalDevice(hPhysicalDevices[i]);
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
#endif

	VkApplicationInfo					AppInfo = {};
	AppInfo.sType						= VK_STRUCTURE_TYPE_APPLICATION_INFO;
	AppInfo.pNext						= nullptr;
	AppInfo.pEngineName					= "GraceEngine";
	AppInfo.pApplicationName			= "GraceEngine";
	AppInfo.applicationVersion			= VK_MAKE_VERSION(1, 0, 0);
	AppInfo.engineVersion				= VK_MAKE_VERSION(1, 0, 0);
	AppInfo.apiVersion					= VK_API_VERSION_1_0;

	VkInstanceCreateInfo				CreateInfo = {};
	CreateInfo.sType					= VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	CreateInfo.pNext					= nullptr;
	CreateInfo.flags					= 0;
	CreateInfo.pApplicationInfo			= &AppInfo;
	CreateInfo.enabledExtensionCount	= (uint32_t)pExtensions.size();
	CreateInfo.ppEnabledExtensionNames	= pExtensions.data();
	CreateInfo.enabledLayerCount		= (uint32_t)pLayers.size();
	CreateInfo.ppEnabledLayerNames		= pLayers.data();

	VkInstance hInstance = VK_NULL_HANDLE;

	if (vkCreateInstance(&CreateInfo, nullptr, &hInstance) == VK_SUCCESS)
	{
		sg_pInstance = new Instance(hInstance);
	}

	return sg_pInstance;
}


VkDebugReportCallbackEXT Instance::CreateDebugReportCallback(VkDebugReportFlagsEXT eFlags,
															 PFN_vkDebugReportCallbackEXT pfnCallback)
{
	VkDebugReportCallbackEXT hDebugReportCallback = VK_NULL_HANDLE;

	PFN_vkCreateDebugReportCallbackEXT pfnCreateDebugReportCallback = nullptr;

	pfnCreateDebugReportCallback = VK_INSTANCE_PROC_ADDR(vkCreateDebugReportCallbackEXT);

	if (pfnCreateDebugReportCallback != nullptr)
	{
		VkDebugReportCallbackCreateInfoEXT	CreateInfo = {};
		CreateInfo.sType					= VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
		CreateInfo.pNext					= nullptr;
		CreateInfo.flags					= eFlags;
		CreateInfo.pfnCallback				= pfnCallback;
		CreateInfo.pUserData				= nullptr;

		pfnCreateDebugReportCallback(m_hInstance, &CreateInfo, nullptr, &hDebugReportCallback);
	}

	return hDebugReportCallback;
}


void Instance::DestroyDebugReportCallback(VkDebugReportCallbackEXT hDebugReportCallback)
{
	PFN_vkDestroyDebugReportCallbackEXT pfnDestroyDebugReportCallback = nullptr;

	pfnDestroyDebugReportCallback = VK_INSTANCE_PROC_ADDR(vkDestroyDebugReportCallbackEXT);

	if (pfnDestroyDebugReportCallback != nullptr)
	{
		pfnDestroyDebugReportCallback(m_hInstance, hDebugReportCallback, nullptr);
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


const std::vector<VkLayerProperties> & Instance::GetLayerProperties()
{
	if (sm_LayerProperties.empty())
	{
		uint32_t PropertyCount = 0;

		vkEnumerateInstanceLayerProperties(&PropertyCount, nullptr);

		sm_LayerProperties.resize(PropertyCount);

		vkEnumerateInstanceLayerProperties(&PropertyCount, sm_LayerProperties.data());
	}

	return sm_LayerProperties;
}


const std::vector<VkExtensionProperties> & Instance::GetExtensionProperties()
{
	if (sm_ExtensionProperties.empty())
	{
		uint32_t PropertyCount = 0;

		vkEnumerateInstanceExtensionProperties(nullptr, &PropertyCount, nullptr);

		sm_ExtensionProperties.resize(PropertyCount);

		vkEnumerateInstanceExtensionProperties(nullptr, &PropertyCount, sm_ExtensionProperties.data());
	}

	return sm_ExtensionProperties;
}


VkBool32 Instance::IsExtensionAvailable(std::string TargetName)
{
	auto & ExtensionProperties = GetExtensionProperties();

	for (size_t i = 0; i < ExtensionProperties.size(); i++)
	{
		if (TargetName == ExtensionProperties[i].extensionName)
		{
			return VK_TRUE;
		}
	}

	return VK_FALSE;
}


const std::vector<PhysicalDevice*> & Instance::GetPhysicalDevices() const
{
	return m_pPhysicalDevices;
}


PFN_vkVoidFunction Instance::GetProcAddress(const char * pName) const
{
	return vkGetInstanceProcAddr(m_hInstance, pName);
}


void Instance::DestroySurface(VkSurfaceKHR hSurface)
{
	vkDestroySurfaceKHR(m_hInstance, hSurface, nullptr);
}


Instance::~Instance() noexcept
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
	}

	sg_pInstance = nullptr;
}