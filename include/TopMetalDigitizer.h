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
	int getNumberOfEventsRead() { return numberEventsRead; };
	char * getBuffer() { return buffer; };
	char * getEventPtr() { return evtptr; };
	CAEN_DGTZ_UINT16_EVENT_t * getEventBuffer() { return eventBuffer; };
	uint32_t getBufferSize() { return bufferSize; };
	uint32_t getReadoutSize() { return readoutSize; };
	CAEN_DGTZ_ErrorCode ConfigureDigitizer();
	CAEN_DGTZ_ErrorCode StartDataAcquisition();
	CAEN_DGTZ_ErrorCode StopDataAcquisition();
	CAEN_DGTZ_ErrorCode SendSWTrigger();
	CAEN_DGTZ_ErrorCode TransferData();
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
	char * buffer = NULL;
	char * evtptr = NULL; // Need to be initialized to null
	CAEN_DGTZ_UINT16_EVENT_t * eventBuffer = NULL;
	uint32_t bufferSize, readoutSize;
        uint32_t numberEventsRead = 0;

	// Misc Settings
	int verbose = 0;
	
};
