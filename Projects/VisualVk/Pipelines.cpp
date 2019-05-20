/*************************************************************************
************************    VisualVk_Pipelines    ************************
*************************************************************************/
#include "Pipelines.h"

using namespace Vk;

/*************************************************************************
********************    GraphicsPipelineCreateInfo    ********************
*************************************************************************/
GraphicsPipelineCreateInfo::GraphicsPipelineCreateInfo() : spRenderPass(nullptr), spPipelineLayout(nullptr)
{
	VkGraphicsPipelineCreateInfo::sType					= VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	VkGraphicsPipelineCreateInfo::pNext					= nullptr;
	VkGraphicsPipelineCreateInfo::flags					= 0;
	VkGraphicsPipelineCreateInfo::stageCount			= 0;
	VkGraphicsPipelineCreateInfo::pStages				= nullptr;
	VkGraphicsPipelineCreateInfo::pVertexInputState		= VertexInputState;
	VkGraphicsPipelineCreateInfo::pTessellationState	= TessellationState;
	VkGraphicsPipelineCreateInfo::pInputAssemblyState	= InputAssemblyState;
	VkGraphicsPipelineCreateInfo::pRasterizationState	= RasterizationState;
	VkGraphicsPipelineCreateInfo::pDepthStencilState	= DepthStencilState;
	VkGraphicsPipelineCreateInfo::pMultisampleState		= MultisampleState;
	VkGraphicsPipelineCreateInfo::pColorBlendState		= ColorBlendState;
	VkGraphicsPipelineCreateInfo::pViewportState		= ViewportState;
	VkGraphicsPipelineCreateInfo::pDynamicState			= DynamicStates;
	VkGraphicsPipelineCreateInfo::renderPass			= VK_NULL_HANDLE;
	VkGraphicsPipelineCreateInfo::layout				= VK_NULL_HANDLE;
	VkGraphicsPipelineCreateInfo::subpass				= 0;
	VkGraphicsPipelineCreateInfo::basePipelineHandle	= VK_NULL_HANDLE;
	VkGraphicsPipelineCreateInfo::basePipelineIndex		= 0;
}


