/*
 * File:   GPe.h
 * Author: Chris
 *
 * Created on April 29, 2011, 1:24 PM
 */


#ifndef _GPE_H
#define	_GPE_H
#include "Neuron.h"
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>
#include<fstream>
#include<iostream>
#include<vector>



class GPe: public Neuron {
public:

  void init(int,double,double,int);
  
  void update();
  double getIGPe_GPi();
  double getIGPe_STN();
  double getIGPe_GPe();
  double getVoltage();
  void   close_files();
private:
  gsl_odeiv_step            *s ;
  gsl_odeiv_control         *c ;
  gsl_odeiv_evolve          *e ;
  gsl_odeiv_system         sys;
  std::ofstream file_volt;
  std::ofstream file_time;
  double* currents;
   double temp_syn_g;
  double temp_syn_s;
};

#endif	/* _GPE_H */
