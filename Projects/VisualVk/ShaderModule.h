/*************************************************************************
**********************    VisualVk_ShaderModule    ***********************
*************************************************************************/
#pragma once

#include "Vulkan.h"

namespace Vk
{
	/*********************************************************************
	*************************    ShaderModule    *************************
	*********************************************************************/

	/**
	 *	@brief	Wrapper for Vulkan shader module object.
	 */
	class ShaderModule
	{

	public:

		//!	@brief	Invalidate this resource handle.
		void Destroy() { m_spUniqueHandle.reset(); }

		//!	@brief	Whether this resource handle is valid.
		bool IsValid() const { return m_spUniqueHandle != nullptr; }

		//!	@brief	Create a new shader module.
		Result Create(VkDevice hDevice, ArrayProxy<const uint32_t> code_spv);

		//!	@brief	Convert to VkShaderModule.
		operator VkShaderModule() const { return (m_spUniqueHandle != nullptr) ? m_spUniqueHandle->m_hShaderModule : VK_NULL_HANDLE; }

		//!	@brief	Read SPIR-V shader.
		static std::vector<uint32_t> ReadSPIRV(const char * pFilePath);

	private:

		/**
		 *	@brief	Unique handle of shader module.
		 */
		struct UniqueHandle
		{
			VK_NONCOPYABLE(UniqueHandle)

		public:

			//!	@brief	Constructor (all handles must be generated outside).
			UniqueHandle(VkDevice, VkShaderModule);

			//!	@brief	Where resource will be released.
			~UniqueHandle() noexcept;

		public:

			const VkDevice					m_hDevice;
			const VkShaderModule			m_hShaderModule;
		};

		std::shared_ptr<UniqueHandle>		m_spUniqueHandle;
	};
}