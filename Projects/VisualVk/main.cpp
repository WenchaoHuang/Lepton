

#include "Instance.h"

using namespace Vk;

int main()
{
  
	Instance * pInstance = Instance::GetCurrent();

	pInstance->GetExtensionProperties();
	
	Instance::Destroy();

    return 0;
}
