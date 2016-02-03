/*
 * File:   TC.h
 * Author: Chris
 *
 * Created on May 4, 2011, 12:56 PM
 */

#ifndef _TC_H
#define	_TC_H
#include "Neuron.h"
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>
#include<fstream>
#include<iostream>
#include<vector>

class TC: public Neuron {
public:

    void init(int,double,double,int);
    void update();
    double getVoltage();
    void close_files();
private:
    double calc_Ism();
    gsl_odeiv_step            *s ;
    gsl_odeiv_control         *c ;
    gsl_odeiv_evolve          *e ;
    gsl_odeiv_system         sys;
    double* currents;
    double* ism_array;
    std::ofstream file_volt;
    std::ofstream file_time;
    std::ofstream file_current;
    double Ism;
    double temp_syn_g;


};

#endif	/* _TC_H */

