#ifndef DAUBECHIES_H
#define DAUBECHIES_H
#include<math.h>

class Daubechies
{
private:
    /** forward transform scaling coefficients */
      double h0, h1, h2, h3;
      /** forward transform wave coefficients */
      double g0, g1, g2, g3;

      double Ih0, Ih1, Ih2, Ih3;
      double Ig0, Ig1, Ig2, Ig3;
public:
    Daubechies();
    void invTransform(double* a,double *al,double *ar, const int n );
    void transform( double* a,double *al,double *ar, const int n );
    void transform2d(double* a,double *aul,double *aur,double *adl,double *adr, const int n, int const m);
    void invTransform2d(double* a,double *aul,double *aur,double *adl,double *adr, const int n, int const m);

};

#endif // DAUBECHIES_H
