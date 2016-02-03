/*
 * File:   GPi.h
 * Author: Chris
 *
 * Created on April 29, 2011, 1:24 PM
 */


#ifndef _GPI_H
#define	_GPI_H
#define nEqs 6
#include "Neuron.h"
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>
#include<fstream>
#include<iostream>
#include<vector>



class GPi: public Neuron {
public:

    void init(int,double,double,int num);
    
    void update();
    double getIGPi_TC();
    double getVoltage();
    void close_files();
    void set_synapse();
private:
    double _aInf(double);
    gsl_odeiv_step            *s ;
    gsl_odeiv_control         *c ;
    gsl_odeiv_evolve          *e ;
    gsl_odeiv_system         sys;
    double* currents;
    std::ofstream file_volt;
    std::ofstream file_time;
    double temp_syn_g;
    double temp_syn;
};

#endif	/* _GPI_H */
