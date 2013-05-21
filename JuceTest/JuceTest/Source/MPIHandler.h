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
    
    template<typename T>
    void mpi_synchronous_recieve(T & value)
    {
        myWorld.recv(-1, -1, value);
    };
    
    template<typename T> 
    void mpi_broadcast(T & value, int root)
    {
        boost::mpi::broadcast(myWorld, value, root);
    };
    
private:
    
    static MPIHandler* _singletonInstance;
    
    MPIHandler()
    {
        
    }
    
    boost::mpi::communicator myWorld;
    
};


#endif
