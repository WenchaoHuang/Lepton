/*************************************************************************
*******************    Lava_AccelerationStructureNV    *******************
*************************************************************************/
#pragma once

#include "Vulkan.h"

namespace Lava
{
	/*********************************************************************
	*****************    AccelerationStructureTypeNV    ******************
	*********************************************************************/

	/**
	 *	@brief	Structure specifying the parameters of acceleration structure object.
	 */
	enum class AccelerationStructureTypeNV
	{
		eTopLevel = VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_NV,
		eBottomLevel = VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_NV,
	};

	/*********************************************************************
	***************    BuildAccelerationStructureFlagNV    ***************
	*********************************************************************/

	/**
	 *	@brief	Bitmask specifying additional parameters for acceleration structure builds.
	 */
	enum class BuildAccelerationStructureFlagNV : VkFlags
	{
		eLowMemory				= VK_BUILD_ACCELERATION_STRUCTURE_LOW_MEMORY_BIT_NV,
		eAllowUpdate			= VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_NV,
		eAllowCompaction		= VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_NV,
		ePreferFastTrace		= VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_NV,
		ePreferFastBuild		= VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_BUILD_BIT_NV,
	};

	/*********************************************************************
	************************    GeometryTypeNV    ************************
	*********************************************************************/

	/**
	 *	@brief	Enum specifying which type of geometry is provided.
	 */
	enum class GeometryTypeNV
	{
		eAABBs			= VK_GEOMETRY_TYPE_AABBS_NV,
		eTriangles		= VK_GEOMETRY_TYPE_TRIANGLES_NV,
	};

	/*********************************************************************
	************************    GeometryFlagNV    ************************
	*********************************************************************/

	/**
	 *	@brief	Bitmask specifying additional parameters for a geometry.
	 */
	enum class GeometryFlagNV : VkFlags
	{
		eOpaque								= VK_GEOMETRY_OPAQUE_BIT_NV,
		eNoDuplicateAnyHitInvocation		= VK_GEOMETRY_NO_DUPLICATE_ANY_HIT_INVOCATION_BIT_NV,
	};

	/*********************************************************************
	*********************    GeometryTrianglesNV    **********************
	*********************************************************************/

	/**
	 *	@brief	Structure specifying a triangle geometry in a bottom-level acceleration structure.
	 */
	struct GeometryTrianglesNV
	{
		const VkStructureType		sType				= VK_STRUCTURE_TYPE_GEOMETRY_TRIANGLES_NV;
		const void * const			pNext				= nullptr;
		VkBuffer					vertexData			= VK_NULL_HANDLE;
		VkDeviceSize				vertexOffset		= 0;
		uint32_t					vertexCount			= 0;
		VkDeviceSize				vertexStride		= 0;
		Format						vertexFormat		= Format::eUndefined;
		VkBuffer					indexData			= VK_NULL_HANDLE;
		VkDeviceSize				indexOffset			= 0;
		uint32_t					indexCount			= 0;
		IndexType					indexType			= IndexType::eNoneNV;
		VkBuffer					transformData		= VK_NULL_HANDLE;
		VkDeviceSize				transformOffset		= 0;
	};

	/*********************************************************************
	************************    GeometryAABBNV    ************************
	*********************************************************************/

	/**
	 *	@brief	Structure specifying axis-aligned bounding box geometry in a bottom-level acceleration structure.
	 */
	struct GeometryAABBNV
	{
		const VkStructureType		sType			= VK_STRUCTURE_TYPE_GEOMETRY_AABB_NV;
		const void * const			pNext			= nullptr;
		VkBuffer					aabbData		= VK_NULL_HANDLE;
		uint32_t					numAABBs		= 0;
		uint32_t					stride			= 0;
		VkDeviceSize				offset			= 0;
	};

	/*********************************************************************
	************************    GeometryDataNV    ************************
	*********************************************************************/

	/**
	 *	@brief	Structure specifying geometry in a bottom-level acceleration structure.
	 */
	struct GeometryDataNV
	{
		GeometryTrianglesNV		triangles;
		GeometryAABBNV			aabbs;
	};

	/*********************************************************************
	*******************    AccelerationStructureNV    ********************
	*********************************************************************/

	/**
	 *	@brief	Vulkan acceleration structure object.
	 */
	class AccelerationStructureNV
	{

	public:

		void Destory() { m_spUniqueHandle.reset(); }

		Result Create(VkDevice hDevice, AccelerationStructureTypeNV eType, Flags<BuildAccelerationStructureFlagNV> eBuildFlags,
					  VkDeviceSize compactedSize, uint32_t instanceCount, ArrayProxy<const GeometryDataNV> pGeometries);

	private:

		/**
		 *	@brief	Unique handle of sampler.
		 */
		struct UniqueHandle
		{
			LAVA_NONCOPYABLE(UniqueHandle)

		public:

			

		public:


		};

		std::shared_ptr<UniqueHandle>		m_spUniqueHandle;
	};
}