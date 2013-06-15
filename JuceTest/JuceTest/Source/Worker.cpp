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
    
    int numOfProcessors = mpiHandle->getNumberOfProcesses();
    int *usefft = new int;
    
    if(numOfProcessors > 1)
    {
        
        int *count = new int;
        
        mpiHandle->getBufferSize(count);
        
        size = *count;
        float *samples = new float[size];
        float** dft = new float*[2];
        float* fftBuffer = new float[size*2];
        
        MPI_Status status;
        initializeDFTCoeffs();
        
        while(true)
        {
            
            MPI_Recv(samples, size, MPI_FLOAT, 0, msg_sampledata, mpiHandle->world, &status);
            performWindowing(samples, size);
            mpiHandle->getShouldUseFFT(usefft);
            
            if(*usefft > 0)
            {
                
                initializeFFTBufferArray(samples, fftBuffer, size);
                performFFT(fftBuffer, size, -1);
                deInterlace(fftBuffer, size*2);
                MPI_Send(&fftBuffer[0],size/2, MPI_FLOAT, 0, msg_result_real, mpiHandle->world);
                
                
            }else{
                
                performDFT(samples, size, dft);
                MPI_Send(&dft[0][0],size/2, MPI_FLOAT, 0, msg_result_real, mpiHandle->world);
                
            }
            
        }
        
        for( int i = 0 ; i < size ; i++ ) {
            delete [] dft[i];
        }
        delete []dft;
        delete []samples;
        delete []fftBuffer;
        
        
    }else
    {
        //testmode
        
        
        
        
        
        
    }
    
}

Worker::~Worker()
{
    
}

void Worker::performWindowing(float *samples, int size)
{
    // 4 Term Blackmann Harris
    // adapted from : http://stackoverflow.com/questions/10660218/blackman-harris-in-c
    
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
    //naive implementation
    
    long bin, k;
    
    dft[0] = new float[size/2];
    dft[1] = new float[size/2];
    
    for (bin = 0; bin <= size/2; bin++) {
        
        dft[0][bin] = 0.0;
        dft[1][bin] = 0.0;
        
        for(k = 0;k < size;k++)
        {
            dft[0][bin] += samples[k] * realCoefs[bin][k];
            dft[1][bin] += samples[k] * imgCoefs[bin][k];
            
            
        }
        dft[0][bin] = (dft[0][bin]*dft[0][bin]) + (dft[1][bin]*dft[1][bin]);
                
    }
}

/*float Worker::performFFT(float *data, unsigned long number_of_complex_samples, int isign)
{
    
    //adapted from http://www.codeproject.com/Articles/9388/How-to-implement-the-FFT-algorithm
    
    //variables for trigonometric recurrences
    unsigned long n,mmax,m,j,istep,i;
    double wtemp,wr,wpr,wpi,wi,theta,tempr,tempi;
    
    //the complex array is real+complex so the array
    //as a size n = 2* number of complex samples
    // real part is the data[index] and the complex part is the data[index+1]
    n=number_of_complex_samples * 2;
    
    //binary inversion (note that the indexes
    //start from 0 witch means that the
    //real part of the complex is on the even-indexes
    //and the complex part is on the odd-indexes
    j=0;
    for (i=0;i<n/2;i+=2) {
        if (j > i) {
            //swap the real part
            float temp = data[j];
            data[j] = data[i];
            data[i] = temp;
            //swap the complex part
            temp = samples[j+1];
            data[j+1] = data[i+1];
            data[i+1] = temp;
            // checks if the changes occurs in the first half
            // and use the mirrored effect on the second half
            if((j/2)<(n/4)){
                //swap the real part
                //SWAP(data[(n-(i+2))],data[(n-(j+2))]);
                temp = data[(n-(i+2))];
                data[(n-(i+2))] = data[(n-(j+2))];
                data[(n-(j+2))] = temp;
                //swap the complex part
                //SWAP(data[(n-(i+2))+1],data[(n-(j+2))+1]);
                temp = data[(n-(i+2))+1];
                data[(n-(i+2))+1] = data[(n-(j+2))+1];
                data[(n-(j+2))+1] = temp;
            }
        }
        m=n/2;
        while (m >= 2 && j >= m) {
            j -= m;
            m = m/2;
        }
        j += m;
    }
    
    //Danielson-Lanzcos routine
    mmax=2;
    //external loop
    while (n > mmax)
    {
        istep = mmax<<  1;
        theta=isign*(2*PI/mmax);
        wtemp=sin(0.5*theta);
        wpr = -2.0*wtemp*wtemp;
        wpi=sin(theta);
        wr=1.0;
        wi=0.0;
        //internal loops
        for (m=1;m<mmax;m+=2) {
            for (i= m;i<=n;i+=istep) {
                j=i+mmax;
                tempr=wr*data[j-1]-wi*data[j];
                tempi=wr*data[j]+wi*data[j-1];
                data[j-1]=data[i-1]-tempr;
                data[j]=data[i]-tempi;
                data[i-1] += tempr;
                data[i] += tempi;
            }
            wr=(wtemp=wr)*wpr-wi*wpi+wr;
            wi=wi*wpr+wtemp*wpi+wi;
        }
        mmax=istep;
    }
    
    
}*/

