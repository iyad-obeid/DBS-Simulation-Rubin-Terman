/*
 * File:   STN.h
 * Author: Chris
 *
 * Created on May 4, 2011, 11:54 AM
 */

#ifndef _STN_H
#define	_STN_H
#include "Neuron.h"
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>
#include <gsl/gsl_rng.h>
#include <stdio.h>
#include<fstream>
#include<iostream>
#include<vector>



class STN: public Neuron{
public:
  void init(int,double,double,int);
  void close_files();
  void update();

  double getVoltage();
private:
  gsl_odeiv_step            *s ;
  gsl_odeiv_control         *c ;
  gsl_odeiv_evolve          *e ;
  gsl_odeiv_system         sys;
  double current;
  std::ofstream file_volt;
  std::ofstream file_time;
  double temp_syn_g;
  
};

#endif	/* _STN_H */

