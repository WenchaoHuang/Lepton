/*************************************************************************
************************    VisualVk_Pipelines    ************************
*************************************************************************/
#include <functional>
#include "Pipelines.h"

using namespace Vk;

/*************************************************************************
***********************    GraphicsPipelineInfo    ***********************
*************************************************************************/
GraphicsPipelineInfo::GraphicsPipelineInfo() : InputAssemblyState(PrimitiveTopology::eTriangleList), TessellationState(0)
{

}


void GraphicsPipelineInfo::VertexInputStateInfo::SetLocation(uint32_t Location, uint32_t Binding, VkFormat eFormat, uint32_t Offset)
{
	for (size_t i = 0; i < attributeDescriptions.size(); i++)
	{
		if (attributeDescriptions[i].location == Location)
		{
			attributeDescriptions[i].binding = Binding;

			attributeDescriptions[i].format = eFormat;

			attributeDescriptions[i].offset = Offset;

			return;
		}
	}

	attributeDescriptions.push_back({ Location, Binding, eFormat, Offset });
}


void GraphicsPipelineInfo::VertexInputStateInfo::SetBinding(uint32_t Binding, uint32_t Stride, VkVertexInputRate eInputRate)
{
	for (size_t i = 0; i < bindingDescriptions.size(); i++)
	{
		if (bindingDescriptions[i].binding == Binding)
		{
			bindingDescriptions[i].inputRate = eInputRate;

			bindingDescriptions[i].stride = Stride;

			return;
		}
	}

	bindingDescriptions.push_back({ Binding, Stride, eInputRate });
}


/*************************************************************************
*************************    GraphicsPipeline    *************************
*************************************************************************/
GraphicsPipeline::GraphicsPipeline() : m_hPipeline(VK_NULL_HANDLE)
{

}


