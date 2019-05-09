/*************************************************************************
************************    VisualVk_Pipelines    ************************
*************************************************************************/
#pragma once

#include "Resource.h"

namespace Vk
{

	struct PipelineViewportState : private VkPipelineViewportStateCreateInfo
	{
		operator VkPipelineViewportStateCreateInfo() { return *this; }

		VkRect2D	Scissor;	VkViewport	Viewport;

		PipelineViewportState();
	};



	/*********************************************************************
	***********************    GraphicsPipeline    ***********************
	*********************************************************************/

	/**
	 *	@brief	Vulkan graphics pipeline object.
	 */
	class GraphicsPipeline : private Resource
	{

	public:

		GraphicsPipeline();

		~GraphicsPipeline();

	public:

		VkResult Refresh();

		void Release() noexcept;

		VkResult SetPrimitiveTopology(VkPrimitiveTopology eTopology);

	private:

		VkRect2D									m_Scissor;
		VkViewport									m_Viewport;
		VkPipeline									m_hPipeline;
		VkGraphicsPipelineCreateInfo				m_CreateInfo;
		VkPipelineDynamicStateCreateInfo			m_DynamicState;
		VkPipelineViewportStateCreateInfo			m_ViewportState;
		VkPipelineColorBlendStateCreateInfo			m_ColorBlendState;
		VkPipelineVertexInputStateCreateInfo		m_VertexInputState;
		VkPipelineMultisampleStateCreateInfo		m_MultisampleState;
		VkPipelineDepthStencilStateCreateInfo		m_DepthStencilState;
		VkPipelineTessellationStateCreateInfo		m_TessellationState;
		VkPipelineInputAssemblyStateCreateInfo		m_InputAssemblyState;
		VkPipelineRasterizationStateCreateInfo		m_RasterizationState;
	};

	/*********************************************************************
	***********************    ComputePipeline    ************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan compute pipeline object.
	 */
	class ComputePipeline : private Resource
	{

	public:

		//!	@brief	Create compute pipeline object.
		ComputePipeline();

		//!	@brief	Destroy compute pipeline object.
		~ComputePipeline();

	public:

		void Release() noexcept;

	private:

		VkPipeline		m_hPipeline;
	};
}