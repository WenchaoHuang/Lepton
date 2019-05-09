/*************************************************************************
************************    VisualVk_Pipelines    ************************
*************************************************************************/
#include "Pipelines.h"

using namespace Vk;

PipelineViewportState::PipelineViewportState()
{
	VkPipelineViewportStateCreateInfo::sType			= VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	VkPipelineViewportStateCreateInfo::pNext			= nullptr;
	VkPipelineViewportStateCreateInfo::flags			= 0;
	VkPipelineViewportStateCreateInfo::viewportCount	= 1;
	VkPipelineViewportStateCreateInfo::pViewports		= &Viewport;
	VkPipelineViewportStateCreateInfo::scissorCount		= 1;
	VkPipelineViewportStateCreateInfo::pScissors		= &Scissor;

	Viewport.x			= 0.0f;
	Viewport.y			= 0.0f;
	Viewport.width		= 0.0f;
	Viewport.height		= 0.0f;
	Viewport.minDepth	= 0.0f;
	Viewport.maxDepth	= 0.0f;

	Scissor.offset.x		= 0;
	Scissor.offset.y		= 0;
	Scissor.extent.width	= 0;
	Scissor.extent.height	= 0;
}

/*************************************************************************
*************************    GraphicsPipeline    *************************
*************************************************************************/
GraphicsPipeline::GraphicsPipeline() : m_hPipeline(VK_NULL_HANDLE)
{
	m_CreateInfo.sType									= VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	m_CreateInfo.pNext									= nullptr;
	m_CreateInfo.flags									= 0;
	m_CreateInfo.stageCount								= 0;
	m_CreateInfo.pVertexInputState						= &m_VertexInputState;		//!	It is ignored if the pipeline includes a mesh shader stage.
	m_CreateInfo.pInputAssemblyState					= &m_InputAssemblyState;	//!	It is ignored if the pipeline includes a mesh shader stage.
	m_CreateInfo.pTessellationState						= &m_TessellationState;		//!	It is ignored if the pipeline does not include a tessellation control shader stage and tessellation evaluation shader stage.
	m_CreateInfo.pViewportState							= &m_ViewportState;			//!	It is ignored if the pipeline has rasterization disabled.
	m_CreateInfo.pRasterizationState					= &m_RasterizationState;	//!	It is necessary always.
	m_CreateInfo.pMultisampleState						= &m_MultisampleState;		//!	It is ignored if the pipeline has rasterization disabled.
	m_CreateInfo.pDepthStencilState						= &m_DepthStencilState;		//!	It is ignored if the pipeline has rasterization disabled or if the subpass of the render pass the pipeline is created against does not use a depth/stencil attachment.
	m_CreateInfo.pColorBlendState						= &m_ColorBlendState;		//!	It is ignored if the pipeline has rasterization disabled or if the subpass of the render pass the pipeline is created against does not use any color attachments.
	m_CreateInfo.pDynamicState							= &m_DynamicState;			//!	This can be NULL, which means no state in the pipeline is considered dynamic.
	m_CreateInfo.layout;
	m_CreateInfo.renderPass;
	m_CreateInfo.subpass;
	m_CreateInfo.basePipelineHandle;
	m_CreateInfo.basePipelineIndex;

	m_VertexInputState.sType							= VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	m_VertexInputState.pNext							= nullptr;
	m_VertexInputState.flags							= 0;
	m_VertexInputState.vertexBindingDescriptionCount	= 0;
	m_VertexInputState.pVertexBindingDescriptions		= nullptr;
	m_VertexInputState.vertexAttributeDescriptionCount	= 0;
	m_VertexInputState.pVertexAttributeDescriptions		= nullptr;

	m_InputAssemblyState.sType							= VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	m_InputAssemblyState.pNext							= nullptr;
	m_InputAssemblyState.flags							= 0;
	m_InputAssemblyState.topology						= VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	m_InputAssemblyState.primitiveRestartEnable			= VK_FALSE;

	m_TessellationState.sType							= VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
	m_TessellationState.pNext							= nullptr;
	m_TessellationState.flags							= 0;
	m_TessellationState.patchControlPoints				= 0;

	m_ViewportState.sType								= VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	m_ViewportState.pNext								= nullptr;
	m_ViewportState.flags								= 0;
	m_ViewportState.viewportCount						= 1;
	m_ViewportState.pViewports							= &m_Viewport;
	m_ViewportState.scissorCount						= 1;
	m_ViewportState.pScissors							= &m_Scissor;

	m_RasterizationState.sType							= VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	m_RasterizationState.pNext							= nullptr;
	m_RasterizationState.flags							= 0;
	m_RasterizationState.depthClampEnable				= VK_FALSE;
	m_RasterizationState.rasterizerDiscardEnable		= VK_FALSE;
	m_RasterizationState.polygonMode					= VK_POLYGON_MODE_FILL;
	m_RasterizationState.cullMode						= VK_CULL_MODE_NONE;
	m_RasterizationState.frontFace						= VK_FRONT_FACE_COUNTER_CLOCKWISE;
	m_RasterizationState.depthBiasEnable				= VK_FALSE;
	m_RasterizationState.depthBiasConstantFactor		= 0.0f;
	m_RasterizationState.depthBiasClamp					= 0.0f;
	m_RasterizationState.depthBiasSlopeFactor			= 0.0f;
	m_RasterizationState.lineWidth						= 1.0f;

	m_MultisampleState.sType							= VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	m_MultisampleState.pNext							= nullptr;
	m_MultisampleState.flags							= 0;
	m_MultisampleState.rasterizationSamples				= VK_SAMPLE_COUNT_1_BIT;
	m_MultisampleState.sampleShadingEnable				= VK_FALSE;
	m_MultisampleState.minSampleShading					= 0.0f;
	m_MultisampleState.pSampleMask						= nullptr;
	m_MultisampleState.alphaToCoverageEnable			= VK_FALSE;
	m_MultisampleState.alphaToOneEnable					= VK_FALSE;

	m_DepthStencilState.sType							= VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	m_DepthStencilState.pNext							= nullptr;
	m_DepthStencilState.flags							= 0;
	m_DepthStencilState.depthTestEnable					= VK_TRUE;
	m_DepthStencilState.depthWriteEnable				= VK_TRUE;
	m_DepthStencilState.depthCompareOp					= VK_COMPARE_OP_LESS_OR_EQUAL;
	m_DepthStencilState.depthBoundsTestEnable			= VK_FALSE;
	m_DepthStencilState.stencilTestEnable				= VK_FALSE;
	m_DepthStencilState.front;
	m_DepthStencilState.back;
	m_DepthStencilState.minDepthBounds					= 0.0f;
	m_DepthStencilState.maxDepthBounds					= 0.0f;

	m_ColorBlendState.sType								= VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	m_ColorBlendState.pNext								= nullptr;
	m_ColorBlendState.flags								= 0;
	m_ColorBlendState.logicOpEnable;
	m_ColorBlendState.logicOp;
	m_ColorBlendState.attachmentCount					= 0;
	m_ColorBlendState.pAttachments						= nullptr;
	m_ColorBlendState.blendConstants[4];

	m_DynamicState.sType								= VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	m_DynamicState.pNext								= nullptr;
	m_DynamicState.flags								= 0;
	m_DynamicState.dynamicStateCount					= 0;
	m_DynamicState.pDynamicStates						= nullptr;
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