VkResult GraphicsPipeline::Create(const GraphicsPipelineInfo & CreateInfo)
{
	std::vector<VkPipelineShaderStageCreateInfo>					ShaderStageCreateInfos;

	if ((CreateInfo.ShaderStages.spVertexShader != 0) && CreateInfo.ShaderStages.spVertexShader->IsValid())
	{
		VkPipelineShaderStageCreateInfo								ShaderStageCreateInfo = {};
		ShaderStageCreateInfo.sType									= VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		ShaderStageCreateInfo.pNext									= nullptr;
		ShaderStageCreateInfo.flags									= 0;
		ShaderStageCreateInfo.stage									= VK_SHADER_STAGE_VERTEX_BIT;
		ShaderStageCreateInfo.module								= CreateInfo.ShaderStages.spVertexShader->GetHandle();
		ShaderStageCreateInfo.pName									= "main";
		ShaderStageCreateInfo.pSpecializationInfo					= nullptr;
		ShaderStageCreateInfos.push_back(ShaderStageCreateInfo);
	}

	if ((CreateInfo.ShaderStages.spFragmentShader != 0) && CreateInfo.ShaderStages.spFragmentShader->IsValid())
	{
		VkPipelineShaderStageCreateInfo								ShaderStageCreateInfo = {};
		ShaderStageCreateInfo.sType									= VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		ShaderStageCreateInfo.pNext									= nullptr;
		ShaderStageCreateInfo.flags									= 0;
		ShaderStageCreateInfo.stage									= VK_SHADER_STAGE_FRAGMENT_BIT;
		ShaderStageCreateInfo.module								= CreateInfo.ShaderStages.spFragmentShader->GetHandle();
		ShaderStageCreateInfo.pName									= "main";
		ShaderStageCreateInfo.pSpecializationInfo					= nullptr;
		ShaderStageCreateInfos.push_back(ShaderStageCreateInfo);
	}
	
	if ((CreateInfo.ShaderStages.spGeometryShader != 0) && CreateInfo.ShaderStages.spGeometryShader->IsValid())
	{
		VkPipelineShaderStageCreateInfo								ShaderStageCreateInfo = {};
		ShaderStageCreateInfo.sType									= VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		ShaderStageCreateInfo.pNext									= nullptr;
		ShaderStageCreateInfo.flags									= 0;
		ShaderStageCreateInfo.stage									= VK_SHADER_STAGE_GEOMETRY_BIT;
		ShaderStageCreateInfo.module								= CreateInfo.ShaderStages.spGeometryShader->GetHandle();
		ShaderStageCreateInfo.pName									= "main";
		ShaderStageCreateInfo.pSpecializationInfo					= nullptr;
		ShaderStageCreateInfos.push_back(ShaderStageCreateInfo);
	}
	
	if ((CreateInfo.ShaderStages.spTessControlShader != 0) && CreateInfo.ShaderStages.spTessControlShader->IsValid())
	{
		VkPipelineShaderStageCreateInfo								ShaderStageCreateInfo = {};
		ShaderStageCreateInfo.sType									= VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		ShaderStageCreateInfo.pNext									= nullptr;
		ShaderStageCreateInfo.flags									= 0;
		ShaderStageCreateInfo.stage									= VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
		ShaderStageCreateInfo.module								= CreateInfo.ShaderStages.spTessControlShader->GetHandle();
		ShaderStageCreateInfo.pName									= "main";
		ShaderStageCreateInfo.pSpecializationInfo					= nullptr;
		ShaderStageCreateInfos.push_back(ShaderStageCreateInfo);
	}
	
	if ((CreateInfo.ShaderStages.spTessEvalutionShader != 0) && CreateInfo.ShaderStages.spTessEvalutionShader->IsValid())
	{
		VkPipelineShaderStageCreateInfo								ShaderStageCreateInfo = {};
		ShaderStageCreateInfo.sType									= VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		ShaderStageCreateInfo.pNext									= nullptr;
		ShaderStageCreateInfo.flags									= 0;
		ShaderStageCreateInfo.stage									= VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
		ShaderStageCreateInfo.module								= CreateInfo.ShaderStages.spTessEvalutionShader->GetHandle();
		ShaderStageCreateInfo.pName									= "main";
		ShaderStageCreateInfo.pSpecializationInfo					= nullptr;
		ShaderStageCreateInfos.push_back(ShaderStageCreateInfo);
	}

	VkPipelineVertexInputStateCreateInfo							VertexInputStateCreateInfo = {};
	VertexInputStateCreateInfo.sType								= VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	VertexInputStateCreateInfo.pNext								= nullptr;
	VertexInputStateCreateInfo.flags								= 0;
	VertexInputStateCreateInfo.vertexBindingDescriptionCount		= static_cast<uint32_t>(CreateInfo.VertexInputState.bindingDescriptions.size());
	VertexInputStateCreateInfo.pVertexBindingDescriptions			= CreateInfo.VertexInputState.bindingDescriptions.data();
	VertexInputStateCreateInfo.vertexAttributeDescriptionCount		= static_cast<uint32_t>(CreateInfo.VertexInputState.attributeDescriptions.size());
	VertexInputStateCreateInfo.pVertexAttributeDescriptions			= CreateInfo.VertexInputState.attributeDescriptions.data();

	VkPipelineInputAssemblyStateCreateInfo							InputAssemblyStateCreateInfo = {};
	InputAssemblyStateCreateInfo.sType								= VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	InputAssemblyStateCreateInfo.pNext								= nullptr;
	InputAssemblyStateCreateInfo.flags								= 0;
	InputAssemblyStateCreateInfo.topology							= static_cast<VkPrimitiveTopology>(CreateInfo.InputAssemblyState);
	InputAssemblyStateCreateInfo.primitiveRestartEnable				= VK_FALSE;

	VkPipelineTessellationStateCreateInfo							TessellationStateCreateInfo = {};
	TessellationStateCreateInfo.sType								= VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
	TessellationStateCreateInfo.pNext								= nullptr;
	TessellationStateCreateInfo.flags								= 0;
	TessellationStateCreateInfo.patchControlPoints					= CreateInfo.TessellationState;

	VkPipelineViewportStateCreateInfo								ViewportStateCreateInfo = {};
	ViewportStateCreateInfo.sType									= VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	ViewportStateCreateInfo.pNext									= nullptr;
	ViewportStateCreateInfo.flags									= 0;
	ViewportStateCreateInfo.viewportCount							= static_cast<uint32_t>(CreateInfo.ViewportState.viewports.size());
	ViewportStateCreateInfo.pViewports								= CreateInfo.ViewportState.viewports.data();
	ViewportStateCreateInfo.scissorCount							= static_cast<uint32_t>(CreateInfo.ViewportState.scissors.size());
	ViewportStateCreateInfo.pScissors								= CreateInfo.ViewportState.scissors.data();

	VkPipelineRasterizationStateCreateInfo							RasterizationStateCreateInfo = {};
	RasterizationStateCreateInfo.sType								= VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	RasterizationStateCreateInfo.pNext								= nullptr;
	RasterizationStateCreateInfo.flags								= 0;
	RasterizationStateCreateInfo.depthClampEnable					= CreateInfo.RasterizationState.depthClampEnable;
	RasterizationStateCreateInfo.rasterizerDiscardEnable			= CreateInfo.RasterizationState.rasterizerDiscardEnable;
	RasterizationStateCreateInfo.polygonMode						= static_cast<VkPolygonMode>(CreateInfo.RasterizationState.polygonMode);
	RasterizationStateCreateInfo.cullMode							= static_cast<VkCullModeFlags>(CreateInfo.RasterizationState.cullMode);
	RasterizationStateCreateInfo.frontFace							= static_cast<VkFrontFace>(CreateInfo.RasterizationState.frontFace);
	RasterizationStateCreateInfo.depthBiasEnable					= CreateInfo.RasterizationState.depthBiasEnable;
	RasterizationStateCreateInfo.depthBiasConstantFactor			= CreateInfo.RasterizationState.depthBiasConstantFactor;
	RasterizationStateCreateInfo.depthBiasClamp						= CreateInfo.RasterizationState.depthBiasClamp;
	RasterizationStateCreateInfo.depthBiasSlopeFactor				= CreateInfo.RasterizationState.depthBiasSlopeFactor;
	RasterizationStateCreateInfo.lineWidth							= CreateInfo.RasterizationState.lineWidth;

	VkPipelineMultisampleStateCreateInfo							MultisampleStateCreateInfo = {};
	MultisampleStateCreateInfo.sType								= VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	MultisampleStateCreateInfo.pNext								= nullptr;
	MultisampleStateCreateInfo.flags								= 0;
	MultisampleStateCreateInfo.rasterizationSamples					= CreateInfo.MultisampleState.rasterizationSamples;
	MultisampleStateCreateInfo.sampleShadingEnable					= CreateInfo.MultisampleState.sampleShadingEnable;
	MultisampleStateCreateInfo.minSampleShading						= CreateInfo.MultisampleState.minSampleShading;
	MultisampleStateCreateInfo.pSampleMask							= nullptr;
	MultisampleStateCreateInfo.alphaToCoverageEnable				= CreateInfo.MultisampleState.alphaToCoverageEnable;
	MultisampleStateCreateInfo.alphaToOneEnable						= CreateInfo.MultisampleState.alphaToOneEnable;

	VkPipelineDepthStencilStateCreateInfo							DepthStencilStateCreateInfo = {};
	DepthStencilStateCreateInfo.sType								= VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	DepthStencilStateCreateInfo.pNext								= nullptr;
	DepthStencilStateCreateInfo.flags								= 0;
	DepthStencilStateCreateInfo.depthTestEnable						= CreateInfo.DepthStencilState.depthTestEnable;
	DepthStencilStateCreateInfo.depthWriteEnable					= CreateInfo.DepthStencilState.depthWriteEnable;
	DepthStencilStateCreateInfo.depthCompareOp						= static_cast<VkCompareOp>(CreateInfo.DepthStencilState.depthCompareOp);
	DepthStencilStateCreateInfo.depthBoundsTestEnable				= CreateInfo.DepthStencilState.depthBoundsTestEnable;
	DepthStencilStateCreateInfo.stencilTestEnable					= CreateInfo.DepthStencilState.stencilTestEnable;
	DepthStencilStateCreateInfo.front								= CreateInfo.DepthStencilState.front;
	DepthStencilStateCreateInfo.back								= CreateInfo.DepthStencilState.back;
	DepthStencilStateCreateInfo.minDepthBounds						= CreateInfo.DepthStencilState.minDepthBounds;
	DepthStencilStateCreateInfo.maxDepthBounds						= CreateInfo.DepthStencilState.maxDepthBounds;

	VkPipelineColorBlendStateCreateInfo								ColorBlendStateCreateInfo = {};
	ColorBlendStateCreateInfo.sType									= VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	ColorBlendStateCreateInfo.pNext									= nullptr;
	ColorBlendStateCreateInfo.flags									= 0;
	ColorBlendStateCreateInfo.logicOpEnable							= CreateInfo.ColorBlendState.logicOpEnable;
	ColorBlendStateCreateInfo.logicOp								= static_cast<VkLogicOp>(CreateInfo.ColorBlendState.logicOp);
	ColorBlendStateCreateInfo.attachmentCount						= static_cast<uint32_t>(CreateInfo.ColorBlendState.attachments.size());
	ColorBlendStateCreateInfo.pAttachments							= reinterpret_cast<const VkPipelineColorBlendAttachmentState*>(CreateInfo.ColorBlendState.attachments.data());
	ColorBlendStateCreateInfo.blendConstants[0]						= CreateInfo.ColorBlendState.blendConstants[0];
	ColorBlendStateCreateInfo.blendConstants[1]						= CreateInfo.ColorBlendState.blendConstants[1];
	ColorBlendStateCreateInfo.blendConstants[2]						= CreateInfo.ColorBlendState.blendConstants[2];
	ColorBlendStateCreateInfo.blendConstants[3]						= CreateInfo.ColorBlendState.blendConstants[3];

	VkPipelineDynamicStateCreateInfo								DynamicStateCreateInfo = {};
	DynamicStateCreateInfo.sType									= VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	DynamicStateCreateInfo.pNext									= nullptr;
	DynamicStateCreateInfo.flags									= 0;
	DynamicStateCreateInfo.dynamicStateCount						= static_cast<uint32_t>(CreateInfo.DynamicStates.size());
	DynamicStateCreateInfo.pDynamicStates							= reinterpret_cast<const VkDynamicState*>(CreateInfo.DynamicStates.data());

	VkGraphicsPipelineCreateInfo									PipelineCreateInfo = {};
	PipelineCreateInfo.sType										= VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	PipelineCreateInfo.pNext										= nullptr;
	PipelineCreateInfo.flags										= 0;
	PipelineCreateInfo.stageCount									= static_cast<uint32_t>(ShaderStageCreateInfos.size());
	PipelineCreateInfo.pStages										= ShaderStageCreateInfos.data();
	PipelineCreateInfo.pVertexInputState							= &VertexInputStateCreateInfo;
	PipelineCreateInfo.pInputAssemblyState							= &InputAssemblyStateCreateInfo;
	PipelineCreateInfo.pTessellationState							= &TessellationStateCreateInfo;
	PipelineCreateInfo.pViewportState								= &ViewportStateCreateInfo;
	PipelineCreateInfo.pRasterizationState							= &RasterizationStateCreateInfo;
	PipelineCreateInfo.pMultisampleState							= &MultisampleStateCreateInfo;
	PipelineCreateInfo.pDepthStencilState							= &DepthStencilStateCreateInfo;
	PipelineCreateInfo.pColorBlendState								= &ColorBlendStateCreateInfo;
	PipelineCreateInfo.pDynamicState								= &DynamicStateCreateInfo;
	PipelineCreateInfo.layout										= (CreateInfo.spPipelineLayout == nullptr) ? VK_NULL_HANDLE : CreateInfo.spPipelineLayout->GetHandle();
	PipelineCreateInfo.renderPass									= (CreateInfo.spRenderPass == nullptr) ? VK_NULL_HANDLE : CreateInfo.spRenderPass->GetHandle();;
	PipelineCreateInfo.subpass										= 0;
	PipelineCreateInfo.basePipelineHandle							= VK_NULL_HANDLE;
	PipelineCreateInfo.basePipelineIndex							= 0;

	VkPipeline hPipeline = VK_NULL_HANDLE;

	if (m_pDevice->CreateGraphicsPipelines(VK_NULL_HANDLE, 1, &PipelineCreateInfo, &hPipeline) == VK_SUCCESS)
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

		m_pDevice->DestroyPipeline(m_hPipeline);

		m_hPipeline = VK_NULL_HANDLE;
	}
}


GraphicsPipeline::~GraphicsPipeline()
{
	this->Release();
}