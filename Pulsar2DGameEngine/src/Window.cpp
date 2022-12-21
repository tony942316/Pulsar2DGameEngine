#include "Window.h"

#include <iostream>

#include <EquinoxSTD.h>

namespace pulsar
{
	void Window::testing()
	{
		eqx::Point<int> p(1, 2);
		std::cout << "Hello There " << p.toString() << std::endl;
	}
}