#ifndef TOPMETALDRONECONFIG_H
#define TOPMETALDRONECONFIG_H

#include "tinyxml2.h"
#include "colors.h"
#include <string>
#include <iostream>

enum DigitizerTriggerModes
{
	Continuous,
	SelfTrigger,
	SoftwareTrigger,
	ExternalTrigger
};


enum TopMetalReadoutMode
{
	FullReadout,
	SinglePixel
};


// Definition of structures containing data
struct CaenDigitizerSettings
{
	double samplingRate; // MHz
	int nSamplesPerTrigger;
	double postTriggerFraction;
	int maxNumberEventsTransferred;
	int triggerPolarity;
	int triggerThreshold;
	DigitizerTriggerModes triggerMode;
	uint16_t acquisitionDCOffset;
	int numberOfBoards;
};

struct TopMetalFPGASettings
{
	bool stopAddressEnable;
	int stopAddress;
	
};


// Configuration class
class TopMetalDroneConfig
{
public:
	TopMetalDroneConfig(){};
	TopMetalDroneConfig(const std::string &configFilename);
	~TopMetalDroneConfig(){};

	// Config setting functions
	bool ReadConfigFile(const std::string &configFilename);
	void PrintConfigSettings() const;

	// Getters
	int GetReadoutMode() { return readOutMode; };
	CaenDigitizerSettings & GetDigitizerSettings() { return digitizerSettings; };
	std::string GetOutputFilename() { return outputFilename; };
	
	// Setters
	// Most setters are controlled by the config file. CLI gives options for overriding some values
	void SetOutputFilename(std::string ofile) { this->outputFilename = ofile; };

private:

	// General
	TopMetalReadoutMode readOutMode;

	// Digitizer
	CaenDigitizerSettings digitizerSettings;

	// FPGA
	TopMetalFPGASettings  fpgaSettings;

	// Output file
	std::string outputFilename;
	std::string inputFilename;

};



#endif
