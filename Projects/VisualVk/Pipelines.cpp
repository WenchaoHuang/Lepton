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
	VkGraphicsPipelineCreateInfo::stageCount			= 0;
	VkGraphicsPipelineCreateInfo::pStages				= nullptr;
	VkGraphicsPipelineCreateInfo::pVertexInputState		= VertexInputState;
	VkGraphicsPipelineCreateInfo::pInputAssemblyState	= InputAssemblyState;
	VkGraphicsPipelineCreateInfo::pTessellationState	= TessellationState;
	VkGraphicsPipelineCreateInfo::pViewportState		= ViewportState;
	VkGraphicsPipelineCreateInfo::pRasterizationState	= RasterizationState;
	VkGraphicsPipelineCreateInfo::pMultisampleState		= MultisampleState;
	VkGraphicsPipelineCreateInfo::pDepthStencilState	= DepthStencilState;
	VkGraphicsPipelineCreateInfo::pColorBlendState		= ColorBlendState;
	VkGraphicsPipelineCreateInfo::pDynamicState			= DynamicStates;

	return (VkGraphicsPipelineCreateInfo*)this;
}


/*************************************************************************
**********************    DynamicStateCreateInfo    **********************
*************************************************************************/
GraphicsPipelineCreateInfo::DynamicStateCreateInfo::DynamicStateCreateInfo()
{
	VkPipelineDynamicStateCreateInfo::sType					= VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	VkPipelineDynamicStateCreateInfo::pNext					= nullptr;
	VkPipelineDynamicStateCreateInfo::flags					= 0;
	VkPipelineDynamicStateCreateInfo::dynamicStateCount		= 0;
	VkPipelineDynamicStateCreateInfo::pDynamicStates		= nullptr;
}


GraphicsPipelineCreateInfo::DynamicStateCreateInfo::operator const VkPipelineDynamicStateCreateInfo*()
{
	VkPipelineDynamicStateCreateInfo::dynamicStateCount		= (uint32_t)std::vector<VkDynamicState>::size();
	VkPipelineDynamicStateCreateInfo::pDynamicStates		= std::vector<VkDynamicState>::data();

	return (VkPipelineDynamicStateCreateInfo*)this;
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
	VkPipelineInputAssemblyStateCreateInfo::sType					= VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	VkPipelineInputAssemblyStateCreateInfo::pNext					= nullptr;
	VkPipelineInputAssemblyStateCreateInfo::flags					= 0;
	VkPipelineInputAssemblyStateCreateInfo::topology				= VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	VkPipelineInputAssemblyStateCreateInfo::primitiveRestartEnable	= VK_FALSE;
}


/*************************************************************************
*******************    TessellationStateCreateInfo    ********************
*************************************************************************/
GraphicsPipelineCreateInfo::TessellationStateCreateInfo::TessellationStateCreateInfo()
{
	VkPipelineTessellationStateCreateInfo::sType				= VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
	VkPipelineTessellationStateCreateInfo::pNext				= nullptr;
	VkPipelineTessellationStateCreateInfo::flags				= 0;
	VkPipelineTessellationStateCreateInfo::patchControlPoints	= 0;
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
	VkPipelineVertexInputStateCreateInfo::sType								= VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	VkPipelineVertexInputStateCreateInfo::pNext								= nullptr;
	VkPipelineVertexInputStateCreateInfo::flags								= 0;
	VkPipelineVertexInputStateCreateInfo::vertexBindingDescriptionCount		= 0;
	VkPipelineVertexInputStateCreateInfo::vertexAttributeDescriptionCount	= 0;
	VkPipelineVertexInputStateCreateInfo::pVertexAttributeDescriptions		= nullptr;
	VkPipelineVertexInputStateCreateInfo::pVertexBindingDescriptions		= nullptr;
}


