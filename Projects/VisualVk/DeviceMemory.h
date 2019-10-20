/*************************************************************************
**********************    VisualVk_DeviceMemory    ***********************
*************************************************************************/
#pragma once

#include "Vulkan.h"

namespace Vk
{
	/*********************************************************************
	*************************    DeviceMemory    *************************
	*********************************************************************/

	/**
	 *	@brief	Wrapper for Vulkan device memory object.
	 */
	class DeviceMemory
	{

	public:

		//!	@brief	Free memory.
		void Free() { m_spHandle.reset(); }

		//!	@brief	Whether this resource handle is valid.
		bool IsValid() const { return m_spHandle != nullptr; }

		//!	@brief	Invalidate range of mapped memory object.
		Result Invalidate(VkDeviceSize offset, VkDeviceSize size) const;

		//!	@brief	Flush mapped memory range.
		Result Flush(VkDeviceSize OffsetBytes, VkDeviceSize SizeBytes) const;

		//!	@brief	Map memory into application address space.
		Result Map(void ** ppData, VkDeviceSize offset, VkDeviceSize size) const;

		//!	@brief	Unmap previously mapped memory.
		void Unmap() const { vkUnmapMemory(m_spHandle->m_hDevice, m_spHandle->m_hDeviceMemory); }

		//!	@brief	Allocate device memory.
		Result Allocate(VkDevice hDevice, VkDeviceSize allocationSize, uint32_t memoryTypeIndex);

		//!	@brief	Return the size of device memory.
		VkDeviceSize Size() const { return (m_spHandle != nullptr) ? m_spHandle->m_AllocateSize : 0; }

		//!	@brief	Return VkDevice handle.
		VkDevice GetDeviceHandle() const { return (m_spHandle != nullptr) ? m_spHandle->m_hDevice : VK_NULL_HANDLE; }

		//!	@brief	Convert to VkDeviceMemory.
		operator VkDeviceMemory() const { return (m_spHandle != nullptr) ? m_spHandle->m_hDeviceMemory : VK_NULL_HANDLE; }

	private:

		/**
		 *	@brief	Unique handle of Vulkan resource.
		 */
		struct UniqueHandle
		{
			VK_NONCOPYABLE(UniqueHandle)

		public:

			//!	@brief	Constructor (all handles must be generated outside).
			UniqueHandle(VkDevice, VkDeviceMemory, VkDeviceSize);

			//!	@brief	Where resource will be released.
			~UniqueHandle() noexcept;

		public:

			const VkDevice					m_hDevice;
			const VkDeviceSize				m_AllocateSize;
			const VkDeviceMemory			m_hDeviceMemory;
		};

		std::shared_ptr<UniqueHandle>		m_spHandle;
	};
}