/*************************************************************************
************************    VisualVk_Pipelines    ************************
*************************************************************************/
#include "Framebuffer.h"
#include "Pipelines.h"
#include <functional>

using namespace Vk;

/*************************************************************************
**********************    GraphicsPipelineParam    ***********************
*************************************************************************/
GraphicsPipelineParam::GraphicsPipelineParam() : InputAssemblyState(PrimitiveTopology::eTriangleList), TessellationState(0)
{

}


void GraphicsPipelineParam::VertexInputStateInfo::SetLocation(uint32_t Location, uint32_t Binding, Format eFormat, uint32_t Offset)
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


void GraphicsPipelineParam::VertexInputStateInfo::SetBinding(uint32_t Binding, uint32_t Stride, VertexInputRate eInputRate)
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


VkResult GraphicsPipeline::Create(const GraphicsPipelineParam & PipelineParam)
{
	std::vector<VkPipelineShaderStageCreateInfo>		ShaderStageCreateInfos;

	auto GetShaderStageInfo = [](VkShaderModule hModule, ShaderStage eStage) -> VkPipelineShaderStageCreateInfo
	{
		VkPipelineShaderStageCreateInfo			PipelineParam = {};
		PipelineParam.sType						= VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		PipelineParam.pNext						= nullptr;
		PipelineParam.flags						= 0;
		PipelineParam.stage						= static_cast<VkShaderStageFlagBits>(eStage);
		PipelineParam.module					= hModule;
		PipelineParam.pName						= "main";
		PipelineParam.pSpecializationInfo		= nullptr;

		return PipelineParam;
	};

	if (PipelineParam.ShaderStages.VertexShader.IsValid())
		ShaderStageCreateInfos.push_back(GetShaderStageInfo(PipelineParam.ShaderStages.VertexShader, ShaderStage::eVertex));
	if (PipelineParam.ShaderStages.FragmentShader.IsValid())
		ShaderStageCreateInfos.push_back(GetShaderStageInfo(PipelineParam.ShaderStages.FragmentShader, ShaderStage::eFragment));
	if (PipelineParam.ShaderStages.GeometryShader.IsValid())
		ShaderStageCreateInfos.push_back(GetShaderStageInfo(PipelineParam.ShaderStages.GeometryShader, ShaderStage::eGeometry));
	if (PipelineParam.ShaderStages.TessControlShader.IsValid())
		ShaderStageCreateInfos.push_back(GetShaderStageInfo(PipelineParam.ShaderStages.TessControlShader, ShaderStage::eTessellationControl));
	if (PipelineParam.ShaderStages.TessEvalutionShader.IsValid())
		ShaderStageCreateInfos.push_back(GetShaderStageInfo(PipelineParam.ShaderStages.TessEvalutionShader, ShaderStage::eTessellationEvaluation));

	VkPipelineVertexInputStateCreateInfo							VertexInputStateCreateInfo = {};
	VertexInputStateCreateInfo.sType								= VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	VertexInputStateCreateInfo.pNext								= nullptr;
	VertexInputStateCreateInfo.flags								= 0;
	VertexInputStateCreateInfo.vertexBindingDescriptionCount		= static_cast<uint32_t>(PipelineParam.VertexInputState.bindingDescriptions.size());
	VertexInputStateCreateInfo.pVertexBindingDescriptions			= PipelineParam.VertexInputState.bindingDescriptions.data();
	VertexInputStateCreateInfo.vertexAttributeDescriptionCount		= static_cast<uint32_t>(PipelineParam.VertexInputState.attributeDescriptions.size());
	VertexInputStateCreateInfo.pVertexAttributeDescriptions			= PipelineParam.VertexInputState.attributeDescriptions.data();

	VkPipelineInputAssemblyStateCreateInfo							InputAssemblyStateCreateInfo = {};
	InputAssemblyStateCreateInfo.sType								= VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	InputAssemblyStateCreateInfo.pNext								= nullptr;
	InputAssemblyStateCreateInfo.flags								= 0;
	InputAssemblyStateCreateInfo.topology							= static_cast<VkPrimitiveTopology>(PipelineParam.InputAssemblyState);
	InputAssemblyStateCreateInfo.primitiveRestartEnable				= VK_FALSE;

	VkPipelineTessellationStateCreateInfo							TessellationStateCreateInfo = {};
	TessellationStateCreateInfo.sType								= VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
	TessellationStateCreateInfo.pNext								= nullptr;
	TessellationStateCreateInfo.flags								= 0;
	TessellationStateCreateInfo.patchControlPoints					= PipelineParam.TessellationState;

	VkPipelineViewportStateCreateInfo								ViewportStateCreateInfo = {};
	ViewportStateCreateInfo.sType									= VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	ViewportStateCreateInfo.pNext									= nullptr;
	ViewportStateCreateInfo.flags									= 0;
	ViewportStateCreateInfo.viewportCount							= static_cast<uint32_t>(PipelineParam.ViewportState.viewports.size());
	ViewportStateCreateInfo.pViewports								= PipelineParam.ViewportState.viewports.data();
	ViewportStateCreateInfo.scissorCount							= static_cast<uint32_t>(PipelineParam.ViewportState.scissors.size());
	ViewportStateCreateInfo.pScissors								= PipelineParam.ViewportState.scissors.data();

	VkPipelineRasterizationStateCreateInfo							RasterizationStateCreateInfo = {};
	RasterizationStateCreateInfo.sType								= VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	RasterizationStateCreateInfo.pNext								= nullptr;
	RasterizationStateCreateInfo.flags								= 0;
	RasterizationStateCreateInfo.depthClampEnable					= PipelineParam.RasterizationState.depthClampEnable;
	RasterizationStateCreateInfo.rasterizerDiscardEnable			= PipelineParam.RasterizationState.rasterizerDiscardEnable;
	RasterizationStateCreateInfo.polygonMode						= static_cast<VkPolygonMode>(PipelineParam.RasterizationState.polygonMode);
	RasterizationStateCreateInfo.cullMode							= static_cast<VkCullModeFlags>(PipelineParam.RasterizationState.cullMode);
	RasterizationStateCreateInfo.frontFace							= static_cast<VkFrontFace>(PipelineParam.RasterizationState.frontFace);
	RasterizationStateCreateInfo.depthBiasEnable					= PipelineParam.RasterizationState.depthBiasEnable;
	RasterizationStateCreateInfo.depthBiasConstantFactor			= PipelineParam.RasterizationState.depthBiasConstantFactor;
	RasterizationStateCreateInfo.depthBiasClamp						= PipelineParam.RasterizationState.depthBiasClamp;
	RasterizationStateCreateInfo.depthBiasSlopeFactor				= PipelineParam.RasterizationState.depthBiasSlopeFactor;
	RasterizationStateCreateInfo.lineWidth							= PipelineParam.RasterizationState.lineWidth;

	VkPipelineMultisampleStateCreateInfo							MultisampleStateCreateInfo = {};
	MultisampleStateCreateInfo.sType								= VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	MultisampleStateCreateInfo.pNext								= nullptr;
	MultisampleStateCreateInfo.flags								= 0;
	MultisampleStateCreateInfo.rasterizationSamples					= static_cast<VkSampleCountFlagBits>(PipelineParam.MultisampleState.rasterizationSamples);
	MultisampleStateCreateInfo.sampleShadingEnable					= PipelineParam.MultisampleState.sampleShadingEnable;
	MultisampleStateCreateInfo.minSampleShading						= PipelineParam.MultisampleState.minSampleShading;
	MultisampleStateCreateInfo.pSampleMask							= nullptr;
	MultisampleStateCreateInfo.alphaToCoverageEnable				= PipelineParam.MultisampleState.alphaToCoverageEnable;
	MultisampleStateCreateInfo.alphaToOneEnable						= PipelineParam.MultisampleState.alphaToOneEnable;

	VkPipelineDepthStencilStateCreateInfo							DepthStencilStateCreateInfo = {};
	DepthStencilStateCreateInfo.sType								= VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	DepthStencilStateCreateInfo.pNext								= nullptr;
	DepthStencilStateCreateInfo.flags								= 0;
	DepthStencilStateCreateInfo.depthTestEnable						= PipelineParam.DepthStencilState.depthTestEnable;
	DepthStencilStateCreateInfo.depthWriteEnable					= PipelineParam.DepthStencilState.depthWriteEnable;
	DepthStencilStateCreateInfo.depthCompareOp						= static_cast<VkCompareOp>(PipelineParam.DepthStencilState.depthCompareOp);
	DepthStencilStateCreateInfo.depthBoundsTestEnable				= PipelineParam.DepthStencilState.depthBoundsTestEnable;
	DepthStencilStateCreateInfo.stencilTestEnable					= PipelineParam.DepthStencilState.stencilTestEnable;
	DepthStencilStateCreateInfo.front.failOp						= static_cast<VkStencilOp>(PipelineParam.DepthStencilState.front.failOp);
	DepthStencilStateCreateInfo.front.passOp						= static_cast<VkStencilOp>(PipelineParam.DepthStencilState.front.passOp);
	DepthStencilStateCreateInfo.front.depthFailOp					= static_cast<VkStencilOp>(PipelineParam.DepthStencilState.front.depthFailOp);
	DepthStencilStateCreateInfo.front.compareOp						= static_cast<VkCompareOp>(PipelineParam.DepthStencilState.front.compareOp);
	DepthStencilStateCreateInfo.front.compareMask					= PipelineParam.DepthStencilState.front.compareMask;
	DepthStencilStateCreateInfo.front.writeMask						= PipelineParam.DepthStencilState.front.writeMask;
	DepthStencilStateCreateInfo.front.reference						= PipelineParam.DepthStencilState.front.reference;
	DepthStencilStateCreateInfo.back.failOp							= static_cast<VkStencilOp>(PipelineParam.DepthStencilState.back.failOp);
	DepthStencilStateCreateInfo.back.passOp							= static_cast<VkStencilOp>(PipelineParam.DepthStencilState.back.passOp);
	DepthStencilStateCreateInfo.back.depthFailOp					= static_cast<VkStencilOp>(PipelineParam.DepthStencilState.back.depthFailOp);
	DepthStencilStateCreateInfo.back.compareOp						= static_cast<VkCompareOp>(PipelineParam.DepthStencilState.back.compareOp);
	DepthStencilStateCreateInfo.back.compareMask					= PipelineParam.DepthStencilState.back.compareMask;
	DepthStencilStateCreateInfo.back.writeMask						= PipelineParam.DepthStencilState.back.writeMask;
	DepthStencilStateCreateInfo.back.reference						= PipelineParam.DepthStencilState.back.reference;
	DepthStencilStateCreateInfo.minDepthBounds						= PipelineParam.DepthStencilState.minDepthBounds;
	DepthStencilStateCreateInfo.maxDepthBounds						= PipelineParam.DepthStencilState.maxDepthBounds;

	VkPipelineColorBlendStateCreateInfo								ColorBlendStateCreateInfo = {};
	ColorBlendStateCreateInfo.sType									= VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	ColorBlendStateCreateInfo.pNext									= nullptr;
	ColorBlendStateCreateInfo.flags									= 0;
	ColorBlendStateCreateInfo.logicOpEnable							= PipelineParam.ColorBlendState.logicOpEnable;
	ColorBlendStateCreateInfo.logicOp								= static_cast<VkLogicOp>(PipelineParam.ColorBlendState.logicOp);
	ColorBlendStateCreateInfo.attachmentCount						= static_cast<uint32_t>(PipelineParam.ColorBlendState.attachments.size());
	ColorBlendStateCreateInfo.pAttachments							= reinterpret_cast<const VkPipelineColorBlendAttachmentState*>(PipelineParam.ColorBlendState.attachments.data());
	ColorBlendStateCreateInfo.blendConstants[0]						= PipelineParam.ColorBlendState.blendConstants[0];
	ColorBlendStateCreateInfo.blendConstants[1]						= PipelineParam.ColorBlendState.blendConstants[1];
	ColorBlendStateCreateInfo.blendConstants[2]						= PipelineParam.ColorBlendState.blendConstants[2];
	ColorBlendStateCreateInfo.blendConstants[3]						= PipelineParam.ColorBlendState.blendConstants[3];

	VkPipelineDynamicStateCreateInfo								DynamicStateCreateInfo = {};
	DynamicStateCreateInfo.sType									= VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	DynamicStateCreateInfo.pNext									= nullptr;
	DynamicStateCreateInfo.flags									= 0;
	DynamicStateCreateInfo.dynamicStateCount						= static_cast<uint32_t>(PipelineParam.DynamicStates.size());
	DynamicStateCreateInfo.pDynamicStates							= reinterpret_cast<const VkDynamicState*>(PipelineParam.DynamicStates.data());

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
	PipelineCreateInfo.layout										= (PipelineParam.spPipelineLayout == nullptr) ? VK_NULL_HANDLE : PipelineParam.spPipelineLayout->GetHandle();
	PipelineCreateInfo.renderPass									= PipelineParam.hRenderPass;
	PipelineCreateInfo.subpass										= 0;
	PipelineCreateInfo.basePipelineHandle							= VK_NULL_HANDLE;
	PipelineCreateInfo.basePipelineIndex							= 0;

	VkPipeline hPipeline = VK_NULL_HANDLE;

	if (m_pDevice->CreateGraphicsPipelines(VK_NULL_HANDLE, 1, &PipelineCreateInfo, &hPipeline) == VK_SUCCESS)
	{
		this->Release();

		m_hPipeline = hPipeline;

		m_PipelineParam = PipelineParam;
	}

	return VK_SUCCESS;
}


void GraphicsPipeline::Release() noexcept
{
	if (m_hPipeline != VK_NULL_HANDLE)
	{
		m_pDevice->DestroyPipeline(m_hPipeline);

		m_PipelineParam = GraphicsPipelineParam();

		m_hPipeline = VK_NULL_HANDLE;
	}
}


GraphicsPipeline::~GraphicsPipeline()
{
	this->Release();
}