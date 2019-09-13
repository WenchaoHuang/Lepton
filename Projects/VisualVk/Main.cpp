

#include "Instance.h"

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

	auto & a = instance.GetPhysicalDevices();
}