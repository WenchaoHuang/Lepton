
#include "Instance.h"
#include "LogicalDevice.h"
#include "PhysicalDevice.h"
#include "ShaderModule.h"
#include "PipelineLayout.h"
#include "GraphicsPipeline.h"

using namespace Vk;

// VK_DEFINE_HANDLE(VkQueue)
// VK_DEFINE_HANDLE(VkDevice)
// VK_DEFINE_HANDLE(VkInstance)
// VK_DEFINE_HANDLE(VkPhysicalDevice)

// VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkEvent)
// VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkFence)
// VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkSemaphore)

// VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkImage)
// VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkSampler)
// VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkPipeline)
// VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkImageView)
// VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkRenderPass)
// VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkFramebuffer)
// VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkShaderModule)
// VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkPipelineLayout)
// VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkDescriptorSetLayout)

// VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkQueryPool)
// VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCommandPool)
// VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkDescriptorPool)

// VK_DEFINE_HANDLE(VkCommandBuffer)
// VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkDescriptorSet)

// VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkBuffer)
// VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkBufferView)
// VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkDeviceMemory)

int main()
{
	std::vector<const char*>	pLayers;
	std::vector<const char*>	pExtensions;
	pExtensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
	pExtensions.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
	pExtensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
	pLayers.push_back("VK_LAYER_LUNARG_standard_validation");

	Instance	instance;
	instance.Create(pExtensions, pLayers);

	PhysicalDevice * pPhysicalDevice = instance.GetPhysicalDevices()[0];
	LogicalDevice * pLogicalDevice = pPhysicalDevice->CreateLogicalDevice();

	pLogicalDevice->PreInstallQueue(0);
	pLogicalDevice->StartUp();

//	PipelineLayout		pipelineLayout(pLogicalDevice->GetHandle());
//	pipelineLayout.Destroy();

	ShaderModule		xxx;
	xxx.Create(pLogicalDevice->GetHandle(), nullptr);
}