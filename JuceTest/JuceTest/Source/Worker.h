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
    

    
    
private:
    
    int myRank;
    int numOfSamples;
    
    
};



#endif  // __WORKER_H_120D1F57__
