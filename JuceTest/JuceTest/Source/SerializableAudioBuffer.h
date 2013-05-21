/*
  ==============================================================================

    SerializableAudioBuffer.h
    Created: 21 May 2013 5:06:20pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#ifndef __SERIALIZABLEAUDIOBUFFER_H_1501DDF2__
#define __SERIALIZABLEAUDIOBUFFER_H_1501DDF2__

#include "JuceHeader.h"
#include <boost/serialization/serialization.hpp>

class SerializableAudioBuffer : public AudioSampleBuffer
{
public:
    
    SerializableAudioBuffer(	int 	numChannels, int 	numSamples )
    : AudioSampleBuffer(numChannels, numSamples) {}
    //~SerializableAudioBuffer();
    
private:
    
    friend class boost::serialization::access;
    
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        int64 i;
        for(i = 0; i < getNumSamples() ; ++i)
            ar & *getSampleData(0, i);
    }
    
    
  
};

#endif  // __SERIALIZABLEAUDIOBUFFER_H_1501DDF2__
