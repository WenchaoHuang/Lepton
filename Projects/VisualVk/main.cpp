
#include "Instance.h"
#include "LogicalDevice.h"
#include "PhysicalDevice.h"
#include "DeviceMemory.h"
#include "Buffer.h"

int main()
{
	Vk::Instance * pInstance = Vk::Instance::GetCurrent();

	Vk::PhysicalDevice * pPhysicalDevice = pInstance->GetPhysicalDevices()[0];

	Vk::LogicalDevice * pLogicalDevice = pPhysicalDevice->CreateLogicalDevice();

	Vk::DeviceMemory	Memory;

	Vk::Buffer			Buffer;

	Vk::Instance::Destroy();
}