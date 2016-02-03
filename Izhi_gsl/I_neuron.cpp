

////////////////////Izhikevich I_neuron///////////////////////////

#include <iostream>
#include<fstream>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <gsl/gsl_rng.h>
#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>
#include "I_neuron.h"
#define nEqs 6
using namespace std;





I_neuron::I_neuron (int opt,double sim_length,double abs_error,int num){
    num_steps = steps;
    OPT = opt;
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
    y[1] = 0.0;
    y_err = new double[nEqs];
    dydt_in = new double[nEqs];
    dydt_out = new double[nEqs];
    v_array = new double[max_size];
    t_array = new double[max_size];
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

I_neuron::~I_neuron () {
  /*
    for (int i = 0; i<num_steps; i++) {
        delete &v[i];
        delete &u[i];
    }
   */
}

void I_neuron::update (int step, double I){
 
 
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
    
    if(OPT==0)
        t += h;
}
/*
 void GPi::init(int opt,double sim_length,double abs_error,int num){
 OPT = opt;
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
 y[1] = 0.0;
 y_err = new double[nEqs];
 dydt_in = new double[nEqs];
 dydt_out = new double[nEqs];
 v_array = new double[max_size];
 t_array = new double[max_size];
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

 */
 int  funcI_update (double t, const double y[], double f[], void *params)
 {
 
 double tau = 0.1; double vt = -40;
 double k = 0.7;  double vr = -60.0;
 double C=1.0;
 double *temp = (double*)params;
 //Y[0] = dv/dt
 //Y[1] = du/dt
 double I = temp[0];
//voltage
f[0] = (k*(y[0]-vr)*(y[0]-vt)-y[1]+I)/C;
// u
f[1] = a*(b*(y[0]-vr)-y[1]);

return GSL_SUCCESS;
}

 


