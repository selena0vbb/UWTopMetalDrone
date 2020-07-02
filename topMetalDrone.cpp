// Standard headers
#include <vector>
#include <iostream>

// xml parsing headers
#include "tinyxml2.h"

// Custom headers
#include "topMetalDroneConfig.h"


int main(int argc, char const *argv[])
{
	/* code */
	std::printf("Hello world, this is the introduction to the Top-metal Drone code\n");

	TopMetalDroneConfig config;
	std::string infile = "topMetalConfig.xml";
	bool configSucces = config.ReadConfigFile(infile);
	if(configSucces) config.PrintConfigSettings();

	return 0;
}
