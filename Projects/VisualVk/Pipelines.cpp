/*************************************************************************
************************    VisualVk_Pipelines    ************************
*************************************************************************/
#include "Pipelines.h"

using namespace Vk;

/*************************************************************************
***********************    GraphicsPipelineInfo    ***********************
*************************************************************************/
GraphicsPipelineInfo::GraphicsPipelineInfo() : spRenderPass(nullptr), spPipelineLayout(nullptr)
{
	VkGraphicsPipelineCreateInfo::sType					= VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	VkGraphicsPipelineCreateInfo::pNext					= nullptr;
	VkGraphicsPipelineCreateInfo::flags					= 0;
	VkGraphicsPipelineCreateInfo::stageCount			= 0;
	VkGraphicsPipelineCreateInfo::pStages				= nullptr;
	VkGraphicsPipelineCreateInfo::pVertexInputState		= VertexInputState;
	VkGraphicsPipelineCreateInfo::pTessellationState	= reinterpret_cast<const VkPipelineTessellationStateCreateInfo*>(&TessellationState);
	VkGraphicsPipelineCreateInfo::pInputAssemblyState	= reinterpret_cast<const VkPipelineInputAssemblyStateCreateInfo*>(&InputAssemblyState);
	VkGraphicsPipelineCreateInfo::pRasterizationState	= reinterpret_cast<const VkPipelineRasterizationStateCreateInfo*>(&RasterizationState);
	VkGraphicsPipelineCreateInfo::pDepthStencilState	= reinterpret_cast<const VkPipelineDepthStencilStateCreateInfo*>(&DepthStencilState);
	VkGraphicsPipelineCreateInfo::pMultisampleState		= reinterpret_cast<const VkPipelineMultisampleStateCreateInfo*>(&MultisampleState);
	VkGraphicsPipelineCreateInfo::pColorBlendState		= ColorBlendState;
	VkGraphicsPipelineCreateInfo::pViewportState		= ViewportState;
	VkGraphicsPipelineCreateInfo::pDynamicState			= DynamicStates;
	VkGraphicsPipelineCreateInfo::renderPass			= VK_NULL_HANDLE;
	VkGraphicsPipelineCreateInfo::layout				= VK_NULL_HANDLE;
	VkGraphicsPipelineCreateInfo::subpass				= 0;
	VkGraphicsPipelineCreateInfo::basePipelineHandle	= VK_NULL_HANDLE;
	VkGraphicsPipelineCreateInfo::basePipelineIndex		= 0;
}


GraphicsPipelineInfo::operator const VkGraphicsPipelineCreateInfo*()
{
	VkGraphicsPipelineCreateInfo::sType					= VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	VkGraphicsPipelineCreateInfo::pNext					= nullptr;
	VkGraphicsPipelineCreateInfo::flags					= 0;
	VkGraphicsPipelineCreateInfo::stageCount			= ShaderStages.GetStageCount();
	VkGraphicsPipelineCreateInfo::pStages				= ShaderStages.GetStages();
	VkGraphicsPipelineCreateInfo::pVertexInputState		= VertexInputState;
	VkGraphicsPipelineCreateInfo::pTessellationState	= reinterpret_cast<const VkPipelineTessellationStateCreateInfo*>(&TessellationState);
	VkGraphicsPipelineCreateInfo::pInputAssemblyState	= reinterpret_cast<const VkPipelineInputAssemblyStateCreateInfo*>(&InputAssemblyState);
	VkGraphicsPipelineCreateInfo::pRasterizationState	= reinterpret_cast<const VkPipelineRasterizationStateCreateInfo*>(&RasterizationState);
	VkGraphicsPipelineCreateInfo::pDepthStencilState	= reinterpret_cast<const VkPipelineDepthStencilStateCreateInfo*>(&DepthStencilState);
	VkGraphicsPipelineCreateInfo::pMultisampleState		= reinterpret_cast<const VkPipelineMultisampleStateCreateInfo*>(&MultisampleState);
	VkGraphicsPipelineCreateInfo::pColorBlendState		= ColorBlendState;
	VkGraphicsPipelineCreateInfo::pViewportState		= ViewportState;
	VkGraphicsPipelineCreateInfo::pDynamicState			= DynamicStates;
	VkGraphicsPipelineCreateInfo::renderPass			= (spRenderPass == nullptr) ? VK_NULL_HANDLE : spRenderPass->GetHandle();
	VkGraphicsPipelineCreateInfo::layout				= (spPipelineLayout == nullptr) ? VK_NULL_HANDLE : spPipelineLayout->GetHandle();
	VkGraphicsPipelineCreateInfo::subpass				= 0;
	VkGraphicsPipelineCreateInfo::basePipelineHandle	= VK_NULL_HANDLE;
	VkGraphicsPipelineCreateInfo::basePipelineIndex		= 0;

	return (VkGraphicsPipelineCreateInfo*)this;
}


