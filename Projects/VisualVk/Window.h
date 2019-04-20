/*************************************************************************
*************************    VisualVk_Window    **************************
*************************************************************************/
#pragma once

#include "Images.h"
#include "Swapchain.h"
#include "Framebuffer.h"

namespace Vk
{

	class Window : private Resource
	{

	public:




	private:

		Swapchain						m_Swapchain;

		Image2D							m_DepthBuffer;

		std::shared_ptr<RenderPass>		m_spRenderPass;

		std::vector<Framebuffer*>		m_pFramebuffers;
	};
}