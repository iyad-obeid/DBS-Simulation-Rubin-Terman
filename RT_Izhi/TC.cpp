/*
 * File:   TC.cpp
 * Author: Chris
 *
 * Created on May 4, 2011, 12:56 PM
 */

#include "TC.h"
#include "Neuron.h"
#include<iostream>
#include<cmath>
#include<fstream>
#include<string.h>
#include <gsl/gsl_rng.h>
#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>
#include <vector>
#define nEqs 3
using namespace std;

#define     gl   0.05//
#define     eL  -70.0//
#define     gNa  3.0//
#define     eNa  50.0//
#define     gK   5.0//
#define     eK  -90.0//
#define     gT   5.0//
#define     eT   0.0
#define     apt  0.3//1.0  in paper//0.3 setnorm
#define     qht  5.5//2.5 in paper//5.5 in set norm
#define g_GPi_TC  0.06//0.08for the one model//0.06 for setnorm
#define e_GPi_TC  -85.00
#define     max_size 5000

static double _m(double);
static double _p(double);
static double _hinf(double);
static double _aH(double);
static double _bH(double);
static double _tauR(double);
static double _rinf(double);
static double _tauH(double, double);
static double _Il(double);
static double _Ina(double , double , double );
static double _Ik(double , double );
static double _It(double, double, double);


 int funcTC (double t, const double y[], double f[], void *params)
{
    double aH,bH,tauH,tauR,p,m,hInf,rInf;
    double Il,Ik,Ina,It,I_SM,I_gi_th;
    double* temp = (double*)params;
        I_SM = temp[0];

    #ifdef NO_SYNAPSE
	I_gi_th = 0;
    #else
    	I_gi_th = temp[1];
    #endif
    m = _m(y[0]);
    p = _p(y[0]);
    hInf = _hinf(y[0]);
    aH   = _aH(y[0]);
    bH   = _bH(y[0]);
    tauH = _tauH(aH,bH);
    rInf = _rinf(y[0]);
    tauR = _tauR(y[0]);


 /*
 * Y[0] = dv/dt
   Y[1] = dr/dt
   Y[2]=dh/dt

*/
    Il = _Il(y[0]);
    Ina = _Ina(y[0],m,y[2]);
    Ik = _Ik(y[0],y[2]);
    It = _It(y[0],y[1],p);

  //voltage
    f[0] = -(Il+Ik+Ina+It+I_gi_th)+I_SM  ;
  // r
//    f[1] = 2.5*((rInf - y[1])/tauR);//
    f[1] = qht*((rInf - y[1])/tauR);//set norm
  // h
    f[2] =((hInf - y[2])/tauH);

 return GSL_SUCCESS;
}