/*************************************************************************
*************************    DynamicStateInfo    *************************
*************************************************************************/
GraphicsPipelineInfo::DynamicStateInfo::DynamicStateInfo()
{
	m_CreateInfo.sType					= VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	m_CreateInfo.pNext					= nullptr;
	m_CreateInfo.flags					= 0;
	m_CreateInfo.dynamicStateCount		= 0;
	m_CreateInfo.pDynamicStates			= nullptr;
}


GraphicsPipelineInfo::DynamicStateInfo::operator const VkPipelineDynamicStateCreateInfo*()
{
	m_CreateInfo.dynamicStateCount		= static_cast<uint32_t>(vector<VkDynamicState>::size());
	m_CreateInfo.pDynamicStates			= std::vector<VkDynamicState>::data();

	return &m_CreateInfo;
}


/*************************************************************************
**********************    InputAssemblyStateInfo    **********************
*************************************************************************/
GraphicsPipelineInfo::InputAssemblyStateInfo::InputAssemblyStateInfo()
{
	m_CreateInfo.sType						= VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	m_CreateInfo.pNext						= nullptr;
	m_CreateInfo.flags						= 0;
	m_CreateInfo.topology					= VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
	m_CreateInfo.primitiveRestartEnable		= VK_FALSE;
}


GraphicsPipelineInfo::InputAssemblyStateInfo::InputAssemblyStateInfo(VkPrimitiveTopology eTopology)
{
	m_CreateInfo.sType						= VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	m_CreateInfo.pNext						= nullptr;
	m_CreateInfo.flags						= 0;
	m_CreateInfo.topology					= eTopology;
	m_CreateInfo.primitiveRestartEnable		= VK_FALSE;
}


/*************************************************************************
**********************    TessellationStateInfo    ***********************
*************************************************************************/
GraphicsPipelineInfo::TessellationStateInfo::TessellationStateInfo()
{
	m_CreateInfo.sType					= VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
	m_CreateInfo.pNext					= nullptr;
	m_CreateInfo.flags					= 0;
	m_CreateInfo.patchControlPoints		= 0;
}


void GraphicsPipelineInfo::TessellationStateInfo::SetPatchControlPoints(uint32_t PatchControlPoints)
{
	m_CreateInfo.patchControlPoints = PatchControlPoints;
}


/*************************************************************************
***********************    VertexInputStateInfo    ***********************
*************************************************************************/
GraphicsPipelineInfo::VertexInputStateInfo::VertexInputStateInfo()
{
	m_CreateInfo.sType								= VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	m_CreateInfo.pNext								= nullptr;
	m_CreateInfo.flags								= 0;
	m_CreateInfo.vertexBindingDescriptionCount		= 0;
	m_CreateInfo.vertexAttributeDescriptionCount	= 0;
	m_CreateInfo.pVertexAttributeDescriptions		= nullptr;
	m_CreateInfo.pVertexBindingDescriptions			= nullptr;
}


void GraphicsPipelineInfo::VertexInputStateInfo::SetAttribute(uint32_t Binding, uint32_t Location, VkFormat eFormat, uint32_t Offset)
{
	for (size_t i = 0; i < m_AttributeDescriptions.size(); i++)
	{
		if (m_AttributeDescriptions[i].location == Location)
		{
			m_AttributeDescriptions[i].binding = Binding;

			m_AttributeDescriptions[i].format = eFormat;

			m_AttributeDescriptions[i].offset = Offset;

			return;
		}
	}

	m_AttributeDescriptions.push_back({ Location, Binding, eFormat, Offset });
}


void GraphicsPipelineInfo::VertexInputStateInfo::SetBinding(uint32_t Binding, uint32_t Stride, VkVertexInputRate eInputRate)
{
	for (size_t i = 0; i < m_BindingDescriptions.size(); i++)
	{
		if (m_BindingDescriptions[i].binding == Binding)
		{
			m_BindingDescriptions[i].inputRate = eInputRate;

			m_BindingDescriptions[i].stride = Stride;

			return;
		}
	}

	m_BindingDescriptions.push_back({ Binding, Stride, eInputRate });
}


