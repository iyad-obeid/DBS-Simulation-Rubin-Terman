/* 
 * File:   Neuron.h
 * Author: Chris
 *
 * Created on May 24, 2011, 12:01 PM
 */

#ifndef _NEURON_H
#define	_NEURON_H
#include <stdio.h>
#include<fstream>
#include<iostream>
#include<vector>


class Neuron {
public:
    struct syn_data{
        double s_curr;
        double s_old;
        double t_old;
        double t_curr;
    };
protected:
    syn_data s_dat;
    syn_data s_dat_G;
    std::vector<Neuron*>presynaptics ;
//    const char * type ;
    char type[50];
    int index;
    int count;
    double t;
    double *y;
    double *y_err;
    double *dydt_in;
    double *dydt_out;
    double* v_array;
    double* t_array;
    double h,t1;
    double val;
    int status;
    int OPT;
    
    void set_params(const char *_type,int);
    double interpolate(syn_data, double t_int);

public:
    syn_data get_s();
    syn_data get_s_G();
    const char* get_type ()const;
    int get_index()const;
    double getTime()const;
    virtual void update();
    virtual void close_files();
    void add_synapse(Neuron*);
};

#endif	/* _NEURON_H */

