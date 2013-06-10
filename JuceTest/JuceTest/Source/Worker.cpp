/*
  ==============================================================================

    Worker.cpp
    Created: 4 Jun 2013 3:09:27pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#include "Worker.h"
#include <boost/mpi.hpp>
#include <boost/serialization/string.hpp>

#define PI 3.14159265359
#define PI_2  6.28318530718
#define PI_4 12.5663706144
#define PI_6 18.8495559215

Worker::Worker()
{
    

    MPIHandler* mpiHandle = MPIHandler::getInstance();
    int *count = new int;
    
    mpiHandle->getBufferSize(count);
    samples = new float[*count];
    std::vector<float> buffer(*count);
    
    
    
    while(true)
    {
        
        //mpiHandle->mpi_recFloatArray(samples, *count);
        
        
        //performWindowing(samples, *count);
        std::cout << "count is " << *count << std::endl;
        std::cout << "worker nr: " << mpiHandle->getRank() << " finished window " << std::endl;
        
        mpiHandle->readyToSendResult();
        
        std::cout << "worker nr: " << mpiHandle->getRank() << " signaled ready " << std::endl;
        
        if(mpiHandle->getRank() == 1)
        {
            for(int i = 0; i < *count;i++)
            {
                std::cout << "1 data: " << samples[i] << std::endl;
            }
        }
        
        mpiHandle->sendResultData(samples, *count);
        
        std::cout << "worker nr: " << mpiHandle->getRank() << " result sent " << std::endl;
        
        //delete []samples;
        
    }
    
    
}

Worker::~Worker()
{
    
}

void Worker::performWindowing(float *samples, int size)
{
    // 4 Term Blackmann Harris
    
    float a0 = 0.35875;
    float a1 = 0.48829;
    float a2 = 0.14128;
    float a3 = 0.01168;
    
    float theta0 = PI_2 / (float)(size -1);
    float theta1 = PI_4 / (float)(size -1);
    float theta2 = PI_6 / (float)(size -1);
    
    
    for(int i = 0;i < size; i++)
    {
        samples[i] = a0 - a1 * cos(theta0 * i) + a2 * cos(theta1 * i) + a3 * cos(theta2 * i);
    }
    
    
    
}
