/*
 * File:   GPi.cpp
 * Author: Chris
 *
 * Created on April 29, 2011, 1:24 PM
 */


#include "GPi.h"
#include "Neuron.h"
#include<string.h>
#include<iostream>
#include<cmath>
#include<fstream>
#include<ctime>
#include <gsl/gsl_rng.h>
#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>
#include <vector>
#define nEqs 6
using namespace std;
     #define gl  0.1
     #define eL  -55.0
     #define gNa  120.0
     #define eNa  55.0
     #define gK  30.0
     #define eK  -80.0
     #define gT  0.50
     #define eCa  120.0
     #define gCa  0.10
     #define gAHP  30.0
     #define tau1H  0.27
     #define tau1N  0.27
     #define tauR  30.0
     #define tau0H  0.05
     #define tau0N  0.05
     #define phiH  0.05
     #define phiN  0.10
     #define phiR  1.0
     #define kl  30.0
     #define kCa  15.0
     #define thetaM  -37.0
     #define thetaH  -58.0
     #define thetaN  -50.0
     #define thetaR  -70.0
     #define thetaA  -57.0//thetasg
     #define thetaS  -35.0//thetas1g
     #define thetaTauH  -40.0//thhg
     #define thetaTauN  -40.0//thng
     #define roM  10.0//sigmamg
     #define roH  -12.0//sigmahg
     #define roN  14.0//sigmang
     #define roR  -2.0//krg
     #define roA  2.0//ksg
     #define roS  2.0//ks1g
     #define roTauH  -12.0// shg
     #define roTauN  -12.0// sng
     #define A_GPi  2.0
     #define B_GPi  0.08
     #define theta_GPi  20.0
     #define Iapp 5.0
     #define g_STN_GPi  0.50//0.5 in setnorm//0.3 in other model
     #define e_STN_GPi  0.0
     #define g_GPe_GPi  1.0//one model= 1.5//1.0 for setnorm
     #define e_GPe_GPi  -100.0
     #define epsilon  1.00e-4
     #define max_size 5000

  static double _ainf(double);
  static double _ninf(double);
  static double _sinf(double);
  static double _rinf(double);
  static double _minf(double);
  static double _hinf(double);
  static double _tauN(double);
  static double _tauH(double);
  static double _Il(double);
  static double _It(double,double,double);
  static double _IAHP(double,double);
  static double _Ina(double,double,double);
  static double _Ik(double, double);
  static double _Ica(double, double);

 int  funcGPi (double t, const double y[], double f[], void *params)
{
    double tauN,tauH,aInf,mInf,sInf,hInf,rInf,nInf;
    double Il,Ik,Ina,It,Ica,IAHP;
    double ISTN_GPi,I_GPe_GPi;
    double *temp = (double*)params;
    #ifdef NO_SYNAPSE	
	ISTN_GPi = 0;
	I_GPe_GPi = 0;
    #else
        ISTN_GPi = temp[0];
        I_GPe_GPi = temp[1];
   #endif
    tauN = _tauN(y[0]);
    tauH = _tauH(y[0]);
    aInf = _ainf(y[0]);
    mInf = _minf(y[0]);
    sInf = _sinf(y[0]);
    hInf = _hinf(y[0]);
    rInf = _rinf(y[0]);
    nInf = _ninf(y[0]);
/*
Y[0] = dv/dt
Y[1] = dn/dt
Y[2]=dh/dt
Y[3]=dr/dt
Y[4]=dca/dt
*/
    Il = _Il(y[0]);
    Ina = _Ina(y[0],y[2],mInf);
    Ik = _Ik(y[0],y[1]);
    Ica = _Ica(y[0],sInf);
    It = _It(y[0],y[3],aInf);
    IAHP = _IAHP(y[0],y[4]);

  //voltage
    f[0] = -Il-Ik-Ina-It-Ica-IAHP-ISTN_GPi-I_GPe_GPi+Iapp;
  // n
    f[1] = phiN*((nInf -y[1])/tauN);
  // h
    f[2] = phiH*((hInf - y[2])/tauH);
  // r
    f[3] = phiR*((rInf -y[3])/tauR);
  //ca
    f[4] = epsilon*(-Ica-It-kCa*y[4]);
  //synaptic strength
    f[5]= A_GPi*(1-y[5])*(1/(1+ exp(-(y[0]-theta_GPi-thetaA)/roA)))-B_GPi*y[5];




 return GSL_SUCCESS;
}

