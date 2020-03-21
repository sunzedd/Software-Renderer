#include <iostream>
#include "EditorDemoApp/EditorDemoApp.h"

int main()
{
	try
	{
		Demo::EditorDemoApp a;
		a.run();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		system("pause");
	}
	
	return 0;
}
