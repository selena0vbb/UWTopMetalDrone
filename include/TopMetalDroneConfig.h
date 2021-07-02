#ifndef TOPMETALDRONECONFIG_H
#define TOPMETALDRONECONFIG_H

#include "tinyxml2.h"
#include "colors.h"
#include <string>
#include <iostream>
#include <vector>

enum DigitizerTriggerModes
{
	Continuous,
	SelfTrigger,
	SoftwareTrigger,
	ExternalTrigger
};


enum TopMetalReadoutMode
{
	SinglePixel,
	FullReadoutWaveform,
	FullReadoutAverage
};


// Definition of structures containing data

struct CaenDigitizerChannelSettings
{
	int channelNumber;
	uint16_t channelDCOffset;
	int pulsePolarity;
	bool isChannelTrigger;

	CaenDigitizerChannelSettings(int number, int offset, int polarity, bool isTrigger) :
		channelNumber(number),
		channelDCOffset(offset),
		pulsePolarity(polarity),
		isChannelTrigger(isTrigger) {}
	CaenDigitizerChannelSettings(){}

};

struct CaenDigitizerSettings
{
	int nchannels = 0;
	int nSamplesPerTrigger;
	double postTriggerFraction;
	int maxNumberEventsTransferred;
	int triggerPolarity;
	int triggerThreshold;
	DigitizerTriggerModes triggerMode;
	uint16_t acquisitionDCOffset;
	int numberOfBoards;
	int useExternalClock;

	std::vector<CaenDigitizerChannelSettings> channelSettings;
};



struct TopMetalFPGASettings
{
	bool stopAddressEnable;
	int stopAddress;
	bool write_mask;
	const char* mask_file;
	int fpga_threshold;
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
	TopMetalFPGASettings  & GetTopMetalFPGASettings() { return fpgaSettings; };
	std::string GetOutputFilename() { return outputFilename; };
	int GetWaveformDownsamplingRate() { return waveformDownsample; };
	int GetNumberFramesInReferenceImage() { return numberFramesInReferenceImage; };
	
	// Setters
	// Most setters are controlled by the config file. CLI gives options for overriding some values
	void SetOutputFilename(std::string ofile) { this->outputFilename = ofile; };

private:

	// General
	TopMetalReadoutMode readOutMode;
	int numberFramesInReferenceImage;

	// Digitizer
	CaenDigitizerSettings digitizerSettings;

	// FPGA
	TopMetalFPGASettings fpgaSettings;

	// Output file
	std::string outputFilename;
	int waveformDownsample;
	std::string inputFilename;

};



#endif