void GPi::init(int opt,double sim_length,double abs_error,int num){
  const char* _type="GPi";
  OPT = opt;
  set_params(_type,num);
  char fname [150];
 #ifdef PARKINSONS
      #define mode 'p'
  #endif
  #if defined  DBS
      #undef mode
      #define mode 'd'
  #endif
  #ifndef PARKINSONS
      #define mode 'n'
  #endif

#ifdef ALLDATA
    sprintf(fname,"/Users/Chris/Dropbox/Program_IO/PD_RK/testFile_%c_GPi_gsl%03i.bin",mode,num );
    file_volt.open(fname);
    sprintf(fname,"/Users/Chris/Dropbox/Program_IO/PD_RK/testFileTimes_%c_GPi_gsl%03i.bin",mode,num );
    file_time.open(fname);
#else
    if(num ==0){
        sprintf(fname,"/Users/Chris/Dropbox/Program_IO/PD_RK/testFile_%c_GPi_gsl%03i.bin",mode,num );
        file_volt.open(fname);
        sprintf(fname,"/Users/Chris/Dropbox/Program_IO/PD_RK/testFileTimes_%c_GPi_gsl%03i.bin",mode,num );
        file_time.open(fname);
    }
#endif
  count = 0;
  const gsl_rng_type * B;
  gsl_rng * r;
  gsl_rng_env_setup();
  B = gsl_rng_default;
  r = gsl_rng_alloc (B);
  gsl_rng_set(r,num);
  t = 0.0;
  t1 = sim_length;
  h = 0.001;
  y = new double[nEqs];
  y[0] = -60.0 +  (gsl_rng_uniform (r))*10;
  gsl_rng_free (r);
  y[1] = _ninf(y[0]);
  y[2] = _hinf(y[0]);
  y[3] = _rinf(y[0]);
  y[4] = (-_Ica(y[0],_sinf(y[0]))-_It(y[0],y[3],_ainf(y[0])))/kCa;
  y[5] = 0.5;
  y_err = new double[nEqs];
  dydt_in = new double[nEqs];
  dydt_out = new double[nEqs];
  currents = new double[2];
  currents[0] = 0;
  currents[1] = 0;
  v_array = new double[max_size];
  t_array = new double[max_size];
  s_dat.s_curr=0;
  s_dat.s_old = 0;
  s_dat.t_curr=0;
  s_dat.t_old=0;
  const gsl_odeiv_step_type *T;
  if      (opt==0) T = gsl_odeiv_step_rk4;
  else if (opt==1) T = gsl_odeiv_step_rkf45;
  else if (opt==2) T = gsl_odeiv_step_bsimp;

  s = gsl_odeiv_step_alloc (T, nEqs);
  c = gsl_odeiv_control_standard_new(abs_error,0,0,0);
  e = gsl_odeiv_evolve_alloc (nEqs);
  sys.function = funcGPi;
  sys.jacobian = NULL;
  sys.dimension = nEqs;
  sys.params = currents;



}

