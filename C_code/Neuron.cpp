//
//  Neuron.cpp
//  
//
//  Created by Chris Tufts on 9/9/12.
//
//

#include "Neuron.h"
#include <iostream>
#include <stdio.h>
using namespace std;

// Date constructor
Neuron::Neuron(int steps, double a_, double b_, double C_,double d_,double k, double vr_,double vt_,double vpeak_, double tau_ )
{
    SetParams(a_,b_,C_, d_, k,vr_, vt_, vpeak_,tau_);
    v = -65;
    v_old = v;
    u = 0;
    u_old = u;

    
    
}

// Date member function
void Neuron::SetParams(double a_, double b_, double C_,double d_, double k_,double vr_,double vt_,
                     double vpeak_,double tau_)
{
    a = a_; b = b_; C = C_;k = k_;
    d = d_; vr = vr_; vt = vt_;
    vpeak = vpeak_; tau = tau_;
}


void Neuron::calc_v(double I){
    v=v_old+(1.0/C)*tau * (k * (v_old-vr)*(v_old-vt) + I -u_old);
    
}

void   Neuron::calc_u(){
    
    u=u_old+ tau * a * (b * (v_old-vt) - u_old);
   

}
double* Neuron::get_v(){return &v;};
double* Neuron::get_u(){return &u;};
void Neuron::update(double I){
    calc_v(I);
    calc_u();
    double scaling_factor = 0.1;
    
    if (v>=(vpeak+ scaling_factor * u)) {
            v_old=vpeak;
            v=vr-(scaling_factor * u);
            u=u+d;
            cout << "spike fired"<<endl;
        }
    
    if (v_old<vr) {
        b = 20.0;
        
    }else b = 0.0;
    
    // pass value of v to v_old for next
    //iteration
    v_old = v;
    u_old = u;
    
}