float Worker::performFFT(float *samples, unsigned long number_of_complex_samples, int isign)
{
    
    float wr, wi, arg, *p1, *p2, temp;
    float tr, ti, ur, ui, *p1r, *p1i, *p2r, *p2i;
    long i, bitm, j, le, le2, k, logN;
    logN = (long)(log(number_of_complex_samples)/log(2.)+.5);
	
    for (i = 2; i < 2*number_of_complex_samples-2; i += 2) {
        for (bitm = 2, j = 0; bitm < 2*number_of_complex_samples; bitm <<= 1) {
            if (i & bitm) j++;
            j <<= 1;
		}
		if (i < j) {
			p1 = samples+i; p2 = samples+j;
			temp = *p1; *(p1++) = *p2;
			*(p2++) = temp; temp = *p1;
			*p1 = *p2; *p2 = temp;
		}
	}
	
	for (k = 0, le = 2; k < logN; k++) {
		le <<= 1;
		le2 = le>>1;
		ur = 1.0;
		ui = 0.0;
		arg = M_PI / (le2>>1);
		wr = cos(arg);
		wi = isign*sin(arg);
		for (j = 0; j < le2; j += 2) {
			p1r = samples+j; p1i = p1r+1;
			p2r = p1r+le2; p2i = p2r+1;
			for (i = j; i < 2*number_of_complex_samples; i += le) {
				tr = *p2r * ur - *p2i * ui;
				ti = *p2r * ui + *p2i * ur;
				*p2r = *p1r - tr; *p2i = *p1i - ti;
				*p1r += tr; *p1i += ti;
				p1r += le; p1i += le;
				p2r += le; p2i += le;
			}
			tr = ur*wr - ui*wi;
			ui = ur*wi + ui*wr;
			ur = tr;
		}
	}
    
}


void Worker::initializeFFTBufferArray(float *samples, float *buffer, int sizeOfSampleBuffer)
{
    for (int i = 0; i < sizeOfSampleBuffer; i++) {
        
        buffer[2*i] = 0.0;
        buffer[(2*i)+1] = samples[i];
        
    }
}

void Worker::deInterlace(float *buffer, int sizeOfSampleBuffer)
{
    
    for (int i = 2; i < sizeOfSampleBuffer; i+=2) {
        
        buffer[i/2] = (buffer[i] * buffer[i]) + (buffer[i-1] * buffer[i-1]);
        //buffer[(i/2)-1] = buffer[i-1];
        
    }
}


void Worker::initializeDFTCoeffs()
{
    //create dft matrix
    double arg, sign = -1.0;
    
    realCoefs = new float*[size/2];
    imgCoefs = new float*[size/2];
    
    for(int i = 0; i <= size/2; i++)
    {
        realCoefs[i] = new float[size];
        imgCoefs[i] = new float[size];
        
        for(int j = 0; j < size; j++)
        {
            arg = 2.0 * (float)i*PI*(float)j / (float)size;
            realCoefs[i][j] = sign * sin(arg);
            imgCoefs[i][j] = cos(arg);
        }
    }
}