void TC::init(int opt,double sim_length,double abs_error,int num){
  const char* _type="TC";
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
      sprintf(fname,"/Users/Chris/Dropbox/Program_IO/PD_RK/testFile_%c_TC_gsl%03i.bin",mode,num );
      file_volt.open(fname);
      sprintf(fname,"/Users/Chris/Dropbox/Program_IO/PD_RK/testFileTimes_%c_TC_gsl%03i.bin",mode,num );
      file_time.open(fname);
      sprintf(fname,"/Users/Chris/Dropbox/Program_IO/PD_RK/testFile_%c_TC_ism_gsl%03i.bin",mode,num );
      file_current.open(fname);
  #else
        if(num==0){
          sprintf(fname,"/Users/Chris/Dropbox/Program_IO/PD_RK/testFile_%c_TC_gsl%03i.bin",mode,num );
          file_volt.open(fname);
          sprintf(fname,"/Users/Chris/Dropbox/Program_IO/PD_RK/testFileTimes_%c_TC_gsl%03i.bin",mode,num );
          file_time.open(fname);
          sprintf(fname,"/Users/Chris/Dropbox/Program_IO/PD_RK/testFile_%c_TC_ism_gsl%03i.bin",mode,num );
          file_current.open(fname);
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
  y[1] = _rinf(y[0]);
  y[2] = _hinf(y[0]);

  y_err = new double[nEqs];
  dydt_in = new double[nEqs];
  dydt_out = new double[nEqs];
  currents = new double[2];
  currents[0]=0;
  currents[1]=0;
  ism_array = new double[max_size];
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

  sys.function = funcTC;
  sys.jacobian = NULL;
  sys.dimension = nEqs;
  sys.params = currents;
//  sys = {funcTC, NULL, nEqs, currents};




}

void TC:: update(){

  //calculate ISM
   Ism = calc_Ism();
   currents[0]=Ism;
   temp_syn_g=0;
   for(int i = 0; i<presynaptics.size();i++){
        if(strcmp(presynaptics[i]->get_type(),"GPi")==0)
            temp_syn_g+=interpolate(presynaptics[i]->get_s(),t);
    }
currents[1]=g_GPi_TC*(y[0]-e_GPi_TC)*temp_syn_g;
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

      if(OPT==0)
      t += h;
      val = y[0];
     if(count<max_size){
          v_array[count]=val;
          t_array[count] = t;
          ism_array[count]=Ism;
          count++;
      }else{
          #ifdef ALLDATA
              file_volt.write((char *)&v_array[0]  , sizeof(double)*max_size);
              file_time.write((char *)&t_array[0]  , sizeof(double)*max_size);
              file_current.write((char *)&ism_array[0]  , sizeof(double)*max_size);

          #else
          if(index==0){
              file_volt.write((char *)&v_array[0]  , sizeof(double)*max_size);
              file_time.write((char *)&t_array[0]  , sizeof(double)*max_size);
              file_current.write((char *)&ism_array[0]  , sizeof(double)*max_size);
          }
         #endif

          //reset counter
          //write new values to arrays


          count = 0;
          v_array[count]=val;
          t_array[count]=t;
          ism_array[count] = Ism;
          count++;
      }
}

double TC:: calc_Ism(){
 double hFunc1,hFunc2;
 double IsmVal = 5;//ismVal==5 for set norm//6 for other model
 double IsmPeriod = 50; //25 for the one set//50 for setnorm
 double IsmDuration = 5;
 double shi = -80.0;
 hFunc2 = sin(2*3.14159265*(t+shi+IsmDuration)/IsmPeriod);
 hFunc1 = sin(2*3.14159265*((t+shi)/IsmPeriod));
 return IsmVal*(1.0/(1.0+exp(-hFunc2/0.001)))*(1-(1/(1.0+exp(-hFunc1/.001))));
}

double TC::getVoltage(){
    return y[0];
}
void TC::close_files(){
#ifdef ALLDATA
     file_volt.write((char *)&v_array[0]  , sizeof(double)*count);
     file_volt.close();
     file_time.write((char *)&t_array[0]  , sizeof(double)*count);
     file_time.close();
     file_current.write((char *)&ism_array[0]  , sizeof(double)*count);
     file_current.close();
 #else
 if(index==0){
     file_volt.write((char *)&v_array[0]  , sizeof(double)*count);
     file_volt.close();
     file_time.write((char *)&t_array[0]  , sizeof(double)*count);
     file_time.close();
     file_current.write((char *)&ism_array[0]  , sizeof(double)*count);
     file_current.close();
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

static double _m(double v){
    return 1/(1+exp(-(v+37.0)/7.0));
}
static double _p(double v){
    return 1/(1+exp(-(v+60)/6.2));
}
static double _hinf(double v){
    return 1/(1+ exp((v+41.0)/4.0));
}
static double _aH(double v){
    return 0.128*exp(-(v+46.0)/18.0);
}
static double _bH(double v){
    return 4.0/(1+ exp(-(v+23.0)/5.0));
}
static double _tauR(double v){
    return 28+ apt*exp((v+25.0)/-10.5);
}
static double _rinf(double v){
    return 1/(1+exp((v+84.0)/4.0));
}
static double _tauH(double aH, double bH){
    return 1/(aH + bH);

}
static double _Il(double v){
    return gl*(v-eL);
}
static double _Ina(double v, double m, double h){
    return gNa*pow(m,3)*h*(v-eNa);;
}
static double _Ik(double v, double h){
    return gK*pow((0.75*(1-h)),4)*(v-eK);
}
static double _It(double v, double r, double p){
    return gT*pow(p,2)*r*(v-eT);
}
