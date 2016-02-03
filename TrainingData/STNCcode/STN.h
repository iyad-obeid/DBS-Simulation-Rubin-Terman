/* 
 * File:   STN.h
 * Author: Chris
 *
 * Created on May 4, 2011, 11:54 AM
 */

#ifndef _STN_H
#define	_STN_H
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>
#include<fstream>
#include<iostream>
#include<vector>

class STN {
public:
    double t;
    std::vector<double> v;
    std::vector<double> time_vector;
    std::vector<double> synCurrent;
    void init(int,double);
    void update(int,double);
    double getISTN_GPe();
    double getISTN_GPi();

private:
//  gsl_odeiv_step            *s ;
//  gsl_odeiv_control         *c ;
//  gsl_odeiv_evolve          *e ;
    double ISTN_GPe;
    double ISTN_GPi;



  double h,t1;
  double *y;
  double *y_err;
  double *dydt_in;
  double *dydt_out;
  double val;
  int status;


};

#endif	/* _STN_H */

