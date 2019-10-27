/*************************************************************************
*********************    VisualVk_ComputePipeline    *********************
*************************************************************************/
#pragma once

#include "Vulkan.h"

namespace Vk
{
	/*********************************************************************
	***********************    ComputePipeline    ************************
	*********************************************************************/

	/**
	 *	@brief	Wrapper for Vulkan compute pipeline object.
	 */
	class ComputePipeline
	{

	public:



	public:

		/**
		 *	@brief	Unique handle of compute pipeline.
		 */
		struct UniqueHandle
		{
			VK_NONCOPYABLE(UniqueHandle)

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