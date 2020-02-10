#include <iostream>
#include "Sandbox/DemoApp_Camera.h"

int main()
{
	try
	{
		DemoApp_Camera a;
		a.run();
	}
	catch ( const std::exception & e )
	{
		std::cout << e.what() << std::endl;
	}
	
	
	return 0;
}