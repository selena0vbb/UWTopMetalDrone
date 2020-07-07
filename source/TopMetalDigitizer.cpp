#include "TopMetalDigitizer.h"
#include "CAENDigitizer.h"

TopMetalDigitizer::TopMetalDigitizer(){
	/*
		Creates a digitizer object with default configuration.
		Should in general not be used if actual operation of a digitizer is intended
		(defaults will often not be good for a specific application)
	*/
	nboards = 1;
	// boardAddr = new int[nboards];
	// boardSelect = 1;


}

TopMetalDigitizer::TopMetalDigitizer(CaenDigitizerSettings & digitizerSettings){

	nboards = digitizerSettings.numberOfBoards;
	nSamplesPerTrigger = digitizerSettings.nSamplesPerTrigger;
	nPreTriggerSamples = digitizerSettings.nPreTriggerSamples;

	// boardAddr = new int[nboards];
	// boardSelect = 1;


}

TopMetalDigitizer::~TopMetalDigitizer(){

	err = CAEN_DGTZ_CloseDigitizer(*boardAddr);
	std::cout << "Status: " << err << ".\tDigitizer closed." << std::endl;
}


CAEN_DGTZ_ErrorCode TopMetalDigitizer::ConfigureDigitizer(){
	/*
		Uses the class settings to connect and configure the physical hardware
	*/

	err = CAEN_DGTZ_OpenDigitizer(CAEN_DGTZ_USB, 0, 0, 0, boardAddr);
	
	std::cout << err << std::endl;
	return err;
}