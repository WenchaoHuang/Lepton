/*************************************************************************
************************    VisualVk_Textures    *************************
*************************************************************************/
#pragma once

#include "Images.h"
#include "Sampler.h"

namespace Vk
{
	/*********************************************************************
	*************************    BaseTexture    **************************
	*********************************************************************/

	/**
	 *	@brief	Template for Vulkan texture objects.
	 */
	class BaseTexture
	{

	public:



	protected:

		bool IsHDR(const char * pFileName);

	};

	/*********************************************************************
	**************************    Texture1D    ***************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan texture 1D object.
	 */
	class Texture1D : public BaseTexture, public Image1D
	{

	public:



	private:

		using Image1D::Create;
	};

	/*********************************************************************
	************************    Texture1DArray    ************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan texture 1D array object.
	 */
	class Texture1DArray : public BaseTexture, public Image1DArray
	{

	public:



	private:

		using Image1DArray::Create;
	};

	/*********************************************************************
	**************************    Texture2D    ***************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan texture 2D object.
	 */
	class Texture2D : public BaseTexture, public Image2D
	{

	public:




	private:

		using Image2D::Create;
	}; 

	/*********************************************************************
	************************    Texture2DArray    ************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan texture 2D array object.
	 */
	class Texture2DArray : public BaseTexture, public Image2DArray
	{

	public:



	private:

		using Image2DArray::Create;
	};

	/*********************************************************************
	*************************    TextureCube    **************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan texture cube object.
	 */
	class TextureCube : public BaseTexture, public ImageCube
	{

	public:



	private:

		using ImageCube::Create;
	};

	/*********************************************************************
	***********************    TextureCubeArray    ***********************
	*********************************************************************/

	/**
	 *	@brief	Vulkan texture cube array object.
	 */
	class TextureCubeArray : public BaseTexture, public ImageCubeArray
	{

	public:


	private:

		using ImageCubeArray::Create;
	};

	/*********************************************************************
	**************************    Texture3D    ***************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan texture 3D object.
	 */
	class Texture3D : public BaseTexture, public Image3D
	{

	public:



	private:

		using Image3D::Create;
	};
}