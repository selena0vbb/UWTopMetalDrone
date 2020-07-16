#include <iostream>
#include "TopMetalDroneConfig.h"
#include "CAENDigitizer.h"


class TopMetalDigitizer
{
public:
	TopMetalDigitizer();
	TopMetalDigitizer(CaenDigitizerSettings & digitizerSettings);
	~TopMetalDigitizer();

	// Setters
	void setVerboseLevel(int verbose) { this->verbose = verbose; };
	
	// Getters
	int getVerboseLevel(){ return verbose; };


	CAEN_DGTZ_ErrorCode ConfigureDigitizer();

private:

	// CAEN data types
	CAEN_DGTZ_ErrorCode err;
	CAEN_DGTZ_BoardInfo_t boardInformation;
	CAEN_DGTZ_EventInfo_t eventInformation;

	int nboards;
	int boardSelect;
	int boardAddr;

	// Sample settings
	int nSamplesPerTrigger;
	int nPreTriggerSamples;

	// Misc Settings
	int verbose = 0;
	
};
