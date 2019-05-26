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


GraphicsPipelineCreateInfo::operator const VkGraphicsPipelineCreateInfo*()
{
	VkGraphicsPipelineCreateInfo::sType					= VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	VkGraphicsPipelineCreateInfo::pNext					= nullptr;
	VkGraphicsPipelineCreateInfo::flags					= 0;
	VkGraphicsPipelineCreateInfo::stageCount			= ShaderStages.GetStageCount();
	VkGraphicsPipelineCreateInfo::pStages				= ShaderStages.GetStages();
	VkGraphicsPipelineCreateInfo::pVertexInputState		= VertexInputState;
	VkGraphicsPipelineCreateInfo::pTessellationState	= TessellationState;
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
*******************    InputAssemblyStateCreateInfo    *******************
*************************************************************************/
GraphicsPipelineCreateInfo::InputAssemblyStateCreateInfo::InputAssemblyStateCreateInfo()
{
	m_CreateInfo.sType						= VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	m_CreateInfo.pNext						= nullptr;
	m_CreateInfo.flags						= 0;
	m_CreateInfo.topology					= VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
	m_CreateInfo.primitiveRestartEnable		= VK_FALSE;
}


GraphicsPipelineCreateInfo::InputAssemblyStateCreateInfo::InputAssemblyStateCreateInfo(VkPrimitiveTopology eTopology)
{
	m_CreateInfo.sType						= VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	m_CreateInfo.pNext						= nullptr;
	m_CreateInfo.flags						= 0;
	m_CreateInfo.topology					= eTopology;
	m_CreateInfo.primitiveRestartEnable		= VK_FALSE;
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
	VkPipelineColorBlendStateCreateInfo::pAttachments			= reinterpret_cast<const VkPipelineColorBlendAttachmentState*>(attachments.data());

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
PipelineLayout::PipelineLayout(VkPipelineLayout hPipelineLayout, VkDescriptorSetLayout hDescriptorSetLayout)
	: m_hPipelineLayout(hPipelineLayout), m_hDescriptorSetLayout(hDescriptorSetLayout)
{

}


std::shared_ptr<PipelineLayout> PipelineLayout::Create(const std::vector<VkDescriptorSetLayoutBinding> & Bindings,
													   const std::vector<VkPushConstantRange> & PushConstantRanges)
{
	VkDescriptorSetLayoutCreateInfo					DescriptorSetLayoutCreateInfo = {};
	DescriptorSetLayoutCreateInfo.sType				= VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	DescriptorSetLayoutCreateInfo.pNext				= nullptr;
	DescriptorSetLayoutCreateInfo.flags				= 0;
	DescriptorSetLayoutCreateInfo.bindingCount		= (uint32_t)Bindings.size();
	DescriptorSetLayoutCreateInfo.pBindings			= Bindings.data();

	VkPipelineLayout hPipelineLayout = VK_NULL_HANDLE;

	VkDescriptorSetLayout hDescriptorSetLayout = VK_NULL_HANDLE;

	if (sm_pDevice->CreateDescriptorSetLayout(&DescriptorSetLayoutCreateInfo, &hDescriptorSetLayout) == VK_SUCCESS)
	{
		VkPipelineLayoutCreateInfo							PipelineLayoutCreateInfo = {};
		PipelineLayoutCreateInfo.sType						= VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		PipelineLayoutCreateInfo.pNext						= nullptr;
		PipelineLayoutCreateInfo.flags						= 0;
		PipelineLayoutCreateInfo.setLayoutCount				= 1;
		PipelineLayoutCreateInfo.pSetLayouts				= &hDescriptorSetLayout;
		PipelineLayoutCreateInfo.pushConstantRangeCount		= (uint32_t)PushConstantRanges.size();
		PipelineLayoutCreateInfo.pPushConstantRanges		= PushConstantRanges.data();

		sm_pDevice->CreatePipelineLayout(&PipelineLayoutCreateInfo, &hPipelineLayout);
	}

	std::shared_ptr<PipelineLayout> spPipelineLayout = std::make_shared<PipelineLayout>(hPipelineLayout, hDescriptorSetLayout);

	if (spPipelineLayout->IsValid())
	{
		spPipelineLayout->m_PushConstantRanges = PushConstantRanges;

		spPipelineLayout->m_DescriptorSetLayoutBindings = Bindings;
	}

	return spPipelineLayout;
}


PipelineLayout::~PipelineLayout() noexcept
{
	sm_pDevice->DestroyDescriptorSetLayout(m_hDescriptorSetLayout);

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