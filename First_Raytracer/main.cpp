
#include <iostream>

#include "Configuration/Configuration.h"

bool main(int argc, char *argv)
{
	if (argc < 2)
	{
		std::cout << "Missing filename: [filename \"file.txt\"]";
		return false;
	}

	Controll::Configuration configuration = Controll::Configuration(argc, argv);
	bool result = configuration.init();
	if (!result) {
		std::cout << "Summin' bad happened.";
		return false;
	}

	return true;
}