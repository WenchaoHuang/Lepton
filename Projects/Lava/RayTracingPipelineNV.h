/*************************************************************************
********************    Lava_RayTracingPipelineNV    *********************
*************************************************************************/
#pragma once

#include "ShaderModule.h"
#include "PipelineLayout.h"

namespace Lava
{


	/*********************************************************************
	*********************    RayTracingPipelineNV    *********************
	*********************************************************************/

	/**
	 *	@brief	Wrapper for Nvidia ray tracing pipeline object.
	 */
	class RayTracingPipelineNV
	{

	public:

		//!	@brief	Invalidate this resource handle.
		void Destroy() { m_spUniqueHandle.reset(); }

		//!	@brief	Whether this resource handle is valid.
		bool IsValid() const { return m_spUniqueHandle != nullptr; }

		Result Create(PipelineLayout pipelineLayout, uint32_t maxRecursionDepth);

		//!	@brief	Convert to VkPipeline.
		operator VkPipeline() const { return (m_spUniqueHandle != nullptr) ? m_spUniqueHandle->m_hPipeline : VK_NULL_HANDLE; }

	public:

		/**
		 *	@brief	Unique handle of ray tracing pipeline.
		 */
		struct UniqueHandle
		{
			LAVA_NONCOPYABLE(UniqueHandle)

		public:

			//!	@brief	Constructor (all handles must be generated outside).
			UniqueHandle(VkDevice, VkPipeline);

			//!	@brief	Where resource will be released.
			~UniqueHandle() noexcept;

		public:

			const VkDevice					m_hDevice;
			const VkPipeline				m_hPipeline;
		};

		std::shared_ptr<UniqueHandle>		m_spUniqueHandle;
	};
}