GraphicsPipelineInfo::VertexInputStateInfo::operator const VkPipelineVertexInputStateCreateInfo*()
{
	m_CreateInfo.vertexBindingDescriptionCount		= static_cast<uint32_t>(m_BindingDescriptions.size());
	m_CreateInfo.vertexAttributeDescriptionCount	= static_cast<uint32_t>(m_AttributeDescriptions.size());
	m_CreateInfo.pVertexAttributeDescriptions		= m_AttributeDescriptions.data();
	m_CreateInfo.pVertexBindingDescriptions			= m_BindingDescriptions.data();

	return &m_CreateInfo;
}


/*************************************************************************
***********************    ColorBlendStateInfo    ************************
*************************************************************************/
GraphicsPipelineInfo::ColorBlendStateInfo::ColorBlendStateInfo()
{
	VkPipelineColorBlendStateCreateInfo::sType					= VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	VkPipelineColorBlendStateCreateInfo::pNext					= nullptr;
	VkPipelineColorBlendStateCreateInfo::flags					= 0;
	VkPipelineColorBlendStateCreateInfo::logicOpEnable			= VK_FALSE;
	VkPipelineColorBlendStateCreateInfo::logicOp				= VK_LOGIC_OP_NO_OP;
	VkPipelineColorBlendStateCreateInfo::pAttachments			= nullptr;
	VkPipelineColorBlendStateCreateInfo::attachmentCount		= 0;
	VkPipelineColorBlendStateCreateInfo::blendConstants[0]		= 1.0f;
	VkPipelineColorBlendStateCreateInfo::blendConstants[1]		= 1.0f;
	VkPipelineColorBlendStateCreateInfo::blendConstants[2]		= 1.0f;
	VkPipelineColorBlendStateCreateInfo::blendConstants[3]		= 1.0f;
}


GraphicsPipelineInfo::ColorBlendStateInfo::operator const VkPipelineColorBlendStateCreateInfo*()
{
	VkPipelineColorBlendStateCreateInfo::attachmentCount		= static_cast<uint32_t>(attachments.size());
	VkPipelineColorBlendStateCreateInfo::pAttachments			= reinterpret_cast<const VkPipelineColorBlendAttachmentState*>(attachments.data());

	return (VkPipelineColorBlendStateCreateInfo*)this;
}


/*************************************************************************
************************    ViewportStateInfo    *************************
*************************************************************************/
GraphicsPipelineInfo::ViewportStateInfo::ViewportStateInfo()
{
	m_CreateInfo.sType			= VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	m_CreateInfo.pNext			= nullptr;
	m_CreateInfo.flags			= 0;
	m_CreateInfo.viewportCount	= 0;
	m_CreateInfo.scissorCount	= 0;
	m_CreateInfo.pViewports		= nullptr;
	m_CreateInfo.pScissors		= nullptr;
}


GraphicsPipelineInfo::ViewportStateInfo::operator const VkPipelineViewportStateCreateInfo*()
{
	m_CreateInfo.viewportCount	= static_cast<uint32_t>(Viewports.size());
	m_CreateInfo.scissorCount	= static_cast<uint32_t>(Scissors.size());
	m_CreateInfo.pViewports		= Viewports.data();
	m_CreateInfo.pScissors		= Scissors.data();

	return &m_CreateInfo;
}



/*************************************************************************
*************************    GraphicsPipeline    *************************
*************************************************************************/
GraphicsPipeline::GraphicsPipeline() : m_hPipeline(VK_NULL_HANDLE)
{

}


VkResult GraphicsPipeline::Create(GraphicsPipelineInfo & CreateInfo)
{
	VkPipeline hPipeline = VK_NULL_HANDLE;

	if (sm_pDevice->CreateGraphicsPipelines(VK_NULL_HANDLE, 1, CreateInfo, &hPipeline) == VK_SUCCESS)
	{
		this->Release();

		m_hPipeline = hPipeline;

		m_CreateInfo = CreateInfo;
	}

	return VK_SUCCESS;
}


void GraphicsPipeline::Release() noexcept
{
	if (m_hPipeline != VK_NULL_HANDLE)
	{
		m_CreateInfo = GraphicsPipelineInfo();

		sm_pDevice->DestroyPipeline(m_hPipeline);

		m_hPipeline = VK_NULL_HANDLE;
	}
}


GraphicsPipeline::~GraphicsPipeline()
{
	this->Release();
}