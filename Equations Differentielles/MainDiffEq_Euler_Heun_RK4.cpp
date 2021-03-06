#include <stdlib.h>
#include <iostream>
using namespace std;
#include <vector>
#include <math.h>
#include <iomanip>

int main(void)
{
  //  ===== initialisation =====
  
  // functions
  double f (double, double);
  double fExact (double, double, double);
  double deltaEuler (double, double);
  double deltaHeun (double, double);
  double deltaRK (double, double);
  double yNext (double, double, double, double);

  // number of points
  int n = 10;			

  // step of x
  double h = 0.1;
  
  // initial conditions
  double x0=0, y0=0;
  
  // intermediate variables
  double yBarre, k1, k2, k3, k4;
  
  // vector definition
  vector<double> x, yExact, yEuler, yHeun, yRK, yEulerDelta, yHeunDelta, yRKDelta;
  
  // vector initialisation
  x.push_back (x0);
  yHeun.push_back (y0);
  yExact.push_back (0);
  yEuler.push_back (0);
  yRK.push_back(y0);
  yHeunDelta.push_back (0);
  yEulerDelta.push_back (0);
  yRKDelta.push_back (0);
  
  

  // ===== calculations =====
  
  // main loop
  for (int i = 1; i <= n; i++)
    {
      // x values
      x.push_back (x[i - 1] + h);
      
      // exact solution
      yExact.push_back(fExact(x[i], x0, y0)); // important to place after x.push_back, if before, argument of x needs to be i+1 (untested)
      
      // old school euler
      yEuler.push_back (yEuler[i - 1] + h * f (x[i - 1], yEuler[i - 1])); 
      
      // rock'n roll euler
      yBarre = yHeun[i-1]+h*f(x[i - 1], yHeun[i - 1]);
      yHeun.push_back (yHeun[i-1]+h*0.5*(f(x[i - 1], yHeun[i - 1]) + f( x[i], yBarre)));
      
      // runge-kutta
      k1 = f(x[i-1], yRK[i-1]);
      k2 = f(x[i-1]+0.5*h, yRK[i-1]+0.5*h*k1);
      k3 = f(x[i-1]+0.5*h, yRK[i-1]+0.5*h*k2);
      k4 = f(x[i-1]+h, yRK[i-1]+h*k3);
      
      yRK.push_back (yRK[i-1]+(h/6)*(k1+2*k2+2*k3+k4));
      
      // relative difference
      yHeunDelta.push_back (deltaHeun (yHeun[i], yExact[i]));
      yEulerDelta.push_back (deltaEuler (yEuler[i], yExact[i]));
      yRKDelta.push_back (deltaRK (yRK[i], yExact[i]));
      
      // debug
      cout << fixed << setprecision(9) << "\t" <<  "yExact = " << yExact[i] << "\t" << "yEuler = " << yEuler[i] << "\t" << "yHeun = " << yHeun[i] << "\t" << "yHeunDelta = " << yHeunDelta[i] << "\t" << "yEulerDelta = " << yEulerDelta[i] << "\t" << "yRK=" << yRK[i] << "\t" << "yRKDelta = " << yRKDelta[i] <<"\n";
    }
}

// ===== functions =====

#include<math.h>
double deltaRK(double yRK, double yExact)
{
  double resultat;
  resultat = abs (((yRK - yExact) / yExact) * 100);
  return (resultat);
}

#include<math.h>
double deltaEuler(double yEuler, double yExact)
{
  double resultat;
  resultat = abs (((yEuler - yExact) / yExact) * 100);
  return (resultat);
}

#include<math.h>
double deltaHeun(double yHeun, double yExact)
{
  double resultat;
  resultat = abs (((yHeun - yExact) / yExact) * 100);
  return (resultat);
}

#include <math.h>
double fExact(double x, double x0, double y0)
{
  double resultat;
  resultat = -x-1+(1+x0+y0)*exp(x-x0);
  return (resultat);
}

double f (double x, double y)
{
  double resultat;
  resultat = x + y;
  return (resultat);
}