/*************************************************************************
**********************    VisualVk_ShaderModule    ***********************
*************************************************************************/
#include "ShaderModule.h"
#include <fstream>

using namespace Vk;

/*************************************************************************
***************************    ShaderModule    ***************************
*************************************************************************/
VkResult ShaderModule::Create(const std::vector<char> & BinaryCode)
{
	VkShaderModuleCreateInfo		CreateInfo = {};
	CreateInfo.sType				= VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	CreateInfo.pNext				= nullptr;
	CreateInfo.flags				= 0;
	CreateInfo.codeSize				= BinaryCode.size();
	CreateInfo.pCode				= reinterpret_cast<const uint32_t*>(BinaryCode.data());

	VkShaderModule hShaderModule = VK_NULL_HANDLE;

	VkResult eResult = Resource::GetDevice()->CreateShaderModule(&CreateInfo, &hShaderModule);

	if (eResult == VK_SUCCESS)
	{
		ShaderModuleH::Replace(hShaderModule, *Resource::GetDevice());
	}

	return eResult;
}


VkResult ShaderModule::Create(const char * Path)
{
	return ShaderModule::Create(ShaderModule::ReadBinary(Path));
}


std::vector<char> ShaderModule::ReadBinary(const char * Path)
{
	std::ifstream Stream(Path, std::ios::ate | std::ios::binary);

	std::vector<char> BinaryCode;

	if (Stream.is_open() && Stream.good())
	{
		BinaryCode.resize(static_cast<size_t>(Stream.tellg()));

		Stream.seekg(0);

		Stream.read(BinaryCode.data(), BinaryCode.size());

		Stream.close();
	}

	return BinaryCode;
}