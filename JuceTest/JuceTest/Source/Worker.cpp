/*
  ==============================================================================

    Worker.cpp
    Created: 4 Jun 2013 3:09:27pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#include "Worker.h"

Worker::Worker()
{
    

    MPIHandler* mpiHandle = MPIHandler::getInstance();
    
    int count = 1024;
    float *samples = new float[count];
    //std::cout << "I'm a worker, rank=" << mpiHandle->getRank();
    //int instruction;
    
    while(true)
    {
        
        //mpiHandle->waitingForInstruction();
                
        mpiHandle->mpi_recFloatArray(samples, count);
        
        for(int i = 0; i < count; i++)
        {
            
        }
        
        std::cout << "got data, rank=" << mpiHandle->getRank();
        
    }
    
    delete []samples;
}

Worker::~Worker()
{
    
}


