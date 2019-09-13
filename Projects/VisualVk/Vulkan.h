/*************************************************************************
*****************************    VisualVk    *****************************
*************************************************************************/
#pragma once

#include "Enums.h"
#include "Flags.h"
#include "Result.h"
#include "ArrayProxy.h"

#define VK_INVALID_INDEX			UINT32_MAX

/*************************************************************************
***************************    Noncopyable    ****************************
*************************************************************************/

#define VK_NONCOPYABLE(ClassName)										\
																		\
ClassName(const ClassName&) = delete;									\
																		\
void operator=(const ClassName&) = delete;								\

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
}