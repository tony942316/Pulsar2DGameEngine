#include <iostream>

#include "Window.h"

int main()
{
	std::cout << "Start" << std::endl;

	eqx::Log::setLevel(eqx::Log::Level::info);

	pulsar::Window win("Window", 1600, 1000);
	win.display();

	std::cout << "End" << std::endl;
}