// Standard headers
#include <vector>
#include <iostream>

// xml parsing headers
#include "tinyxml2.h"

// Command line interface header
#include "CLI11.hpp"

// Custom headers
#include "TopMetalDroneConfig.h"
#include "TopMetalDigitizer.h"


int main(int argc, char const *argv[])
{
	
	CLI::App topMetalDroneParser{"UW Top Metal II- Drone Controller"};

	// command line input variables
	std::string infile = "topMetalConfig.xml";

	// define command line arguments
	topMetalDroneParser.add_option("-c, --config", infile, "Top Metal Drone Config file (xml)")->check(CLI::ExistingFile);

	// parse command line arguments
	try{
		topMetalDroneParser.parse(argc, argv);
	}
	catch (const CLI::ParseError &e) {
		return topMetalDroneParser.exit(e);
	}

	// start controller
	std::cout << "Starting UW Top Metal II- Drone Controller\n";
	TopMetalDroneConfig config;
	bool configSucces = config.ReadConfigFile(infile);
	if(configSucces) config.PrintConfigSettings();


	// Create and communicate with digitizer
	std::printf("Connect and configure digitizer....\n");
	TopMetalDigitizer digitizer(config.GetDigitizerSettings());
	digitizer.SetVerboseLevel(1);
	digitizer.ConfigureDigitizer();
	digitizer.StartDataAcquisition();

	// Test some readout and software trigger
	for(int i=0; i < 20; i++){
	
	digitizer.SendSWTrigger();
//	leep(30);
	}
	// digitizer.SendSWTrigger();
	// digitizer.SendSWTrigger();
	digitizer.TransferData();

	// Get event info
	CAEN_DGTZ_EventInfo_t eventInfo;
	for(int i=0; i<digitizer.GetNumberOfEventsRead(); i++){
		char * evtptr = digitizer.GetEventPtr();
		void * eventBuffer = digitizer.GetEventBuffer();
		
		CAEN_DGTZ_GetEventInfo(digitizer.GetBoardAddress(), digitizer.GetBuffer(), digitizer.GetReadoutSize(), i, &eventInfo, &evtptr);
		std::cout << "EventCounter: " << eventInfo.EventCounter << "\t  ";
		CAEN_DGTZ_DecodeEvent(digitizer.GetBoardAddress(), evtptr, &eventBuffer);
		CAEN_DGTZ_UINT16_EVENT_t * test = static_cast<	CAEN_DGTZ_UINT16_EVENT_t * >(eventBuffer);
		double mean = 0;
		for(int j=0; j < test->ChSize[0]; j++){
			mean += test->DataChannel[0][j];
		}
		mean /= test->ChSize[0];
		std::cout << "Mean ADU: " << mean;	
		std::cout << "\n";
	        CAEN_DGTZ_FreeEvent(digitizer.GetBoardAddress(), &eventBuffer);
	}
	
	std::cout << "Number of Events: " << digitizer.GetNumberOfEventsRead() << std::endl;
	return 0;
}
