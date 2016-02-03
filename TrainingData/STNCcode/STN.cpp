/* 
 * File:   STN.cpp
 * Author: Chris
 * 
 * Created on May 4, 2011, 11:54 AM
 */

#include "STN.h"
#include<iostream>
#include<cmath>
#include<fstream>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>
#include <vector>
#define nEqs 7
using namespace std;

#define gl  2.25
#define eL  -60.0//vl
#define gNa  37.5
#define eNa  55.0
#define gK  45.0
#define eK  -80.0
#define gT  0.50
#define eCa  140.0
#define gCa  0.5
#define tau1H  500.00//msec
#define tau1N  100.00//msec
#define tau1R  17.5//msec
#define tau0H  1.0
#define tau0N  1.0
#define tau0R  40.0
#define phiH  0.75
#define phiN  0.75
#define phiR  0.2
#define kl 15.0
#define kCa  22.5
#define thetaM  -30.0
#define thetaH  -39.0
#define thetaN  -32.0
#define thetaR  -67.0
#define thetaA  -63.0
#define thetaB  0.4
#define thetaS  -39.0
#define thetaTauH  -57.0
#define thetaTauR  68.0
#define thetaTauN  -80.0
#define thetaHG  -39.0
#define thetaG  30.0
#define roM  15.0
#define roH  -3.1
#define roN  8.0
#define roR  -2.0
#define roA  7.8
#define roB  -0.1
#define roS  8.0
#define roTauH  -3.0
#define roTauN  -26.0
#define roTauR  -2.2
#define roTauHG  8.0

     ///values for synaptic calculations
#define g_STN_GPe  0.30;
#define e_STN_GPe  0.0;
#define g_STN_GPi  0.30;
#define e_STN_GPi  0.0;
#define A_STN  5.0////////////same
#define B_STN  1.00//////////////same
#define theta_STN  0.0//spec is 30////////////
#define theta_STN_GPi  30.0//spec is 30////////////
#define A_STN_GPi  1.0/////////////same
#define B_STN_GPi  0.05///////////same
//#define Iapp  0//
#define epsilon  3.75e-5
#define gAHP  9.0

int  func (double t, const double y[], double f[], void *params)
{
    double tauN,tauH,tauR,aInf,mInf,sInf,hInf,rInf,nInf,bInf;
    double Il,Ik,Ina,It,Ica,IAHP,Iapp;
//    if(t>800&&t<1200)
//        Iapp = -30.0;
//    else
//        Iapp = 0;
    Iapp = 0.0;
    //calculate  static terms
    //double phi[2] = *(double *)params;
//    double phi[2];
//    phi[0] = *(double *)params;
//    phi[1] = *(double *)(params+sizeof(double));
    tauN = tau0N+tau1N/(1+exp(-(y[0]-thetaTauN)/roTauN));
    tauH = tau0H+tau1H/(1+exp(-(y[0]-thetaTauH)/roTauH));
    tauR = tau0R+tau1R/(1+exp(-(y[0]-thetaTauR)/roTauR));
    aInf = 1/(1+ exp(-(y[0]-thetaA)/roA));
    bInf = (1/(1+ exp((y[3]-thetaB)/roB))) - (1/(1+exp(-thetaB/roB)));
    mInf = 1/(1+ exp(-(y[0]-thetaM)/roM));
    sInf = 1/(1+ exp(-(y[0]-thetaS)/roS));
    hInf = 1/(1+ exp(-(y[0]-thetaH)/roH));
    rInf = 1/(1+ exp(-(y[0]-thetaR)/roR));
    nInf = 1/(1+ exp(-(y[0]-thetaN)/roN));
/*
Y[0] = dv/dt
Y[1] = dn/dt
Y[2]=dh/dt
Y[3]=dr/dt
Y[4]=dca/dt
*/
    Il   = gl*(y[0]-eL);
    Ina  = gNa*pow(mInf,3)*y[2]*(y[0]-eNa);
    Ik   = gK*pow(y[1],4)*(y[0]-eK);
    Ica  = gCa*pow(sInf,2)*(y[0]-eCa);
    It   = gT*pow(aInf,3)*bInf*bInf*(y[0]-eCa);
    IAHP = gAHP*(y[0]-eK)*(y[4]/(y[4]+kl));


  //voltage
    f[0] = -Il-Ik-Ina-It-Ica-IAHP+Iapp;
  // n
    f[1] = phiN*((nInf -y[1])/tauN);
  // h
    f[2] = phiH*((hInf - y[2])/tauH);
  // r
    f[3] = phiR*((rInf -y[3])/tauR);
  //ca
    f[4] = epsilon*(-Ica-It-kCa*y[4]);
  //synaptic strengths
  //y[5]=syn;y[6]=syn_GPi
     if((y[0]-theta_STN) <0 ){
        f[5] =-(B_STN*y[5]);
        f[6] =-(B_STN_GPi*y[6]);
     }
    else{
        f[5] = A_STN*(1-y[5])-(B_STN*y[5]);
        f[6] = A_STN_GPi*(1-y[6])-(B_STN_GPi*y[6]);
    }
 return GSL_SUCCESS;
}

