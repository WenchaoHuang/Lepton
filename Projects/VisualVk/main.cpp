
#include "Instance.h"
#include "LogicalDevice.h"
#include "PhysicalDevice.h"
#include "Swapchain.h"
#include "Buffer.h"
#include "Images.h"

int main()
{
	Vk::Instance * pInstance = Vk::Instance::GetCurrent();

	Vk::PhysicalDevice * pPhysicalDevice = pInstance->GetPhysicalDevices()[0];

	Vk::LogicalDevice * pLogicalDevice = pPhysicalDevice->CreateLogicalDevice();

	Vk::Resource::SetupDevice(pPhysicalDevice, pLogicalDevice);

	Vk::Image1D				image1D;
	Vk::Image2D				image2D;
	Vk::Image3D				image3D;
	Vk::ImageCube			imageCube;
	Vk::Image1DArray		image1DArray;
	Vk::Image2DArray		image2DArray;

	image2D.CreateColorAttachment(VK_FORMAT_R8G8B8A8_UNORM, 100, 10, 1);
	image2D.CreateDepthAttachment(VK_FORMAT_R8G8B8A8_UNORM, 100, 10, 1);

	Vk::Instance::Destroy();
}