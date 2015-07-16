#include "daubechies.h"

Daubechies::Daubechies()
{
    const double sqrt_3 = sqrt( 3 );
          const double denom = 4 * sqrt( 2 );

          //
          // forward transform scaling (smoothing) coefficients
          //
          h0 = (1 + sqrt_3)/denom;
          h1 = (3 + sqrt_3)/denom;
          h2 = (3 - sqrt_3)/denom;
          h3 = (1 - sqrt_3)/denom;
          //
          // forward transform wavelet coefficients
          //
          g0 =  h3;
          g1 = -h2;
          g2 =  h1;
          g3 = -h0;

          Ih0 = h2;
          Ih1 = g2;  // h1
          Ih2 = h0;
          Ih3 = g0;  // h3

          Ig0 = h3;
          Ig1 = g3;  // -h0
          Ig2 = h1;
          Ig3 = g1;  // -h2
}
void Daubechies::transform( double* a,double *al,double *ar, const int n )
{
   if (n >= 4) {
      int i, j;
      const int half = n >> 1;


      for (i = 0, j = 0; j < n-3; j += 2, i++) {
         al[i]      = a[j]*h0 + a[j+1]*h1 + a[j+2]*h2 + a[j+3]*h3;
         ar[i] = a[j]*g0 + a[j+1]*g1 + a[j+2]*g2 + a[j+3]*g3;
      }

      al[i]      = a[n-2]*h0 + a[n-1]*h1 + a[0]*h2 + a[1]*h3;
      ar[i] = a[n-2]*g0 + a[n-1]*g1 + a[0]*g2 + a[1]*g3;


   }
}
void Daubechies::invTransform2d(double* a,double *aul,double *aur,double *adl,double *adr, const int n, int const m){
    int sizeTlTr=n;
    if(m>n) sizeTlTr=m;

    double *tl=new double[sizeTlTr];
    double *tr=new double[sizeTlTr];
    double *taHoriz= new double[n*2];
    double *taVert= new double[m*2];
    double *tup= new double[m*n*2];
    double *tdown= new double[m*n*2];
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            tl[j]=aul[i*n+j];
            tr[j]=aur[i*n+j];
        }
        invTransform(taHoriz,tl,tr,n);
        for(int j=0;j<(2*n);j++){
            tup[i*(2*n)+j]=taHoriz[j];
        }

        for(int j=0;j<n;j++){
            tl[j]=adl[i*n+j];
            tr[j]=adr[i*n+j];
        }
        invTransform(taHoriz,tl,tr,n);
        for(int j=0;j<(2*n);j++){
            tdown[i*(2*n)+j]=taHoriz[j];
        }
    }
    for(int j=0;j<(n*2);j++){
         for(int i=0;i<m;i++){
             tl[i]=tup[i*n+j];
             tr[i]=tdown[i*n+j];
         }
         invTransform(taVert,tl,tr,m);
         for(int i=0;i<m;i++){
             a[i*(n*2)+j]=taVert[i];
         }
    }
    delete tl;
    delete tr;
    delete taHoriz;
    delete taVert;
    delete tup;
    delete tdown;
}
void Daubechies::invTransform( double* a,double *al,double *ar, const int n1 )
{
  if ((n1*2) >= 4) {
    int i, j;
    int n=n1*2;
    const int half = n >> 1;
    const int halfPls1 = half + 1;

    double* tmp = new double[n];
    for(int i=0;i<n1;i++){
        tmp[i]=al[i];
        tmp[i+half]=ar[i];
    }

    //      last smooth val  last coef.  first smooth  first coef
    a[0] = tmp[half-1]*Ih0 + tmp[n-1]*Ih1 + tmp[0]*Ih2 + tmp[half]*Ih3;
    a[1] = tmp[half-1]*Ig0 + tmp[n-1]*Ig1 + tmp[0]*Ig2 + tmp[half]*Ig3;
    for (i = 0, j = 2; i < half-1; i++) {
       //smooth val     coef. val       smooth val    coef. val
       a[j++] = tmp[i]*Ih0 + tmp[i+half]*Ih1 + tmp[i+1]*Ih2 + tmp[i+halfPls1]*Ih3;
       a[j++] = tmp[i]*Ig0 + tmp[i+half]*Ig1 + tmp[i+1]*Ig2 + tmp[i+halfPls1]*Ig3;
    }
    delete [] tmp;
  }
}


