#include "Application.h"
#include "Dry_Vulkan.h"

namespace Dry
{
	Application::Application(int _WindowHeight, int _WindowWidth)
		:m_Engine_(_WindowHeight, _WindowWidth)
	{
	}

	void Application::Run()
	{
		m_Engine_.run();
	}

}