void STN::init(int opt,double sim_length){
//ofstream fid("//media//windowshare//NILprogramIO//data.bin", ios::out | ios::binary);


  t = 0.0;
  t1 = sim_length;
  h = 0.01;
  y = new double[nEqs];
  y[0] = -60.0;
  y[1] = 0.0;
  y[2] = 0.0;
  y[3] = 0.0;
  y[4] = 0.0;
  y[5] = 0.5;
  y[6] = 0.5;

  //double y[nEqs] = {-60.0,0,0,0,0};
  y_err = new double[nEqs];
  dydt_in = new double[nEqs];
  dydt_out = new double[nEqs];


  cout << dydt_in[0] << endl;
  cout << dydt_in[1] << endl;
  cout << dydt_in[2] << endl;
  cout << dydt_in[3] << endl;

}

void STN:: update(int opt,double abs_error){

  const gsl_odeiv_step_type *T;
  if      (opt==0) T = gsl_odeiv_step_rk4;
  else if (opt==1) T = gsl_odeiv_step_rkf45;
  else if (opt==2) T = gsl_odeiv_step_bsimp;

  gsl_odeiv_step            *s = gsl_odeiv_step_alloc (T, nEqs);
  gsl_odeiv_control         *c = gsl_odeiv_control_standard_new(abs_error,0,0,0);
  gsl_odeiv_evolve          *e = gsl_odeiv_evolve_alloc (nEqs);
  gsl_odeiv_system         sys = {func, NULL, nEqs, NULL};

  if (opt==0)
      {
      status = gsl_odeiv_step_apply (s, t, h, y, y_err, dydt_in, dydt_out, &sys);
  }
      else if ((opt==1) | (opt==2))
      {
      status = gsl_odeiv_evolve_apply (e, c, s, &sys, &t, t1, &h, y);
}
      if (status != GSL_SUCCESS) return;

  ISTN_GPi = y[0]-e_STN_GPi;
  ISTN_GPi *=y[6]*g_STN_GPi;
  ISTN_GPe = y[0]-e_STN_GPe;
  ISTN_GPe *= y[5]*g_STN_GPe;
//  synCurrent.push_back(ISTN_GPi);
    //////copy current values
    
//    if(t>800&&t<1200)
//        synCurrent.push_back(-30.0);
//    else
        synCurrent.push_back(0.0);
  



      dydt_in[0] = dydt_out[0];
      dydt_in[1] = dydt_out[1];
      dydt_in[2] = dydt_out[2];
      dydt_in[3] = dydt_out[3];
      dydt_in[4] = dydt_out[4];
      dydt_in[5] = dydt_out[5];
      dydt_in[6] = dydt_out[6];

      if(opt==0)
      t += h;

      val = y[0];
      v.push_back(val);
      time_vector.push_back(t);
      cout<<"time = "<<t<<endl;
      if(t>=t1)
  gsl_odeiv_step_free (s);


}

double STN::getISTN_GPe(){
     return ISTN_GPe;
}

double STN::getISTN_GPi(){
    return ISTN_GPi;
}