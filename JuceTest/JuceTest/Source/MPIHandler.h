//
//  mpi_handler.h
//  JuceTest
//
//  Created by Alexander Gustafson on 20.05.13.
//
//

#ifndef JuceTest_MPIHandler_h
#define JuceTest_MPIHandler_h

#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi.hpp>
#include "JuceHeader.h"

enum MESSAGE_TAG {msg_sampledata, msg_resultdata, msg_bufferSize, msg_dataReady, msg_workerBusy, msg_workerReady, msg_broadcastData, msg_finished};


class MPIHandler
{
    
public:
    

    ~MPIHandler()
    {
        // this ensures that no dangling pointers are left when the
        // singleton is deleted.
    }
    
    
    
    static MPIHandler* getInstance()
    {
        if(_singletonInstance == nullptr)
        {
            _singletonInstance = new MPIHandler();
        }
        return _singletonInstance;
    };
    
    void initializeEnvironment(int argc, char* argv[])
    {
        
    };
    
    int getRank()
    {
        return myWorld.rank();
    };
    
    void sendSampleBuffer(float* buffer, int sliceSize, int destination)
    {
        MPI_Send(buffer, sliceSize, MPI_FLOAT, destination , msg_sampledata, myWorld);
    }
    
    template<typename T>
    void mpi_synchronous_recieve(T & value)
    {
        myWorld.recv(0, 0, value);
    };
    
    void mpi_recFloatArray(void* sampleBuffer, int &count)
    {
        MPI_Recv(sampleBuffer, count, MPI_FLOAT, 0, msg_sampledata, myWorld, NULL);
    }
    
    template<typename T> 
    void mpi_broadcast(T & value, int root)
    {
        boost::mpi::broadcast(myWorld, value, root);
    };
    
    template<typename T>
    void send(int dest, int tag, const T & value)
    {
        myWorld.send(dest, tag, value);
    };
    
    int getNumberOfProcesses()
    {
        return myWorld.size();
    }

    void getBufferSize(int *buffersize);
    void sendResultData(void* sampleBuffer, int &count);
    void isResultReady(int workerNr, std::string &ready);
    void readyToSendResult();
    boost::mpi::request igetResultData(void* sampleBuffer, int &count, int fromWorkerNr);
    void getResultData(void* sampleBuffer, int &count, int fromWorkerNr);
    
private:
    
    static MPIHandler* _singletonInstance;
    
    MPIHandler()
    {
        
    }
    
    boost::mpi::communicator myWorld;
    
};


#endif
