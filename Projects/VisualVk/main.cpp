
#include "Instance.h"
#include "LogicalDevice.h"
#include "PhysicalDevice.h"

int main()
{
	Vk::Instance * pInstance = Vk::Instance::GetCurrent();

	Vk::PhysicalDevice * pPhysicalDevice = pInstance->GetPhysicalDevices()[0];

	Vk::LogicalDevice * pLogicalDevice = pPhysicalDevice->CreateLogicalDevice();
	
	Vk::Instance::Destroy();
}