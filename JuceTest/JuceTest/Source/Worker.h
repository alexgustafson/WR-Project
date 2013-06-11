/*
  ==============================================================================

    Worker.h
    Created: 4 Jun 2013 3:09:27pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#ifndef __WORKER_H_120D1F57__
#define __WORKER_H_120D1F57__

#include "JuceHeader.h"
#include "MPIHandler.h"

class Worker
{
public:
    
    Worker();
    ~Worker();
    
    void performWindowing(float* samples, int size);
    void performDFT(float* samples, int size, float** dft);
    void initializeDFTCoeffs();
    
    
private:
    
    int myRank;
    int numOfSamples;
    int size;
    float *samples;
    
    float** realCoefs;
    float** imgCoefs;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Worker)
    
};



#endif  // __WORKER_H_120D1F57__
