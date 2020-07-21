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
	int getBoardAddress() { return boardAddr; };

	CAEN_DGTZ_ErrorCode ConfigureDigitizer();
	CAEN_DGTZ_ErrorCode StartDataAcquisition();
	CAEN_DGTZ_ErrorCode StopDataAcquisition();
	CAEN_DGTZ_ErrorCode SendSWTrigger();
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
	int maxNumberOfEventsPerTransfer = 1;

	// Trigger settings
	DigitizerTriggerModes triggerMode;
	int triggerThreshold; // in ADC

	// Readout settings
	int maxNumberEventsTransferred;

	// Misc Settings
	int verbose = 0;
	
};