GraphicsPipelineCreateInfo::operator const VkGraphicsPipelineCreateInfo*()
{
	VkGraphicsPipelineCreateInfo::sType					= VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	VkGraphicsPipelineCreateInfo::pNext					= nullptr;
	VkGraphicsPipelineCreateInfo::flags					= 0;
	VkGraphicsPipelineCreateInfo::stageCount			= ShaderStages.GetStageCount();
	VkGraphicsPipelineCreateInfo::pStages				= ShaderStages.GetStages();
	VkGraphicsPipelineCreateInfo::pVertexInputState		= VertexInputState;
	VkGraphicsPipelineCreateInfo::pTessellationState	= TessellationState;
	VkGraphicsPipelineCreateInfo::pInputAssemblyState	= InputAssemblyState;
	VkGraphicsPipelineCreateInfo::pRasterizationState	= RasterizationState;
	VkGraphicsPipelineCreateInfo::pDepthStencilState	= DepthStencilState;
	VkGraphicsPipelineCreateInfo::pMultisampleState		= MultisampleState;
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
**********************    DynamicStateCreateInfo    **********************
*************************************************************************/
GraphicsPipelineCreateInfo::DynamicStateCreateInfo::DynamicStateCreateInfo()
{
	m_CreateInfo.sType					= VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	m_CreateInfo.pNext					= nullptr;
	m_CreateInfo.flags					= 0;
	m_CreateInfo.dynamicStateCount		= 0;
	m_CreateInfo.pDynamicStates			= nullptr;
}


GraphicsPipelineCreateInfo::DynamicStateCreateInfo::operator const VkPipelineDynamicStateCreateInfo*()
{
	m_CreateInfo.dynamicStateCount		= (uint32_t)std::vector<VkDynamicState>::size();
	m_CreateInfo.pDynamicStates			= std::vector<VkDynamicState>::data();

	return &m_CreateInfo;
}


/*************************************************************************
*******************    RasterizationStateCreateInfo    *******************
*************************************************************************/
GraphicsPipelineCreateInfo::RasterizationStateCreateInfo::RasterizationStateCreateInfo()
{
	VkPipelineRasterizationStateCreateInfo::sType						= VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	VkPipelineRasterizationStateCreateInfo::pNext						= nullptr;
	VkPipelineRasterizationStateCreateInfo::flags						= 0;
	VkPipelineRasterizationStateCreateInfo::rasterizerDiscardEnable		= VK_FALSE;
	VkPipelineRasterizationStateCreateInfo::depthClampEnable			= VK_FALSE;
	VkPipelineRasterizationStateCreateInfo::polygonMode					= VK_POLYGON_MODE_FILL;
	VkPipelineRasterizationStateCreateInfo::cullMode					= VK_CULL_MODE_NONE;
	VkPipelineRasterizationStateCreateInfo::frontFace					= VK_FRONT_FACE_COUNTER_CLOCKWISE;
	VkPipelineRasterizationStateCreateInfo::depthBiasEnable				= VK_FALSE;
	VkPipelineRasterizationStateCreateInfo::depthBiasConstantFactor		= 0.0f;
	VkPipelineRasterizationStateCreateInfo::depthBiasSlopeFactor		= 0.0f;
	VkPipelineRasterizationStateCreateInfo::depthBiasClamp				= 0.0f;
	VkPipelineRasterizationStateCreateInfo::lineWidth					= 1.0f;
}


/*************************************************************************
*******************    InputAssemblyStateCreateInfo    *******************
*************************************************************************/
GraphicsPipelineCreateInfo::InputAssemblyStateCreateInfo::InputAssemblyStateCreateInfo()
{
	m_CreateInfo.sType					= VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	m_CreateInfo.pNext					= nullptr;
	m_CreateInfo.flags					= 0;
	m_CreateInfo.topology				= VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	m_CreateInfo.primitiveRestartEnable	= VK_FALSE;
}



void GraphicsPipelineCreateInfo::InputAssemblyStateCreateInfo::operator=(VkPrimitiveTopology eTopology)
{
	m_CreateInfo.topology = eTopology;
}


GraphicsPipelineCreateInfo::InputAssemblyStateCreateInfo::operator const VkPipelineInputAssemblyStateCreateInfo*()
{
	return &m_CreateInfo;
}


/*************************************************************************
*******************    TessellationStateCreateInfo    ********************
*************************************************************************/
GraphicsPipelineCreateInfo::TessellationStateCreateInfo::TessellationStateCreateInfo()
{
	m_CreateInfo.sType					= VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
	m_CreateInfo.pNext					= nullptr;
	m_CreateInfo.flags					= 0;
	m_CreateInfo.patchControlPoints		= 0;
}


void GraphicsPipelineCreateInfo::TessellationStateCreateInfo::SetPatchControlPoints(uint32_t PatchControlPoints)
{
	m_CreateInfo.patchControlPoints = PatchControlPoints;
}


GraphicsPipelineCreateInfo::TessellationStateCreateInfo::operator const VkPipelineTessellationStateCreateInfo*()
{
	return &m_CreateInfo;
}


/*************************************************************************
*******************    DepthStencilStateCreateInfo    ********************
*************************************************************************/
GraphicsPipelineCreateInfo::DepthStencilStateCreateInfo::DepthStencilStateCreateInfo()
{
	VkPipelineDepthStencilStateCreateInfo::sType					= VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	VkPipelineDepthStencilStateCreateInfo::pNext					= nullptr;
	VkPipelineDepthStencilStateCreateInfo::flags					= 0;
	VkPipelineDepthStencilStateCreateInfo::depthTestEnable			= VK_TRUE;
	VkPipelineDepthStencilStateCreateInfo::depthWriteEnable			= VK_TRUE;
	VkPipelineDepthStencilStateCreateInfo::depthCompareOp			= VK_COMPARE_OP_LESS_OR_EQUAL;
	VkPipelineDepthStencilStateCreateInfo::depthBoundsTestEnable	= VK_FALSE;
	VkPipelineDepthStencilStateCreateInfo::minDepthBounds			= 0.0f;
	VkPipelineDepthStencilStateCreateInfo::maxDepthBounds			= 0.0f;
	VkPipelineDepthStencilStateCreateInfo::stencilTestEnable		= VK_FALSE;
	VkPipelineDepthStencilStateCreateInfo::front.failOp				= VK_STENCIL_OP_KEEP;
	VkPipelineDepthStencilStateCreateInfo::front.passOp				= VK_STENCIL_OP_KEEP;
	VkPipelineDepthStencilStateCreateInfo::front.depthFailOp		= VK_STENCIL_OP_KEEP;
	VkPipelineDepthStencilStateCreateInfo::front.compareOp			= VK_COMPARE_OP_ALWAYS;
	VkPipelineDepthStencilStateCreateInfo::front.compareMask		= 0;
	VkPipelineDepthStencilStateCreateInfo::front.writeMask			= 0;
	VkPipelineDepthStencilStateCreateInfo::front.reference			= 0;
	VkPipelineDepthStencilStateCreateInfo::back						= front;
}


/*************************************************************************
********************    MultisampleStateCreateInfo    ********************
*************************************************************************/
GraphicsPipelineCreateInfo::MultisampleStateCreateInfo::MultisampleStateCreateInfo()
{
	VkPipelineMultisampleStateCreateInfo::sType						= VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	VkPipelineMultisampleStateCreateInfo::pNext						= nullptr;
	VkPipelineMultisampleStateCreateInfo::flags						= 0;
	VkPipelineMultisampleStateCreateInfo::rasterizationSamples		= VK_SAMPLE_COUNT_1_BIT;
	VkPipelineMultisampleStateCreateInfo::sampleShadingEnable		= VK_FALSE;
	VkPipelineMultisampleStateCreateInfo::minSampleShading			= 0.0f;
	VkPipelineMultisampleStateCreateInfo::pSampleMask				= nullptr;
	VkPipelineMultisampleStateCreateInfo::alphaToCoverageEnable		= VK_FALSE;
	VkPipelineMultisampleStateCreateInfo::alphaToOneEnable			= VK_FALSE;
}


/*************************************************************************
********************    VertexInputStateCreateInfo    ********************
*************************************************************************/
GraphicsPipelineCreateInfo::VertexInputStateCreateInfo::VertexInputStateCreateInfo()
{
	m_CreateInfo.sType								= VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	m_CreateInfo.pNext								= nullptr;
	m_CreateInfo.flags								= 0;
	m_CreateInfo.vertexBindingDescriptionCount		= 0;
	m_CreateInfo.vertexAttributeDescriptionCount	= 0;
	m_CreateInfo.pVertexAttributeDescriptions		= nullptr;
	m_CreateInfo.pVertexBindingDescriptions			= nullptr;
}


void GraphicsPipelineCreateInfo::VertexInputStateCreateInfo::SetAttribute(uint32_t Binding, uint32_t Location, VkFormat eFormat, uint32_t Offset)
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


void GraphicsPipelineCreateInfo::VertexInputStateCreateInfo::SetBinding(uint32_t Binding, uint32_t Stride, VkVertexInputRate eInputRate)
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


GraphicsPipelineCreateInfo::VertexInputStateCreateInfo::operator const VkPipelineVertexInputStateCreateInfo*()
{
	m_CreateInfo.vertexBindingDescriptionCount		= (uint32_t)m_BindingDescriptions.size();
	m_CreateInfo.vertexAttributeDescriptionCount	= (uint32_t)m_AttributeDescriptions.size();
	m_CreateInfo.pVertexAttributeDescriptions		= m_AttributeDescriptions.data();
	m_CreateInfo.pVertexBindingDescriptions			= m_BindingDescriptions.data();

	return &m_CreateInfo;
}


/*************************************************************************
********************    ColorBlendStateCreateInfo    *********************
*************************************************************************/
GraphicsPipelineCreateInfo::ColorBlendAttachmentState::ColorBlendAttachmentState()
{
	VkPipelineColorBlendAttachmentState::blendEnable			= VK_FALSE;
	VkPipelineColorBlendAttachmentState::colorBlendOp			= VK_BLEND_OP_ADD;
	VkPipelineColorBlendAttachmentState::alphaBlendOp			= VK_BLEND_OP_ADD;
	VkPipelineColorBlendAttachmentState::colorWriteMask			= VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	VkPipelineColorBlendAttachmentState::srcColorBlendFactor	= VK_BLEND_FACTOR_ZERO;
	VkPipelineColorBlendAttachmentState::dstColorBlendFactor	= VK_BLEND_FACTOR_ZERO;
	VkPipelineColorBlendAttachmentState::srcAlphaBlendFactor	= VK_BLEND_FACTOR_ZERO;
	VkPipelineColorBlendAttachmentState::dstAlphaBlendFactor	= VK_BLEND_FACTOR_ZERO;
}


GraphicsPipelineCreateInfo::ColorBlendStateCreateInfo::ColorBlendStateCreateInfo()
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


GraphicsPipelineCreateInfo::ColorBlendStateCreateInfo::operator const VkPipelineColorBlendStateCreateInfo*()
{
	VkPipelineColorBlendStateCreateInfo::attachmentCount		= (uint32_t)attachments.size();
	VkPipelineColorBlendStateCreateInfo::pAttachments			= attachments.data();

	return (VkPipelineColorBlendStateCreateInfo*)this;
}


/*************************************************************************
*********************    ViewportStateCreateInfo    **********************
*************************************************************************/
GraphicsPipelineCreateInfo::ViewportStateCreateInfo::ViewportStateCreateInfo()
{
	m_CreateInfo.sType			= VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	m_CreateInfo.pNext			= nullptr;
	m_CreateInfo.flags			= 0;
	m_CreateInfo.viewportCount	= 0;
	m_CreateInfo.scissorCount	= 0;
	m_CreateInfo.pViewports		= nullptr;
	m_CreateInfo.pScissors		= nullptr;
}


GraphicsPipelineCreateInfo::ViewportStateCreateInfo::operator const VkPipelineViewportStateCreateInfo*()
{
	m_CreateInfo.viewportCount	= (uint32_t)Viewports.size();
	m_CreateInfo.scissorCount	= (uint32_t)Scissors.size();
	m_CreateInfo.pViewports		= Viewports.data();
	m_CreateInfo.pScissors		= Scissors.data();

	return &m_CreateInfo;
}


/*************************************************************************
**************************    PipelineLayout    **************************
*************************************************************************/
PipelineLayout::PipelineLayout(VkPipelineLayout hPipelineLayout) : m_hPipelineLayout(hPipelineLayout)
{

}


std::shared_ptr<PipelineLayout> PipelineLayout::Create(const std::vector<VkDescriptorSetLayout> & DescriptorSetLayouts,
													   const std::vector<VkPushConstantRange> & PushConstantRanges)
{
	VkPipelineLayoutCreateInfo			CreateInfo = {};
	CreateInfo.sType					= VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	CreateInfo.pNext					= nullptr;
	CreateInfo.flags					= 0;
	CreateInfo.setLayoutCount			= (uint32_t)DescriptorSetLayouts.size();
	CreateInfo.pSetLayouts				= DescriptorSetLayouts.data();
	CreateInfo.pushConstantRangeCount	= (uint32_t)PushConstantRanges.size();
	CreateInfo.pPushConstantRanges		= PushConstantRanges.data();

	VkPipelineLayout hPipelineLayout = VK_NULL_HANDLE;

	sm_pDevice->CreatePipelineLayout(&CreateInfo, &hPipelineLayout);

	std::shared_ptr<PipelineLayout> spPipelineLayout = std::make_shared<PipelineLayout>(hPipelineLayout);

	if (spPipelineLayout->IsValid())
	{
		spPipelineLayout->m_DescriptorSetLayouts = DescriptorSetLayouts;

		spPipelineLayout->m_PushConstantRanges = PushConstantRanges;
	}

	return spPipelineLayout;
}


PipelineLayout::~PipelineLayout() noexcept
{
	sm_pDevice->DestroyPipelineLayout(m_hPipelineLayout);
}


/*************************************************************************
*************************    GraphicsPipeline    *************************
*************************************************************************/
GraphicsPipeline::GraphicsPipeline() : m_hPipeline(VK_NULL_HANDLE)
{

}


VkResult GraphicsPipeline::Create(GraphicsPipelineCreateInfo & CreateInfo)
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
		m_CreateInfo = GraphicsPipelineCreateInfo();

		sm_pDevice->DestroyPipeline(m_hPipeline);

		m_hPipeline = VK_NULL_HANDLE;
	}
}


GraphicsPipeline::~GraphicsPipeline()
{
	this->Release();
}