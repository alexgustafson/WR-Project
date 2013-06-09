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

void MPIHandler::sendResultData(void *sampleBuffer, int &count)
{
    MPI_Send(sampleBuffer, count, MPI_FLOAT, 0 , msg_resultdata, myWorld);
}

void MPIHandler::getResultData(void* sampleBuffer, int &count, int fromWorkerNr)
{
    MPI_Recv(sampleBuffer, count, MPI_FLOAT, fromWorkerNr, msg_resultdata, myWorld, NULL);
}

boost::mpi::request MPIHandler::igetResultData(void* sampleBuffer, int &count, int fromWorkerNr)
{
    return myWorld.irecv(fromWorkerNr, msg_resultdata, sampleBuffer);
}



void MPIHandler::readyToSendResult()
{
    std::string ready;
    ready = "ready";
    myWorld.send(0, msg_resultdata, ready);
    
}

