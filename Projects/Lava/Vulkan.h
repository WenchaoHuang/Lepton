/*************************************************************************
*******************************    Lava    *******************************
*************************************************************************/
#pragma once

#include <memory>
#include "Enums.h"
#include "Flags.h"
#include "Result.h"
#include "ArrayProxy.h"

#define LAVA_INVALID_INDEX				UINT32_MAX
#define LAVA_DEFAULT_TIMEOUT			100000000000L	//!	100s.
#define LAVA_RESULT_CAST(eResult)		static_cast<Result>(eResult)

/*************************************************************************
***************************    Noncopyable    ****************************
*************************************************************************/

#define LAVA_NONCOPYABLE(ClassName)										\
																		\
	ClassName(const ClassName&) = delete;								\
	ClassName & operator=(const ClassName&) = delete;					\

/*************************************************************************
*************************    Unique_Resource    **************************
*************************************************************************/

#define LAVA_UNIQUE_RESOURCE(ResName)									\
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
*******************************    Lava    *******************************
*************************************************************************/
namespace Lava
{
	class Instance;
	class LogicalDevice;
	class PhysicalDevice;

	class CommandPool;
	class CommandQueue;
	class CommandBuffer;

	class Image1D;
	class Image2D;
	class Image3D;
	class ImageCube;
	class Image1DArray;
	class Image2DArray;
	class ImageCubeArray;

	class Event;
	class Fence;
	class Sampler;
	class Semaphore;
	class Swapchain;
	class RenderPass;
	class Framebuffer;
	class ShaderModule;
	class Win32Surface;
	class DeviceMemory;
	class DescriptorSet;
	class PipelineLayout;
	class ComputePipeline;
	class GraphicsPipeline;
	class HostVisibleBuffer;
	class DeviceLocalBuffer;
	class RayTracingPipelineNV;
}