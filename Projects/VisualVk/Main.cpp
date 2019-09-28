
#include "Instance.h"
#include "LogicalDevice.h"
#include "PhysicalDevice.h"
#include "ShaderModule.h"
#include "PipelineLayout.h"
#include "Pipelines.h"

using namespace Vk;

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

	pLogicalDevice->InstallQueue(0);
	pLogicalDevice->StartUp();

	PipelineLayout		pipelineLayout(pLogicalDevice->GetHandle());
	pipelineLayout.Destroy();
}