// Standard headers
#include <vector>
#include <iostream>

// xml parsing headers
#include "tinyxml2.h"

// Custom headers
#include "TopMetalDroneConfig.h"
#include "TopMetalDigitizer.h"


int main(int argc, char const *argv[])
{
	/* code */
	std::cout << "Starting UW Top Metal II- Drone Controller\n";

	TopMetalDroneConfig config;
	std::string infile = "topMetalConfig.xml";
	bool configSucces = config.ReadConfigFile(infile);
	if(configSucces) config.PrintConfigSettings();


	// Create and communicate with digitizer
	std::printf("Connect and configure digitizer....\n");
	TopMetalDigitizer digitizer(config.GetDigitizerSettings());
	digitizer.setVerboseLevel(1);
	digitizer.ConfigureDigitizer();
	digitizer.StartDataAcquisition();

	// Test some readout and software trigger
	digitizer.SendSWTrigger();
	char * buffer = NULL;
	char * evtptr = NULL;
	uint32_t size, bsize;
	uint32_t numEvents;

	int err = CAEN_DGTZ_MallocReadoutBuffer(digitizer.getBoardAddress(), &buffer, &size);
	std::cout << err << "\n";
	digitizer.SendSWTrigger();
	CAEN_DGTZ_ReadData(digitizer.getBoardAddress(), CAEN_DGTZ_SLAVE_TERMINATED_READOUT_MBLT, buffer, &bsize);
	CAEN_DGTZ_GetNumEvents(digitizer.getBoardAddress(), buffer, bsize, &numEvents);
	CAEN_DGTZ_FreeReadoutBuffer(&buffer);
	std::cout << "Number of Events: " << numEvents << std::endl;
	return 0;
}
