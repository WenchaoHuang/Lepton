/*************************************************************************
************************    Lava_DeviceMemory    *************************
*************************************************************************/
#pragma once

#include "Vulkan.h"

namespace Lava
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
		void Free() { m_spUniqueHandle.reset(); }

		//!	@brief	Whether this resource handle is valid.
		bool IsEmpty() const { return m_spUniqueHandle != nullptr; }

		//!	@brief	Invalidate range of mapped memory object.
		Result Invalidate(VkDeviceSize offset, VkDeviceSize size) const;

		//!	@brief	Flush mapped memory range.
		Result Flush(VkDeviceSize OffsetBytes, VkDeviceSize SizeBytes) const;

		//!	@brief	Map memory into application address space.
		Result Map(void ** ppData, VkDeviceSize offset, VkDeviceSize size) const;

		//!	@brief	Unmap previously mapped memory.
		void Unmap() const { vkUnmapMemory(m_spUniqueHandle->m_hDevice, m_spUniqueHandle->m_hDeviceMemory); }

		//!	@brief	Return the size of device memory.
		VkDeviceSize Size() const { return (m_spUniqueHandle != nullptr) ? m_spUniqueHandle->m_AllocateSize : 0; }

		//!	@brief	Return VkDevice handle.
		VkDevice GetDeviceHandle() const { return (m_spUniqueHandle != nullptr) ? m_spUniqueHandle->m_hDevice : VK_NULL_HANDLE; }

		//!	@brief	Allocate device memory.
		Result Allocate(const LogicalDevice * pLogicalDevice, VkMemoryRequirements memoryRequirements, Flags<MemoryProperty> eProperties);

		//!	@brief	Convert to VkDeviceMemory.
		operator VkDeviceMemory() const { return (m_spUniqueHandle != nullptr) ? m_spUniqueHandle->m_hDeviceMemory : VK_NULL_HANDLE; }

	private:

		/**
		 *	@brief	Unique handle of device memory.
		 */
		struct UniqueHandle
		{
			LAVA_NONCOPYABLE(UniqueHandle)

		public:

			//!	@brief	Constructor (handles must be initialized).
			UniqueHandle(VkDevice, VkDeviceMemory, VkDeviceSize);

			//!	@brief	Where resource will be released.
			~UniqueHandle() noexcept;

		public:

			const VkDevice					m_hDevice;
			const VkDeviceSize				m_AllocateSize;
			const VkDeviceMemory			m_hDeviceMemory;
		};

		std::shared_ptr<UniqueHandle>		m_spUniqueHandle;
	};

	/*********************************************************************
	**********************    DeviceLocalMemory    ***********************
	*********************************************************************/

	/**
	 *	@brief	Wrapper for Vulkan device-local memory object.
	 */
	class DeviceLocalMemory
	{

	public:

		//!	@brief	Free device memory.
		void Free() { m_spUniqueHandle.reset(); }

		//!	@brief	Whether this resource handle is valid.
		bool IsEmpty() const { return m_spUniqueHandle != nullptr; }

		//!	@brief	Allocate a new device memory object.
		Result Allocate(const LogicalDevice * pLogicalDevice, VkMemoryRequirements memoryRequirements);

		//!	@brief	Return the size of device memory in bytes.
		VkDeviceSize Size() const { return (m_spUniqueHandle != nullptr) ? m_spUniqueHandle->m_SizeBytes : 0; }

		//!	@brief	Return VkDevice handle.
		VkDevice GetDeviceHandle() const { return (m_spUniqueHandle != nullptr) ? m_spUniqueHandle->m_hDevice : VK_NULL_HANDLE; }

		//!	@brief	Convert to VkDeviceMemory.
		operator VkDeviceMemory() const { return (m_spUniqueHandle != nullptr) ? m_spUniqueHandle->m_hDeviceMemory : VK_NULL_HANDLE; }

	private:

		/**
		 *	@brief	Unique handle of device memory.
		 */
		struct UniqueHandle
		{
			LAVA_NONCOPYABLE(UniqueHandle)

		public:

			//!	@brief	Constructor (handles must be initialized).
			UniqueHandle(VkDevice, VkDeviceMemory, VkDeviceSize);

			//!	@brief	Where resource will be released.
			~UniqueHandle() noexcept;

		public:

			const VkDevice					m_hDevice;
			const VkDeviceSize				m_SizeBytes;
			const VkDeviceMemory			m_hDeviceMemory;
		};

		std::shared_ptr<UniqueHandle>		m_spUniqueHandle;
	};
}