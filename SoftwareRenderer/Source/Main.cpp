#include <iostream>
#include "Sandbox/DemoApp.h"
#include "Sandbox/DemoApp_Scene.h"


int main()
{
	
	try
	{
		DemoApp_Scene a;
		a.run();
	}
	catch ( const std::exception & e )
	{
		std::cout << e.what() << std::endl;
	}
	
	//system("pause");
	return 0;
}