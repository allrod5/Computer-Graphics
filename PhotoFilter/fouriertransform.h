#ifndef FOURIERTRANSFORM_H
#define FOURIERTRANSFORM_H

#include <complex>
#include <math.h>

class FourierTransform
{
private:
    /*
       This computes an in-place complex-to-complex FFT
       x and y are the real and imaginary arrays of 2^m points.
       dir =  1 gives forward transform
       dir = -1 gives reverse transform
    */
    static short fftLowLevel(short int dir,long m,double *x,double *y);

public:
    FourierTransform();
static  void fft(double *vetInR,double *vetInI,double *vetOutR,double *vetOutI, int size );
static  void ifft(double *vetInR,double *vetInI,double *vetOutR,double *vetOutI, int size );
static  void fftShift(double *vetInR,double *vetInI,double *vetOutR,double *vetOutI, int size );
static  void ifftShift(double *vetInR,double *vetInI,double *vetOutR,double *vetOutI, int size );
};


#endif // FOURIERTRANSFORM_H