void GPi:: update(){

    temp_syn_g=0;
    temp_syn=0;
    for(int i = 0; i<presynaptics.size();i++){
        if(strcmp(presynaptics[i]->get_type(),"GPe")==0)
            temp_syn_g+=interpolate(presynaptics[i]->get_s_G(),t);
        else if(strcmp(presynaptics[i]->get_type(),"STN")==0)
            temp_syn+=interpolate(presynaptics[i]->get_s_G(),t);
    }
    currents[0]=g_GPe_GPi*(y[0]-e_GPe_GPi)*temp_syn_g;
    currents[1]=temp_syn*g_STN_GPi*(y[0]-e_STN_GPi);
    s_dat.s_old=y[5];
    s_dat.t_old=t;
  if (OPT==0)
      {
      status = gsl_odeiv_step_apply (s, t, h, y, y_err, dydt_in, dydt_out, &sys);
  }
      else if ((OPT==1) | (OPT==2))
      {
      status = gsl_odeiv_evolve_apply (e, c, s, &sys, &t, t1, &h, y);
  }
      if (status != GSL_SUCCESS) return;

  //calculate synaptic outputs
      dydt_in[0] = dydt_out[0];
      dydt_in[1] = dydt_out[1];
      dydt_in[2] = dydt_out[2];
      dydt_in[3] = dydt_out[3];
      dydt_in[4] = dydt_out[4];
      dydt_in[5] = dydt_out[5];

      if(OPT==0)
      t += h;

      s_dat.s_curr=y[5];
      s_dat.t_curr=t;
      val = y[0];
     if(count<max_size){
          v_array[count]=val;
          t_array[count] = t;
          count++;
      }else{
       #ifdef ALLDATA
              file_volt.write((char *)&v_array[0]  , sizeof(double)*max_size);
              file_time.write((char *)&t_array[0]  , sizeof(double)*max_size);
       #else
          if(index==0){
              file_volt.write((char *)&v_array[0]  , sizeof(double)*max_size);
              file_time.write((char *)&t_array[0]  , sizeof(double)*max_size);
          }
       #endif
          //reset counter
          //write new values to arrays
          count = 0;
          v_array[count]=val;
          t_array[count]=t;
          count++;
      }
}
double GPi::getIGPi_TC(){

    return y[5];
}

double GPi::getVoltage(){
    return y[0];
}

void GPi::close_files(){
 #ifdef ALLDATA
     file_volt.write((char *)&v_array[0]  , sizeof(double)*count);
     file_volt.close();
     file_time.write((char *)&t_array[0]  , sizeof(double)*count);
     file_time.close();
 #else
 if(index==0){
     file_volt.write((char *)&v_array[0]  , sizeof(double)*count);
     file_volt.close();
     file_time.write((char *)&t_array[0]  , sizeof(double)*count);
     file_time.close();
 }
 #endif
 delete[]y;
 delete[]dydt_in;
 delete[]dydt_out;
 delete[]v_array;
 delete[]t_array;
 delete[]y_err;
 gsl_odeiv_step_free (s);
 return;
}
static double _ainf(double v){
    return 1/(1+ exp(-(v-thetaA)/roA));
}
static double _minf(double v){
    return 1/(1+ exp(-(v-thetaM)/roM));
}
static double _sinf(double v){
    return 1/(1+ exp(-(v-thetaS)/roS));
}
static double _hinf(double v){
    return 1/(1+ exp(-(v-thetaH)/roH));
}
static double _rinf(double v){
    return 1/(1+ exp(-(v-thetaR)/roR));
}
static double _ninf(double v){
    return 1/(1+ exp(-(v-thetaN)/roN));
}
static double _tauN(double v){
    return tau0N+tau1N/(1+exp(-(v-thetaTauN)/roTauN));
}
static double _tauH(double v){
    return tau0H+tau1H/(1+exp(-(v-thetaTauH)/roTauH));
}
static double _Il(double v){
    return gl*(v-eL);
}
static double _It(double v,double r,double aInf){
    return gT*pow(aInf,3.0)*r*(v-eCa);
}
static double _Ina(double v, double h, double mInf){
    return gNa*pow(mInf,3)*h*(v-eNa);
}
static double _Ik(double v, double n){
    return gK*pow(n,4)*(v-eK);
}
static double _Ica(double v, double sInf){
    return gCa*pow(sInf,2)*(v-eCa);
}
static double _IAHP(double v, double ca){
    return gAHP*(v-eK)*(ca/(ca+kl));
}
