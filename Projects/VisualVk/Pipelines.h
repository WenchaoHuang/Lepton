/*************************************************************************
************************    VisualVk_Pipelines    ************************
*************************************************************************/
#pragma once

#include "Resource.h"

namespace Vk
{
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

	public:

		VkResult Refresh();

	private:

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


	private:

		VkPipeline			m_hPipeline;
	};
}