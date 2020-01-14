#include <iostream>
#include "App.h"

using namespace Core;

int main()
{
	try
	{
		Core::App a;
		a.run();
	}
	catch ( const std::exception & e )
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}