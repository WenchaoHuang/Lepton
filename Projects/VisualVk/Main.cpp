

#include "Instance.h"
#include "PhysicalDevice.h"

using namespace Vk;

int main()
{
	Instance			instance;
	LogicalDevice *		pLogicalDevice = nullptr;
	PhysicalDevice *	pPhysicalDevice = nullptr;

	instance.EnableExtension(VK_KHR_SURFACE_EXTENSION_NAME);
	instance.EnableExtension(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);

	if (instance.Validate() == Result::eSuccess)
	{
		pPhysicalDevice = instance.GetPhysicalDevices().front();

		pLogicalDevice = pPhysicalDevice->CreateLogicalDevice();
	}



}