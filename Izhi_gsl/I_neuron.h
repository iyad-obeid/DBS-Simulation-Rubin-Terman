#define nEqs 6
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>
#include<fstream>
#include<iostream>

class I_neuron {
    double a,b,c_param,d,threshold;
    //double tau,vr,vt,C,k;
    int num_steps;
    gsl_odeiv_step            *s ;
    gsl_odeiv_control         *c ;
    gsl_odeiv_evolve          *e ;
    gsl_odeiv_system         sys;
    std::ofstream file_volt;
    std::ofstream file_time;
public:
    double* v;double* u;
public:
    I_neuron (double,double,double,double,double,int);
    ~I_neuron ();
    void update(int, double);
};
