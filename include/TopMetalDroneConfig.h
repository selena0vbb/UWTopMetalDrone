#ifndef TOPMETALDRONECONFIG_H
#define TOPMETALDRONECONFIG_H

#include "tinyxml2.h"
#include "colors.h"
#include <string>
#include <iostream>

enum DigitizerTriggerModes
{
	Continous,
	HardwareTrigger,
	SoftwareTrigger
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
	int nPreTriggerSamples;
	double triggerThreshold;
	DigitizerTriggerModes triggerMode;
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

	// Setters
	// No need for setters. Settings should only be controlled from config file

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

	// For printing enums
	// const char * TopMetalReadoutModeChar[] = {
	// 	"FullReadout",
	// 	"SinglePixel"
	// };

	// const char * DigitizerTriggerModesChar[] = 
	// {
	// 	"Continous",
	// 	"HardwareTrigger",
	// 	"SoftwareTrigger"
	// };


};



#endif