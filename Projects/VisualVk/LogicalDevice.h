/*************************************************************************
**********************    VisualVk_LogicalDevice    **********************
*************************************************************************/
#pragma once

#include <set>
#include "Vulkan.h"

namespace Vk
{
	/*********************************************************************
	************************    LogicalDevice    *************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan logical device object.
	 */
	class LogicalDevice
	{
		friend class PhysicalDevice;

	private:

		//!	@brief	Create logical device object.
		LogicalDevice(PhysicalDevice * pPhysicalDevice);

		//!	@brief	Destroy logical device object.
		~LogicalDevice() noexcept;

	public:

		//!	@brief	Return Vulkan type of this object.
		VkDevice GetHandle() const { return m_hDevice; }

		//!	@brief	If device is started up.
		bool IsReady() const { return m_hDevice != VK_NULL_HANDLE; }

		//!	@brief	Wait for a device to become idle.
		Result WaitIdle() { return VK_RESULT_CAST(vkDeviceWaitIdle(m_hDevice)); }

		CommandQueue * InstallQueue(uint32_t familyIndex, float priority = 0.0f);

		Result StartUp(const VkPhysicalDeviceFeatures * pEnabledFeatures = nullptr);

		bool EnableLayer(const char * pLayerName);

		bool EnableExtension(const char * pExtensionName);

		PhysicalDevice * GetPhysicalDevice() { return m_pPhysicalDevice; }

		const PhysicalDevice * GetPhysicalDevice() const { return m_pPhysicalDevice; }

		//!	@brief	Return the pointer to command queue.
		CommandQueue * GetCommandQueue(uint32_t familyIndex, uint32_t queueIndex)
		{
			if (familyIndex < m_PerFamilQueues.size())
			{
				if (queueIndex < m_PerFamilQueues[familyIndex].size())
				{
					return m_PerFamilQueues[familyIndex][queueIndex];
				}
			}

			return nullptr;
		}

	private:

		VkDevice									m_hDevice;

		std::set<const char*>						m_EnabledLayers;

		std::set<const char*>						m_EnabledExtensions;

		PhysicalDevice * const						m_pPhysicalDevice;

		std::vector<std::vector<CommandQueue*>>		m_PerFamilQueues;
	};
}