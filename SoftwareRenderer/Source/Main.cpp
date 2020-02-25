#include <iostream>
#include "Sandbox/DemoApp_Camera.h"
#include "Sandbox/Test2/TestDemo2.h"
#include "DemoApp/DemoApp.h"

int main()
{
	try
	{
		Demo::DemoApp a;
		a.run();

		//auto app = new Demo::TestApp2();
		//app->run();
		//delete app;
	}
	catch ( const std::exception & e )
	{
		std::cout << e.what() << std::endl;
	}
	
	//system("pause");
	return 0;
}