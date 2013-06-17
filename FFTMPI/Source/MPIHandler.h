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
#include <boost/serialization/vector.hpp>
#include <boost/serialization/complex.hpp>
#include <boost/mpi.hpp>
#include "JuceHeader.h"

enum MESSAGE_TAG {msg_sampledata, msg_resultdata, msg_bufferSize, msg_dataReady, msg_workerBusy, msg_workerReady, msg_broadcastData, msg_finished, msg_result_real, msg_result_img, msg_usefft };


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
    
    
    int getRank()
    {
        return world.rank();
    };
    
    void sendSampleBuffer(void* buffer, int sliceSize, int destination);
    
    template<typename T>
    void mpi_synchronous_recieve(T & value)
    {
        world.recv(0, 0, value);
    };
    
    void mpi_recFloatArray(void* sampleBuffer, int &count);
    
    template<typename T> 
    void mpi_broadcast(T & value, int root)
    {
        boost::mpi::broadcast(world, value, root);
    };
    
    template<typename T>
    void send(int dest, int tag, const T & value)
    {
        world.send(dest, tag, value);
    };
    
    int getNumberOfProcesses()
    {
        return world.size();
    }

    void getBufferSize(int *buffersize);
    void getShouldUseFFT(int *shouldUseFFT);
    void sendResultData(void* sampleBuffer, int &count);
    void isResultReady(int workerNr, std::string &ready);
    void readyToSendResult();
    void getResultData(void* sampleBuffer, int &count, int fromWorkerNr);
    
    
    boost::mpi::communicator world;
    
    
    
private:
    
    static MPIHandler* _singletonInstance;
    
    MPIHandler()
    {
        
    }
    
    
    
};


#endif
