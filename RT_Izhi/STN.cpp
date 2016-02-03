/*
 * File:   STN.cpp
 * Author: Chris
 *
 * Created on May 4, 2011, 11:54 AM
 */

#include "STN.h"
#include "Neuron.h"
#include<string.h>
#include <gsl/gsl_rng.h>
#include <stdio.h>
#include<iostream>
#include<cmath>
#include<fstream>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>
#include <vector>
#define nEqs 7
using namespace std;



///values for synaptic calculations
#define gl  2.25
#define eL  -60.0//vl//
#define gNa  37.5
#define eNa  55.0//
#define gK  45.0
#define eK  -80.0//
#define gT  0.50
#define eCa  140.0
#define gCa  0.5
#define tau1H  500.00//msec
#define tau1N  100.00//msec
#define tau1R  17.5//msec
#define tau0H  1.0
#define tau0N  1.0
#define tau0R  7.1//7.1 IN MODEL//40 in paper
#define phiH  0.75
#define phiN  0.75
#define phiR  0.5//0.5 IN MODEL//0.2 paper
#define kl 15.0
#define kCa  22.5
#define thetaM  -30.0//
#define thetaH  -39.0
#define thetaN  -32.0
#define thetaR  -67.0
#define thetaA  -63.0
#define thetaB  0.25//was 0.4//model states 0.25
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
#define roB  -0.07//was -0.1-model states -0.07
#define roS  8.0
#define roTauH  -3.0
#define roTauN  -26.0
#define roTauR  -2.2
#define roTauHG  8.0
#define g_GPe_STN  0.9
#define e_GPe_STN  -100.00

#define A_STN  5.0////////////same
#define B_STN  1.00//////////////same
#define theta_STN  30.0//spec is 30////////////0
#define theta_STN_GPi  30.0//spec is 30////////////
#define A_STN_GPi  1.0/////////////same
#define B_STN_GPi  0.05///////////same
#define Iapp  25.0//
#define epsilon  5e-5////5E-05 IN MODEL//3.75e-5 paper
#define gAHP  9.0
#define max_size 5000


  static double _ainf(double);
  static double _binf(double);
  static double _ninf(double);
  static double _sinf(double);
  static double _rinf(double);
  static double _minf(double);
  static double _hinf(double);
  static double _tauN(double);
  static double _tauH(double);
  static double _tauR(double);
  static double _Il(double);
  static double _It(double,double,double);
  static double _IAHP(double,double);
  static double _Ina(double,double,double);
  static double _Ik(double, double);
  static double _Ica(double, double);
  static double get_IDBS(double );
 int  funcSTN (double t, const double y[], double f[], void *params)
{
    double tauN,tauH,tauR,aInf,mInf,sInf,hInf,rInf,nInf,bInf;
    double Il,Ik,Ina,It,Ica,IAHP,I_GPi_STN,Idbs;
    //calculate  static terms
    #ifdef DBS
        Idbs = get_IDBS(t);
    #else
        Idbs = 0;
    #endif
    #ifdef NO_SYNAPSE
      I_GPi_STN = 0;
    #else
      I_GPi_STN = *(double *)params;
    #endif
    tauN = _tauN(y[0]);
    tauH = _tauH(y[0]);
    aInf = _ainf(y[0]);
    mInf = _minf(y[0]);
    sInf = _sinf(y[0]);
    hInf = _hinf(y[0]);
    rInf = _rinf(y[0]);
    nInf = _ninf(y[0]);
    tauR = _tauR(y[0]);
    bInf = _binf(y[3]);

    /*
Y[0] = dv/dt
Y[1] = dn/dt
Y[2]=dh/dt
Y[3]=dr/dt
Y[4]=dca/dt
*/
    It   = _It(y[0],bInf,aInf);
    Il = _Il(y[0]);
    Ina = _Ina(y[0],y[2],mInf);
    Ik = _Ik(y[0],y[1]);
    Ica = _Ica(y[0],sInf);
    IAHP = _IAHP(y[0],y[4]);

  //voltage
    f[0] = -Il-Ik-Ina-It-Ica-IAHP-I_GPi_STN+Iapp+Idbs;
  // n
    f[1] = phiN*((nInf -y[1])/tauN);
  // h
    f[2] = phiH*((hInf - y[2])/tauH);
  // r
    f[3] = phiR*((rInf -y[3])/tauR);
  //ca
    f[4] = epsilon*(-Ica-It-kCa*y[4]);

    f[5]= A_STN*(1-y[5])*(1/(1+ exp(-(y[0]-theta_STN-thetaS)/roS)))-B_STN*y[5];
    f[6]= A_STN_GPi*(1-y[6])*(1/(1+ exp(-(y[0]-theta_STN-thetaS)/roS)))-B_STN_GPi*y[6];


 return GSL_SUCCESS;
}

