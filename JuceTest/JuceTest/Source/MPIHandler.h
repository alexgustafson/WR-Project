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

class MPIHandler
{
    
public:
    
    enum MESSAGE_TAGS {msg_sampledata, msg_broadcast_data, msg_finished};

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
        //MPI_Bsend(buffer, sliceSize, MPI_FLOAT, destination , MPIHandler::MESSAGE_TAGS::msg_sampledata, myWorld);
        MPI_Send(buffer, sliceSize, MPI_FLOAT, destination , MPIHandler::MESSAGE_TAGS::msg_sampledata, myWorld);
    }
    
    template<typename T>
    void mpi_synchronous_recieve(T & value)
    {
        myWorld.recv(0, 0, value);
    };
    
    void mpi_oldschoolRevieveFloatArray(void* sampleBuffer, int &count)
    {
        std::cout << " worker got here " << getRank();
        MPI_Status *status;
        MPI_Recv(sampleBuffer, count, MPI_FLOAT, 0, MPIHandler::MESSAGE_TAGS::msg_sampledata, myWorld, NULL);
        std::cout << " and stuff received " << getRank();
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
    
private:
    
    static MPIHandler* _singletonInstance;
    
    MPIHandler()
    {
        
    }
    
    boost::mpi::communicator myWorld;
    
};


#endif
