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
    MPI_Recv(buffersize, 1, MPI_INT, 0, msg_bufferSize, myWorld, NULL);
}

void MPIHandler::sendSampleBuffer(void* buffer, int sliceSize, int destination)
{
    MPI_Send(buffer, sliceSize, MPI_DOUBLE, destination , msg_sampledata, myWorld);
}

void MPIHandler::sendResultData(void *sampleBuffer, int &count)
{
    MPI_Send(sampleBuffer, count, MPI_DOUBLE, 0 , msg_resultdata, myWorld);
}

void MPIHandler::getResultData(void* sampleBuffer, int &count, int fromWorkerNr)
{
    MPI_Recv(sampleBuffer, count, MPI_DOUBLE, fromWorkerNr, msg_resultdata, myWorld, NULL);
}

void MPIHandler::mpi_recFloatArray(void* sampleBuffer, int &count)
{
    MPI_Recv(sampleBuffer, count, MPI_DOUBLE, 0, msg_sampledata, myWorld, NULL);
    
}


void MPIHandler::readyToSendResult()
{
    std::string ready;
    ready = "ready";
    myWorld.send(0, msg_resultdata, ready);
    
}



