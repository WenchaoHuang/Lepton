/*************************************************************************
*****************************    VisualVk    *****************************
*************************************************************************/
#pragma once

#include "Enums.h"
#include "Flags.h"
#include "Result.h"
#include "ArrayProxy.h"

#define VK_INVALID_INDEX				UINT32_MAX
#define VK_DEFAULT_TIMEOUT				100000000000L	//!	100s.
#define VK_RESULT_CAST(eResult)			static_cast<Result>(eResult)

/*************************************************************************
***************************    Noncopyable    ****************************
*************************************************************************/

#define VK_NONCOPYABLE(ClassName)										\
																		\
	ClassName(const ClassName&) = delete;								\
	ClassName & operator=(const ClassName&) = delete;					\

/*************************************************************************
*************************    Unique_Resource    **************************
*************************************************************************/

#define VK_UNIQUE_RESOURCE(ResName)										\
																		\
public:																	\
																		\
	ResName(const ResName&) = delete;									\
	ResName & operator=(const ResName&) = delete;						\
	operator Vk##ResName() const { return m_h##ResName; }				\
	Vk##ResName GetHandle() const { return m_h##ResName; }				\
	Vk##Device GetDeviceHandle() const { return m_hDevice; }			\
	bool IsValid() const { return m_h##ResName != VK_NULL_HANDLE; }		\
																		\
private:																\
																		\
	Vk##Device		m_hDevice;											\
	Vk##ResName		m_h##ResName;										\

/*************************************************************************
*****************************    VisualVk    *****************************
*************************************************************************/
namespace Vk
{
	class Instance;
	class LogicalDevice;
	class PhysicalDevice;

	class CommandPool;
	class CommandQueue;
	class CommandBuffer;

	class Event;
	class Fence;
	class Sampler;
	class Semaphore;
	class Swapchain;
	class RenderPass;
	class Framebuffer;
	class ShaderModule;
	class Win32Surface;

	/*********************************************************************
	***************************    Offset2D    ***************************
	*********************************************************************/

	/**
	 *	@brief	Structure specifying a two-dimensional offset.
	 */
	struct Offset2D
	{
		int32_t		x;
		int32_t		y;

		constexpr Offset2D() : x(0), y(0) {}
		constexpr Offset2D(int32_t v0) : x(v0), y(v0) {}
		constexpr Offset2D(int32_t v1, int32_t v2) : x(v1), y(v2) {}

		constexpr bool operator==(const Offset2D & rhs) const { return (x == rhs.x) && (y == rhs.y); }
		constexpr bool operator!=(const Offset2D & rhs) const { return (x != rhs.x) || (y != rhs.y); }

		constexpr operator VkOffset2D() const { return { x, y }; }
	};

	static_assert(sizeof(Offset2D) == sizeof(VkOffset2D), "Struct and wrapper have different size!");

	/*********************************************************************
	***************************    Extent2D    ***************************
	*********************************************************************/

	/**
	 *	@brief	Structure specifying a two-dimensional extent.
	 */
	struct Extent2D
	{
		uint32_t	width;
		uint32_t	height;

		constexpr Extent2D() : width(0), height(0) {}
		constexpr Extent2D(uint32_t v0) : width(v0), height(v0) {}
		constexpr Extent2D(uint32_t w, uint32_t h) : width(w), height(h) {}

		constexpr bool operator==(const Extent2D & rhs) const { return (width == rhs.width) && (height == rhs.height); }
		constexpr bool operator!=(const Extent2D & rhs) const { return (width != rhs.width) || (height != rhs.height); }

		constexpr operator VkExtent2D() const { return { width, height }; }
	};

	static_assert(sizeof(Extent2D) == sizeof(VkExtent2D), "Struct and wrapper have different size!");

	/*********************************************************************
	***************************    Extent3D    ***************************
	*********************************************************************/

	/**
	 *	@brief	Structure specifying a three-dimensional extent.
	 */
	struct Extent3D
	{
		uint32_t	width;
		uint32_t	height;
		uint32_t	depth;

		constexpr Extent3D() : width(0), height(0), depth(0) {}
		constexpr Extent3D(uint32_t v0) : width(v0), height(v0), depth(0) {}
		constexpr Extent3D(uint32_t w, uint32_t h, uint32_t d) : width(w), height(h), depth(d) {}

		constexpr bool operator==(const Extent3D & rhs) const { return (width == rhs.width) && (height == rhs.height) && (depth == rhs.depth); }
		constexpr bool operator!=(const Extent3D & rhs) const { return (width != rhs.width) || (height != rhs.height) || (depth != rhs.depth); }

		constexpr operator VkExtent3D() const { return { width, height, depth }; }
	};

	static_assert(sizeof(Extent3D) == sizeof(VkExtent3D), "Struct and wrapper have different size!");

	/*********************************************************************
	****************************    Rect2D    ****************************
	*********************************************************************/

	/**
	 *	@brief	Structure specifying a two-dimensional subregion.
	 */
	struct Rect2D
	{
		Offset2D	offset;
		Extent2D	extent;

		constexpr Rect2D() {}
		constexpr Rect2D(Offset2D _offset, Extent2D _extent) : offset(_offset), extent(_extent) {}

		constexpr bool operator==(const Rect2D & rhs) const { return (offset == rhs.offset) && (extent == rhs.extent); }
		constexpr bool operator!=(const Rect2D & rhs) const { return (offset != rhs.offset) || (extent != rhs.extent); }

		constexpr operator VkRect2D() const { return { offset, extent }; }
	};

	static_assert(sizeof(Rect2D) == sizeof(VkRect2D), "Struct and wrapper have different size!");
}