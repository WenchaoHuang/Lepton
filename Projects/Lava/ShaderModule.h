/*************************************************************************
************************    Lava_ShaderModule    *************************
*************************************************************************/
#pragma once

#include "Vulkan.h"

namespace Lava
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
		Result Create(VkDevice hDevice, const char * pShaderPath, ShaderStage eStage);

		//!	@brief	Create a new shader module.
		Result Create(VkDevice hDevice, ArrayProxy<uint32_t> pCode, ShaderStage eStage);

		//!	@brief	Return device handle.
		VkDevice GetDeviceHandle() const { return (m_spUniqueHandle != nullptr) ? m_spUniqueHandle->m_hDevice : VK_NULL_HANDLE; }

		//!	@brief	Return shader stage create info for creating graphics pipeline.
		const VkPipelineShaderStageCreateInfo & GetStageInfo() const { return m_spUniqueHandle->m_StageInfo; }

	private:

		/**
		 *	@brief	Unique handle of shader module.
		 */
		struct UniqueHandle
		{
			LAVA_NONCOPYABLE(UniqueHandle)

		public:

			//!	@brief	Constructor (handles must be initialized).
			UniqueHandle(VkDevice, VkShaderModule, ShaderStage);

			//!	@brief	Where resource will be released.
			~UniqueHandle() noexcept;

		public:

			const VkDevice						m_hDevice;
			VkPipelineShaderStageCreateInfo		m_StageInfo;
		};

		std::shared_ptr<UniqueHandle>			m_spUniqueHandle;
	};
}