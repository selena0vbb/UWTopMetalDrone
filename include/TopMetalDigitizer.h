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
	void SetVerboseLevel(int verbose) { this->verbose = verbose; };
	
	// Getters
	int GetVerboseLevel(){ return verbose; };
	int GetBoardAddress() { return boardAddr; };
	int GetNumberOfEventsRead() { return numberEventsRead; };
	char * GetBuffer() { return buffer; };
	char * GetEventPtr() { return evtptr; };
	void * GetEventBuffer() { return eventBuffer; };
	uint16_t GetAcquisitionDCOffset() { return acquisitionDCOffset; };
	uint32_t GetBufferSize() { return bufferSize; };
	uint32_t GetReadoutSize() { return readoutSize; };

	// Utility functions
	
	// CAEN Digitizer wrapper functions
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
	double postTriggerFraction;
	int maxNumberOfEventsPerTransfer = 1;
	uint32_t useExternalClock;

	// Trigger settings
	DigitizerTriggerModes triggerMode;
	CAEN_DGTZ_PulsePolarity_t triggerPolarity;
	int triggerThreshold; // in ADC

	// Readout settings
	int channel;
	int maxNumberEventsTransferred;
	char * buffer = NULL;
	char * evtptr = NULL; // Need to be initialized to null
	void * eventBuffer = NULL;
	uint32_t bufferSize, readoutSize;
    uint32_t numberEventsRead = 0;
	uint16_t acquisitionDCOffset;

	// Relevant Register address
	const uint32_t ClockSourceAddress = 0x8100;

	// Misc Settings
	int verbose = 0;
	
};
