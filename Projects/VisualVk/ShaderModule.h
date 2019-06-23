/*************************************************************************
**********************    VisualVk_ShaderModule    ***********************
*************************************************************************/
#pragma once

#include <memory>
#include "Resource.h"

namespace Vk
{
	/*********************************************************************
	*********************    ShaderStageFlagBits    **********************
	*********************************************************************/

	/**
	 *	@brief	
	 */
	enum class ShaderStageFlagBits
	{
		eAll						= VK_SHADER_STAGE_ALL,
		eVertex						= VK_SHADER_STAGE_VERTEX_BIT,
		eCompute					= VK_SHADER_STAGE_COMPUTE_BIT,
		eGeometry					= VK_SHADER_STAGE_GEOMETRY_BIT,
		eFragment					= VK_SHADER_STAGE_FRAGMENT_BIT,
		eAllGraphics				= VK_SHADER_STAGE_ALL_GRAPHICS,
		eTessellationControl		= VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT,
		eTessellationEvaluation		= VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT,
		eIntersectionNV				= VK_SHADER_STAGE_INTERSECTION_BIT_NV,
		eClosestHitNV				= VK_SHADER_STAGE_CLOSEST_HIT_BIT_NV,
		eCallableNV					= VK_SHADER_STAGE_CALLABLE_BIT_NV,
		eRaygenNV					= VK_SHADER_STAGE_RAYGEN_BIT_NV,
		eAnyHitNV					= VK_SHADER_STAGE_ANY_HIT_BIT_NV,
		eMissNV						= VK_SHADER_STAGE_MISS_BIT_NV,
		eTaskNV						= VK_SHADER_STAGE_TASK_BIT_NV,
		eMeshNV						= VK_SHADER_STAGE_MESH_BIT_NV
	};

	/*********************************************************************
	*************************    ShaderModule    *************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan shader module object.
	 */
	class ShaderModule : private Resource
	{

	public:

		//!	@brief	Create shader module object.
		ShaderModule(VkShaderModule hShaderModule = VK_NULL_HANDLE);

		//!	@brief	Destroy shader module object.
		~ShaderModule() noexcept;

	public:

		//!	@brief	Read file as binary data.
		static std::vector<char> ReadBinary(const char * pFileName);

		//!	@brief	Create a new shader module object
		static std::shared_ptr<ShaderModule> Create(const char * pFileName);

		//!	@brief	Create a new shader module object
		static std::shared_ptr<ShaderModule> Create(const std::vector<char> & BinaryCode);

		//!	@brief	If shader handle is valid.
		VkBool32 IsValid() const { return m_hShaderModule != VK_NULL_HANDLE; }

		//!	@brief	Return VkShaderModule handle.
		VkShaderModule GetHandle() const { return m_hShaderModule; }

	private:

		const VkShaderModule		m_hShaderModule;
	};
}