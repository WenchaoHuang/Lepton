/*************************************************************************
************************    VisualVk_Textures    *************************
*************************************************************************/
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include <stb/stb_image_write.h>
#include <stb/stb_image.h>
#include "Textures.h"

using namespace Vk;

/*************************************************************************
***************************    BaseTexture    ****************************
*************************************************************************/
bool BaseTexture::IsHDR(const char * pFileName)
{
	return stbi_is_hdr(pFileName) != 0;
}


