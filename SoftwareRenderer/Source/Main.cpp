#include <iostream>
#include "Sandbox/DemoApp.h"
#include "Sandbox/DemoApp_Entities.h"


int main()
{
	
	try
	{
		DemoApp_Entities a;
		a.run();
	}
	catch ( const std::exception & e )
	{
		std::cout << e.what() << std::endl;
	}
	
	//system("pause");
	return 0;
}