GraphicsPipelineCreateInfo::VertexInputStateCreateInfo::operator const VkPipelineVertexInputStateCreateInfo*()
{
	VkPipelineVertexInputStateCreateInfo::vertexBindingDescriptionCount		= (uint32_t)bindingDescriptions.size();
	VkPipelineVertexInputStateCreateInfo::vertexAttributeDescriptionCount	= (uint32_t)attributeDescriptions.size();
	VkPipelineVertexInputStateCreateInfo::pVertexAttributeDescriptions		= attributeDescriptions.data();
	VkPipelineVertexInputStateCreateInfo::pVertexBindingDescriptions		= bindingDescriptions.data();

	return (VkPipelineVertexInputStateCreateInfo*)this;
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
	VkPipelineViewportStateCreateInfo::sType			= VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	VkPipelineViewportStateCreateInfo::pNext			= nullptr;
	VkPipelineViewportStateCreateInfo::flags			= 0;
	VkPipelineViewportStateCreateInfo::viewportCount	= 0;
	VkPipelineViewportStateCreateInfo::scissorCount		= 0;
	VkPipelineViewportStateCreateInfo::pViewports		= nullptr;
	VkPipelineViewportStateCreateInfo::pScissors		= nullptr;
}


GraphicsPipelineCreateInfo::ViewportStateCreateInfo::operator const VkPipelineViewportStateCreateInfo*()
{
	VkPipelineViewportStateCreateInfo::viewportCount	= (uint32_t)Viewports.size();
	VkPipelineViewportStateCreateInfo::scissorCount		= (uint32_t)Scissors.size();
	VkPipelineViewportStateCreateInfo::pViewports		= Viewports.data();
	VkPipelineViewportStateCreateInfo::pScissors		= Scissors.data();

	return (VkPipelineViewportStateCreateInfo*)this;
}


/*************************************************************************
**************************    PipelineLayout    **************************
*************************************************************************/
PipelineLayout::PipelineLayout(VkPipelineLayout hPipelineLayout) : m_hPipelineLayout(hPipelineLayout)
{

}


std::shared_ptr<PipelineLayout> PipelineLayout::Create(const std::vector<std::shared_ptr<DescriptorSetLayout>> & DescriptorSetLayouts,
													   const std::vector<VkPushConstantRange> & PushConstantRanges)
{
	std::vector<VkDescriptorSetLayout>	SetLayouts;

	for (size_t i = 0; i < DescriptorSetLayouts.size(); i++)
	{
		if ((DescriptorSetLayouts[i] != nullptr) && DescriptorSetLayouts[i]->IsValid())
		{
			SetLayouts.push_back(*DescriptorSetLayouts[i]);
		}
	}

	VkPipelineLayoutCreateInfo			CreateInfo = {};
	CreateInfo.sType					= VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	CreateInfo.pNext					= nullptr;
	CreateInfo.flags					= 0;
	CreateInfo.setLayoutCount			= (uint32_t)SetLayouts.size();
	CreateInfo.pSetLayouts				= SetLayouts.data();
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


std::shared_ptr<PipelineLayout> PipelineLayout::Create(const std::vector<std::shared_ptr<DescriptorSetLayout>> & DescriptorSetLayouts)
{
	std::vector<VkPushConstantRange> PushConstantRanges;
	
	return PipelineLayout::Create(DescriptorSetLayouts, PushConstantRanges);
}


std::shared_ptr<PipelineLayout> PipelineLayout::Create(const std::vector<VkPushConstantRange> & PushConstantRanges)
{
	std::vector<std::shared_ptr<DescriptorSetLayout>> DescriptorSetLayouts;
	
	return PipelineLayout::Create(DescriptorSetLayouts, PushConstantRanges);
}


std::shared_ptr<PipelineLayout> PipelineLayout::Create()
{
	std::vector<VkPushConstantRange> PushConstantRanges;

	std::vector<std::shared_ptr<DescriptorSetLayout>> DescriptorSetLayouts;

	return PipelineLayout::Create(DescriptorSetLayouts, PushConstantRanges);
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


VkResult GraphicsPipeline::Create(GraphicsPipelineCreateInfo & CreateInfo, std::shared_ptr<RenderPass> spRenderPass)
{
	VkPipeline hPipeline = VK_NULL_HANDLE;

	if (sm_pDevice->CreateGraphicsPipelines(VK_NULL_HANDLE, 1, CreateInfo, &hPipeline) == VK_SUCCESS)
	{
		sm_pDevice->DestroyPipeline(m_hPipeline);

		m_CreateInfo = CreateInfo;
		
		m_hPipeline = hPipeline;
	}

	return VK_SUCCESS;
}


void GraphicsPipeline::Release() noexcept
{
	
}


GraphicsPipeline::~GraphicsPipeline()
{
	this->Release();
}