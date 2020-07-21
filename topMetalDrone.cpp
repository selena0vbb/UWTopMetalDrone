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
	for(int i=0; i < 20; i++){
	
	digitizer.SendSWTrigger();
//	leep(30);
	}
	// digitizer.SendSWTrigger();
	// digitizer.SendSWTrigger();
	digitizer.TransferData();

	// Get event info
	CAEN_DGTZ_EventInfo_t eventInfo;
	for(int i=0; i<digitizer.getNumberOfEventsRead(); i++){
		char * evtptr = digitizer.getEventPtr();
		CAEN_DGTZ_UINT16_EVENT_t * eventBuffer = digitizer.getEventBuffer();
		void * voidEventBuffer = NULL;
		CAEN_DGTZ_GetEventInfo(digitizer.getBoardAddress(), digitizer.getBuffer(), digitizer.getReadoutSize(), i, &eventInfo, &evtptr);
		std::cout << "EventCounter: " << eventInfo.EventCounter << "\t  ";
		CAEN_DGTZ_DecodeEvent(digitizer.getBoardAddress(), evtptr, &voidEventBuffer);
		CAEN_DGTZ_UINT16_EVENT_t * test = static_cast<	CAEN_DGTZ_UINT16_EVENT_t * >(voidEventBuffer);
		double mean = 0;
		for(int j=0; j < test->ChSize[0]; j++){
			mean += test->DataChannel[0][j];
		}
		mean /= test->ChSize[0];
		std::cout << "Mean ADU: " << mean;	
		std::cout << "\n";
	        CAEN_DGTZ_FreeEvent(digitizer.getBoardAddress(), &voidEventBuffer);
	}
	
	std::cout << "Number of Events: " << digitizer.getNumberOfEventsRead() << std::endl;
	return 0;
}
