#include "TopMetalDigitizer.h"
#include "CAENDigitizer.h"

TopMetalDigitizer::TopMetalDigitizer(){
	/*
		Creates a digitizer object with default configuration.
		Should in general not be used if actual operation of a digitizer is intended
		(defaults will often not be good for a specific application)
	*/
	nboards = 1;

}

TopMetalDigitizer::TopMetalDigitizer(CaenDigitizerSettings & digitizerSettings){

	nboards = digitizerSettings.numberOfBoards;
	nSamplesPerTrigger = digitizerSettings.nSamplesPerTrigger;
	nPreTriggerSamples = digitizerSettings.nPreTriggerSamples;

}

TopMetalDigitizer::~TopMetalDigitizer(){

	err = CAEN_DGTZ_CloseDigitizer(boardAddr);
	if (verbose) std::cout << "Closing Digitizer...\t\tStatus: " << err << "\n";
}


CAEN_DGTZ_ErrorCode TopMetalDigitizer::ConfigureDigitizer(){
	/*
		Uses the class settings to connect and configure the physical hardware
	*/

	// Open connection to digitizer
	err = CAEN_DGTZ_OpenDigitizer(CAEN_DGTZ_USB, 0, 0, 0, &boardAddr);

	// Get Board info
	err = CAEN_DGTZ_GetInfo(boardAddr, &boardInformation);

	// Congifure board with settings
	err = CAEN_DGTZ_Reset(boardAddr); 
	err = CAEN_DGTZ_SetRecordLength(boardAddr, nSamplesPerTrigger);
	err = CAEN_DGTZ_SetChannelEnableMask(boardAddr, 1);
	err = CAEN_DGTZ_SetMaxNumEventsBLT(boardAddr, maxNumberOfEventsPerTransfer);

	if (verbose) std::cout<< "Opening and configuring digitizer....\t\tStatus: " << err << "\n";
	return err;
}
