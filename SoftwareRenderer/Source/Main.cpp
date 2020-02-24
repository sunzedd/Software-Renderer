#include <iostream>
#include "Sandbox/DemoApp_Camera.h"
#include "Sandbox/Test1/TestDemo1.h"

int main()
{
	try
	{
		auto app = Demo::TestApp1::Create();
		app->run();
	}
	catch ( const std::exception & e )
	{
		std::cout << e.what() << std::endl;
	}
	
	//system("pause");
	return 0;
}