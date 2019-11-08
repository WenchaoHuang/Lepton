/*************************************************************************
************************    Lava_LogicalDevice    ************************
*************************************************************************/
#pragma once

#include <set>
#include "Vulkan.h"

namespace Lava
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

		CommandQueue * PreInstallQueue(uint32_t familyIndex, float priority = 0.0f);

		Result StartUp(const VkPhysicalDeviceFeatures * pEnabledFeatures = nullptr);

		const PhysicalDevice * GetPhysicalDevice() const { return m_pPhysicalDevice; }
		
		PhysicalDevice * GetPhysicalDevice() { return m_pPhysicalDevice; }
		
		bool EnableExtension(const char * pExtensionName);

		bool EnableLayer(const char * pLayerName);

	private:

		VkDevice									m_hDevice;

		std::set<const char*>						m_EnabledLayers;

		std::set<const char*>						m_EnabledExtensions;

		PhysicalDevice * const						m_pPhysicalDevice;

		std::vector<std::vector<CommandQueue*>>		m_PerFamilQueues;
	};
}