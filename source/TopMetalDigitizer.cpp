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
	triggerMode = digitizerSettings.triggerMode;
	maxNumberEventsTransferred = digitizerSettings.maxNumberEventsTransferred;

}

TopMetalDigitizer::~TopMetalDigitizer(){

	err = CAEN_DGTZ_FreeReadoutBuffer(&buffer);
	err = CAEN_DGTZ_CloseDigitizer(boardAddr);
	if (verbose) std::cout << "Closing Digitizer...\t\tStatus: " << err << "\n";
}


CAEN_DGTZ_ErrorCode TopMetalDigitizer::ConfigureDigitizer(){
	/*
		Uses the class settings to connect and configure the physical hardware
	*/

	// Open connection to digitizer
	err = CAEN_DGTZ_OpenDigitizer(CAEN_DGTZ_USB, 0, 0, 0, &boardAddr);
	if (verbose) std::cout << "Opening communication with digitizer...\t\tStatus: " << err << "\n";
	// Get Board info
	err = CAEN_DGTZ_GetInfo(boardAddr, &boardInformation);

	// Congifure board with settings
	err = CAEN_DGTZ_Reset(boardAddr); 
	err = CAEN_DGTZ_SetRecordLength(boardAddr, nSamplesPerTrigger);
	err = CAEN_DGTZ_SetChannelEnableMask(boardAddr, 1);
	err = CAEN_DGTZ_SetMaxNumEventsBLT(boardAddr, maxNumberEventsTransferred);
	err = CAEN_DGTZ_SetAcquisitionMode(boardAddr, CAEN_DGTZ_SW_CONTROLLED);
	if (verbose) std::cout << "Congfigure board settings...\t\tStatus: " << err << "\n";

	// Configure Trigger and acquisition settings depending on the settings file
	switch(triggerMode){
		case Continuous:
			break;
		case SelfTrigger:
			break;
		case SoftwareTrigger:
			err = CAEN_DGTZ_SetChannelSelfTrigger(boardAddr, CAEN_DGTZ_TRGMODE_ACQ_ONLY, 1);
			err = CAEN_DGTZ_SetSWTriggerMode(boardAddr, CAEN_DGTZ_TRGMODE_ACQ_ONLY);
			break;
		case ExternalTrigger:
			break;
	}
	if (verbose) std::cout << "Configure trigger settings...\t\tStatus: " << err << "\n";
	
	// Allocate buffer memory
	err = CAEN_DGTZ_MallocReadoutBuffer(boardAddr, &buffer, &bufferSize);
	if (verbose) std::cout << "Allocate buffer memory...\t\tStatus: " << err << "\n";
	
	return err;
}

CAEN_DGTZ_ErrorCode TopMetalDigitizer::TransferData(){

	// Readout data
	err = CAEN_DGTZ_ReadData(boardAddr, CAEN_DGTZ_SLAVE_TERMINATED_READOUT_MBLT, buffer, &readoutSize);
	err = CAEN_DGTZ_GetNumEvents(boardAddr, buffer, readoutSize, &numberEventsRead);

	return err;
}

CAEN_DGTZ_ErrorCode TopMetalDigitizer::StartDataAcquisition(){
	err = CAEN_DGTZ_SWStartAcquisition(boardAddr);
	if (verbose) std::cout << "Start data acquisition...\t\tStatus: " << err << "\n";
	return err;
}

CAEN_DGTZ_ErrorCode TopMetalDigitizer::StopDataAcquisition(){
	err = CAEN_DGTZ_SWStopAcquisition(boardAddr);
	if (verbose) std::cout << "Stop data acquisition...\t\tStatus: " << err << "\n";
	return err;
}

CAEN_DGTZ_ErrorCode TopMetalDigitizer::SendSWTrigger(){
	err = CAEN_DGTZ_SendSWtrigger(boardAddr);
	return err;
}
