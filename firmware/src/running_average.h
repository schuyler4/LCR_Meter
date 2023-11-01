//
//  FILENAME: running_average.h
// 
// description: Header file for running_average.c
//
// Written by Marek Newton
//

#ifndef RUNNING_AVERAGE
#define RUNNING_AVERAGE

#include <stdint.h>

#define MAX_FILTER_LENGTH 30

// struct used to implement a running average filter
typedef struct running_average_filter
{
    // the length of the samples that are averaged
    uint16_t length;
    // an array of all the data the filter is averaging
    uint16_t data[MAX_FILTER_LENGTH];
    // the current position of the filter
    uint16_t data_length;
    // set to the next sample before calling the sample function
    uint16_t sample;
} Running_Average_Filter;

// used to add a sample to the filter
// returns the most recent running average
int running_average_filter_sample(Running_Average_Filter *filter);

#endif