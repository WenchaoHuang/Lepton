/*************************************************************************
***********************    Lepton_LogicalDevice    ***********************
*************************************************************************/

#include <algorithm>
#include "Commands.h"
#include "LogicalDevice.h"
#include "PhysicalDevice.h"

using namespace Lepton;

/*************************************************************************
**************************    LogicalDevice    ***************************
*************************************************************************/
LogicalDevice::LogicalDevice(PhysicalDevice * pPhysicalDevice) : m_pPhysicalDevice(pPhysicalDevice)
{
	m_PerFamilQueues.resize(m_pPhysicalDevice->GetQueueFamilies().size());
}


Result LogicalDevice::StartUp(const VkPhysicalDeviceFeatures * pEnabledFeatures)
{
	if (m_hDevice != VK_NULL_HANDLE)				return Result::eSuccess;

	std::vector<const char*>						pEnabledLayers;
	std::vector<const char*>						pEnabledExtensions;

	for (auto iter : m_EnabledLayers)				pEnabledLayers.push_back(iter);
	for (auto iter : m_EnabledExtensions)			pEnabledExtensions.push_back(iter);

	std::vector<std::vector<float>>					Priorities(m_PerFamilQueues.size());
	std::vector<VkDeviceQueueCreateInfo>			QueueCreateInfos;

	for (uint32_t familyIndex = 0; familyIndex < m_PerFamilQueues.size(); familyIndex++)
	{
		if (m_PerFamilQueues[familyIndex].empty())		continue;

		for (size_t queueIndex = 0; queueIndex < m_PerFamilQueues[familyIndex].size(); queueIndex++)
		{
			Priorities[familyIndex].push_back(m_PerFamilQueues[familyIndex][queueIndex]->GetPriority());
		}
	
		QueueCreateInfos.resize(QueueCreateInfos.size() + 1);

		QueueCreateInfos.back().sType					= VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		QueueCreateInfos.back().pNext					= nullptr;
		QueueCreateInfos.back().flags					= 0;
		QueueCreateInfos.back().queueFamilyIndex		= familyIndex;
		QueueCreateInfos.back().queueCount				= static_cast<uint32_t>(m_PerFamilQueues[familyIndex].size());
		QueueCreateInfos.back().pQueuePriorities		= Priorities[familyIndex].data();
	}

	VkDeviceCreateInfo								DeviceCreateInfo = {};
	DeviceCreateInfo.sType							= VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	DeviceCreateInfo.pNext							= nullptr;
	DeviceCreateInfo.flags							= 0;
	DeviceCreateInfo.queueCreateInfoCount			= static_cast<uint32_t>(QueueCreateInfos.size());
	DeviceCreateInfo.pQueueCreateInfos				= QueueCreateInfos.data();
	DeviceCreateInfo.enabledLayerCount				= static_cast<uint32_t>(pEnabledLayers.size());
	DeviceCreateInfo.ppEnabledLayerNames			= pEnabledLayers.data();
	DeviceCreateInfo.enabledExtensionCount			= static_cast<uint32_t>(pEnabledExtensions.size());
	DeviceCreateInfo.ppEnabledExtensionNames		= pEnabledExtensions.data();
	DeviceCreateInfo.pEnabledFeatures				= pEnabledFeatures;

	VkDevice hDevice = VK_NULL_HANDLE;

	VkResult eResult = vkCreateDevice(m_pPhysicalDevice->Handle(), &DeviceCreateInfo, nullptr, &hDevice);

	if (eResult == VK_SUCCESS)
	{
		for (uint32_t familyIndex = 0; familyIndex < m_PerFamilQueues.size(); familyIndex++)
		{
			for (uint32_t queueIndex = 0; queueIndex < m_PerFamilQueues[familyIndex].size(); queueIndex++)
			{
				vkGetDeviceQueue(hDevice, familyIndex, queueIndex, &m_PerFamilQueues[familyIndex][queueIndex]->m_hQueue);

				m_PerFamilQueues[familyIndex][queueIndex]->m_hDevice = hDevice;
			}
		}

		m_hDevice = hDevice;
	}

	return LAVA_RESULT_CAST(eResult);
}


CommandQueue * LogicalDevice::PreInstallQueue(uint32_t familyIndex, float priority)
{
	if (m_hDevice != VK_NULL_HANDLE)				return nullptr;

	auto & QueueFamilyProperties = m_pPhysicalDevice->GetQueueFamilies();

	if (familyIndex >= QueueFamilyProperties.size())			return nullptr;

	if (m_PerFamilQueues[familyIndex].size() < QueueFamilyProperties[familyIndex].queueCount)
	{
		priority = std::clamp(priority, 0.0f, 1.0f);

		CommandQueue * pCommandQueue = new CommandQueue(familyIndex, vk::QueueFlags(QueueFamilyProperties[familyIndex].queueFlags), priority);

		m_PerFamilQueues[familyIndex].push_back(pCommandQueue);

		return pCommandQueue;	
	}

	return nullptr;
}


bool LogicalDevice::EnableExtension(const char * pExtensionName)
{
	if (m_hDevice != VK_NULL_HANDLE)			return false;

	if (m_pPhysicalDevice->IsExtensionAvailable(pExtensionName))
	{
		m_EnabledExtensions.insert(pExtensionName);

		return true;
	}

	return false;
}


bool LogicalDevice::EnableLayer(const char * pLayerName)
{
	if (m_hDevice != VK_NULL_HANDLE)		return false;

	if (m_pPhysicalDevice->IsLayerAvailable(pLayerName))
	{
		m_EnabledLayers.insert(pLayerName);

		return true;
	}

	return false;
}


LogicalDevice::~LogicalDevice() noexcept
{
	if (m_hDevice != VK_NULL_HANDLE)
	{
		for (auto & pQueues : m_PerFamilQueues)
		{
			for (size_t i = 0; i < pQueues.size(); i++)
			{
				pQueues[i]->WaitIdle();

				delete pQueues[i];
			}
		}

		this->WaitIdle();

		vkDestroyDevice(m_hDevice, nullptr);
	}
}