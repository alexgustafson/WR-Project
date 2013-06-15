//
//  MPIHandler.cpp
//  JuceTest
//
//  Created by Alexander Gustafson on 20.05.13.
//
//

#include "MPIHandler.h"

MPIHandler *MPIHandler::_singletonInstance = nullptr;

void MPIHandler::getBufferSize(int *buffersize)
{
    MPI_Recv(buffersize, 1, MPI_INT, 0, msg_bufferSize, world, NULL);
}

void MPIHandler::getShouldUseFFT(int *shouldUseFFT)
{
    MPI_Recv(shouldUseFFT, 1, MPI_INT, 0, msg_usefft, world, NULL);
}

void MPIHandler::sendSampleBuffer(void* buffer, int sliceSize, int destination)
{
    MPI_Send(buffer, sliceSize, MPI_FLOAT, destination , msg_sampledata, world);
}

void MPIHandler::sendResultData(void *buffer, int &count)
{
    MPI_Send(buffer, count, MPI_FLOAT, 0 , msg_resultdata, world);
}

void MPIHandler::getResultData(void* sampleBuffer, int &count, int fromWorkerNr)
{
    MPI_Recv(sampleBuffer, count, MPI_FLOAT, fromWorkerNr, msg_resultdata, world, NULL);
}

void MPIHandler::mpi_recFloatArray(void* sampleBuffer, int &count)
{
    MPI_Recv(sampleBuffer, count, MPI_FLOAT, 0, msg_sampledata, world, NULL);
    
}


void MPIHandler::readyToSendResult()
{
    std::string ready;
    ready = "ready";
    world.send(0, msg_resultdata, ready);
    
}



