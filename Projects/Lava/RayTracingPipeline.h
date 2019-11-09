/*************************************************************************
*********************    Lava_RayTracingPipeline    **********************
*************************************************************************/
#pragma once

#include "Vulkan.h"

namespace Lava
{
	/*********************************************************************
	**********************    RayTracingPipeline    **********************
	*********************************************************************/

	/**
	 *	@brief	Wrapper for Vulkan ray tracing pipeline object.
	 */
	class RayTracingPipeline
	{

	public:

		


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

		std::shared_ptr<UniqueHandle>		m_spHandle;
	};
}