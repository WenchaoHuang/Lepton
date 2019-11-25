/*************************************************************************
*******************    Lava_AccelerationStructureNV    *******************
*************************************************************************/
#pragma once

#include "DeviceMemory.h"

namespace Lava
{
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
		Format						vertexFormat		= Format::eRGBA32Sfloat;
		VkBuffer					indexData			= VK_NULL_HANDLE;
		VkDeviceSize				indexOffset			= 0;
		uint32_t					indexCount			= 0;
		IndexType					indexType			= IndexType::eUint32;
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
	**************************    GeometryNV    **************************
	*********************************************************************/

	/**
	 *	@brief	Structure specifying a geometry in a bottom-level acceleration structure.
	 */
	struct GeometryNV
	{
		const VkStructureType		sType				= VK_STRUCTURE_TYPE_GEOMETRY_NV;
		const void * const			pNext				= nullptr;
		GeometryTypeNV				geometryType		= GeometryTypeNV::eTriangles;
		GeometryTrianglesNV			triangles;
		GeometryAABBNV				aabbs;
		Flags<GeometryFlagNV>		flags				= 0;
	};

	static_assert(sizeof(GeometryNV) == sizeof(VkGeometryNV), "Struct and wrapper have different size!");

	/*********************************************************************
	********************    TopLevelAccelStructNV    *********************
	*********************************************************************/

	/**
	 *	@brief	Wrapper for Nvidia top-level acceleration structure object.
	 */
	class TopLevelAccelStructNV
	{

	public:

		//!	@brief	Invalidate this resource handle.
		void Destroy() { m_spUniqueHandle.reset(); }

		//!	@brief	Whether this resource handle is valid.
		bool IsValid() const { return m_spUniqueHandle != nullptr; }

		//!	@brief	Create a new top-level acceleration structure.
		Result Create(const LogicalDevice * pLogicalDevice, uint32_t instanceCount);

		//!	@brief	Return memory allocation size.
		VkDeviceSize MemSize() const { return (m_spUniqueHandle != nullptr) ? m_spUniqueHandle->m_DeviceMemory.Size() : 0; }

		//!	@brief	Convert to VkAccelerationStructureNV.
		operator VkAccelerationStructureNV() const { return (m_spUniqueHandle != nullptr) ? m_spUniqueHandle->m_hAccelStruct : VK_NULL_HANDLE; }

	private:

		/**
		 *	@brief	Unique handle of sampler.
		 */
		struct UniqueHandle
		{

		public:

			//!	@brief	Constructor (handles must be initialized).
			UniqueHandle(DeviceLocalMemory, VkAccelerationStructureNV, uint64_t);

			//!	@brief	Where resource will be released.
			~UniqueHandle() noexcept;

		public:

			const uint64_t						m_Handle;
			const DeviceLocalMemory				m_DeviceMemory;
			const VkAccelerationStructureNV		m_hAccelStruct;
		};

		std::shared_ptr<UniqueHandle>			m_spUniqueHandle;
	};

	/*********************************************************************
	*******************    BottomLevelAccelStructNV    *******************
	*********************************************************************/

	/**
	 *	@brief	Wrapper for Nvidia bottom-level acceleration structure object.
	 */
	class BottomLevelAccelStructNV
	{

	public:

		//!	@brief	Invalidate this resource handle.
		void Destroy() { m_spUniqueHandle.reset(); }

		//!	@brief	Whether this resource handle is valid.
		bool IsValid() const { return m_spUniqueHandle != nullptr; }

		uint64_t GetHandle() const { return (m_spUniqueHandle != nullptr) ? m_spUniqueHandle->m_Handle : 0; }

		//!	@brief	Create a new top-level acceleration structure.
		Result Create(const LogicalDevice * pLogicalDevice, ArrayProxy<const GeometryNV> pGeometries);

		//!	@brief	Return memory allocation size.
		VkDeviceSize MemSize() const { return (m_spUniqueHandle != nullptr) ? m_spUniqueHandle->m_DeviceMemory.Size() : 0; }

		//!	@brief	Convert to VkAccelerationStructureNV.
		operator VkAccelerationStructureNV() const { return (m_spUniqueHandle != nullptr) ? m_spUniqueHandle->m_hAccelStruct : VK_NULL_HANDLE; }

	private:

		/**
		 *	@brief	Unique handle of sampler.
		 */
		struct UniqueHandle
		{

		public:

			//!	@brief	Constructor (handles must be initialized).
			UniqueHandle(DeviceLocalMemory, VkAccelerationStructureNV, uint64_t);

			//!	@brief	Where resource will be released.
			~UniqueHandle() noexcept;

		public:

			const uint64_t						m_Handle;
			const DeviceLocalMemory				m_DeviceMemory;
			const VkAccelerationStructureNV		m_hAccelStruct;
		};

		std::shared_ptr<UniqueHandle>			m_spUniqueHandle;
	};
}