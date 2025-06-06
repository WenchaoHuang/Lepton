/*************************************************************************
**********************    Lepton_ComputePipeline    **********************
*************************************************************************/
#pragma once

#include "Vulkan.h"

namespace Lepton
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
			LAVA_NONCOPYABLE(UniqueHandle)

		public:

			//!	@brief	Constructor (handles must be initialized).
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