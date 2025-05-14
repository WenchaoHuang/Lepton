/*************************************************************************
*************************    Lepton_Instance    **************************
*************************************************************************/

#include "Instance.h"
#include "PhysicalDevice.h"

using namespace Lepton;

/*************************************************************************
*****************************    Instance    *****************************
*************************************************************************/
Instance::Instance() : m_hInstance(VK_NULL_HANDLE)
{

}


Result Instance::Create(vk::ArrayProxy<const char*> pExtensions, vk::ArrayProxy<const char*> pLayers)
{
	VkApplicationInfo						AppInfo = {};
	AppInfo.sType							= VK_STRUCTURE_TYPE_APPLICATION_INFO;
	AppInfo.pNext							= nullptr;
	AppInfo.pEngineName						= "Lepton";
	AppInfo.pApplicationName				= "Lepton";
	AppInfo.applicationVersion				= VK_MAKE_VERSION(1, 0, 0);
	AppInfo.engineVersion					= VK_MAKE_VERSION(1, 0, 0);
	AppInfo.apiVersion						= VK_API_VERSION_1_0;

	VkInstanceCreateInfo					CreateInfo = {};
	CreateInfo.sType						= VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	CreateInfo.pNext						= nullptr;
	CreateInfo.flags						= 0;
	CreateInfo.pApplicationInfo				= &AppInfo;
	CreateInfo.enabledExtensionCount		= pExtensions.size();
	CreateInfo.ppEnabledExtensionNames		= pExtensions.data();
	CreateInfo.enabledLayerCount			= pLayers.size();
	CreateInfo.ppEnabledLayerNames			= pLayers.data();

	VkInstance hInstance = VK_NULL_HANDLE;

	VkResult eResult = vkCreateInstance(&CreateInfo, nullptr, &hInstance);

	if (eResult == VK_SUCCESS)
	{
		this->Destroy();

		m_hInstance = hInstance;

		uint32_t physicalDeviceCount = 0;

		for (auto iter : pExtensions)		m_pExtensions.insert(iter);

		vkEnumeratePhysicalDevices(m_hInstance, &physicalDeviceCount, nullptr);

		std::vector<VkPhysicalDevice> hPhysicalDevices(physicalDeviceCount);

		vkEnumeratePhysicalDevices(m_hInstance, &physicalDeviceCount, hPhysicalDevices.data());

		m_pPhysicalDevices.resize(physicalDeviceCount);

		for (size_t i = 0; i < hPhysicalDevices.size(); i++)
		{
			m_pPhysicalDevices[i] = new PhysicalDevice(this, hPhysicalDevices[i]);
		}
	}

	return LAVA_RESULT_CAST(eResult);
}


bool Instance::IsExtensionEnabled(std::string extensionName) const
{
	return m_pExtensions.find(extensionName) != m_pExtensions.end();
}


bool Instance::IsExtensionAvailable(std::string extensionName) const
{
	for (size_t i = 0; i < m_AvailableExtensions.size(); i++)
	{
		if (extensionName == m_AvailableExtensions[i].extensionName)
		{
			return true;
		}
	}

	return false;
}


bool Instance::IsLayerAvailable(std::string layerName) const
{
	auto AvailableLayers = this->GetAvailableLayers();

	for (size_t i = 0; i < AvailableLayers.size(); i++)
	{
		if (layerName == AvailableLayers[i].layerName)
		{
			return true;
		}
	}

	return false;
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

		m_pExtensions.clear();
	}
}


std::vector<VkExtensionProperties> Instance::GetAvailableExtensions()
{
	uint32_t extensionCount = 0;

	std::vector<VkExtensionProperties> availableExtensions;

	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

	availableExtensions.resize(extensionCount);

	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, availableExtensions.data());

	return availableExtensions;
}


std::vector<VkLayerProperties> Instance::GetAvailableLayers()
{
	uint32_t layerCount = 0;

	std::vector<VkLayerProperties> availableLayers;

	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	availableLayers.resize(layerCount);

	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	return availableLayers;
}


Instance::~Instance()
{
	this->Destroy();
}