//
//  Neuron.h
//  
//
//  Created by Chris Tufts on 9/9/12.
//
//

#ifndef ____Neuron__
#define ____Neuron__

#include <iostream>
#include <stdio.h>
class Neuron{
private:
    double v,v_old;
    double u,u_old;
    double k,a,b,C,d,vr,vt,vpeak,tau;

    Neuron(){}
public:    
    
    
    Neuron(int steps, double a_, double b_, double C_,double d_,double k, double vr_,double vt_,double vpeak_, double tau_ );
    double* get_v();
    double* get_u();
    void   calc_v(double I);
    void   calc_u();
    void SetParams(double a_, double b_,
                   double C_, double d_,
                   double k_,
                   double vr_,double vt_,
                   double vpeak_,double tau_);
    void update(double I);
    
};
#endif /* defined(____Neuron__) */
