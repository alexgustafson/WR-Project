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
    int size = *count;
    samples = new float[size];
    float** dft = new float*[2];
        
    MPI_Status status;

    
    while(true)
    {
        
        MPI_Recv(samples, size, MPI_FLOAT, 0, msg_sampledata, mpiHandle->world, &status);
        
        performWindowing(samples, size);
        performDFT(samples, size, dft);
        
        MPI_Send(&dft[0][0],size/2, MPI_FLOAT, 0, msg_result_real, mpiHandle->world);
        //MPI_Send(&dft[1],size, MPI_FLOAT, 0, msg_result_img, mpiHandle->world);
        
        
    }
    
    
    for( int i = 0 ; i < size ; i++ ) {
        delete [] dft[i];
    }
    delete []dft;
    delete []samples;
    
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
        samples[i] = (a0 - a1 * cos(theta0 * i) + a2 * cos(theta1 * i) + a3 * cos(theta2 * i)) * samples[i];
    }

}

void Worker::performDFT(float *samples, int size, float** dft)
{
    long bin, k;
    double arg, sign = -1.0;
    
    dft[0] = new float[size/2];
    dft[1] = new float[size/2];
    
    for (bin = 0; bin <= size/2; bin++) {
        
        dft[0][bin] = 0.0;
        dft[1][bin] = 0.0;
        
        for(k = 0;k < size;k++)
        {
            arg = 2.0 * (float)bin*PI*(float)k / (float)size;
            dft[0][bin] += samples[k] * sign * sin(arg);
            dft[1][bin] += samples[k] * cos(arg);
            
        }
                
    }
}
