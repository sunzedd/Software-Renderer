#include <iostream>
#include "DemoApp/DemoApp.h"

int main()
{
	try
	{
		Demo::DemoApp a;
		a.run();
	}
	catch ( const std::exception & e )
	{
		std::cout << e.what() << std::endl;
		system("pause");
	}
	
	return 0;
}
