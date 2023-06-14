#include <iostream>
#include "Client.h"
#include "Driver.h"
#include "UberSystem.h"

int main()
{
	try {
		UberSystem system;
		system.run();
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}


	return 0;
}

