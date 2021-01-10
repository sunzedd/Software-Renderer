#include <iostream>
#include "Sandbox/DemoApplication.h"

int main()
{
    try
    {
        DemoApplication a;
        a.run();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
        std::cin.get();
    }

    return 0;
}
