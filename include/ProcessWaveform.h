#ifndef ProcessWaveform_H
#define ProcessWaveform_H


// Includes
#include <stdint.h>

int FindTriggerLoc(uint16_t * data, uint16_t triggerThreshold, int n);

#endif