void STN::init(int opt,double sim_length,double abs_error,int num){
  const char* _type="STN";
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
      sprintf(fname,"/Users/Chris/Dropbox/Program_IO/PD_RK/testFile_%c_STN_gsl%03i.bin",mode,num );
      file_volt.open(fname);
      sprintf(fname,"/Users/Chris/Dropbox/Program_IO/PD_RK/testFileTimes_%c_STN_gsl%03i.bin",mode,num );
      file_time.open(fname);
  #else
      if(num==0){
          sprintf(fname,"/Users/Chris/Dropbox/Program_IO/PD_RK/testFile_%c_STN_gsl%03i.bin",mode,num );
          file_volt.open(fname);
          sprintf(fname,"/Users/Chris/Dropbox/Program_IO/PD_RK/testFileTimes_%c_STN_gsl%03i.bin",mode,num );
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
  t  = 0.0;
  t1 = sim_length;
  h  = 0.001;
  y  = new double[nEqs];
  y[0] = -60.0 +  (gsl_rng_uniform (r))*10;
  gsl_rng_free (r);
  y[1] = _ninf(y[0]);
  y[2] = _hinf(y[0]);
  y[3] = _rinf(y[0]);
  y[4] = (_Ica(y[0],_sinf(y[0]))+_It(y[0],_binf(y[3]),_ainf(y[0])))/-kCa;
  y[5] = 0.5;
  y[6] = 0.5;
  y_err = new double[nEqs];
  dydt_in = new double[nEqs];
  dydt_out = new double[nEqs];
  v_array = new double[max_size];
  t_array = new double[max_size];
  current = 0;
  s_dat.s_curr=y[5];
  s_dat.s_old = y[5];
  s_dat.t_curr=0;
  s_dat.t_old=0;
  s_dat_G.s_curr=y[6];
  s_dat_G.s_old = y[6];
  s_dat_G.t_curr=0;
  s_dat_G.t_old=0;

  const gsl_odeiv_step_type *T;
  if      (opt==0) T = gsl_odeiv_step_rk4;
  else if (opt==1) T = gsl_odeiv_step_rkf45;
  else if (opt==2) T = gsl_odeiv_step_bsimp;

 s = gsl_odeiv_step_alloc (T, nEqs);
 c = gsl_odeiv_control_standard_new(abs_error,0,0,0);
 e = gsl_odeiv_evolve_alloc (nEqs);
 sys.function = funcSTN;
  sys.jacobian = NULL;
  sys.dimension = nEqs;
  sys.params = &current;


}

void STN:: update(){
  s_dat.s_old = y[5];
  s_dat.t_old=t;
  s_dat_G.s_old = y[6];
  s_dat_G.t_old=t;


  temp_syn_g=0;
    for(int i = 0; i<presynaptics.size();i++){
        if(strcmp(presynaptics[i]->get_type(),"GPe")==0)
            temp_syn_g+=interpolate(presynaptics[i]->get_s(),t);
    }
  current = g_GPe_STN*(y[0]-e_GPe_STN)*temp_syn_g;
  
  if (OPT==0)
      {
      status = gsl_odeiv_step_apply (s, t, h, y, y_err, dydt_in, dydt_out, &sys);
  }
      else if ((OPT==1) | (OPT==2))
      {
      status = gsl_odeiv_evolve_apply (e, c, s, &sys, &t, t1, &h, y);
}
      if (status != GSL_SUCCESS) return;
      dydt_in[0] = dydt_out[0];
      dydt_in[1] = dydt_out[1];
      dydt_in[2] = dydt_out[2];
      dydt_in[3] = dydt_out[3];
      dydt_in[4] = dydt_out[4];
      dydt_in[5] = dydt_out[5];
      dydt_in[6] = dydt_out[6];

      if(OPT==0)
      t += h;

      s_dat.s_curr=y[5];
      s_dat.t_curr=t;
      s_dat_G.s_curr=y[6];
      s_dat_G.t_curr=t;


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



double STN::getVoltage(){
    return y[0];
}
void STN::close_files(){
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
static double _binf(double r){
    return (1/(1+ exp((r-thetaB)/roB))) - (1/(1+exp(-thetaB/roB)));
//rnew(r)=1/(1+exp((r-rth)/rsig))-1/(1+exp(-rth/rsig))

}
static double _tauN(double v){
    return tau0N+tau1N/(1+exp(-(v-thetaTauN)/roTauN));
}
static double _tauH(double v){
    return tau0H+tau1H/(1+exp(-(v-thetaTauH)/roTauH));
}
static double _tauR(double v){
    return tau0R+tau1R/(1+exp(-(v-thetaTauR)/roTauR));
}
static double _Il(double v){
    return gl*(v-eL);
}
static double _It(double v,double bInf,double aInf){
//    return gT*pow(aInf,3.0)*r*(v-eCa);
    return gT*pow(aInf,3)*bInf*bInf*(v-eCa);
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

//dbs(t)=i1*hv(sin(6.2831853*t/pdbs))*(1-hv(sin(6.2831853*(t+ddbs)/pdbs)))
//hv(v)=1./(1.+exp(-v/.001))
static double get_IDBS(double t){
    double amplitude = 200;
    double period = 6.0;//ms
    double duration = 0.6;//ms
    double term1,term2;
    term1 = (sin(6.2831853*t/period));
    term2 = (sin(6.2831853*(t+duration)/period));
    term1 = 1/(1+exp(-term1/0.001));
    term2 = 1-1/(1+exp(-term2/0.001));
    return amplitude*term1*term2;

}
