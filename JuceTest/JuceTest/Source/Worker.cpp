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
    
    MPI_Status status;
    int size = *count;
    double buffer2[size];
    
    while(true)
    {
        
        //mpiHandle->mpi_recFloatArray(samples, size);
        //mpiHandle->myWorld.recv(0, msg_sampledata, buffer);
        //mpiHandle->myWorld.recv(0, msg_sampledata, buffer, size);
        
        //mpiHandle->mpi_recFloatArray(buffer2, size);
        MPI_Recv(buffer2, size, MPI_DOUBLE, 0, msg_sampledata, mpiHandle->myWorld, &status);
        
        for(int i = 0; i < size; i++)
        {
            buffer[i] = samples[i];
        }
        
        //performWindowing(samples, size);
        std::cout << "count is " << size << std::endl;
        std::cout << "worker nr: " << mpiHandle->getRank() << " finished window " << std::endl;
        
        mpiHandle->readyToSendResult();
        
        std::cout << "worker nr: " << mpiHandle->getRank() << " signaled ready " << std::endl;
        
        if(mpiHandle->getRank() == 1)
        {
            for(int i = 0; i < size ;i++)
            {
                std::cout << "1 data: " << buffer2[i] << std::endl;
            }
           // mpiHandle->sendResultData(&buffer2[0], *count);
            
        }
        MPI_Send(&buffer2[0],size,MPI_DOUBLE,0,msg_resultdata,mpiHandle->myWorld);
        //mpiHandle->myWorld.send(0, msg_resultdata, buffer);
        //mpiHandle->sendResultData(&buffer2[0], *count);
        
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
