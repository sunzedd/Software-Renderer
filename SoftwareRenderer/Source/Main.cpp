#include <iostream>
#include "Sandbox/DemoApp.h"


int main()
{
	
	try
	{
		DemoApp a;
		a.run();
	}
	catch ( const std::exception & e )
	{
		std::cout << e.what() << std::endl;
	}
	
	//system("pause");
	return 0;
}