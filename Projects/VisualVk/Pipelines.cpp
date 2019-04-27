/*************************************************************************
************************    VisualVk_Pipelines    ************************
*************************************************************************/
#include "Pipelines.h"

using namespace Vk;

/*************************************************************************
*************************    GraphicsPipeline    *************************
*************************************************************************/
GraphicsPipeline::GraphicsPipeline() : m_hPipeline(VK_NULL_HANDLE)
{
	m_CreateInfo.pVertexInputState		= &m_VertexInputState;		//!	It is ignored if the pipeline includes a mesh shader stage.
	m_CreateInfo.pInputAssemblyState	= &m_InputAssemblyState;	//!	It is ignored if the pipeline includes a mesh shader stage.
	m_CreateInfo.pTessellationState		= &m_TessellationState;		//!	It is ignored if the pipeline does not include a tessellation control shader stage and tessellation evaluation shader stage.
	m_CreateInfo.pViewportState			= &m_ViewportState;			//!	It is ignored if the pipeline has rasterization disabled.
	m_CreateInfo.pRasterizationState	= &m_RasterizationState;	//!	It is necessary always.
	m_CreateInfo.pMultisampleState		= &m_MultisampleState;		//!	It is ignored if the pipeline has rasterization disabled.
	m_CreateInfo.pDepthStencilState		= &m_DepthStencilState;		//!	It is ignored if the pipeline has rasterization disabled or if the subpass of the render pass the pipeline is created against does not use a depth/stencil attachment.
	m_CreateInfo.pColorBlendState		= &m_ColorBlendState;		//!	It is ignored if the pipeline has rasterization disabled or if the subpass of the render pass the pipeline is created against does not use any color attachments.
	m_CreateInfo.pDynamicState			= &m_DynamicState;			//!	This can be NULL, which means no state in the pipeline is considered dynamic.
}


VkResult GraphicsPipeline::Refresh()
{
	VkPipeline hPipeline = VK_NULL_HANDLE;

	VkResult eResult = sm_pDevice->CreateGraphicsPipelines(VK_NULL_HANDLE, 1, &m_CreateInfo, &hPipeline);

	if (eResult == VK_SUCCESS)
	{
		sm_pDevice->DestroyPipeline(m_hPipeline);

		m_hPipeline = hPipeline;
	}

	return eResult;
}


VkResult GraphicsPipeline::SetPrimitiveTopology(VkPrimitiveTopology eTopology)
{
	if (m_InputAssemblyState.topology == eTopology)		return VK_SUCCESS;

	VkPipelineInputAssemblyStateCreateInfo InputAssemblyState = m_InputAssemblyState;

	InputAssemblyState.topology = eTopology;

	//!	TODO

	return VK_SUCCESS;
}


void GraphicsPipeline::Release() noexcept
{

}


GraphicsPipeline::~GraphicsPipeline()
{
	this->Release();
}


/*************************************************************************
*************************    ComputePipeline    **************************
*************************************************************************/
ComputePipeline::ComputePipeline() : m_hPipeline(VK_NULL_HANDLE)
{

}


void ComputePipeline::Release() noexcept
{
	sm_pDevice->DestroyPipeline(m_hPipeline);

	m_hPipeline = VK_NULL_HANDLE;
}


ComputePipeline::~ComputePipeline()
{
	this->Release();
}