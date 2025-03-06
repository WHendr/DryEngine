#ifndef DRY_APPLICATION_HPP
#define DRY_APPLICATION_HPP

#include "Engine.h"
#include "GameWindow.h"
namespace Dry
{

class Application
{
public:
	Application(int _WindowHeight, int _WindowWidth);
	void Run();

private:
	Engine m_Engine_;
};

}
#endif // !DRY_APPLICATION_HPP

