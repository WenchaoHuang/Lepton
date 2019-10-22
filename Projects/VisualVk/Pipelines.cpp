/*************************************************************************
************************    VisualVk_Pipelines    ************************
*************************************************************************/

#include <functional>
#include "Pipelines.h"
#include "Framebuffer.h"
#include "ShaderModule.h"
#include "PipelineLayout.h"

using namespace Vk;

/*************************************************************************
**********************    GraphicsPipelineParam    ***********************
*************************************************************************/
GraphicsPipelineParam::GraphicsPipelineParam() : inputAssemblyState(PrimitiveTopology::eTriangleList), tessellationState(0)
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
GraphicsPipeline::GraphicsPipeline() : m_hGraphicsPipeline(VK_NULL_HANDLE)
{

}


GraphicsPipeline::GraphicsPipeline(const GraphicsPipelineParam & Param) : GraphicsPipeline()
{
	this->Create(Param);
}


Result GraphicsPipeline::Create(const GraphicsPipelineParam & Param)
{
	if (!Param.renderPass.IsValid() ||
		(Param.spPipelineLayout == nullptr) || !Param.spPipelineLayout->IsValid() ||
		 Param.renderPass.GetDeviceHandle() != Param.spPipelineLayout->GetDeviceHandle())
	{
		return Result::eErrorInvalidDeviceHandle;
	}

	std::vector<VkPipelineShaderStageCreateInfo>		ShaderStageCreateInfos;

	auto pfnGetShaderStageInfo = [](VkShaderModule hModule, ShaderStage eStage) -> VkPipelineShaderStageCreateInfo
	{
		VkPipelineShaderStageCreateInfo					ShaderStageCreateInfo = {};
		ShaderStageCreateInfo.sType						= VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		ShaderStageCreateInfo.pNext						= nullptr;
		ShaderStageCreateInfo.flags						= 0;
		ShaderStageCreateInfo.stage						= static_cast<VkShaderStageFlagBits>(eStage);
		ShaderStageCreateInfo.module					= hModule;
		ShaderStageCreateInfo.pName						= "main";
		ShaderStageCreateInfo.pSpecializationInfo		= nullptr;

		return ShaderStageCreateInfo;
	};

	if (Param.shaderStages.VertexShader.IsValid())
		ShaderStageCreateInfos.push_back(pfnGetShaderStageInfo(Param.shaderStages.VertexShader, ShaderStage::eVertex));
	if (Param.shaderStages.FragmentShader.IsValid())
		ShaderStageCreateInfos.push_back(pfnGetShaderStageInfo(Param.shaderStages.FragmentShader, ShaderStage::eFragment));
	if (Param.shaderStages.GeometryShader.IsValid())
		ShaderStageCreateInfos.push_back(pfnGetShaderStageInfo(Param.shaderStages.GeometryShader, ShaderStage::eGeometry));
	if (Param.shaderStages.TessControlShader.IsValid())
		ShaderStageCreateInfos.push_back(pfnGetShaderStageInfo(Param.shaderStages.TessControlShader, ShaderStage::eTessellationControl));
	if (Param.shaderStages.TessEvalutionShader.IsValid())
		ShaderStageCreateInfos.push_back(pfnGetShaderStageInfo(Param.shaderStages.TessEvalutionShader, ShaderStage::eTessellationEvaluation));

	VkPipelineVertexInputStateCreateInfo							VertexInputStateCreateInfo = {};
	VertexInputStateCreateInfo.sType								= VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	VertexInputStateCreateInfo.pNext								= nullptr;
	VertexInputStateCreateInfo.flags								= 0;
	VertexInputStateCreateInfo.vertexBindingDescriptionCount		= static_cast<uint32_t>(Param.vertexInputState.bindingDescriptions.size());
	VertexInputStateCreateInfo.pVertexBindingDescriptions			= Param.vertexInputState.bindingDescriptions.data();
	VertexInputStateCreateInfo.vertexAttributeDescriptionCount		= static_cast<uint32_t>(Param.vertexInputState.attributeDescriptions.size());
	VertexInputStateCreateInfo.pVertexAttributeDescriptions			= Param.vertexInputState.attributeDescriptions.data();

	VkPipelineInputAssemblyStateCreateInfo							InputAssemblyStateCreateInfo = {};
	InputAssemblyStateCreateInfo.sType								= VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	InputAssemblyStateCreateInfo.pNext								= nullptr;
	InputAssemblyStateCreateInfo.flags								= 0;
	InputAssemblyStateCreateInfo.topology							= static_cast<VkPrimitiveTopology>(Param.inputAssemblyState);
	InputAssemblyStateCreateInfo.primitiveRestartEnable				= VK_FALSE;

	VkPipelineTessellationStateCreateInfo							TessellationStateCreateInfo = {};
	TessellationStateCreateInfo.sType								= VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
	TessellationStateCreateInfo.pNext								= nullptr;
	TessellationStateCreateInfo.flags								= 0;
	TessellationStateCreateInfo.patchControlPoints					= Param.tessellationState;

	VkPipelineViewportStateCreateInfo								ViewportStateCreateInfo = {};
	ViewportStateCreateInfo.sType									= VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	ViewportStateCreateInfo.pNext									= nullptr;
	ViewportStateCreateInfo.flags									= 0;
	ViewportStateCreateInfo.viewportCount							= static_cast<uint32_t>(Param.viewportState.viewports.size());
	ViewportStateCreateInfo.pViewports								= Param.viewportState.viewports.data();
	ViewportStateCreateInfo.scissorCount							= static_cast<uint32_t>(Param.viewportState.scissors.size());
	ViewportStateCreateInfo.pScissors								= Param.viewportState.scissors.data();

	VkPipelineRasterizationStateCreateInfo							RasterizationStateCreateInfo = {};
	RasterizationStateCreateInfo.sType								= VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	RasterizationStateCreateInfo.pNext								= nullptr;
	RasterizationStateCreateInfo.flags								= 0;
	RasterizationStateCreateInfo.depthClampEnable					= Param.rasterizationState.depthClampEnable;
	RasterizationStateCreateInfo.rasterizerDiscardEnable			= Param.rasterizationState.rasterizerDiscardEnable;
	RasterizationStateCreateInfo.polygonMode						= static_cast<VkPolygonMode>(Param.rasterizationState.polygonMode);
	RasterizationStateCreateInfo.cullMode							= static_cast<VkCullModeFlags>(Param.rasterizationState.cullMode);
	RasterizationStateCreateInfo.frontFace							= static_cast<VkFrontFace>(Param.rasterizationState.frontFace);
	RasterizationStateCreateInfo.depthBiasEnable					= Param.rasterizationState.depthBiasEnable;
	RasterizationStateCreateInfo.depthBiasConstantFactor			= Param.rasterizationState.depthBiasConstantFactor;
	RasterizationStateCreateInfo.depthBiasClamp						= Param.rasterizationState.depthBiasClamp;
	RasterizationStateCreateInfo.depthBiasSlopeFactor				= Param.rasterizationState.depthBiasSlopeFactor;
	RasterizationStateCreateInfo.lineWidth							= Param.rasterizationState.lineWidth;

	VkPipelineMultisampleStateCreateInfo							MultisampleStateCreateInfo = {};
	MultisampleStateCreateInfo.sType								= VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	MultisampleStateCreateInfo.pNext								= nullptr;
	MultisampleStateCreateInfo.flags								= 0;
	MultisampleStateCreateInfo.rasterizationSamples					= static_cast<VkSampleCountFlagBits>(Param.multisampleState.rasterizationSamples);
	MultisampleStateCreateInfo.sampleShadingEnable					= Param.multisampleState.sampleShadingEnable;
	MultisampleStateCreateInfo.minSampleShading						= Param.multisampleState.minSampleShading;
	MultisampleStateCreateInfo.pSampleMask							= nullptr;
	MultisampleStateCreateInfo.alphaToCoverageEnable				= Param.multisampleState.alphaToCoverageEnable;
	MultisampleStateCreateInfo.alphaToOneEnable						= Param.multisampleState.alphaToOneEnable;

	VkPipelineDepthStencilStateCreateInfo							DepthStencilStateCreateInfo = {};
	DepthStencilStateCreateInfo.sType								= VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	DepthStencilStateCreateInfo.pNext								= nullptr;
	DepthStencilStateCreateInfo.flags								= 0;
	DepthStencilStateCreateInfo.depthTestEnable						= Param.depthStencilState.depthTestEnable;
	DepthStencilStateCreateInfo.depthWriteEnable					= Param.depthStencilState.depthWriteEnable;
	DepthStencilStateCreateInfo.depthCompareOp						= static_cast<VkCompareOp>(Param.depthStencilState.depthCompareOp);
	DepthStencilStateCreateInfo.depthBoundsTestEnable				= Param.depthStencilState.depthBoundsTestEnable;
	DepthStencilStateCreateInfo.stencilTestEnable					= Param.depthStencilState.stencilTestEnable;
	DepthStencilStateCreateInfo.front.failOp						= static_cast<VkStencilOp>(Param.depthStencilState.front.failOp);
	DepthStencilStateCreateInfo.front.passOp						= static_cast<VkStencilOp>(Param.depthStencilState.front.passOp);
	DepthStencilStateCreateInfo.front.depthFailOp					= static_cast<VkStencilOp>(Param.depthStencilState.front.depthFailOp);
	DepthStencilStateCreateInfo.front.compareOp						= static_cast<VkCompareOp>(Param.depthStencilState.front.compareOp);
	DepthStencilStateCreateInfo.front.compareMask					= Param.depthStencilState.front.compareMask;
	DepthStencilStateCreateInfo.front.writeMask						= Param.depthStencilState.front.writeMask;
	DepthStencilStateCreateInfo.front.reference						= Param.depthStencilState.front.reference;
	DepthStencilStateCreateInfo.back.failOp							= static_cast<VkStencilOp>(Param.depthStencilState.back.failOp);
	DepthStencilStateCreateInfo.back.passOp							= static_cast<VkStencilOp>(Param.depthStencilState.back.passOp);
	DepthStencilStateCreateInfo.back.depthFailOp					= static_cast<VkStencilOp>(Param.depthStencilState.back.depthFailOp);
	DepthStencilStateCreateInfo.back.compareOp						= static_cast<VkCompareOp>(Param.depthStencilState.back.compareOp);
	DepthStencilStateCreateInfo.back.compareMask					= Param.depthStencilState.back.compareMask;
	DepthStencilStateCreateInfo.back.writeMask						= Param.depthStencilState.back.writeMask;
	DepthStencilStateCreateInfo.back.reference						= Param.depthStencilState.back.reference;
	DepthStencilStateCreateInfo.minDepthBounds						= Param.depthStencilState.minDepthBounds;
	DepthStencilStateCreateInfo.maxDepthBounds						= Param.depthStencilState.maxDepthBounds;

	VkPipelineColorBlendStateCreateInfo								ColorBlendStateCreateInfo = {};
	ColorBlendStateCreateInfo.sType									= VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	ColorBlendStateCreateInfo.pNext									= nullptr;
	ColorBlendStateCreateInfo.flags									= 0;
	ColorBlendStateCreateInfo.logicOpEnable							= Param.colorBlendState.logicOpEnable;
	ColorBlendStateCreateInfo.logicOp								= static_cast<VkLogicOp>(Param.colorBlendState.logicOp);
	ColorBlendStateCreateInfo.attachmentCount						= static_cast<uint32_t>(Param.colorBlendState.attachments.size());
	ColorBlendStateCreateInfo.pAttachments							= reinterpret_cast<const VkPipelineColorBlendAttachmentState*>(Param.colorBlendState.attachments.data());
	ColorBlendStateCreateInfo.blendConstants[0]						= Param.colorBlendState.blendConstants[0];
	ColorBlendStateCreateInfo.blendConstants[1]						= Param.colorBlendState.blendConstants[1];
	ColorBlendStateCreateInfo.blendConstants[2]						= Param.colorBlendState.blendConstants[2];
	ColorBlendStateCreateInfo.blendConstants[3]						= Param.colorBlendState.blendConstants[3];

	VkPipelineDynamicStateCreateInfo								DynamicStateCreateInfo = {};
	DynamicStateCreateInfo.sType									= VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	DynamicStateCreateInfo.pNext									= nullptr;
	DynamicStateCreateInfo.flags									= 0;
	DynamicStateCreateInfo.dynamicStateCount						= static_cast<uint32_t>(Param.dynamicStates.size());
	DynamicStateCreateInfo.pDynamicStates							= reinterpret_cast<const VkDynamicState*>(Param.dynamicStates.data());

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
	PipelineCreateInfo.layout										= Param.spPipelineLayout->GetHandle();
	PipelineCreateInfo.renderPass									= Param.renderPass;
	PipelineCreateInfo.subpass										= 0;
	PipelineCreateInfo.basePipelineHandle							= VK_NULL_HANDLE;
	PipelineCreateInfo.basePipelineIndex							= 0;

	VkPipeline hPipeline = VK_NULL_HANDLE;

	VkResult eResult = vkCreateGraphicsPipelines(Param.renderPass.GetDeviceHandle(), VK_NULL_HANDLE, 1, &PipelineCreateInfo, nullptr, &hPipeline);

	if (eResult == VK_SUCCESS)
	{
		this->Destroy();

		m_hDevice = Param.renderPass.GetDeviceHandle();

		m_hGraphicsPipeline = hPipeline;

		m_Parameter = Param;
	}

	return VK_RESULT_CAST(eResult);
}


void GraphicsPipeline::Destroy()
{
	if (m_hGraphicsPipeline != VK_NULL_HANDLE)
	{
		vkDestroyPipeline(m_hDevice, m_hGraphicsPipeline, nullptr);

		m_Parameter = GraphicsPipelineParam();

		m_hGraphicsPipeline = VK_NULL_HANDLE;

		m_hDevice = VK_NULL_HANDLE;
	}
}


GraphicsPipeline::~GraphicsPipeline()
{
	this->Destroy();
}


/*************************************************************************
*************************    ComputePipeline    **************************
*************************************************************************/
ComputePipeline::ComputePipeline() : m_hDevice(VK_NULL_HANDLE), m_hComputePipeline(VK_NULL_HANDLE)
{

}


ComputePipeline::~ComputePipeline()
{

}


/*************************************************************************
************************    RayTracingPipeline    ************************
*************************************************************************/
RayTracingPipeline::RayTracingPipeline() : m_hDevice(VK_NULL_HANDLE), m_hRayTracingPipeline(VK_NULL_HANDLE)
{

}


RayTracingPipeline::~RayTracingPipeline()
{

}