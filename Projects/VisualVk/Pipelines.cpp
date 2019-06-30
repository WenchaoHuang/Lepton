/*************************************************************************
************************    VisualVk_Pipelines    ************************
*************************************************************************/
#include "Framebuffer.h"
#include "Pipelines.h"

using namespace Vk;

/*************************************************************************
***********************    GraphicsPipelineInfo    ***********************
*************************************************************************/
GraphicsPipelineInfo::GraphicsPipelineInfo() : InputAssemblyState(PrimitiveTopology::eTriangleList), TessellationState(0)
{

}


void GraphicsPipelineInfo::VertexInputStateInfo::SetLocation(uint32_t Location, uint32_t Binding, Format eFormat, uint32_t Offset)
{
	for (size_t i = 0; i < attributeDescriptions.size(); i++)
	{
		if (attributeDescriptions[i].location == Location)
		{
			attributeDescriptions[i].format = static_cast<VkFormat>(eFormat);

			attributeDescriptions[i].binding = Binding;

			attributeDescriptions[i].offset = Offset;

			return;
		}
	}

	attributeDescriptions.push_back({ Location, Binding, static_cast<VkFormat>(eFormat), Offset });
}


void GraphicsPipelineInfo::VertexInputStateInfo::SetBinding(uint32_t Binding, uint32_t Stride, VertexInputRate eInputRate)
{
	for (size_t i = 0; i < bindingDescriptions.size(); i++)
	{
		if (bindingDescriptions[i].binding == Binding)
		{
			bindingDescriptions[i].inputRate = static_cast<VkVertexInputRate>(eInputRate);

			bindingDescriptions[i].stride = Stride;

			return;
		}
	}

	bindingDescriptions.push_back({ Binding, Stride, static_cast<VkVertexInputRate>(eInputRate) });
}


/*************************************************************************
*************************    GraphicsPipeline    *************************
*************************************************************************/
GraphicsPipeline::GraphicsPipeline() : m_hPipeline(VK_NULL_HANDLE)
{

}


VkResult GraphicsPipeline::Create(const GraphicsPipelineInfo & CreateInfo)
{
	std::vector<VkPipelineShaderStageCreateInfo>		ShaderStageCreateInfos;

	if ((CreateInfo.ShaderStages.spVertexShader != nullptr) && CreateInfo.ShaderStages.spVertexShader->IsValid())
		ShaderStageCreateInfos.push_back(CreateInfo.ShaderStages.spVertexShader->GetStageInfo(ShaderStage::eVertex));
	if ((CreateInfo.ShaderStages.spFragmentShader != nullptr) && CreateInfo.ShaderStages.spFragmentShader->IsValid())
		ShaderStageCreateInfos.push_back(CreateInfo.ShaderStages.spFragmentShader->GetStageInfo(ShaderStage::eFragment));
	if ((CreateInfo.ShaderStages.spGeometryShader != nullptr) && CreateInfo.ShaderStages.spGeometryShader->IsValid())
		ShaderStageCreateInfos.push_back(CreateInfo.ShaderStages.spGeometryShader->GetStageInfo(ShaderStage::eGeometry));
	if ((CreateInfo.ShaderStages.spTessControlShader != nullptr) && CreateInfo.ShaderStages.spTessControlShader->IsValid())
		ShaderStageCreateInfos.push_back(CreateInfo.ShaderStages.spTessControlShader->GetStageInfo(ShaderStage::eTessellationControl));
	if ((CreateInfo.ShaderStages.spTessEvalutionShader != nullptr) && CreateInfo.ShaderStages.spTessEvalutionShader->IsValid())
		ShaderStageCreateInfos.push_back(CreateInfo.ShaderStages.spTessEvalutionShader->GetStageInfo(ShaderStage::eTessellationEvaluation));

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
	DepthStencilStateCreateInfo.front.failOp						= static_cast<VkStencilOp>(CreateInfo.DepthStencilState.front.failOp);
	DepthStencilStateCreateInfo.front.passOp						= static_cast<VkStencilOp>(CreateInfo.DepthStencilState.front.passOp);
	DepthStencilStateCreateInfo.front.depthFailOp					= static_cast<VkStencilOp>(CreateInfo.DepthStencilState.front.depthFailOp);
	DepthStencilStateCreateInfo.front.compareOp						= static_cast<VkCompareOp>(CreateInfo.DepthStencilState.front.compareOp);
	DepthStencilStateCreateInfo.front.compareMask					= CreateInfo.DepthStencilState.front.compareMask;
	DepthStencilStateCreateInfo.front.writeMask						= CreateInfo.DepthStencilState.front.writeMask;
	DepthStencilStateCreateInfo.front.reference						= CreateInfo.DepthStencilState.front.reference;
	DepthStencilStateCreateInfo.back.failOp							= static_cast<VkStencilOp>(CreateInfo.DepthStencilState.back.failOp);
	DepthStencilStateCreateInfo.back.passOp							= static_cast<VkStencilOp>(CreateInfo.DepthStencilState.back.passOp);
	DepthStencilStateCreateInfo.back.depthFailOp					= static_cast<VkStencilOp>(CreateInfo.DepthStencilState.back.depthFailOp);
	DepthStencilStateCreateInfo.back.compareOp						= static_cast<VkCompareOp>(CreateInfo.DepthStencilState.back.compareOp);
	DepthStencilStateCreateInfo.back.compareMask					= CreateInfo.DepthStencilState.back.compareMask;
	DepthStencilStateCreateInfo.back.writeMask						= CreateInfo.DepthStencilState.back.writeMask;
	DepthStencilStateCreateInfo.back.reference						= CreateInfo.DepthStencilState.back.reference;
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
	PipelineCreateInfo.renderPass									= CreateInfo.hRenderPass;
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