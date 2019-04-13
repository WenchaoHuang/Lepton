
#include "Instance.h"
#include "LogicalDevice.h"
#include "PhysicalDevice.h"
#include "DeviceMemory.h"
#include "Buffer.h"

#include <vector>

int main()
{
	Vk::Instance * pInstance = Vk::Instance::GetCurrent();

	Vk::PhysicalDevice * pPhysicalDevice = pInstance->GetPhysicalDevices()[0];

	Vk::LogicalDevice * pLogicalDevice = pPhysicalDevice->CreateLogicalDevice();

	Vk::Resource::SetupDevice(pPhysicalDevice, pLogicalDevice);

	Vk::Buffer			Buffer;

	std::vector<int>	A(100, 5);
	Buffer.Create(sizeof(int) * A.size());
	Buffer.Write(A.data(), 0, sizeof(int) * A.size());
	Buffer.Write(A.data(), 0, sizeof(int) * A.size());
	Buffer.Write(A.data(), 0, sizeof(int) * A.size());
	Buffer.Write(A.data(), 0, sizeof(int) * A.size());

	Vk::Instance::Destroy();

	return 0;
}