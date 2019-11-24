/*************************************************************************
********************    Lava_RayTracingPipelineNV    *********************
*************************************************************************/
#pragma once

#include "ShaderModule.h"
#include "PipelineLayout.h"

namespace Lava
{
	typedef VkPipeline		VkRayTracingPipelineNV;

	/*********************************************************************
	*****************    RayTracingShaderGroupTypeNV    ******************
	*********************************************************************/

	/**
	 *	@brief	Ray tracing shader group types.
	 */
	enum class RayTracingShaderGroupTypeNV
	{
		eGeneral				= VK_RAY_TRACING_SHADER_GROUP_TYPE_GENERAL_NV,
		eTrianglesHitGroup		= VK_RAY_TRACING_SHADER_GROUP_TYPE_TRIANGLES_HIT_GROUP_NV,
		eProceduralHitGoutp		= VK_RAY_TRACING_SHADER_GROUP_TYPE_PROCEDURAL_HIT_GROUP_NV,
	};

	/*********************************************************************
	*******************    RayTracingPipelineParam    ********************
	*********************************************************************/

	/**
	 *	@brief	Vulkan ray tracing pipeline parameters.
	 */
	struct RayTracingPipelineParam
	{

	public:

		/**
		 *	@brief	Structure specifying shaders in a shader group.
		 */
		struct ShaderGroup
		{
			RayTracingShaderGroupTypeNV		eType					= RayTracingShaderGroupTypeNV::eGeneral;
			uint32_t						generalShader			= VK_SHADER_UNUSED_NV;
			uint32_t						closestHitShader		= VK_SHADER_UNUSED_NV;
			uint32_t						anyHitShader			= VK_SHADER_UNUSED_NV;
			uint32_t						intersectionShader		= VK_SHADER_UNUSED_NV;
		};

	public:

		uint32_t						maxRecursionDepth = 1;
		PipelineLayout					pipelineLayout;
		std::vector<ShaderGroup>		shaderGroups;
		std::vector<ShaderModule>		shaderStages;
	};

	/*********************************************************************
	*********************    RayTracingPipelineNV    *********************
	*********************************************************************/

	/**
	 *	@brief	Wrapper for Nvidia ray tracing pipeline object.
	 */
	class RayTracingPipelineNV
	{
		LAVA_UNIQUE_RESOURCE(RayTracingPipelineNV)

	public:

		//!	@brief	Create ray tracing pipeline object.
		RayTracingPipelineNV();

		//!	@brief	Create and initialize immediately.
		explicit RayTracingPipelineNV(const RayTracingPipelineParam & Param);

		//!	@brief	Destroy ray tracing pipeline object.
		~RayTracingPipelineNV();

	public:

		//!	@brief	Create a new ray tracing pipeline.
		Result Create(const RayTracingPipelineParam & Param);

		//!	@brief	Return pipeline parameters.
		const RayTracingPipelineParam & GetParam() const { return m_Parameter; }

		//!	@brief	Destroy the ray tracing pipeline.
		void Destroy();

	public:
		
		RayTracingPipelineParam		m_Parameter;
	};
}